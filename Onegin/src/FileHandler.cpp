#include "OneginSorter.h"
#include "FileHandler.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/stat.h>
#include <cassert>

void FileHandler::WriteToFile(const char* fileName, std::string_view* text, int stringCount)
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

void FileHandler::GetAnswer(const char* text, const char* fileOut, size_t textSize)
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

int FileHandler::SizeOfText(const char* fileName)
{
    struct stat file_stats;
    stat(fileName, &file_stats);
    return file_stats.st_size;
}

void FileHandler::OpenFile(FILE** file, const char* fileName)
{
    while (*file == nullptr) {
        *file = fopen(fileName, "r");
        if (*file == nullptr) {
            printf("Wrong name of file");
        }
    }
}

void FileHandler::ReadFileOnegin(const char* fileName, const char* fileOut)
{
    int textSize = 0;
    char* text = nullptr;

    textSize = SizeOfText(fileName);

    FILE* file = nullptr;
    OpenFile(&file, fileName);

    ++textSize;
    text = new char[textSize];
    fread(text, sizeof(char), textSize, file);
    text[textSize - 1] = '\0';

    fclose(file);

    GetAnswer(text, fileOut, textSize);

    delete [] text;
}

