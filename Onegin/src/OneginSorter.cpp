#include "OneginSorter.h"

OneginSorter::OneginSorter(const char* text, int size_of_text)
{
    int string_count = 0;
    //_buf = new char[size_of_text];

    /*for (int i = 0; i < size_of_text; ++i)
    {
        if (text[i] == '\n')
            _buf[i] = '\0';
        else
            _buf[i] = text[i];
    }*/

    for (size_t i = 0; i < size_of_text; ++i)
    {
        if (text[i] == '\0' || text[i] == '\n')
        {
            string_count++;
        }
    }
    _numberOfStrings = string_count;
    _arrayOfStringviews = new std::string_view[string_count];
    /*if (string_count) {
        _arrayOfStringviews[0] = std::string_view(&_buf[0]);
    }
    size_t j = 1;
    for (size_t i = 1; i < size_of_text; ++i) {
        if (_buf[i - 1] == '\0') {
            _arrayOfStringviews[j++] = std::string_view(&_buf[i]);
        }
    }*/
    size_t j = 0;
    for (size_t i = 1; i < size_of_text; ++i)
    {
        if (text[i] == '\n' || text[i] == '\0')
        {
            if (!j)
            {
                _arrayOfStringviews[j] = std::string_view(&text[0], i);
            }
            else
            {
                const char* temp = &_arrayOfStringviews[j - 1][0] + _arrayOfStringviews[j - 1].length() + 1;
                _arrayOfStringviews[j] = std::string_view(temp, &text[i] - temp);
            }
            j++;
        }
    }

}

void OneginSorter::SortInDirectOrder(std::string_view* sortedText)
{
    for (int i = 0; i < _numberOfStrings; ++i)
    {
        sortedText[i] = _arrayOfStringviews[i];
    }

    std::sort(sortedText, sortedText + _numberOfStrings, CompareDirectOrder);

}

void OneginSorter::SortInReverseOreder(std::string_view* sortedText)
{
    for (int i = 0; i < _numberOfStrings; ++i)
    {
        sortedText[i] = _arrayOfStringviews[i];
    }

    std::sort(sortedText, sortedText + _numberOfStrings, CompareReverseOrder);
}

void OneginSorter::Source(std::string_view *sortedText)
{
    for (int i = 0; i < _numberOfStrings; ++i)
    {
        sortedText[i] = _arrayOfStringviews[i];
    }
}

bool OneginSorter::CompareDirectOrder(const std::string_view &s1, const std::string_view &s2)
{
    for (size_t counter1 = 0, counter2 = 0; counter1 < s1.length() && counter2 < s2.length();
         ++counter1, ++counter2)
    {
        while (!isalpha(s1[counter1]))
        {
            ++counter1;
            if (counter1 == s1.length())
            {
                return true;
            }
        }

        while (!isalpha(s2[counter2]))
        {
            ++counter2;
            if (counter2 == s2.length())
            {
                return false;
            }
        }

        int difference = tolower(s1[counter1]) - tolower(s2[counter2]);
        if (difference > 0)
        {
            return false;
        }
        if (difference < 0)
        {
            return true;
        }
    }
    return false;
}

bool OneginSorter::CompareReverseOrder(const std::string_view &s1, const std::string_view &s2)
{
    for (size_t counter1 = s1.length() - 1, counter2 = s2.length() - 1; counter1 >= 0 && counter2 >= 0;
         --counter1, --counter2)
    {
        while (!isalpha(s1[counter1]))
        {
            --counter1;
            if (counter1 == -1)
            {
                return true;
            }
        }

        while (!isalpha(s2[counter2]))
        {
            --counter2;
            if (counter2 == -1)
            {
                return false;
            }
        }

        int difference = tolower(s1[counter1]) - tolower(s2[counter2]);
        if (difference > 0)
        {
            return false;
        }
        if (difference < 0)
        {
            return true;
        }
    }
    return false;
}

int OneginSorter::NumberOfStrings()
{
    return _numberOfStrings;
}