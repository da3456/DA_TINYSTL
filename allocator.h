#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_

#include <cstddef>
#include "construct.h"

namespace mystl
{
    template <typename T>
    typename std::remove_reference<T>::type &&move(T &&arg) noexcept
    {
        return static_cast<typename std::remove_reference<T>::type &&>(arg);
    }

    template <typename T>
    T &&forward(typename std::remove_reference<T>::type &arg) noexcept
    {
        return static_cast<T &&>(arg);
    }

    template <typename T>
    class allocator_
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
        static void construct(T *ptr, Args &&...args);

        static void destroy(T *ptr);
        static void destroy(T *first, T *last);
    };

    template <typename T>
    T *allocator_<T>::allocate()
    {
        return static_cast<T *>(::operator new(sizeof(T)));
    }

    template <typename T>
    T *allocator_<T>::allocate(size_t n)
    {
        if (n == 0)
            return nullptr;
        return static_cast<T *>(::operator new(n * sizeof(T)));
    }

    template <typename T>
    void allocator_<T>::deallocate(T *ptr)
    {
        if (ptr == nullptr)
            return;
        ::operator delete(ptr);
    }

    template <typename T>
    void allocator_<T>::construct(T *ptr)
    {
        mystl::construct(ptr);
    }

    template <typename T>
    void allocator_<T>::construct(T *ptr, const T &value)
    {
        mystl::construct(ptr, value);
    }

    template <typename T>
    void allocator_<T>::construct(T *ptr, T &&value)
    {
        mystl::construct(ptr, mystl::move(value));
    }

    template <typename T>
    template <typename... Args>
    void allocator_<T>::construct(T *ptr, Args &&...args)
    {
        mystl::construct(ptr, mystl::forward<Args>(args)...);
    }

    template <typename T>
    void allocator_<T>::destroy(T *ptr)
    {
        mystl::destroy(ptr);
    }

    template <typename T>
    void allocator_<T>::destroy(T *first, T *last)
    {
        mystl::destroy(first, last);
    }
}
#endif