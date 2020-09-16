//
//  main.cpp
//  GTests
//
//  Created by roko on 7/22/16.
//  Copyright © 2016 roko. All rights reserved.
//

#include <thread>

#include "InstanceCounter.h"
#include "gtest/gtest.h"

TEST(InstanceCounterTests, DefaultConstructorDestructor)
{
    class MyClass : public InstanceCounter<MyClass>
    {
    };

    ASSERT_EQ(InstanceCounter<MyClass>::getCount(), 0);
    {
        MyClass a;
        ASSERT_EQ(InstanceCounter<MyClass>::getCount(), 1);
    }
    ASSERT_EQ(InstanceCounter<MyClass>::getCount(), 0);
}

TEST(InstanceCounterTests, CopyConstructor)
{
    class MyClass : public InstanceCounter<MyClass>
    {
    };

    ASSERT_EQ(InstanceCounter<MyClass>::getCount(), 0);
    {
        MyClass a;
        MyClass b(a);
        ASSERT_EQ(InstanceCounter<MyClass>::getCount(), 2);
    }
    ASSERT_EQ(InstanceCounter<MyClass>::getCount(), 0);
}

TEST(InstanceCounterTests, MoveConstructor)
{
    class MyClass : public InstanceCounter<MyClass>
    {
    };

    ASSERT_EQ(InstanceCounter<MyClass>::getCount(), 0);
    {
        MyClass a;
        MyClass b(std::move(a));
        ASSERT_EQ(InstanceCounter<MyClass>::getCount(), 2);
    }
    ASSERT_EQ(InstanceCounter<MyClass>::getCount(), 0);
}

TEST(InstanceCounterTests, Multithread)
{
    class MyClass : public InstanceCounter<MyClass>
    {
    };

    auto threadFunc = [](std::vector<MyClass> &container, int count) {
        for (int i = 0; i < count; ++i)
        {
            container.push_back(MyClass());
        }
    };

    {
        std::vector<MyClass> v1;
        std::vector<MyClass> v2;

        const int instanceCount = 1000000;

        ASSERT_EQ(InstanceCounter<MyClass>::getCount(), 0);

        std::thread t1(threadFunc, std::ref(v1), instanceCount);
        std::thread t2(threadFunc, std::ref(v2), instanceCount);

        t1.join();
        t2.join();

        ASSERT_EQ(InstanceCounter<MyClass>::getCount(), instanceCount * 2);
    }

    ASSERT_EQ(InstanceCounter<MyClass>::getCount(), 0);
}
