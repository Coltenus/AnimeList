//
// Created by colte on 16.01.2023.
//

#include "Button.h"
#include "common.h"

namespace al {
    Button::Button(const char* text, Vector2 pos, Vector2 size, short opcode)
    : Button(text, pos, size, opcode, 0) {}

    Button::Button(const char* text, Vector2 pos, Vector2 size, short opcode, short value)
            : _pos(pos), _size(size), _opcode(opcode), _value(value), _text(text), _thickness(5), isTextureExtern(false) {
        if(_size.x < 30)
            _size.x = 35;
        if(_size.y < 16)
            _size.y = 16;
        _fontH = size.y / 2;
        {
            Image buf = LoadImage("res/button.png");
            ImageResize(&buf, _size.x, _size.y);
            buttonTexture = LoadTextureFromImage(buf);
        }
    }

    Button::Button(const char *text, Vector2 pos, Vector2 size, short opcode, short value, Texture2D bTexture)
            : _pos(pos), _size(size), _opcode(opcode), _value(value), _text(text), _thickness(5),
            buttonTexture(bTexture), isTextureExtern(true) {
        if(_size.x < 30)
            _size.x = 35;
        if(_size.y < 16)
            _size.y = 16;
        _fontH = size.y / 2;
    }

    void Button::Draw() {
        const static Rectangle rec = {0, 0, 500, 500};
        static Vector2 mouse;
        mouse = GetMousePosition();
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
           && mouse.x >= _pos.x && mouse.x <= _pos.x + _size.x
           && mouse.y >= _pos.y && mouse.y <= _pos.y + _size.y)
            DrawTextureTiled(buttonTexture, rec, {_pos.x, _pos.y, _size.x, _size.y}, {0, 0}, 0, 1, GRAY);
        else DrawTextureTiled(buttonTexture, rec, {_pos.x, _pos.y, _size.x, _size.y}, {0, 0}, 0, 1, WHITE);
        DrawTextEx(font, _text.c_str(), {_pos.x + 10 + (_size.x > _size.y ? (_size.x - _size.y)/10 : 0 ),
                                         _pos.y + _size.y / 4}, _fontH, 1, BLACK);
    }

    void Button::Update(short& opcode) {
        static Vector2 mouse;
        mouse = GetMousePosition();
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
        && mouse.x >= _pos.x && mouse.x <= _pos.x + _size.x
        && mouse.y >= _pos.y && mouse.y <= _pos.y + _size.y)
            opcode = _opcode;
    }

    void Button::Update(short &opcode, short &value) {
        static Vector2 mouse;
        mouse = GetMousePosition();
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
           && mouse.x >= _pos.x && mouse.x <= _pos.x + _size.x
           && mouse.y >= _pos.y && mouse.y <= _pos.y + _size.y) {
            opcode = _opcode;
            value = _value;
        }

    }

    void Button::ShiftByOne() {
        _value--;
    }

    void Button::SetThickness(short value) {
        _thickness = value;
    }

    void Button::MoveByValue(Vector2 offset) {
        _pos.x += offset.x;
        _pos.y += offset.y;
    }

    short Button::GetValue() {
        return _value;
    }

    Button::~Button() {
        if(!isTextureExtern)
            UnloadTexture(buttonTexture);
    }
} // al