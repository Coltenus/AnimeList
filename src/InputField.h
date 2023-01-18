//
// Created by colte on 16.01.2023.
//

#ifndef ANIMELIST_INPUTFIELD_H
#define ANIMELIST_INPUTFIELD_H

#include <raylib.h>
#include <string>

namespace al {

    class InputField {
    private:
        Vector2 _pos, _size;
        std::u16string _text, _addition_text;
        short _fontH;
        bool _active;
        short _maxSymbols;

    public:
        InputField(Vector2 pos, Vector2 size, short maxSymbols);
        InputField(Vector2 pos, Vector2 size, short maxSymbols, const char16_t* add_text);
        ~InputField() = default;
        void Draw();
        void Update();
        const char* GetText();
        short GetSize();
    };

} // al

#endif //ANIMELIST_INPUTFIELD_H
