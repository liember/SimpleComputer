#pragma once

#include "terminal.hpp"

#include <iostream>
#include <map>

namespace gui_kit
{

//################## functions #######################

// ####################### classes ######################
class base_parameters
{
private:
    int x, y;
    terminal::colors bgcolor;
    terminal::colors fgcolor;

public:
    static terminal::Interface terminal;

    void SetFgColor(terminal::colors c = terminal::colors::defaul);
    void SetBgColor(terminal::colors c = terminal::colors::defaul);
    void SetPos(int new_x, int new_y);

    base_parameters();
    terminal::colors BgColor();
    terminal::colors FgColor();
    int PosX();
    int PosY();
};

class titled_box : public base_parameters
{
private:
    std::string title;

    // box size
    int width;
    int height;

public:
    void Move(int new_x, int new_y);
    void Resize(int new_width, int new_height);

    void Draw();

    void ChangeTitle(std::string new_title);

    titled_box(int w, int h, int _x, int _y, std::string _title);
};

class untitled_box : public base_parameters
{
private:
    std::string title;

    // box size
    int width;
    int height;

public:
    void Move(int x, int y);
    void Resize(int w, int h);

    void Draw();

    untitled_box(int w, int h, int x, int y);
};

class big_hex_bumbers : public base_parameters
{
private:
    std::map<int, int *> alf;

    int number;

public:
    big_hex_bumbers(int num, int new_x = 0, int new_y = 0);

    void SetNumber(int new_number);
    void Move(int new_x, int new_y);

    void Draw();
};

} // namespace gui_kit
