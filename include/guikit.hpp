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
public:
    int x, y;
    terminal::colors bgcolor;
    terminal::colors fgcolor;

    static terminal::Interface &output();

    void SetFgColor(terminal::colors c = terminal::colors::defaul);
    void SetBgColor(terminal::colors c = terminal::colors::defaul);
    void SetPos(int new_x, int new_y);

    base_parameters();
    terminal::colors BgColor();
    terminal::colors FgColor();
    int PosX();
    int PosY();
};

class untitled_box : public base_parameters
{
public:
    // box size
    int width;
    int height;

    void Move(int x, int y);
    void Resize(int w, int h);

    virtual void Draw();

    untitled_box(int w, int h, int x, int y);
};

class titled_box : public untitled_box
{
public:
    std::string title;

    void Draw();
    void ChangeTitle(std::string new_title);
    titled_box(int w, int h, int _x, int _y, std::string _title);
};

class big_hex_bumbers : public base_parameters
{
private:
    std::map<int, int *> alf;

public:
    int number;

    big_hex_bumbers(int num, int new_x = 0, int new_y = 0);

    void SetNumber(int new_number);
    void Move(int new_x, int new_y);

    void Draw();
};

} // namespace gui_kit
