#include <gtest/gtest.h>
#include "../vector/vector18.hpp"

class Vector18Test : public ::testing::Test
{
protected:
    Vector18 v5 = {1.0, 2.0, 3.0};
    Vector18 v6 = Vector18(30);
};

void foo(const Vector18 v)
{
    for (int i = 0; i < v.size(); ++i)
    {
        EXPECT_EQ(v[i], 0.0);
    }
}

TEST_F(Vector18Test, Constructors)
{
    Vector18 v0(1);
    EXPECT_EQ(v0.size(), 1);
    EXPECT_FLOAT_EQ(v0[0], 0.0);

    Vector18 v1 = v0;
    EXPECT_EQ(v0[0], v1[0]);
    EXPECT_EQ(v0.size(), v1.size());

    Vector18 v2 = {1.1, 2.1, 3.1};
    EXPECT_EQ(v2.size(), 3);

    Vector18 v3 = Vector18(3);
    EXPECT_EQ(v3.size(), 3);

    Vector18 v4;
    EXPECT_EQ(v4.size(), 0);
}

TEST_F(Vector18Test, Size)
{
    EXPECT_EQ(v5.size(), 3);
    EXPECT_EQ(v6.size(), 30);
}

TEST_F(Vector18Test, Operators)
{
    foo(v6);
    v6 = v5;
    EXPECT_EQ(v5.size(), 3);
    for (int i = 0; i < v6.size(); ++i)
    {
        v6[i] = 1.2;
    }
    for (int i = 0; i < v6.size(); ++i)
    {
        EXPECT_EQ(v6[i], 1.2);
    }
}

TEST_F(Vector18Test, Erase)
{
    v5.erase();
    v6.erase();
    EXPECT_EQ(v5.size(), 0);
    EXPECT_EQ(v6.size(), 0);
}