#ifndef MAP_H_
#define MAP_H_

#include "allocator.h"
#include "rb_tree.h"
#include "reverse_iterator.h"

namespace mystl
{
    template <typename first_T, typename second_T, typename key_compare = mystl::key_comp_<first_T>>
    class map
    {
    public:
        typedef rb_tree<pair<first_T, second_T>, key_compare> rb_tree;
        typedef typename rb_tree::iterator iterator;
        typedef typename rb_tree::reverse_iterator reverse_iterator;
        rb_tree tree;

    public:
        explicit map()
        {
        }
        explicit map(typename rb_tree::iterator &first, typename rb_tree::iterator &last)
        {
            for (auto iter = first; iter != last; ++iter)
            {
                tree.insert(iter);
            }
        }
        explicit map(typename rb_tree::iterator &&first, typename rb_tree::iterator &&last)
        {
            for (auto iter = first; iter != last; ++iter)
            {
                tree.insert(iter);
            }
        }
        explicit map(const map &tmp)
        {
            tree = tmp.tree;
        }
        map(std::initializer_list<pair<first_T, second_T>> il)
        {
            for (auto iter = il.begin(); iter != il.end(); ++iter)
            {
                tree.emplace(iter->key_value, iter->mapped_value);
            }
        }
        ~map() {}
        second_T &at(first_T key)
        {
            iterator iter = tree.find(key);
            if (iter != tree.end())
                return iter.node->value.mapped_value;
            else
                throw std::out_of_range("map does no have no equivalent value.");
        }
        iterator begin()
        {
            return tree.begin();
        }
        iterator end()
        {
            return tree.end();
        }
        reverse_iterator rbegin(){
            return tree.rbegin();
        }
        reverse_iterator rend(){
            return tree.rend();
        }
        void clear() noexcept
        {
            tree.clear_rb_tree();
        }
        size_t count(first_T &key)
        {

            iterator iter = tree.find(key);
            if (iter != tree.end())
                return 1;
            else
                return 0;
        }
        template <typename... Args>
        void emplace(Args &&...args)
        {
            tree.emplace(args...);
        }
        template <typename... Args>
        void emplace_hint(iterator iter, Args &&...args)
        {
            tree.emplace_hint(iter, args...);
        }
        bool empty()
        {
            return tree.empty();
        }
        void erase(iterator iter)
        {
            tree.erase(iter);
        }
        void erase(first_T key)
        {
            iterator iter = tree.find(key);
            erase(iter);
        }
        void erase(iterator iter_first, iterator iter_last)
        {
            for (auto iter = iter_first; iter != iter_last;)
            {
                auto tmp = iter++;
                erase(tmp);
            }
        }
        iterator find(first_T key){
            auto iter = tree.find(key);
            return iter;
        }
        void insert(std::initializer_list<pair<first_T, second_T>> li)
        {
            for (auto iter = li.begin(); iter != li.end(); iter++)
            {
                tree.emplace(iter->key_value, iter->mapped_value);
            }
        }
        void insert(iterator first_iter, iterator last_iter)
        {
            for (auto iter = first_iter; iter != last_iter; iter++)
            {
                tree.insert(iter);
            }
        }
        pair<iterator, bool> insert(pair<first_T, second_T> value)
        {
            return tree.insert(value);
        }
        iterator lower_bound(first_T key_type)
        {
            return tree.lower_bound(mystl::move(key_type));
        }
        size_t max_size() noexcept
        {
            return static_cast<size_t>(-1);
        }
        second_T &operator[](first_T key) noexcept
        {
            try
            {
                return at(key);
            }
            catch(std::out_of_range e){
                tree.emplace(key,second_T());
                return at(key);
            }
        }
        map<first_T,second_T> &operator=(map<first_T,second_T> &tmp){
            tree = tmp.tree;
            return *this;
        }
        map<first_T,second_T> &operator=(map<first_T,second_T> &&tmp){
            tree = tmp.tree;
            return *this;
        }
        map<first_T,second_T> &operator=(std::initializer_list<pair<first_T,second_T>> il){
            for(auto iter = il.begin();iter!=il.end();iter++){
                tree.emplace(iter->key_value,iter->mapped_value);
            }
            return *this;
        }
        size_t size(){
            return tree.node_count_;
        }
        void swap(map<first_T,second_T> &tmp){
            rb_tree tmp_tree = tree;
            tree = tmp.tree;
            tmp.tree = tmp_tree;
        }
        iterator upper_bound(first_T key_type){
            return tree.upper_bound(mystl::move(key_type));
        }
    };

}
class myclass
{
public:
    int x;
    char y;

public:
    myclass()
    {
    }
    myclass(int xx, char yy)
    {
        x = xx;
        y = yy;
    }
    bool operator<(myclass &b)
    {
        return x < b.x;
    }
    friend std::ostream &operator<<(std::ostream &os, myclass &daclass)
    {
        os << "( myclass.x : " << daclass.x << ", myclass.y : " << daclass.y << " )";

        return os;
    }
};


#endif