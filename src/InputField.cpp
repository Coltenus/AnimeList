//
// Created by colte on 16.01.2023.
//

#include <locale>
#include <codecvt>
#include "InputField.h"
#include "common.h"

namespace al {
    InputField::InputField(Vector2 pos, Vector2 size, short maxSymbols, const char16_t *add_text)
            : _pos(pos), _size(size), _active(false), _maxSymbols(maxSymbols),
              _addition_text(add_text) {
        if(_size.x < 30)
            _size.x = 30;
        if(_size.y < 16)
            _size.y = 16;
        _fontH = size.y / 2;
    }

    InputField::InputField(Vector2 pos, Vector2 size, short maxSymbols)
    : InputField(pos, size, maxSymbols, u"") {}

    void InputField::Draw() {
        static std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> convert;
        if(_active)
            DrawRectangleV(_pos, _size, WHITE);
        else DrawRectangleV(_pos, _size, LIGHTGRAY);
        DrawRectangleLinesEx({_pos.x, _pos.y, _size.x, _size.y}, 3, BLACK);
        if(_text != std::u16string())
            DrawTextEx(font, convert.to_bytes(_text).c_str(), {_pos.x + 10, _pos.y + _size.y / 4}, _fontH, 1, BLACK);
        else DrawTextEx(font, convert.to_bytes(_addition_text).c_str(), {_pos.x + 10, _pos.y + _size.y / 4}, _fontH, 1, GRAY);
    }

    void InputField::Update() {
        static std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> convert;
        static Vector2 mouse;
        static short key;
        mouse = GetMousePosition();
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
           && mouse.x >= _pos.x && mouse.x <= _pos.x + _size.x
           && mouse.y >= _pos.y && mouse.y <= _pos.y + _size.y)
            _active = !_active;
        if(_active && ((key = GetCharPressed()) >= 65 && key <= 90
                       || key >= 97 && key <= 122 || key == 33 || key == 64 || key == 58 || key >= 39 && key <= 41
                       || key == 63 || key >= 43 && key <= 46 || key == KEY_SPACE || key >= 48 && key <= 57
                       || key >= 1040 && key <= 1103 || key == 1110 || key == 1108 || key == 1111 || key == 1105
                       || key == 1030 || key == 1028 || key == 1031 || key == 1025)
                       && GetSize() < _maxSymbols)
            _text += key;
        else if(_active && IsKeyPressed(KEY_BACKSPACE) && _text.size() > 0)
            _text.pop_back();
        else if(_active && IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_V))
        {
            std::string buf(GetClipboardText());
            if(_text.size() + buf.size() <= _maxSymbols)
                _text += convert.from_bytes(buf);
            else {
                short i = 0;
                while(_text.size() != _maxSymbols)
                {
                    _text += buf[i];
                    i++;
                }
            }
        }
    }

    const char *InputField::GetText() {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> convert;
        return convert.to_bytes(_text).c_str();
    }

    short InputField::GetSize() {
        short result = 0;

        for(auto& el: _text)
            result++;

        return result;
    }
} // al