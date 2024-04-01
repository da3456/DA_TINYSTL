#ifndef CONSTRUCT_H_
#define CONSTRUCT_H_

#include <new>

template <typename Ty>
void construct(Ty *ptr)
{
    new ((void *)ptr) Ty();
}

template <typename Ty1, typename Ty2>
void construct(Ty1 *ptr, const Ty2 &value)
{
    new ((void *)ptr) Ty1(value);
}

template <class Ty, class... Args>
void construct(Ty *ptr, Args &&...args)
{
    new ((void *)ptr) Ty(args...);
}

template <typename Ty>
void destroy_one(Ty*, std:: true_type){ }

template <typename Ty>
void destroy_one(Ty* pointer, std::false_type){
    if(pointer!=nullptr){
        pointer->~Ty();
    }
}

template <typename FowardIter>
void destroy_cat(FowardIter , FowardIter , std::true_type){

}

template <typename ForwardIter>
void destroy_cat(ForwardIter first,ForwardIter last, std::false_type){
    for(;first!=last;++first){
        destroy(&*first);
    }
}

template <typename Ty>
void destroy(Ty* pointer){
    destroy_one(pointer, std::is_trivially_destructible<Ty>{});
}

template <typename ForwardIter>
void destroy(ForwardIter* first, ForwardIter* last){
    destroy_cat(first, last, std::is_trivially_destructible<ForwardIter>{});
}

#ifndef _MSC_VER
#pragma warning(pop)
#endif

#endif