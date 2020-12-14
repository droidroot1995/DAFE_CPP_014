#include <gtest/gtest.h>
#include "../vector/vector17.hpp"

TEST(Vector17Test, Constructor)
{
    Vector17 v0{1};
    Vector17 v1{10};
    Vector17 v2{0};
}
TEST(Vector17Test, Size)
{
    Vector17 v0{1};
    EXPECT_EQ(v0.size(), 1);

    Vector17 v1{10};
    EXPECT_EQ(v1.size(), 10);

    Vector17 v2{0};
    EXPECT_EQ(v2.size(), 0);

    const Vector17 v3(2);
    EXPECT_EQ(v3.size(),2);
}

TEST(Vector17Test, SetGet)
{

    Vector17 v0{1};
    Vector17 v1{10};
    Vector17 v2{0};

    v0.set(0, 1.1);
    EXPECT_EQ(v0.get(0), 1.1);

    for (int i = 0; i < v1.size(); ++i)
    {
        v1.set(i, i * 1.1);
    }

    for (int i = 0; i < v1.size(); ++i)
    {
        EXPECT_EQ(v1.get(i), i * 1.1);
    }
}

TEST(Vector17Test, Erase){
    Vector17 v{10};
    for (int i = 0; i < v.size(); ++i)
    {
        v.set(i, i * 1.1);
    }
    v.erase();
    for (int i = 0; i < v.size(); ++i)
    {
        EXPECT_EQ(v.get(i), 0.0);
    }
    
}
