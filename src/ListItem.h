//
// Created by colte on 16.01.2023.
//

#ifndef ANIMELIST_LISTITEM_H
#define ANIMELIST_LISTITEM_H

#include <raylib.h>
#include <string>
#include "Button.h"

namespace al {

    class ListItem {
    private:
        std::string _text;
        Vector2 _pos, _size;
        short _fontH;
        Button* _delButton;

    public:
        static short elementsCount;
        ListItem(const char*, Vector2 startPos, Vector2 size);
        ~ListItem();
        void Draw();
        void Update(short& opcode, short& value);
        void ShiftByOne();
        std::string GetText();
    };

} // al

#endif //ANIMELIST_LISTITEM_H
