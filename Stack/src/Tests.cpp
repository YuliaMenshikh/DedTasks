#include "Stack.h"

#include "gtest/gtest.h"

TEST(Stack, Top)
{
    Stack<int> a;
    a.push(1);
    a.push(2);
    EXPECT_EQ(2, a.top());
}

TEST(Stack, size)
{
    Stack<int> a;
    a.push(1);
    a.push(2);
    EXPECT_EQ(2, a.size());
}

TEST(Stack, empty)
{
    Stack<int> a;
    a.push(1);
    a.push(2);
    EXPECT_EQ(false, a.empty());
}

TEST(Stack, NotAvailableStackException)
{
    try
    {
        Stack<int> a;
        a.push(4);
        a.push(3);
        a.push(1);
        int* ptr = &a.top();
        *(ptr - 2) = 166;
    }
    catch (const std::exception &exc)
    {
        EXPECT_EQ(exc.what(), "Not Available Stack");
    }
}

TEST(Stack, IncorrectOperationException)
{
    try
    {
        Stack<int> a;
        a.push(4);
        a.pop();
        a.pop();

    }
    catch (const std::exception &exc)
    {
        EXPECT_EQ(exc.what(), "Incorrect Operation");
    }
}