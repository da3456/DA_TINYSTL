#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_

#include <cstddef>
#include "construct.h"

template <typename T>
typename std::remove_reference<T>::type&& move(T&& arg) noexcept{
    return static_cast<typename std::remove_reference<T>::type&&>(arg);
}

template <typename T>
T&& forward(typename std::remove_reference<T>::type& arg) noexcept{
    return static_cast<T&&>(arg);
}


template <typename T>
class allocator
{
public:
    static T *allocate();
    static T *allocate(size_t n);

    static void deallocate(T *ptr);
    static void deallocate(T *ptr, size_t n);

    static void construct(T *ptr);
    static void construct(T *ptr, const T &value);
    static void construct(T *ptr, T &&value);

    template <typename... Args>
    static void construct(T *ptr, Args&& ...args);

    static void destroy(T *ptr);
    static void destroy(T *first, T *last);
};

template <typename T>
T *allocator<T>::allocate()
{
    return static_cast<T *>(::operator new(sizeof(T)));
}

template <typename T>
T *allocator<T>::allocate(size_t n)
{
    if (n == 0)
        return nullptr;
    return static_cast<T *>(::operator new(n * sizeof(T)));
}

template <typename T>
void allocator<T>::deallocate(T* ptr){
    if(ptr == nullptr)
        return;
    ::operator delete(ptr);
}

template <typename T>
void allocator<T>::construct(T* ptr){
    ::construct(ptr);
}

template <typename T>
void allocator<T>::construct(T* ptr,const T& value){
    ::construct(ptr,value);
}

template <typename T>
void allocator<T>::construct(T* ptr, T&& value){
    ::construct(ptr,::move(value));
}

template<typename T>
template<typename... Args>
void allocator<T>::construct(T* ptr, Args&& ...args){
    ::construct(ptr, ::forward<Args>(args)...);
}

template <typename T>
void allocator<T>::destroy(T* ptr){
    ::destroy(ptr);
}

template <typename T>
void allocator<T>::destroy(T* first, T* last){
    ::destroy(first, last);
}

#endif