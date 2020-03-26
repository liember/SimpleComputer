#pragma once

#include "myTerm.hpp"
#include "myBigChars.hpp"

#include <iostream>
#include <map>

namespace gui_kit
{

//################## functions #######################



// ####################### classes ######################

//Adapter for myTerm and myBigChars modules
class VOS // visual output system
{
public:
    myBigChars *bc;
    myTerm *term;

public:
    void SetSize(int row, int col);
    void ClrScr();
    void GoToLastRow();

    VOS(/* args */);
    VOS(myTerm *t, myBigChars *b);
    ~VOS();
};

class base_parameters
{
private:
    int x, y;
    myTerm::colors bgcolor;
    myTerm::colors fgcolor;
    static VOS *vos;

public:
    static void SetVOS(VOS *out);
    void SetFgColor(myTerm::colors c = myTerm::colors::defaul);
    void SetBgColor(myTerm::colors c = myTerm::colors::defaul);
    void SetPos(int new_x, int new_y);

    myTerm::colors BgColor();
    myTerm::colors FgColor();
    int PosX();
    int PosY();
    static VOS *Window();
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
