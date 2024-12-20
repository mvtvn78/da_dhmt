#pragma once
#include <vector>
#include <map>
#include <GL/glut.h>
#include <GL/gl.h>
#include<iostream>
#include <FFType/ft2build.h> 
#include <algorithm>
#include FT_FREETYPE_H
class TextRenderer {
private:
    FT_Library ft;
    FT_Face face;
    struct Character {
        std::vector<unsigned char> bitmap;
        int width;
        int height;
        int bearingX;
        int bearingY;
        int advance;
    };
    std::map<wchar_t, Character> characters;

public:
    TextRenderer() {
        if (FT_Init_FreeType(&ft)) {
            throw std::runtime_error("Không thể khởi tạo FreeType");
        }
    }

    void loadFont(const char* fontPath, int fontSize) {
        if (FT_New_Face(ft, fontPath, 0, &face)) {
            throw std::runtime_error("Không thể load font");
        }

        // Đặt encoding là Unicode
        FT_Select_Charmap(face, FT_ENCODING_UNICODE);

        // Đặt kích thước font
        FT_Set_Pixel_Sizes(face, 0, fontSize);

        // Load tất cả ký tự tiếng Việt vào cache
        loadCharacterSet();
    }

private:
    void loadCharacterSet() {
        // Danh sách các ký tự tiếng Việt cần load
        const std::wstring vietnameseChars =
            L"abcdefghijklmnopqrstuvwxyz"
            L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            L"áàạảãâấầậẩẫăắằặẳẵ"
            L"ÁÀẠẢÃÂẤẦẬẨẪĂẮẰẶẲẴ"
            L"éèẹẻẽêếềệểễ"
            L"ÉÈẸẺẼÊẾỀỆỂỄ"
            L"óòọỏõôốồộổỗơớờợởỡ"
            L"ÓÒỌỎÕÔỐỒỘỔỖƠỚỜỢỞỠ"
            L"úùụủũưứừựửữ"
            L"ÚÙỤỦŨƯỨỪỰỬỮ"
            L"íìịỉĩ"
            L"ÍÌỊỈĨ"
            L"đĐýỳỵỷỹ"
            L"ÝỲỴỶỸ"
            L"0123456789"
            L" ,.!?-+*/=()[]{}";

        for (wchar_t c : vietnameseChars) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER | FT_LOAD_FORCE_AUTOHINT)) {
                continue;
            }

            // Lưu thông tin glyph vào cache
            Character character;
            FT_GlyphSlot glyph = face->glyph;

            character.width = glyph->bitmap.width;
            character.height = glyph->bitmap.rows;
            character.bearingX = glyph->bitmap_left;
            character.bearingY = glyph->bitmap_top;
            character.advance = glyph->advance.x >> 6;

            // Copy bitmap data
            size_t size = glyph->bitmap.width * glyph->bitmap.rows;
            character.bitmap.resize(size);
            std::copy(glyph->bitmap.buffer,
                glyph->bitmap.buffer + size,
                character.bitmap.begin());
            // Xử lý lật bitmap để hiển thị đúng
            for (unsigned int row = 0; row < glyph->bitmap.rows; row++) {
                for (unsigned int col = 0; col < glyph->bitmap.width; col++) {
                    character.bitmap[row * glyph->bitmap.width + col] = glyph->bitmap.buffer[row * glyph->bitmap.width +
                        (glyph->bitmap.width - 1 - col)];
                }
            }
            std::reverse(character.bitmap.begin(), character.bitmap.end());
            characters[c] = character;
        }
    }

public:
 
    void renderText(const std::wstring& text, GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
        // Bật blend để hỗ trợ alpha
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glPushMatrix();
        // Đặt màu với alpha
        glColor4f(r, g, b, a);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        float currentX = x;
        float currentY = y;

        FT_UInt previousIndex = 0;

        for (wchar_t c : text) {
            auto it = characters.find(c);
            if (it == characters.end()) continue;

            const Character& ch = it->second;

            // Áp dụng kerning
            FT_UInt currentIndex = FT_Get_Char_Index(face, c);
            if (previousIndex && currentIndex) {
                FT_Vector delta;
                FT_Get_Kerning(face, previousIndex, currentIndex,
                    FT_KERNING_DEFAULT, &delta);
                currentX += delta.x >> 6;
            }

            float xpos = currentX + ch.bearingX;
            float ypos = currentY - (ch.height - ch.bearingY);

            // Tạo texture từ bitmap ký tự và vẽ
            if (!ch.bitmap.empty()) {
                GLuint textureID;
                glGenTextures(1, &textureID);
                glBindTexture(GL_TEXTURE_2D, textureID);

                // Tạo texture từ bitmap (luminance + alpha)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, ch.width, ch.height, 0,
                    GL_LUMINANCE, GL_UNSIGNED_BYTE, ch.bitmap.data());

                // Áp dụng các thuộc tính của texture (filter, wrapping)
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

                // Vẽ hình chữ nhật với texture
                glEnable(GL_TEXTURE_2D);
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 0.0f); glVertex2f(xpos, ypos);
                glTexCoord2f(1.0f, 0.0f); glVertex2f(xpos + ch.width, ypos);
                glTexCoord2f(1.0f, 1.0f); glVertex2f(xpos + ch.width, ypos + ch.height);
                glTexCoord2f(0.0f, 1.0f); glVertex2f(xpos, ypos + ch.height);
                glEnd();
                glDisable(GL_TEXTURE_2D);

                // Giải phóng texture
                glDeleteTextures(1, &textureID);
            }

            currentX += ch.advance;
            previousIndex = currentIndex;
        }

        glPopMatrix();

        // Tắt blend sau khi vẽ xong
        glDisable(GL_BLEND);
    }

    ~TextRenderer() {
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }
};