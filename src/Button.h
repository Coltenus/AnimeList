//
// Created by colte on 16.01.2023.
//

#ifndef ANIMELIST_BUTTON_H
#define ANIMELIST_BUTTON_H

#include <raylib.h>
#include <string>

namespace al {

    class Button {
    private:
        Vector2 _pos, _size;
        std::string _text;
        short _fontH, _opcode, _value, _thickness;
        Texture2D buttonTexture;
        bool isTextureExtern;

    public:
        Button(const char* text, Vector2 pos, Vector2 size, short opcode);
        Button(const char* text, Vector2 pos, Vector2 size, short opcode, short value);
        Button(const char* text, Vector2 pos, Vector2 size, short opcode, short value, Texture2D bTexture);
        ~Button();
        void Draw();
        void Update(short& opcode);
        void Update(short& opcode, short& value);
        void ShiftByOne();
        void SetThickness(short value);
        void MoveByValue(Vector2 offset);
        short GetValue();
    };

} // al

#endif //ANIMELIST_BUTTON_H
