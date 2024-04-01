#include <iostream>
#include "allocator.h"
#include "reverse_iterator.h"

#define len0 9

template <typename T>
class vector
{
public:
    typedef T value_type;
    typedef T *iterator;
    T *begin_, *end_, *cap_;
    typedef allocator<T> allocator_type;

public:
    vector()
    {
        begin_ = allocator_type::allocate(); // to be completed
        end_ = begin_;
        cap_ = begin_ + len0;
    }

    vector(size_t n, const value_type &val = value_type())
    {
        size_t init_size = n > len0 ? n : len0;
        begin_ = allocator_type::allocate(init_size);
        end_ = begin_ + n;
        cap_ = begin_ + init_size;
        for (size_t i = 0; i < n; i++)
        {
            allocator_type::construct(begin_ + i, val);
        }
    }

    vector(iterator first, iterator last) noexcept
    {
        range_init(first, last);
    }
    
    vector(const vector &x)
    {
        size_t xcap = x.cap_ - x.begin_;
        size_t xsize = x.end_ - x.begin_;

        begin_ = allocator_type::allocate(x.cap_ - x.begin_);
        end_ = begin_ + xsize;
        cap_ = begin_ + xcap;

        for (int i = 0; i < xsize; i++)
        {
            allocator_type::construct(begin_ + i, *(x.begin_ + i));
        }
    }

    vector(std::initializer_list<value_type> il)
    {
        range_init(il.begin(), il.end());
    }

    ~vector()
    {
        allocator_type::destroy(begin_, end_);
        allocator_type::deallocate(begin_);

        begin_ = nullptr;
        end_ = nullptr;
        cap_ = nullptr;
    }

    void pswap(iterator &a, iterator &b)
    {
        iterator temp = a;
        a = b;
        b = temp;
    }

    void swap(vector<T> &tmp)
    {
        pswap(begin_, tmp.begin_);
        pswap(end_, tmp.end_);
        pswap(cap_, tmp.cap_);
    }

    template <typename iter>
    void range_init(iter first, iter last)
    {
        begin_ = allocator_type::allocate(last - first);
        end_ = begin_ + (last - first);
        cap_ = end_;

        if (cap_ - begin_ >= last - first)
        {
            T *cur = begin_;
            for (; first != last; cur++, first++)
            {
                allocator_type::construct(cur, *first);
            }
            end_ = cur;
        }
        else
        {
            vector<value_type> temp(last - first);
            auto cur = temp.begin_;
            for (; first != last; cur++, first++)
            {
                allocator_type::construct(cur, *first);
            }
            temp.end_ = cur;
            swap(temp);
        }
    }

    void assign(iterator first, iterator last)
    {
        clear();
        range_init(first, last);
    }

    void assign(size_t n, const value_type &val)
    {
        vector<value_type> temp(n, val);
        swap(temp);
    }

    void assign(std::initializer_list<value_type> il)
    {
        range_init(il.begin(), il.end());
    }

    value_type &at(size_t n)
    {
        return *(begin_ + n);
    }

    const value_type &at(size_t n) const
    {
        return *(begin_ + n);
    }

    value_type &back()
    {
        return *(end_ - 1);
    }

    const value_type &back() const
    {
        return *(end_ - 1);
    }

    iterator begin() noexcept
    {
        return begin_;
    }

    const iterator begin() const noexcept
    {
        return begin_;
    }

    size_t capacity()
    {
        return cap_ - begin_;
    }

    const iterator cbegin() const noexcept
    {
        return begin_;
    }

    const iterator cend() const noexcept
    {
        return end_;
    }

    void clear() noexcept
    {
        allocator_type::destroy(begin_, end_);
        end_ = begin_;
    }

    const reverse_iterator_<value_type> rbegin() const noexcept{
        return reverse_iterator_<value_type>(end());
    }

    const reverse_iterator_<value_type> rend() const noexcept{
        return reverse_iterator_<value_type>(begin());
    }

    value_type *data() noexcept
    {
        return begin_;
    }

    const value_type *data() const noexcept
    {
        return begin_;
    }

    template <typename... Args>
    iterator emplace(const iterator position, Args &&...args)
    {
        if (end_ < cap_)
        {
            for (iterator i = end_; i != position; i--)
            {
                allocator_type::construct(i, *(i - 1));
            }
            end_ = end_ + 1;
            allocator_type::construct(position, args...);
            return position;
        }
        else
        {
            size_t len = cap_ - begin_;
            vector<value_type> tmp(len * 2);
            iterator cur_ = tmp.begin_;

            for (iterator i = begin_; i != position; i++, cur_++)
            {
                allocator_type::construct(cur_, *i);
            }
            allocator_type::construct(cur_, args...);
            cur_++;
            for (iterator i = position; i != end_; i++, cur_++)
            {
                allocator_type::construct(cur_, *i);
            }
            tmp.end_ = cur_;
            swap(tmp);
            return position;
        }
    }
    
    template <typename... Args>
    void emplace_back(Args &&...args)
    {
        if (end_ != cap_)
        {
            allocator_type::construct(end_, args...);
            end_++;
        }
        else
        {
            size_t len = cap_ - begin_;
            vector<value_type> tmp(len * 2);
            iterator cur_ = tmp.begin_;

            for (iterator i = begin_; i != end_; i++, cur_++)
            {
                allocator_type::construct(cur_, *i);
            }
            allocator_type::construct(cur_, args...);
            tmp.end_ = cur_ + 1;
            swap(tmp);
        }
    }

    bool empty() const noexcept
    {
        return begin_ == end_;
    }

