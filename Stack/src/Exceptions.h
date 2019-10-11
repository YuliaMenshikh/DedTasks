#ifndef STACKKK_EXCEPTIONS_H
#define STACKKK_EXCEPTIONS_H

#include <exception>

class NotAvailableStackException : public std::exception
{
    virtual const char* what() const noexcept
    {
        return "Not Available Stack";
    }
};

class IncorrectOperationException : public std::exception
{
    virtual const char* what() const noexcept
    {
        return "Incorrect Operation";
    }
};

#endif //STACKKK_EXCEPTIONS_H
