#include <iostream>
#include <raylib.h>
#include <vector>
#include <fstream>
#include "src/common.h"
#include "src/InputField.h"
#include "src/Button.h"
#include "src/ListItem.h"

short al::ListItem::elementsCount = 0;
Font font;

int main() {
    InitWindow(WIDTH, HEIGHT, "Anime List");
    SetTargetFPS(30);
    Camera2D cam = {{WIDTH/2, HEIGHT/2}, {WIDTH/2, HEIGHT/2}, 0, 1};
    int codepoints[512] = { 0 };
    for (int i = 0; i < 95; i++) codepoints[i] = 32 + i;   // Basic ASCII characters
    for (int i = 0; i < 255; i++) codepoints[96 + i] = 0x400 + i;   // Cyrillic characters
    font = LoadFontEx("res/Days.otf", 32, codepoints, 512);
    al::InputField input({50, 20}, {650, 50}, 30, u"Input name of anime (min char-4, max-30)");
    al::Button saveButton("Save", {750, 20}, {100, 50}, 1);
    al::Button upButton("Up", {WIDTH - 100, HEIGHT - 100}, {55, 50}, 3);
    std::vector<al::ListItem*> list;
    {
        std::string buf;
        std::ifstream data("anime_list.txt");
        while(std::getline(data, buf))
        {
            if(buf != std::string("")) {
                short shift = 0;
                short counter = 0;
                for(auto& el: buf)
                {
                    if(counter >= 60)
                        break;
                    if(el > 0)
                        shift = !shift;
                    counter++;
                }
                while((buf[0] < 0 || buf[1] < 0 || buf[2] < 0 || buf[3] < 0)
                && buf.size() > 60 + shift
                || buf[0] > 0 && buf[1] > 0 && buf[2] > 0 && buf[3] > 0
                && buf.size() > 30)
                {
                    buf.pop_back();
                }
                list.push_back(new al::ListItem(buf.c_str(), {50, 120}, {700, 40}));
            }
        }
    }
    float wheelOffset;
    short opcode, num;
    while (!WindowShouldClose())
    {
        opcode = 0;
        num = 0;
        if((wheelOffset = GetMouseWheelMove()) != 0)
        {
            if(wheelOffset > 0 && cam.offset.y < HEIGHT / 2 || wheelOffset < 0 && cam.offset.y > HEIGHT * 3 / 2 - (120 + 55 * al::ListItem::elementsCount))
                cam.offset.y += wheelOffset * 25;
        }
        if(cam.offset.y < HEIGHT / 2)
            upButton.Update(opcode);
        input.Update();
        saveButton.Update(opcode);
        for(auto& el: list)
            el->Update(opcode, num);
        if(IsKeyPressed(KEY_ENTER))
            opcode = 1;
        switch (opcode) {
            case 1:
                {
                    auto buffer = std::string(input.GetText());
                    if (buffer != std::string("") && buffer.size() > 3)
                    list.push_back(new al::ListItem(buffer.c_str(), {50, 120}, {700, 40}));
                }
                break;
            case 2:
                delete list[num];
                list.erase(std::next(list.begin(), num));
                for(short i = num; i<list.size(); i++)
                    list[i]->ShiftByOne();
                break;
            case 3:
                cam.offset.y = HEIGHT / 2;
                break;
        }
        BeginDrawing();
        ClearBackground(GREEN);
        if(cam.offset.y < HEIGHT / 2)
            upButton.Draw();
        BeginMode2D(cam);
        input.Draw();
        saveButton.Draw();
        for(auto& el: list)
            el->Draw();
        EndMode2D();
        EndDrawing();
    }
    {
        std::string buf;
        std::ofstream data("anime_list.txt");
        short i = 0;
        for(auto& el: list)
        {
            buf = el->GetText();
            data << buf;
            if(i < list.size()-1)
                data << '\n';
            i++;
        }
    }
    for(auto& el: list)
        delete el;
    UnloadFont(font);
    CloseWindow();
}
