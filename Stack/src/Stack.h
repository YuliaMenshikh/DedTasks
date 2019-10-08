#pragma once

#include <iostream>
#include "Exceptions.h"

template <typename T>
class Stack
{
public:
    constexpr static int SIZE_DEFAULT = 8;

    /*!
     * Stack constructor
     */
    Stack();

    /*!
     * Stack destructor
     */
    ~Stack();

    /*!
     * @return top element in stack
     */
    T& top();

    /*!
     * Checks if the stack is empty
     * @return true if empty; false otherwise
     */
    bool empty() const;

    /*!
     * @return size of Stack
     */
    int size() const;

    /*!
     * Puts an item on top of the stack
     * @param value - item type T
     */
    void push(const T& value);

    /*!
     * Construct element and push it
     * @param args params fot construct
     */
    template< class... Args >
    void emplace(Args&&... args );

    /*!
     * Delete top element
     */
    void pop();

    /*!
     * Prints the contents of the stack
     */
    void Dump() const;

private:
    /*!
     * Hash value
     * @param value
     * @return hash for value
     */
    size_t HashFAQ6(const T& value) const;

    /*!
     * Check if Stack is available
     */
    void checkHash() const;

    char* _buffer;
    bool* _isConstructed;
    size_t* _hash;

    int _buffSize;
    int _size;
    int _typeSize;
};


template <typename T>
Stack<T>::Stack() :_buffer(nullptr), _typeSize(sizeof(T)), _size(0)
{
    _buffSize = SIZE_DEFAULT;

    _buffer = new char[_buffSize * _typeSize];
    _isConstructed = new bool[_buffSize];
    _hash = new size_t[_buffSize];
    for (int i = 0; i < _buffSize; ++i)
    {
        _isConstructed[i] = false;
    }
}

template <typename T>
Stack<T>::~Stack()
{
    for (int i = 0; i < _buffSize; ++i)
    {
        if (_isConstructed[i])
        {
            reinterpret_cast<T*>(_buffer)[i].~T();
        }
    }
    delete[] _buffer;
    delete[] _isConstructed;
    delete[] _hash;
}

template <typename T>
T& Stack<T>::top()
{
    if (_size <= 0)
    {
        throw IncorrectOperationException();
    }
    T* ptr = &reinterpret_cast<T*>(_buffer)[_size - 1];
    checkHash();
    return *ptr;
}

template <typename T>
bool Stack<T>::empty() const
{
    checkHash();
    if (_size)
        return false;
    return true;
}

template <typename T>
int Stack<T>::size() const
{
    checkHash();
    return _size;
}

template <typename T>
void Stack<T>::pop()
{
    if (_size <= 0)
    {
        throw IncorrectOperationException();
    }
    _size--;
    reinterpret_cast<T*>(_buffer)[_size].~T();
    _isConstructed[_size] = false;
    checkHash();
}

template <typename T>
void Stack<T>::push(const T &value)
{
    if (_size > _buffSize)
    {
        _buffSize *= 2;
        char* newBuffer = new char[_buffSize * _typeSize];
        bool* newIsConstructed = new bool[_buffSize];
        for (int i = 0; i <= _size; ++i)
        {
            if (_isConstructed[i])
            {
                reinterpret_cast<T*>(newBuffer)[i] = reinterpret_cast<T*>(_buffer)[i];
                newIsConstructed[i] = true;
            }
        }
        for (int i = _size; i < _buffSize; ++i)
        {
            newIsConstructed[i] = false;
        }
        delete[] _buffer;
        delete[] _isConstructed;
        _buffer = newBuffer;
        _isConstructed = newIsConstructed;

    }

    reinterpret_cast<T*>(_buffer)[_size] = value;
    _hash[_size] = HashFAQ6(value);
    _isConstructed[_size] = true;

    _size++;
    checkHash();
}

template <typename T>
template< class... Args >
void Stack<T>::emplace(Args&&... args)
{
    push(T(std::forward<Args>(args)...));
}

template <typename T>
size_t Stack<T>::HashFAQ6(const T &value) const
{
    size_t hash = 0;
    int bits = sizeof(T);
    const T* valuePtr = &value;
    const char* valuePTr = reinterpret_cast<const char*>(valuePtr);

    for (int i = 0; i < bits; ++i)
    {
        hash += (unsigned char)(*valuePTr);
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

template <typename T>
void Stack<T>::checkHash() const
{
    T* value;
    for (int i = 0; i < _size; ++i)
    {
        value = &reinterpret_cast<T*>(_buffer)[i];
        if (_hash[i] != HashFAQ6(*value))
        {
            Dump();
            throw NotAvailableStackException();
        }
    }
}

template <typename T>
void Stack<T>::Dump() const
{
    std::cout << "Stack\nsize : " << _size << "\nbuffer size : " << _buffSize << std::endl;
    std::cout << "stack contents : ";
    for (int i = 0; i < _size; ++i)
    {
        std::cout << reinterpret_cast<T*>(_buffer)[i] << " ";
    }
    std::cout << std::endl;
}