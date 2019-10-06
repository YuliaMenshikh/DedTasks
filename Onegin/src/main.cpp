#include "OneginSorter.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/stat.h>
#include <cassert>

#include "gtest/gtest.h"

/*!
 * Write text to the file
 * @param fileName name of file
 * @param text array of std::string_view with text
 * @param stringCount number of strings
 */
void WriteToFile(const char* fileName, std::string_view* text, int stringCount)
{
    FILE* file = nullptr;
    file = fopen(fileName, "a");

    for (size_t i = 0; i < stringCount; ++i)
    {
        fwrite(text[i], file);
        fputc('\n', file);
    }

    fputs("\n\n_____________________________________\n\n", file);

    fclose(file);
}

/*!
 * It does the necessary manipulations in the task
 * @param text source
 * @param fileOut file to write in
 */
void GetAnswer(const char* text, const char* fileOut)
{
    OneginSorter onegin(text, textSize);

    std::string_view* sortedText = new std::string_view[onegin.NumberOfStrings()];

    onegin.SortInDirectOrder(sortedText);
    WriteToFile(fileOut, sortedText, onegin.NumberOfStrings());

    onegin.SortInReverseOreder(sortedText);
    WriteToFile(fileOut, sortedText, onegin.NumberOfStrings());

    onegin.Source(sortedText);
    WriteToFile(fileOut, sortedText, onegin.NumberOfStrings());

    delete [] sortedText;
}

/*!
 * Reads a file and does the necessary manipulations in the task
 * @param fileName name of file
 */
void ReadFileOnegin(const char* fileName, const char* fileOut)
{
    int textSize = 0;
    char* text = nullptr;


    if (textSize) {
        delete[] text;
    }

    struct stat file_stats;
    stat(fileName, &file_stats);
    textSize = file_stats.st_size;

    FILE* file = nullptr;
    while (file == nullptr) {
        file = fopen(fileName, "r");
        if (file == nullptr) {
            printf("Wrong name of file");
        }
    }

    ++textSize;
    text = new char[textSize];
    fread(text, sizeof(char), textSize, file);
    text[textSize - 1] = '\0';

    fclose(file);

    GetAnswer(text, fileOut);

    delete [] text;
}

int main()
{
    const char* fileName = "Onegin.txt";
    const char* fileOut = "Onegin2.txt";
    ReadFile(fileName, fileOut);

    RUN_ALL_TESTS();
    return 0;
}