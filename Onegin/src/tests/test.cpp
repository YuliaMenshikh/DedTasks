#include "gtest/gtest.h"
#include "../OneginSorter.h"

TEST(OneginSorter, numberOfStrings)
{
    const char* text = "bbb\nccc\naaa\n";
    OneginSorter poem(text, 12);
    EXPECT_EQ(poem.NumberOfStrings(), 3);
}

TEST(OneginSorter, SortDirectOrder)
{
    const char* text = "bbb\nccc\naaa\n";
    OneginSorter poem(text, 12);
    std::string_view* t = new std::string_view[3];
    poem.SortInDirectOrder(t);
    EXPECT_EQ(t[0][0], text[8]);
    delete [] t;
}

TEST(OneginSorter, SortReverseOrder)
{
    const char* text = "bbb\nccc\naaa\n";
    OneginSorter poem(text, 12);
    std::string_view* t = new std::string_view[3];
    poem.SortInReverseOreder(t);
    EXPECT_EQ(t[0][0], text[4]);
    delete [] t;
}

TEST(OneginSorter, Sourse)
{
    const char* text = "bbb\nccc\naaa\n";
    OneginSorter poem(text, 12);
    std::string_view* t = new std::string_view[3];
    poem.SortInReverseOreder(t);
    poem.Sourse(t);
    EXPECT_EQ(t[0][0], text[0]);
    delete [] t;
}

