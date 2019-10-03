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
        for (int j = 0; j < text[i].length(); ++j)
        {
            fputc(text[i][j], file);
        }
        fputc('\n', file);
    }

    fputs("\n\n_____________________________________\n\n", file);

    fclose(file);
}

/*!
 * Reads a file and does the necessary manipulations in the task
 * @param fileName name of file
 */
void ReadFile(const char* fileName)
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


    OneginSorter onegin(text, textSize);

    std::string_view* sortedText = new std::string_view[onegin.NumberOfStrings()];

    onegin.SortInDirectOrder(sortedText);
    WriteToFile("Onegin2.txt", sortedText, onegin.NumberOfStrings());

    onegin.SortInReverseOreder(sortedText);
    WriteToFile("Onegin2.txt", sortedText, onegin.NumberOfStrings());

    onegin.Sourse(sortedText);
    WriteToFile("Onegin2.txt", sortedText, onegin.NumberOfStrings());

    delete [] text;
    delete [] sortedText;
}

void Test()
{
    RUN_ALL_TESTS();
}

int main()
{
    const char* fileName = "Onegin.txt";
    ReadFile(fileName);

    Test();
    return 0;
}