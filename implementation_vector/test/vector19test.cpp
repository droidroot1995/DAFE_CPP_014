#include <gtest/gtest.h>
#include "../vector/vector19.hpp"
#include <exception>
#include "../vector/vector19.cpp" //there is some problem with indexation of this file


class Vector19Test : public ::testing::Test
{
protected:
    Vector19<double> v5 = {1.0, 2.0, 3.0};
    Vector19<double> v6 = Vector19<double>(30);
    Vector19<char> v7 = Vector19<char>(80);
};

void foo(const Vector19<double> v)
{
    for (int i = 0; i < v.size(); ++i)
    {
        EXPECT_EQ(v[i], 0.0);
    }
}

TEST_F(Vector19Test, Constructors)
{
    Vector19<double> v0(1);
    EXPECT_EQ(v0.size(), 1);
    EXPECT_FLOAT_EQ(v0[0], 0.0);

    Vector19<double> v1 = v0;
    EXPECT_EQ(v0[0], v1[0]);
    EXPECT_EQ(v0.size(), v1.size());

    Vector19<char> v2 = {'a', 'b', 'c'};
    EXPECT_EQ(v2.size(), 3);

    Vector19<double> v3 = Vector19<double>(3);
    EXPECT_EQ(v3.size(), 3);

    Vector19<double> v4;
    EXPECT_EQ(v4.size(), 0);

    v5.push_back(1.3);
    EXPECT_NO_THROW(v5[5]);
}


TEST_F(Vector19Test, Operators)
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

TEST_F(Vector19Test, Push_back){
    v5.push_back(90);
    EXPECT_EQ(v5[v5.size()-1], 90);
    v7.push_back('n');
    EXPECT_EQ(v7[v7.size()-1], 'n');

    Vector19<int> v = {1,2};
    v.push_back(3);
    EXPECT_EQ(v.capacity(),4);
}

TEST_F(Vector19Test, Reserve){
    Vector19<char> v = {'q','c','a'};
    EXPECT_THROW(v.reserve(2), std::bad_alloc);
    EXPECT_EQ(v.capacity(), 3);
    v.reserve(8);
    EXPECT_EQ(v.capacity(), 8);
}

TEST_F(Vector19Test, Capacity){
    Vector19<int> v ={1,2,3};
    EXPECT_EQ(v.capacity(),3);
    v.push_back(4);
    EXPECT_EQ(v.capacity(),6);
}

TEST_F(Vector19Test, Size)
{
    EXPECT_EQ(v5.size(), 3);
    EXPECT_EQ(v6.size(), 30);
    EXPECT_EQ(v7.size(), 80);
    Vector19<Vector19<int>> v8(7);
    EXPECT_EQ(v8.size(), 7);
}


TEST_F(Vector19Test, At){
    EXPECT_FLOAT_EQ(v5.at(0),1.0);
    EXPECT_FLOAT_EQ(v5.at(1),2.0);
    EXPECT_FLOAT_EQ(v5.at(2),3.0);
    v5.push_back(1.3);
    EXPECT_THROW(v5.at(4),std::out_of_range);
    EXPECT_THROW(v5.at(-4),std::out_of_range);
}