    iterator end() noexcept
    {
        return end_;
    }

    const iterator end() const noexcept
    {
        return end_;
    }

    iterator erase(const iterator position)
    {
        for (iterator i = position; i != end_; i++)
        {
            allocator_type::construct(i, *(i + 1));
        }
        end_ = end_ - 1;

        return position;
    }

    iterator erase(const iterator first, const iterator last)
    {
        iterator cur_ = last;
        size_t len = last - first;
        for (; cur_ != end_; cur_++)
        {
            allocator_type::construct((cur_ - len), *cur_);
        }
        end_ -= len;

        return first;
    }

    value_type &front()
    {
        return *begin_;
    }

    const value_type &front() const
    {
        return *begin_;
    }

    // get_allocator
    iterator insert(iterator position, const value_type &val)
    {
        // std::cout<<"position: "<<position<<" ,val: "<<val.a<<" "<<val.b<<" , begin:"<<begin_<<", end:"<<end_<<std::endl;
        if (end_ < cap_)
        {
            for (iterator i = end_; i != position; i--)
            {
                allocator_type::construct(i, *(i - 1));
            }
            end_ = end_ + 1;
            allocator_type::construct(position, val);
        }
        else
        {
            size_t len = cap_ - begin_;
            vector<value_type> tmp(len * 2);
            iterator cur_ = tmp.begin_;

            for (iterator i = begin_; i != position; i++, cur_++)
            {
                allocator_type::construct(cur_, *i);
            }
            allocator_type::construct(cur_, val);
            iterator ptemp = cur_;
            cur_++;
            for (iterator i = position; i != end_; i++, cur_++)
            {
                allocator_type::construct(cur_, *i);
            }
            tmp.end_ = cur_;
            swap(tmp);
            position = ptemp;
        }

        // std::cout<<"begin######"<<std::endl;
        // for (iterator i = begin_; i != end_; i++)
        // {
        //     std::cout << i->a << " " << i->b << std::endl;
        // }
        // std::cout<<"end######"<<std::endl;

        return position;
    }

    iterator insert(const iterator position, size_t n, const value_type &val)
    {
        iterator position_now = position;
        for (size_t i = 0; i < n; i++)
        {
            position_now = insert(position_now, val);
        }
        return position_now;
    }

    size_t max_size() const noexcept
    {
        return cap_ - begin_;
    }

    value_type &operator[](size_t n)
    {
        return *(begin_ + n);
    }

    const value_type &operator[](size_t n) const
    {
        return *(begin_ + n);
    }

    vector &operator=(const vector &x)
    {
        vector<value_type> temp(x);
        swap(temp);

        return *this;
    }

    vector &operator=(const vector &&x)
    {
        vector<value_type> temp(x);
        swap(temp);

        return *this;
    }

    vector &operator=(std::initializer_list<value_type> li)
    {
        range_init(li.begin(), li.end());

        return *this;
    }

    void pop_back()
    {
        if (!empty())
        {
            end_--;
        }
    }

    void push_back(const value_type &val)
    {
        insert(end_, val);
    }

    void shrink_to_fit()
    {
        vector<value_type> tmp(begin_, end_);
        swap(tmp);
    }

    size_t size() const noexcept
    {
        return end_ - begin_;
    }
};

template <typename aT, typename bT>
class myclass
{
public:
    myclass()
    {
        a = 0;
        b = '0';
    }
    myclass(aT aa, bT bb)
    {
        a = aa;
        b = bb;
    }
    ~myclass(){}
public:
    aT a;
    bT b;

    // 声明迭代器所需的类型别名
    using value_type = aT;
    using difference_type = std::ptrdiff_t;
    using pointer = aT *;
    using reference = aT &;
    using iterator_category = std::forward_iterator_tag;
};

// template <typename ForwardIter>
// void printvalue(ForwardIter* point){
//     bool bvalue = std::is_trivially_destructible<ForwardIter>::value;
//     std::cout << bvalue << std::endl;
// }

// template <int a, int b>
// void fun(std::false_type){
//     std::cout << "false_type !" <<std::endl;
// }

// template <int a, int b>
// void fun(std::true_type){
//     std::cout << "true_type !" <<std::endl;
// }

// template <int a = 0, int b = 0>
// void check() {
//     fun<a,b>(std::integral_constant<bool, (a==b)>{});
// }

int main(void)
{
    using namespace std;

    myclass<int, char> mcl(1, 'a');
    myclass<int, char> ssll(100, 'g');
    myclass<int, char> scl(9, 'e');

    vector<myclass<int,char>> dd(3,mcl);
    vector<myclass<int,char>> da{mcl,ssll,scl};
    //da = dd;

    for (vector<myclass<int,char>>::iterator i = da.begin(); i != da.end(); i++)
    {
        std::cout<<i - da.begin_<<" :" << i->a << " " << i->b << std::endl;
    }
    cout << "size : "<< da.size() << " , max_size : "<< da.max_size() <<endl;
    std::cout << "*******" << std::endl;
    
    //cout<< da[0].a<<endl;
    da.shrink_to_fit();

    for (auto i = da.begin(); i != da.end(); i++)
    {
        std::cout << i - da.begin_<<" :" << i->a << " " << i->b << std::endl;
    }
    cout << "size : "<< da.size() << " , max_size : "<< da.max_size() <<endl;

    for(reverse_iterator_<myclass<int, char>> i = da.rbegin();i!=da.rend();++i){
        cout << (*i).a << " " << (*i).b <<endl;
    }

    return 0;
}

