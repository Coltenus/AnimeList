//
// Created by colte on 16.01.2023.
//

#include "ListItem.h"
#include "common.h"

namespace al {
    ListItem::ListItem(const char* text, Vector2 startPos, Vector2 size)
    : _text(text), _size(size){
        if(_size.x < 100)
            _size.x = 100;
        if(_size.y < 16)
            _size.y = 16;
        _fontH = _size.y / 2;
        _pos = {startPos.x, startPos.y + (_size.y + 15) * elementsCount};
        _delButton = new Button("Delete", {_pos.x + _size.x/10*7, _pos.y}, {_size.x/10*3, _size.y}, 2, elementsCount);
        _delButton->SetThickness(3);
        elementsCount++;
    }

    ListItem::~ListItem() {
        delete _delButton;
        _delButton = nullptr;
        elementsCount--;
    }

    void ListItem::Draw() {
        DrawRectangleLinesEx({_pos.x, _pos.y, _size.x, _size.y}, 2, BLACK);
        DrawTextEx(font, _text.c_str(), {_pos.x + 10, _pos.y + _size.y/4}, _fontH, 1, BLACK);
        _delButton->Draw();
    }

    void ListItem::Update(short &opcode, short &value) {
        static Vector2 mouse;
        mouse = GetMousePosition();
        _delButton->Update(opcode, value);
        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)
        && mouse.x >= _pos.x && mouse.x <= _pos.x + _size.x/10*7
        && mouse.y >= _pos.y && mouse.y <= _pos.y + _size.y)
            SetClipboardText(_text.c_str());
    }

    void ListItem::ShiftByOne() {
        if(_delButton->GetValue() > 0){
            _delButton->ShiftByOne();
            _delButton->MoveByValue({0, -(_size.y + 15)});
            _pos.y -= _size.y + 15;
        }
    }

    std::string ListItem::GetText() {
        return _text;
    }
} // al