#pragma once

#include <exception>
#include <string>

class Except : virtual public std::exception
{

protected:
    std::string error_message;

public:
    explicit Except(const std::string &msg) : error_message(msg)
    {
    }
    virtual ~Except() throw() {}

    virtual const char *what() const throw()
    {
        return error_message.c_str();
    }
};