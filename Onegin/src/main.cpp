#include "gtest/gtest.h"
#include "FileHandler.h"

int main()
{
    const char* fileName = "Onegin1.txt";
    const char* fileOut = "Onegin2.txt";

    FileHandler::ReadFileOnegin(fileName, fileOut);

    testing::InitGoogleTest();
    RUN_ALL_TESTS();

    return 0;
}