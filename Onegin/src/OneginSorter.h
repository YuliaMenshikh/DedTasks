#pragma once

#include <algorithm>
#include <string_view>

class OneginSorter
{
public:

    /*!
     * Constructor for OneginSorter object
     * @param text source pointer
     * @param size_of_text source length
     */
    OneginSorter(const char* text, int size_of_text);

    /*!
     * Sorts the lines of the source text in direct lexicographic order
     * @param sortedText array of std::string_view into which sorted rows are written
     */
    void SortInDirectOrder(std::string_view* sortedText);

    /*!
     * Sorts the lines of the source text in reverse lexicographic order
     * @param sortedText array of std::string_view into which sorted rows are written
     */
    void SortInReverseOreder(std::string_view* sortedText);

    /*!
     * Returns source
     * @param sortedText array of std::string_view into which rows are written
     */
    void Source(std::string_view *sortedText);

    /*!
     * Number of strings
     * @return number of strings in source
     */
    int NumberOfStrings();

    /*!
     * Destructor for OneginSorter object
     */
    ~OneginSorter();

private:
    /*!
     * String comparator (direct lexicographic order)
     * @param s1 first string
     * @param s2 second string
     * @return
     */
    static bool CompareDirectOrder(const std::string_view &s1, const std::string_view &s2);

    /*!
     * String comparator (reverse lexicographic order)
     * @param s1 first string
     * @param s2 second string
     * @return
     */
    static bool CompareReverseOrder(const std::string_view &s1, const std::string_view &s2);

    /*!
     * Array of std::string_viewfor storing text
     */
    std::string_view* _arrayOfStringviews;

    /*!
     * Variable to store the number of rows
     */
    int _numberOfStrings;

    /*!
     * Variable to store text
     */
    char * _buf;
};