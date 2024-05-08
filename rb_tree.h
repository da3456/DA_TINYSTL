#ifndef _RB_TREE_H_
#define _RB_TREE_H_

#include <iostream>
#include "allocator.h"
#include "construct.h"
#include "reverse_iterator.h"
#include <cstddef>

namespace mystl
{
    // 声明make_pair和pair
    template <typename first_type, typename second_type>
    class pair;

    template <typename T1, typename T2>
    pair<T1, T2> make_pair(T1 key, T2 value);

    static constexpr bool rb_tree_red = false;
    static constexpr bool rb_tree_black = true;

    // rb tree node design...
    template <typename T>
    class rb_tree_node
    {
    public:
        typedef rb_tree_node<T> *node_ptr;

        typedef T value_type;

        node_ptr parent;
        node_ptr left;
        node_ptr right;

        bool color;

        value_type value;

        friend std::ostream &operator<<(std::ostream &os, node_ptr ptr)
        {
            if (ptr != nullptr)
            {
                if (ptr->color == true)
                    os << " node_ptr->color : "
                       << "black"
                       << " , " << ptr->value;
                else
                    os << " node_ptr->color : "
                       << "red"
                       << " , " << ptr->value;
            }
            else
            {
                os << " ptr = nullptr, it's null node ";
            }
            return os;
        }

        node_ptr get_node_ptr()
        {
            return this;
        }

        node_ptr get_node_ref()
        {
            return &*this;
        }
    };

    // rb_tree iterator
    template <typename T>
    class rb_tree_iterator
    {
    public:
        typedef rb_tree_iterator<T> iterator;
        typedef typename rb_tree_node<T>::node_ptr node_ptr;
        node_ptr node;

        // construct function
        rb_tree_iterator() : node(nullptr) {}
        rb_tree_iterator(node_ptr x) { node = x; }
        rb_tree_iterator(const iterator &rhs) { node = rhs.node; }

        void inc()
        { // 先不考虑只有一个根节点的情况
            if (!(node->parent->parent == node && node->color == rb_tree_red))
            {
                if (node->right != nullptr)
                {
                    node = rb_tree_min(node->right);
                }
                else
                {
                    while (!rb_tree_is_lchild(node) && !(node->parent->parent == node && node->color == rb_tree_red))
                    {
                        node = node->parent;
                    }
                    if (rb_tree_is_lchild(node) && !(node->parent->parent == node && node->color == rb_tree_red))
                    {
                        node = node->parent;
                    }
                }
            }
        }

        void dec()
        {
            if (node->left != nullptr)
            {
                node = rb_tree_max(node->left);
            }
            else
            {
                while (rb_tree_is_rchild(node))
                {
                    node = node->parent;
                }
                if (rb_tree_is_rchild(node))
                {
                    node = node->parent;
                }
            }
        }

        bool operator==(const rb_tree_iterator &rhs) { return node == rhs.node; }
        bool operator!=(const rb_tree_iterator &rhs) { return node != rhs.node; }
        typename rb_tree_node<T>::value_type &operator*() const { return node->value; }
        typename rb_tree_node<T>::value_type *operator->() const { return &(operator*()); }

        iterator operator+(int n)
        {
            for (int i = 0; i < n; i++)
            {
                operator++();
            }
            return *this;
        }

        iterator operator-(int n)
        {
            for (int i = 0; i < n; i++)
            {
                operator++();
            }
            return *this;
        }

        void operator=(const iterator &rhs)
        {
            node = rhs.node;
        }

        iterator &operator++()
        {
            inc();
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp(*this);
            inc();
            return tmp;
        }

        iterator &operator--()
        {
            dec();
            return *this;
        }

        iterator operator--(int)
        {
            iterator tmp(*this);
            dec();
            return tmp;
        }

        friend std::ostream &operator<<(std::ostream &os, iterator iter)
        {
            os << iter.node;

            return os;
        }
    };

    template <typename T>
    class rb_tree_reverse_iterator
    {
    public:
        typedef rb_tree_reverse_iterator<T> reverse_iterator;
        typedef typename rb_tree_node<T>::node_ptr node_ptr;
        node_ptr node;

        // construct function
        rb_tree_reverse_iterator() : node(nullptr) {}
        rb_tree_reverse_iterator(node_ptr x) { node = x; }
        rb_tree_reverse_iterator(const reverse_iterator &rhs) { node = rhs.node; }

