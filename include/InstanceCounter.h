//
//  InstanceCounter.h
//  UDPServer
//
//  Created by roko on 04/05/2019.
//

#ifndef InstanceCounter_h
#define InstanceCounter_h

#include <atomic>

template <typename T>
class InstanceCounter
{
   public:
    static int getCount() { return count; }

   protected:
    ~InstanceCounter() { --count; }

    InstanceCounter() { ++count; }

    InstanceCounter(const InstanceCounter &) { ++count; }

   private:
    static std::atomic<int> count;
};

template <typename T>
std::atomic<int> InstanceCounter<T>::count(0);

#endif /* InstanceCounter_h */
