#pragma once

#include <mutex>
#include <memory>
#include <iostream>

template<typename T>
class Singleton
{
public:

    static std::shared_ptr<T> Instance() {
        static std::once_flag init_flag;
        std::call_once(init_flag, [&]() {
            m_instance = std::shared_ptr<T>(new T());
        });
        return m_instance;
    }

    ~Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

protected:

    Singleton() = default;

    static std::shared_ptr<T> m_instance;

};

template<typename T>
std::shared_ptr<T> Singleton<T>::m_instance = nullptr;