        void inc()
        { // 先不考虑只有一个根节点的情况
            if (!(node->parent->parent == node && node->color == rb_tree_red))
            {
                if (node->right != nullptr)
                {
                    node = rb_tree_min(node->right);
                }
                else
                {
                    while (!rb_tree_is_lchild(node) && !(node->parent->parent == node && node->color == rb_tree_red))
                    {
                        node = node->parent;
                    }
                    if (rb_tree_is_lchild(node) && !(node->parent->parent == node && node->color == rb_tree_red))
                    {
                        node = node->parent;
                    }
                }
            }
        }

        void dec()
        {
            if (!(node->parent->parent == node && node->color == rb_tree_red))
                if (node->left != nullptr)
                {
                    node = rb_tree_max(node->left);
                }
                else
                {
                    while (rb_tree_is_lchild(node) && !(node->parent->parent == node && node->color == rb_tree_red))
                    {
                        node = node->parent;
                    }
                    if (!rb_tree_is_lchild(node) && !(node->parent->parent == node && node->color == rb_tree_red))
                    {
                        node = node->parent;
                    }
                }
        }

        bool operator==(const rb_tree_reverse_iterator &rhs) { return node == rhs.node; }
        bool operator!=(const rb_tree_reverse_iterator &rhs) { return node != rhs.node; }
        typename rb_tree_node<T>::value_type &operator*() const { return node->value; }
        typename rb_tree_node<T>::value_type *operator->() const { return &(operator*()); }

        reverse_iterator operator+(int n)
        {
            for (int i = 0; i < n; i++)
            {
                operator++();
            }
            return *this;
        }

        reverse_iterator operator-(int n)
        {
            for (int i = 0; i < n; i++)
            {
                operator++();
            }
            return *this;
        }

        void operator=(const reverse_iterator &rhs)
        {
            node = rhs.node;
        }

        reverse_iterator &operator++()
        {
            dec();
            return *this;
        }

        reverse_iterator operator++(int)
        {
            reverse_iterator tmp(*this);
            dec();
            return tmp;
        }

        reverse_iterator &operator--()
        {
            inc();
            return *this;
        }

        reverse_iterator operator--(int)
        {
            reverse_iterator tmp(*this);
            inc();
            return tmp;
        }

        friend std::ostream &operator<<(std::ostream &os, reverse_iterator iter)
        {
            os << iter.node;

            return os;
        }
    };

    // tree algorithm
    template <typename NodePtr>
    NodePtr rb_tree_min(NodePtr x) noexcept
    {
        while (x->left != nullptr)
        {
            x = x->left;
        }
        return x;
    }

    template <typename T>
    T rb_tree_max(T x) noexcept
    {
        while (x->right != nullptr)
        {
            x = x->right;
        }
        return x;
    }

    template <typename T>
    bool rb_tree_is_lchild(T node) noexcept
    {
        return node == node->parent->left;
    }

    template <typename T>
    T rb_tree_next(T node) noexcept
    {
        if (node->right)
        {
            return node->right;
        }
        while (!rb_tree_is_lchild(node))
        {
            node = node->parent;
        }
        return node->parent;
    }

