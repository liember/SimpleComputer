#pragma once

#include <exception>
#include <string>

class StringException : virtual public std::exception
{
protected:
    std::string error_message;

public:
    explicit StringException(const std::string &msg) : error_message(msg)
    {
    }
    virtual ~StringException() throw() {}

    virtual const char *what() const throw()
    {
        return error_message.c_str();
    }
};