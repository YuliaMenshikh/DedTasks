#pragma once

#include <string_view>

namespace FileHandler
{
    /*!
     * Write text to the file
    * @param fileName name of file
    * @param text array of std::string_view with text
    * @param stringCount number of strings
    */
    void WriteToFile(const char* fileName, std::string_view* text, int stringCount);

    /*!
     * It does the necessary manipulations in the task
    * @param text source
    * @param fileOut file to write in
    */
    void GetAnswer(const char* text, const char* fileOut, size_t textSize);

    /*!
     * Measures file size
     * @param fileName
     * @return size of text
     */
    int SizeOfText(const char* fileName);

    /*!
     * Open file
     * @param file
     * @param fileName
     */
    void OpenFile(FILE** file, const char* fileName);

    /*!
    * Reads a file and does the necessary manipulations in the task
    * @param fileName name of file
    */
    void ReadFileOnegin(const char* fileName, const char* fileOut);

}