    /*---------------------------------------*\
    |       p                         p       |
    |      / \                       / \      |
    |     x   d    rotate left      y   d     |
    |    / \       ===========>    / \        |
    |   a   y                     x   c       |
    |      / \                   / \          |
    |     b   c                 a   b         |
    \*---------------------------------------*/
    // 左旋，参数一为左旋点，参数二为根节点
    template <typename T>
    void rb_tree_rotate_left(T x, T &root) noexcept
    {
        auto y = x->right;

        x->right = y->left;
        if (x->right)
            x->right->parent = x;

        y->parent = x->parent;
        if (x == root)
            root = y;
        else if (rb_tree_is_lchild(x))
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    /*----------------------------------------*\
    |     p                         p          |
    |    / \                       / \         |
    |   d   x      rotate right   d   y        |
    |      / \     ===========>      / \       |
    |     y   a                     b   x      |
    |    / \                           / \     |
    |   b   c                         c   a    |
    \*----------------------------------------*/
    // 右旋，参数一为右旋点，参数二为根节点
    template <typename T>
    void rb_tree_rotate_right(T x, T &root) noexcept
    {
        auto y = x->left;

        x->left = y->right;
        if (y->right)
            y->right->parent = x;

        y->parent = x->parent;
        if (x == root)
            root = y;
        else if (rb_tree_is_lchild(x))
            x->parent->left = y;
        else
            x->parent->right = y;

        y->right = x;
        x->parent = y;
    }

    // insert rebalance
    template <typename T>
    void rb_tree_insert_rebalance(T x, T &root) noexcept
    {
        x->color = rb_tree_red;
        while (x->parent->color == rb_tree_red && x != root)
        {
            if (rb_tree_is_lchild(x->parent))
            {
                auto uncle = x->parent->parent->right;

                if (uncle != nullptr && uncle->color == rb_tree_red)
                {
                    x->parent->color = rb_tree_black;
                    uncle->color = rb_tree_black;

                    x->parent->parent->color = rb_tree_red;
                    x = x->parent->parent;
                }
                else
                {
                    if (!rb_tree_is_lchild(x))
                    {
                        rb_tree_rotate_left(x->parent, root);
                        x = x->left;
                    }
                    x->parent->color = rb_tree_black;
                    x->parent->parent->color = rb_tree_red;
                    rb_tree_rotate_right(x->parent->parent, root);
                }
            }
            else
            {
                auto uncle = x->parent->parent->left;

                if (uncle != nullptr && uncle->color == rb_tree_red)
                {
                    x->parent->color = rb_tree_black;
                    uncle->color = rb_tree_black;

                    x->parent->parent->color = rb_tree_red;
                    x = x->parent->parent;
                }
                else
                {
                    if (rb_tree_is_lchild(x))
                    {
                        rb_tree_rotate_right(x->parent, root);
                        x = x->right;
                    }
                    x->parent->color = rb_tree_black;
                    x->parent->parent->color = rb_tree_red;
                    rb_tree_rotate_left(x->parent->parent, root);
                }
            }
        }
        if (x == root)
            x->color = rb_tree_black;
    }

    // delete rebalance
    template <typename T>
    void rb_tree_erase_rebalance(T z, T &root, T &leftmost, T &rightmost)
    {
        T x, y;
        // 先执行正常的树删除节点操作
        if (z->left == nullptr || z->right == nullptr)
        {
            y = z;
        }
        else
        {
            T node = z;
            if (!(node->parent->parent == node && node->color == rb_tree_red))
            {
                if (node->right != nullptr)
                {
                    node = rb_tree_min(node->right);
                }
                else
                {
                    while (!rb_tree_is_lchild(node) && !(node->parent->parent == node && node->color == rb_tree_red))
                    {
                        node = node->parent;
                    }
                    if (rb_tree_is_lchild(node) && !(node->parent->parent == node && node->color == rb_tree_red))
                    {
                        node = node->parent;
                    }
                }
            }
            y = node;
        }
        if (y->left != nullptr)
        {
            x = y->left;
        }
        else
            x = y->right;

        if (y != z)
        {
            y->left = z->left;
            y->left->parent = y;
            if (y != z->right)
            {
                if (x != nullptr)
                    x->parent = y->parent;
                y->parent->left = x;

                y->right = z->right;
                y->right->parent = y;
            }

            y->parent = z->parent;
            if (z == root)
                root = y;
            else if (rb_tree_is_lchild(z))
                z->parent->left = y;
            else
                z->parent->right = y;

            auto temp = z->color;
            z->color = y->color;
            y->color = temp;

            y = z;
        }
        else
        {
            auto xp = y->parent;
            if (x != nullptr)
                x->parent = y->parent;

            if (y == root)
                root = x;
            else if (rb_tree_is_lchild(y))
                y->parent->left = x;
            else
                y->parent->right = x;

            if (leftmost == z)
                leftmost = x == nullptr ? xp : rb_tree_min(x);
            if (rightmost == z)
                rightmost = x == nullptr ? xp : rb_tree_max(x);
        }

        // 若代替节点color为 black/black
        if (y->color == rb_tree_black)
        {
            while (x != nullptr && x != root && x->color == rb_tree_black)
            {
                if (rb_tree_is_lchild(x))
                {
                    auto brother = x->parent->right;
                    if (brother == nullptr)
                        x = x->parent;
                    else if (brother->color == rb_tree_red) // case 1
                    {
                        x->parent->color = rb_tree_red;
                        brother->color = rb_tree_black;
                        rb_tree_rotate_left(x->parent, root);
                        brother = x->parent->right;
                    }
                    else if (brother->right != nullptr && brother->right->color == rb_tree_red) // case 4
                    {
                        auto uncle = x->parent->parent->right;
                        uncle->color = uncle->parent->color;
                        x->parent->color = rb_tree_black;
                        uncle->right->color = rb_tree_black;
                        rb_tree_rotate_left(x->parent, root);
                        break;
                    }
                    else if (brother->left != nullptr && brother->left->color == rb_tree_red) // case 3
                    {
                        brother->color = rb_tree_red;
                        brother->left->color = rb_tree_black;
                        rb_tree_rotate_right(brother, root);
                        brother = x->parent->right;
                    }
                    else // case 2
                    {
                        brother->color = rb_tree_red;
                        x = x->parent;
                    }
                }
                else
                {
                    auto brother = x->parent->left;
                    if (brother == nullptr)
                        x = x->parent;
                    else if (brother->color == rb_tree_red) // case 1
                    {
                        x->parent->color = rb_tree_red;
                        brother->color = rb_tree_black;
                        rb_tree_rotate_right(x->parent, root);
                        brother = x->parent->left;
                    }
                    else if (brother->left != nullptr && brother->left->color == rb_tree_red) // case 4
                    {
                        auto uncle = x->parent->parent->left;
                        uncle->color = uncle->parent->color;
                        x->parent->color = rb_tree_black;
                        uncle->left->color = rb_tree_black;
                        rb_tree_rotate_right(x->parent, root);
                        break;
                    }
                    else if (brother->left != nullptr && brother->left->color == rb_tree_red) // case 3
                    {
                        brother->color = rb_tree_red;
                        brother->right->color = rb_tree_black;
                        rb_tree_rotate_left(brother, root);
                        brother = x->parent->left;
                    }
                    else // case 2
                    {
                        brother->color = rb_tree_red;
                        x = x->parent;
                    }
                }
            }
            if (x != nullptr)
                x->color = rb_tree_black;
        }
    }

    template <typename T, typename key_compare>
    class rb_tree
    {
    public:
        typedef rb_tree_node<T> node;
        typedef typename rb_tree_node<T>::node_ptr node_ptr;
        typedef allocator_<rb_tree_node<T>> node_allocator;
        typedef allocator_<T> value_allocator;
        typedef rb_tree_iterator<T> iterator;
        typedef rb_tree_reverse_iterator<T> reverse_iterator;

    public:
        node_ptr header_; // header_的父亲存储根节点，左孩子为树的最小值，右孩子为树的最大值。 root的父母节点为header_
        size_t node_count_;
        key_compare key_comp_;

    public:
        void init()
        {
            header_ = node_allocator::allocate();
            header_->color = rb_tree_red;
            header_->parent = nullptr;
            header_->left = nullptr;
            header_->right = nullptr;
            value_allocator::allocate();
            value_allocator::construct(&header_->value);
            node_count_ = 0;
        }
        // 构造函数
        rb_tree()
        {
            init();
        }

        // 复制构造函数
        rb_tree(rb_tree &rhs)
        {
            init();
            header_->parent = rb_tree_node_copy(rhs.header_->parent);
            header_->parent->parent = header_;
            header_->left = rb_tree_min(header_->parent);
            header_->right = rb_tree_max(header_->parent);

            node_count_ = rhs.node_count_;
        }

        node_ptr rb_tree_node_copy(node_ptr root)
        {
            if (root != nullptr)
            {
                node_ptr tmp = copy_node_value(root);

                node_ptr tmpleft = rb_tree_node_copy(root->left);
                tmp->left = tmpleft;
                if (tmpleft != nullptr)
                    tmpleft->parent = tmp;

                node_ptr tmpright = rb_tree_node_copy(root->right);
                tmp->right = tmpright;
                if (tmpright != nullptr)
                    tmpright->parent = tmp;

                return tmp;
            }
            return nullptr;
        }

        node_ptr copy_node_value(node_ptr x)
        {
            node_ptr tmp = node_allocator::allocate();
            tmp->parent = nullptr;
            tmp->right = nullptr;
            tmp->left = nullptr;
            tmp->color = x->color;
            tmp->value = x->value;

            return tmp;
        }

        // 复制赋值构造函数
        rb_tree &operator=(const rb_tree &rhs)
        {
            this->clear_rb_tree();

            header_->parent = rb_tree_node_copy(rhs.header_->parent);
            header_->parent->parent = header_;
            header_->left = rb_tree_min(header_->parent);
            header_->right = rb_tree_max(header_->parent);

            node_count_ = rhs.node_count_;

            return *this;
        }

        // 析构函数
        ~rb_tree()
        {
            clear_rb_tree();
            node_allocator::deallocate(header_);
            header_ = nullptr;
        }
        // 清除红黑树的根节点并设置指针为空，但header_不处理
        void clear_rb_tree()
        {
            clear_rb_tree_node(header_->parent);
            header_->right = nullptr;
            header_->left = nullptr;
            header_->parent = nullptr;
        }

        void clear_rb_tree_node(node_ptr &root)
        {
            if (root != nullptr)
            {
                clear_rb_tree_node(root->left);
                clear_rb_tree_node(root->right);
                destroy_node(root);
                root = nullptr;
            }
        }

        // 迭代器相关，，，
        iterator begin() noexcept
        {
            if (header_->left)
                return iterator(header_->left);
            else
            {
                printf("tree have no value.\n");
                return iterator(header_);
            }
        }

        iterator end() noexcept
        {
            return iterator(header_);
        }

        reverse_iterator rbegin() noexcept
        {
            return reverse_iterator(header_->right);
        }

        reverse_iterator rend() noexcept
        {
            return reverse_iterator(header_);
        }

        // 容量相关操作
        bool empty() const noexcept { return node_count_ == 0; }
        size_t size() const noexcept { return node_count_; }
        size_t max_size() const noexcept { return static_cast<size_t>(-1); }

        // 创建节点和删除节点
        template <typename... Args>
        node_ptr create_new_node(Args &&...args)
        {
            node_ptr tmp = node_allocator::allocate();
            value_allocator::construct(&(tmp->value), args...);
            tmp->left = nullptr;
            tmp->right = nullptr;
            tmp->parent = nullptr;
            tmp->color = rb_tree_red;

            return tmp;
        }

        node_ptr create_new_node(node_ptr copy_node)
        {
            node_ptr tmp = node_allocator::allocate();
            value_allocator::construct(&(tmp->value), copy_node->value);
            tmp->left = nullptr;
            tmp->right = nullptr;
            tmp->parent = nullptr;
            tmp->color = rb_tree_red;

            return tmp;
        }

        node_ptr create_new_node(pair<typename T::first, typename T::second> tmp_pair)
        {
            node_ptr tmp = node_allocator::allocate();
            value_allocator::construct(&(tmp->value), tmp_pair);
            tmp->left = nullptr;
            tmp->right = nullptr;
            tmp->parent = nullptr;
            tmp->color = rb_tree_red;

            return tmp;
        }

        void destroy_node(node_ptr tmp)
        {
            if (tmp != nullptr)
            {
                value_allocator::destroy(&(tmp->value));
                node_allocator::deallocate(tmp);
            }
        }
        // 插入删除相关操作(还未考虑插入值的键相同情况)
        template <typename... Args>
        node_ptr emplace(Args &&...args)
        {
            node_ptr tmp = create_new_node(args...);
            node_ptr x = header_->parent;
            node_ptr y = header_;
            bool val;

            while (x != nullptr)
            {
                y = x;
                val = key_comp_(x->value.key_value, tmp->value.key_value);
                if (val)
                {
                    x = x->right;
                }
                else
                {
                    x = x->left;
                }
            }
            if (x == nullptr && y == header_)
            {
                header_->parent = tmp;
                tmp->color = rb_tree_black;
                tmp->parent = header_;
            }
            else if (val)
            {
                y->right = tmp;
                tmp->parent = y;
            }
            else
            {
                y->left = tmp;
                tmp->parent = y;
            }
            // 平衡操作
            rb_tree_insert_rebalance(tmp, header_->parent);

            header_->right = rb_tree_max(header_->parent);
            header_->left = rb_tree_min(header_->parent);
            node_count_++;

            return tmp;
        }

        template <typename... Args>
        node_ptr emplace_hint(iterator iter, Args &&...args)
        {
            node_ptr iter_node = iter.node, x, y;
            node_ptr tmp = create_new_node(args...);
            bool val;

            // iter_node不是跟节点
            if (rb_tree_is_lchild(iter_node) && key_comp_(tmp->value.key_value, iter_node->parent->value.key_value) ||
                (!rb_tree_is_lchild(iter_node)) && key_comp_(iter_node->parent->value.key_value, tmp->value.key_value))
            {
                x = iter_node;
                y = iter_node->parent;
            }
            else
            {
                x = header_->parent;
                y = header_;
            }

            while (x != nullptr)
            {
                y = x;
                val = key_comp_(x->value.key_value, tmp->value.key_value);
                if (val)
                {
                    x = x->right;
                }
                else
                {
                    x = x->left;
                }
            }
            if (x == nullptr && y == header_)
            {
                header_->parent = tmp;
                tmp->color = rb_tree_black;
                tmp->parent = header_;
            }
            else if (val)
            {
                y->right = tmp;
                tmp->parent = y;
            }
            else
            {
                y->left = tmp;
                tmp->parent = y;
            }
            // 平衡操作
            rb_tree_insert_rebalance(tmp, header_->parent);

            header_->right = rb_tree_max(header_->parent);
            header_->left = rb_tree_min(header_->parent);
            node_count_++;

            return tmp;
        }

        node_ptr insert(node_ptr temp)
        {
            node_ptr tmp = create_new_node(temp);
            node_ptr x = header_->parent;
            node_ptr y = header_;
            bool val;

            while (x != nullptr)
            {
                y = x;
                val = key_comp_(x->value.key_value, tmp->value.key_value);
                if (val)
                {
                    x = x->right;
                }
                else
                {
                    x = x->left;
                }
            }
            if (x == nullptr && y == header_)
            {
                header_->parent = tmp;
                tmp->color = rb_tree_black;
                tmp->parent = header_;
            }
            else if (val)
            {
                y->right = tmp;
                tmp->parent = y;
            }
            else
            {
                y->left = tmp;
                tmp->parent = y;
            }
            // 平衡操作
            rb_tree_insert_rebalance(tmp, header_->parent);

            header_->right = rb_tree_max(header_->parent);
            header_->left = rb_tree_min(header_->parent);
            node_count_++;

            return tmp;
        }

        iterator insert(iterator &tmp_iterator)
        {
            node_ptr tmp = create_new_node(tmp_iterator.node);
            node_ptr x = header_->parent;
            node_ptr y = header_;
            bool val;

            while (x != nullptr)
            {
                y = x;
                val = key_comp_(x->value.key_value, tmp->value.key_value);
                if (val)
                {
                    x = x->right;
                }
                else
                {
                    x = x->left;
                }
            }
            if (x == nullptr && y == header_)
            {
                header_->parent = tmp;
                tmp->color = rb_tree_black;
                tmp->parent = header_;
            }
            else if (val)
            {
                y->right = tmp;
                tmp->parent = y;
            }
            else
            {
                y->left = tmp;
                tmp->parent = y;
            }
            // 平衡操作
            rb_tree_insert_rebalance(tmp, header_->parent);

            header_->right = rb_tree_max(header_->parent);
            header_->left = rb_tree_min(header_->parent);
            node_count_++;

            return iterator(tmp);
        }

        pair<iterator, bool> insert(pair<typename T::first, typename T::second> tmp_pair)
        {
            node_ptr tmp = create_new_node(tmp_pair);
            node_ptr x = header_->parent;
            node_ptr y = header_;
            bool val;

            while (x != nullptr)
            {
                y = x;
                val = key_comp_(x->value.key_value, tmp->value.key_value);
                if (val)
                {
                    x = x->right;
                }
                else
                {
                    x = x->left;
                }
            }
            if (x == nullptr && y == header_)
            {
                header_->parent = tmp;
                tmp->color = rb_tree_black;
                tmp->parent = header_;
            }
            else if (val)
            {
                y->right = tmp;
                tmp->parent = y;
            }
            else
            {
                y->left = tmp;
                tmp->parent = y;
            }
            // 平衡操作
            rb_tree_insert_rebalance(tmp, header_->parent);

            header_->right = rb_tree_max(header_->parent);
            header_->left = rb_tree_min(header_->parent);
            node_count_++;

            return pair<iterator, bool>(iterator(tmp), true);
        }

        void erase(iterator x_iterator)
        {
            rb_tree_erase_rebalance(x_iterator.node, header_->parent, header_->left, header_->right);
            destroy_node(x_iterator.node);
            node_count_--;
        }

        // find函数
        iterator find(typename T::first &key)
        {
            node_ptr y = header_;
            node_ptr x = header_->parent;
            bool is_left, is_right;

            while (x != nullptr)
            {
                y = x;
                is_right = key_comp_(x->value.key_value, key);
                is_left = key_comp_(key, x->value.key_value);
                if (is_left)
                {
                    x = x->left;
                }
                if (is_right)
                {
                    x = x->right;
                }
                if (is_right == false && is_left == false)
                {
                    return iterator(y);
                }
            }
            return iterator(header_);
        }

        iterator find(typename T::first &&key)
        {
            node_ptr y = header_;
            node_ptr x = header_->parent;
            bool is_left, is_right;

            while (x != nullptr)
            {
                y = x;
                is_right = key_comp_(x->value.key_value, key);
                is_left = key_comp_(key, x->value.key_value);
                if (is_left)
                {
                    x = x->left;
                }
                if (is_right)
                {
                    x = x->right;
                }
                if (is_right == false && is_left == false)
                {
                    return iterator(y);
                }
            }
            return iterator(header_);
        }

        iterator lower_bound(typename T::first &&key)
        {
            node_ptr y = header_;
            node_ptr x = header_->parent;
            bool is_left, is_right;

            while (x != nullptr)
            {
                y = x;
                is_right = key_comp_(x->value.key_value, key);
                is_left = key_comp_(key, x->value.key_value);
                if (is_left)
                {
                    x = x->left;
                }
                if (is_right)
                {
                    x = x->right;
                }
                if (is_left == false && is_right == false) // 如果有相同节点
                    return iterator(y);
            }
            if (is_left)
                return iterator(y);
            else
                return ++iterator(y);
        }

        iterator upper_bound(typename T::first &&key)
        {
            node_ptr y = header_;
            node_ptr x = header_->parent;
            bool is_left, is_right;

            while (x != nullptr)
            {
                y = x;
                is_right = key_comp_(x->value.key_value, key);
                is_left = key_comp_(key, x->value.key_value);
                if (is_left)
                {
                    x = x->left;
                }
                if (is_right)
                {
                    x = x->right;
                }
                if (is_left == false && is_right == false) // 如果有相同节点
                    return ++iterator(y);
            }
            if (is_left)
                return iterator(y);
            else
                return ++iterator(y);
        }
    };

    template <typename first_type, typename second_type>
    class pair
    {
    public:
        typedef first_type first;
        typedef second_type second;

        first key_value;
        second mapped_value;

    public:
        pair()
        {
        }
        pair(first key, second mapped)
        {
            key_value = key;
            mapped_value = mapped;
        }

        friend std::ostream &operator<<(std::ostream &os, pair<first_type, second_type> &value)
        {
            os << "{ key_value : " << value.key_value << " , mapped_value : " << value.mapped_value << " } ";

            return os;
        }
        ~pair()
        {
        }
    };

    template <typename T>
    class key_comp_
    {
    public:
        bool operator()(T a, T b)
        {
            return key_compare(a, b);
        }

        bool key_compare(T a, T b)
        {
            if (a < b)
                return true;
            else
                return false;
        }
    };

    template <typename T1, typename T2>
    pair<T1, T2> make_pair(T1 key, T2 value)
    {
        pair<T1, T2> tmp(key, value);
        return tmp;
    }
}
// int main()
// {
//     using namespace mystl;
//     using std::cout;
//     using std::endl;

//     rb_tree<mystl::pair<int, char>, key_comp_<int>> tree;
//     tree.emplace(6, 't');
//     tree.emplace(3, 'a');
//     tree.emplace(44, 's');
//     tree.emplace(10, 't');
//     tree.emplace(8, 'g');

//     rb_tree<mystl::pair<int, char>, key_comp_<int>> tree_copy;
//     tree_copy = tree;
//     for (auto iterate = tree_copy.begin(); iterate != tree_copy.end(); ++iterate)
//     {
//         cout << iterate << endl;
//     }

//     auto ite = tree_copy.begin() + 3;
//     cout << "*************************" << endl;
//     cout << ite.node << endl;
//     tree_copy.erase(ite);
//     cout << "*************************" << endl;

//     for (auto iterate = tree_copy.find(8); iterate != tree_copy.end(); ++iterate)
//     {
//         cout << iterate << endl;
//     }

//     return 0;
// }

#endif