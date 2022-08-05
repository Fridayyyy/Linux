//
// Created by 常贵杰 on 2022/8/4.
//
#include <vector>               // std::vector
#include <queue>                // std::queue
#include <memory>               // std::make_shared
#include <stdexcept>            // std::runtime_error
#include <thread>               // std::thread
#include <mutex>                // std::mutex,        std::unique_lock
#include <condition_variable>   // std::condition_variable
#include <future>               // std::future,       std::packaged_task
#include <functional>           // std::function,     std::bind
#include <utility>
#include <iostream>
using namespace std;

int fn(int){
    return int();
}

template<class T,class X>;
auto t = [](T,X) -> result_of<T(X)>::type{
    typedef result_of<T(X)>::type A;
    cout<<A<<endl;
    return A;
};
int main(){

    return 0;
};

