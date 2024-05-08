#ifndef REVERSE_ITERATOR_H_
#define REVERSE_ITERATOR_H_

namespace mystl
{

    template <typename value_type>
    class reverse_iterator_
    {
    public:
        typedef reverse_iterator_<value_type> iterator_type;
        typedef value_type *iterator;

    private:
        iterator riterator = nullptr;

    public:
        reverse_iterator_(){};
        explicit reverse_iterator_(iterator iter) : riterator(iter) {}
        reverse_iterator_(const iterator_type &re_iter) : riterator(re_iter.riterator) {}

    public:
        iterator base() const
        {
            return riterator;
        }

        value_type &operator*() const
        {
            iterator tmp = riterator;
            return *--tmp;
        }

        iterator operator->() const
        {
            return &(operator*());
        }

        iterator_type &operator++()
        {
            --riterator;
            return *this;
        }

        iterator_type &operator--()
        {
            ++riterator;
            return *this;
        }

        iterator_type &operator+(int n) const
        {
            return iterator_type(riterator - n);
        }

        iterator_type &operator-(int n) const
        {
            return iterator_type(riterator + n);
        }

        iterator_type &operator+=(int n)
        {
            riterator -= n;
            return *this;
        }

        iterator_type &operator-=(int n)
        {
            riterator += n;
            return *this;
        }

        value_type &operator[](int n) const
        {
            return *(*this + n);
        }
    };

    template <typename value_type>
    int operator-(const reverse_iterator_<value_type> &lhs, const reverse_iterator_<value_type> &rhs)
    {
        return rhs.base() - lhs.base();
    }

    template <typename value_type>
    bool operator==(const reverse_iterator_<value_type> &lhs, const reverse_iterator_<value_type> &rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <typename value_type>
    bool operator!=(const reverse_iterator_<value_type> &lhs, const reverse_iterator_<value_type> &rhs)
    {
        return !(lhs == rhs);
    }

    template <typename value_type>
    bool operator<(const reverse_iterator_<value_type> &lhs, const reverse_iterator_<value_type> &rhs)
    {
        return rhs.base() < lhs.base();
    }

    template <typename value_type>
    bool operator<=(const reverse_iterator_<value_type> &lhs, const reverse_iterator_<value_type> &rhs)
    {
        return rhs.base() <= lhs.base();
    }

    template <typename value_type>
    bool operator>(const reverse_iterator_<value_type> &lhs, const reverse_iterator_<value_type> &rhs)
    {
        return rhs > lhs;
    }

    template <typename value_type>
    bool operator>=(const reverse_iterator_<value_type> &lhs, const reverse_iterator_<value_type> &rhs)
    {
        return rhs >= lhs;
    }
}
#endif