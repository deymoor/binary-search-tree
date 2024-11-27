#pragma once
#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <memory>
#include <utility>

namespace BinarySearchTree {

    enum Traversal {
        preorder = 0,
        inorder,
        postorder
    };

    struct BaseNode {
        BaseNode* left = nullptr;
        BaseNode* right = nullptr;
        BaseNode* parent = nullptr;
    };

    template <typename T>
    struct Node : BaseNode {
        Node(const T& value): value(value) {};
        T value;
    };

    template <typename Key, Traversal traversal,
            typename Compare = std::less<Key>,
            typename Allocator = std::allocator<Key>>
    class Bst;

    template<Traversal traversal>
    const BaseNode* GetNextNode(const BaseNode* current);

    template<>
    inline const BaseNode* GetNextNode<preorder>(const BaseNode* current) {
        if (current->left) {
            current = current->left;
        } else if (current->right) {
            current = current->right;
        } else {
            while (current->parent) {
                if (current->parent->left == current && current->parent->right) {
                    if (current->parent->parent == nullptr) {
                        current = current->parent;
                    } else {
                        current = current->parent->right;
                    }
                    break;
                }
                current = current->parent;
            }
        }
        return current;
    }

    template<>
    inline const BaseNode* GetNextNode<inorder>(const BaseNode* current) {
        if (current->right) {
            current = current->right;
            while (current->left) {
                current = current->left;
            }
        } else {
            while (current->parent) {
                if (current->parent->left == current) {
                    current = current->parent;
                    break;
                }
                current = current->parent;
            }
        }
        return current;
    }

    template<>
    inline const BaseNode* GetNextNode<postorder>(const BaseNode* current) {
        if (current->parent->parent == nullptr) {
            current = current->parent;
        }
        else if (current->parent->left == current && current->parent->right) {
            current = current->parent->right;
            while (current->left || current->right) {
                while (current->left) {
                    current = current->left;
                }
                while (current->right) {
                    current = current->right;
                }
            }
        } else {
            current = current->parent;
        }
        return current;
    }

    template<Traversal traversal>
    const BaseNode* GetPrevNode(const BaseNode* current);

    template<>
    inline const BaseNode* GetPrevNode<preorder>(const BaseNode* current) {
        if (!current->parent) {
            while (current->right || current->left) {
                if (current->right) {
                    current = current->right;
                    continue;
                }
                current = current->left;
            }
        } else if (current->parent->left && current->parent->right == current) {
            current = current->parent->left;
            while (current->right || current->left) {
                if (current->right) {
                    current = current->right;
                    continue;
                }
                current = current->left;
            }
        } else {
            current = current->parent;
        }
        return current;
    }

    template<>
    inline const BaseNode* GetPrevNode<inorder>(const BaseNode* current) {
        if (!current->parent) {
            while (current->right) {
                current = current->right;
            }
        } else if (current->left) {
            current = current->left;
            while (current->right || current->left) {
                if (current->right) {
                    current = current->right;
                    continue;
                }
                current = current->left;
            }
        } else {
            while (current->parent) {
                if (current->parent->right == current) {
                    current = current->parent;
                    break;
                }
                current = current->parent;
            }
        }
        return current;
    }

    template<>
    inline const BaseNode* GetPrevNode<postorder>(const BaseNode* current) {
        if (current->right) {
            current = current->right;
        } else {
            while (current->parent) {
                if (current->parent->left && current->parent->left != current) {
                    current = current->parent->left;
                    break;
                }
                current = current->parent;
            }
        }
        return current;
    }

    template <typename T, Traversal traversal,
            typename Compare, typename Allocator>
    class BaseIterator {
    public:
        using pointer = const BaseNode*;
        using reference = T&;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;

        BaseIterator(const BaseNode* ptr): current(ptr) {};
        BaseIterator(const BaseIterator&) = default;
        BaseIterator& operator=(const BaseIterator&) = default;

        bool operator==(const BaseIterator& other) {
            return current == other.current;
        }

        bool operator!=(const BaseIterator& other) {
            return !(*this == other);
        }

        reference operator*() {
            return static_cast<Node<T>*>(const_cast<BaseNode*>(current))->value;
        }

        pointer operator->() {
            return current;
        }

        BaseIterator& operator++() {
            current = GetNextNode<traversal>(current);
            return *this;
        }

        BaseIterator& operator--() {
            current = GetPrevNode<traversal>(current);
            return *this;
        }

        BaseIterator& operator++(int) {
            BaseIterator copy = *this;
            operator++();
            return copy;
        }
    private:
        pointer current;
        friend class Bst<T, traversal, Compare, Allocator>;
    };


    template <typename Key, Traversal traversal,
            typename Compare, typename Allocator>
    class Bst {
    public:
        using key_type = Key;
        using mapped_type = Key;
        using value_type = Key;
        using key_compare = Compare;
        using value_compare = key_compare;

        using reference = Key&;
        using const_reference = const Key&;
        using const_iterator = BaseIterator<Key, traversal, Compare, Allocator>;
        using iterator = const_iterator;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using difference_type = std::ptrdiff_t;
        using size_type = size_t;

        using AllocType = typename std::allocator_traits<Allocator>::template rebind_alloc<Node<Key>>;
        using AllocTraits = typename std::allocator_traits<AllocType>;

        explicit Bst(const AllocType& alloc = AllocType()): alloc_(alloc) {};

        explicit Bst(const Compare& comp,
         const AllocType& alloc = AllocType()): alloc_(alloc), comp_(comp) {};

        Bst(Bst& other): sz_(other.sz_), alloc_(AllocTraits::select_on_container_copy_construction(other.alloc_)) {
            BaseNode* current_other = &other.end_;
            BaseNode* end_other = &other.end_;
            BaseNode* current = &end_;
            while (end_other->right) {
                end_other = end_other->right;
            }
            while (current_other != end_other) {
                if (current_other->left) {
                    current_other = current_other->left;
                    Node<Key>* node = static_cast<Node<Key>*>(current->left);
                    Node<Key>* node_other = static_cast<Node<Key>*>(current_other);
                    node = AllocTraits::allocate(alloc_, 1);
                    AllocTraits::construct(alloc_, node, node_other->value);
                    node->parent = current;
                    current->left = node;
                    if (current->parent == nullptr) {
                        current->right = node;
                    }
                    current = node;
                } else if (current_other->right) {
                    current_other = current_other->right;
                    Node<Key>* node = static_cast<Node<Key>*>(current->right);
                    Node<Key>* node_other = static_cast<Node<Key>*>(current_other);
                    node = AllocTraits::allocate(alloc_, 1);
                    AllocTraits::construct(alloc_, node, node_other->value);
                    node->parent = current;
                    current->right = node;
                    current = node;
                } else {
                    while (current_other->parent) {
                        if (current_other->parent->left == current_other && current_other->parent->right) {
                            if (current_other->parent->parent == nullptr) {
                                current_other = current_other->parent;
                            } else {
                                current = current->parent;
                                current_other = current_other->parent->right;
                                Node<Key>* node = static_cast<Node<Key>*>(current->right);
                                Node<Key>* node_other = static_cast<Node<Key>*>(current_other);
                                node = AllocTraits::allocate(alloc_, 1);
                                AllocTraits::construct(alloc_, node, node_other->value);
                                node->parent = current;
                                current->right = node;
                                current = node;
                            }
                            break;
                        }
                        current_other = current_other->parent;
                        current = current->parent;
                    }
                }
            }
        }

        template<typename InputIterator>
        Bst(InputIterator first, InputIterator second,
         const Compare& comp = std::less<int>(),
         const AllocType& alloc = AllocType()): alloc_(alloc), comp_(comp) {
            insert(first, second);
        }

        Bst(std::initializer_list<value_type> lst,
         const Compare& comp = std::less<int>(),
         const AllocType& alloc = AllocType()): alloc_(alloc), comp_(comp) {
            insert(lst);
        }

        Bst& operator=(Bst& other) {
            clear();
            sz_ = other.sz_;
            if (AllocTraits::propagate_on_container_copy_assignment::value) {
                alloc_ = other.alloc_;
            }
            BaseNode* current_other = &other.end_;
            BaseNode* end_other = &other.end_;
            BaseNode* current = &end_;
            while (end_other->right) {
                end_other = end_other->right;
            }
            while (current_other != end_other) {
                if (current_other->left) {
                    current_other = current_other->left;
                    Node<Key>* node = static_cast<Node<Key>*>(current->left);
                    Node<Key>* node_other = static_cast<Node<Key>*>(current_other);
                    node = AllocTraits::allocate(alloc_, 1);
                    AllocTraits::construct(alloc_, node, node_other->value);
                    node->parent = current;
                    current->left = node;
                    if (current->parent == nullptr) {
                        current->right = node;
                    }
                    current = node;
                } else if (current_other->right) {
                    current_other = current_other->right;
                    Node<Key>* node = static_cast<Node<Key>*>(current->right);
                    Node<Key>* node_other = static_cast<Node<Key>*>(current_other);
                    node = AllocTraits::allocate(alloc_, 1);
                    AllocTraits::construct(alloc_, node, node_other->value);
                    node->parent = current;
                    current->right = node;
                    current = node;
                } else {
                    while (current_other->parent) {
                        if (current_other->parent->left == current_other && current_other->parent->right) {
                            if (current_other->parent->parent == nullptr) {
                                current_other = current_other->parent;
                            } else {
                                current = current->parent;
                                current_other = current_other->parent->right;
                                Node<Key>* node = static_cast<Node<Key>*>(current->right);
                                Node<Key>* node_other = static_cast<Node<Key>*>(current_other);
                                node = AllocTraits::allocate(alloc_, 1);
                                AllocTraits::construct(alloc_, node, node_other->value);
                                node->parent = current;
                                current->right = node;
                                current = node;
                            }
                            break;
                        }
                        current_other = current_other->parent;
                        current = current->parent;
                    }
                }
            }
            return *this;
        }

        Bst& operator=(std::initializer_list<value_type> lst) {
            clear();
            for (auto i : lst) {
                insert(i);
            }
            return *this;
        }

        bool operator==(const Bst& other) const {
            return sz_ == other.sz_ && std::equal(begin(), end(), other.begin(), other.end());
        }

        bool operator!=(const Bst& other) const {
            return !(*this == other);
        }

        void swap(Bst& other) {
            std::swap(end_, other.end_);
            std::swap(sz_, other.sz_);
            if (AllocTraits::propagate_on_container_swap::value) {
                std::swap(alloc_, other.alloc_);
            }
        }

        size_type size() {
            return sz_;
        }

        size_type max_size() {
            return std::numeric_limits<size_t>::max() / sizeof(Key);
        }

        bool empty() {
            return !sz_;
        }

        iterator begin() {
            if (end_.left == nullptr) {
                return &end_;
            }
            else if (traversal == preorder) {
                return FindPreorderBegin();
            } else if (traversal == inorder) {
                return FindInorderBegin();
            }
            return FindPostorderBegin();
        }

        iterator end() {
            return &end_;
        }

        const_iterator begin() const {
            if (end_.left == nullptr) {
                return &end_;
            }
            else if (traversal == preorder) {
                return FindPreorderBegin();
            } else if (traversal == inorder) {
                return FindInorderBegin();
            }
            return FindPostorderBegin();
        }

        const_iterator end() const {
            return &end_;
        }

        const_iterator cbegin() const {
            if (end_.left == nullptr) {
                return &end_;
            }
            else if (traversal == preorder) {
                return FindPreorderBegin();
            } else if (traversal == inorder) {
                return FindInorderBegin();
            }
            return FindPostorderBegin();
        }

        const_iterator cend() const {
            return &end_;
        }

        reverse_iterator rbegin() {
            return reverse_iterator(end());
        }

        const_reverse_iterator rbegin() const {
            return reverse_iterator(end());
        }

        reverse_iterator rend() {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rend() const {
            return reverse_iterator(begin());
        }

        const_reverse_iterator crbegin() const {
            return rbegin();
        }

        const_reverse_iterator crend() const {
            return rend();
        }

        std::pair<iterator, bool> insert(const key_type& value) {
            Node<Key>* node = AllocTraits::allocate(alloc_, 1);
            AllocTraits::construct(alloc_, node, value);
            if (end_.left == nullptr) {
                end_.left = node;
                end_.right = node;
                node->parent = &end_;
                ++sz_;
                return {node, true};
            }
            BaseNode* parent = end_.left;
            while (true) {
                if (comp_(node->value, static_cast<Node<Key>*>(parent)->value)) {
                    if (parent->left != nullptr) {
                        parent = parent->left;
                    } else {
                        node->parent = parent;
                        parent->left = node;
                        break;
                    }
                } else if (comp_(static_cast<Node<Key>*>(parent)->value, node->value)) {
                    if (parent->right != nullptr) {
                        parent = parent->right;
                    } else {
                        node->parent = parent;
                        parent->right = node;
                        break;
                    }
                } else {
                    AllocTraits::destroy(alloc_, node);
                    AllocTraits::deallocate(alloc_, node, 1);
                    return {nullptr, false};
                }
            }
            ++sz_;
            return {node, true};
        }

        iterator insert(iterator, value_type value) {
            return insert(value).first;
        }

        template<typename InputIterator>
        void insert(InputIterator first, InputIterator second) {
            while (first != second) {
                insert(*first);
                ++first;
            }
        }

        void insert(std::initializer_list<value_type> lst) {
            for (auto i : lst) {
                insert(i);
            }
        }

        void merge(Bst& other) {
            std::vector<iterator> iterators;
            for (auto i = other.begin(); i != other.end(); ++i) {
                iterators.push_back(i);
            }
            for (auto iter : iterators) {
                if (insert(*iter).second) {
                    erase(iter);
                } 
            }
        }

        iterator find(const key_type& key) {
            if (empty()) {
                return end();
            }
            Node<Key>* current = static_cast<Node<Key>*>(end_.left);
            while (true) {
                if (current->value == key) {
                    return current;
                } else if (current->left && current->value > key) {
                    current = static_cast<Node<Key>*>(current->left);
                } else if (current->right && current->value < key) {
                    current = static_cast<Node<Key>*>(current->right);
                } else {
                    return end();
                }
            }
        }

        iterator lower_bound(const key_type& key) {
            iterator result = &end_;
            auto current = static_cast<Node<Key>*>(end_.left);
            while (current) {
                if (!comp_(current->value, key)) {
                    result = current;
                    current = static_cast<Node<Key>*>(current->left);
                } else {
                    current = static_cast<Node<Key>*>(current->right);
                }
            }
            return iterator(result);
        }

        const_iterator lower_bound(const key_type& key) const {
            iterator result = &end_;
            auto current = static_cast<Node<Key>*>(end_.left);
            while (current) {
                if (!comp_(current->value, key)) {
                    result = current;
                    current = static_cast<Node<Key>*>(current->left);
                } else {
                    current = static_cast<Node<Key>*>(current->right);
                }
            }
            return const_iterator(result);
        }

        iterator upper_bound(const key_type& key) {
            iterator result = &end_;
            auto current = static_cast<Node<Key>*>(end_.left);
            while (current) {
                if (comp_(key, current->value)) {
                    result = current;
                    current = static_cast<Node<Key>*>(current->left);
                } else {
                    current = static_cast<Node<Key>*>(current->right);
                }
            }
            return iterator(result);
        }

        const_iterator upper_bound(const key_type& key) const {
            iterator result = &end_;
            auto current = static_cast<Node<Key>*>(end_.left);
            while (current) {
                if (comp_(key, current->value)) {
                    result = current;
                    current = static_cast<Node<Key>*>(current->left);
                } else {
                    current = static_cast<Node<Key>*>(current->right);
                }
            }
            return const_iterator(result);
        }

        std::pair<iterator, iterator> equal_range(const key_type& key) {
            return {lower_bound(key), upper_bound(key)};
        }

        std::pair<const_iterator, const_iterator> equal_range(const key_type& key) const {
            return {lower_bound(key), upper_bound(key)};
        }

        bool contains(const key_type& key) {
            return find(key) != end();
        }

        size_type count(const key_type& key) {
            return contains(key);
        }

        void clear() {
            const BaseNode* current = FindPostorderBegin();
            while (current != &end_) {
                const BaseNode* next_node = GetNextNode<postorder>(current);
                AllocTraits::destroy(alloc_, static_cast<Node<Key>*>(const_cast<BaseNode*>(current)));
                AllocTraits::deallocate(alloc_, static_cast<Node<Key>*>(const_cast<BaseNode*>(current)), 1);
                std::swap(current, next_node);
            }
            end_.left = nullptr;
            end_.right = nullptr;
            sz_ = 0;
        }

        size_type erase(const key_type& key) {
            bool is_empty = empty();
            iterator next_iter = erase(find(key));
            if (next_iter == end()) {
                if (empty()) {
                    if (is_empty) {
                        return 0;
                    }
                    return 1;
                }
                return 0;
            }
            return 1;
        }

        iterator erase(iterator iter) {
            if (iter == end()) {
                return &end_;
            }
            auto res = GetNextNode<traversal>(iter.current);
            Node<Key>* node = static_cast<Node<Key>*>(const_cast<BaseNode*>(iter.current));
            if (!node->left && !node->right) {
                BaseNode* parent = node->parent;
                if (parent == &end_) {
                    parent->left = nullptr;
                    parent->right = nullptr;
                } else if (parent->left == node) {
                    parent->left = nullptr;
                } else {
                    parent->right = nullptr;
                }

                AllocTraits::destroy(alloc_, node);
                AllocTraits::deallocate(alloc_, node, 1);
                --sz_;
            } else if (!(node->left && node->right) && (node->left || node->right)) {
                BaseNode* parent = node->parent;
                BaseNode* child;
                if (node->left) {
                    child = node->left;
                } else {
                    child = node->right;
                }

                if (parent == &end_) {
                    parent->left = child;
                    parent->right = child;
                } else if (parent->left == node) {
                    parent->left = child;
                } else {
                    parent->right = child;
                }
                child->parent = parent;

                AllocTraits::destroy(alloc_, node);
                AllocTraits::deallocate(alloc_, node, 1);
                --sz_;
            } else {
                BaseNode* parent = node->parent;
                Node<Key>* min_node = static_cast<Node<Key>*>(node->right);
                while (min_node->left) {
                    min_node = static_cast<Node<Key>*>(min_node->left);
                }

                if (min_node == node->right) {
                    node->left->parent = min_node;

                    if (parent == &end_) {
                        parent->left = min_node;
                        parent->right = min_node;
                    } else if (parent->left == node) {
                        parent->left = min_node;
                    } else {
                        parent->right = min_node;
                    }

                    min_node->parent = node->parent;
                    min_node->left = node->left;
                    node->right = min_node->right;
                    min_node->right = node;
                    node->parent = min_node;
                    node->left = nullptr;
                } else {
                    node->left->parent = min_node;
                    node->right->parent = min_node;

                    if (parent == &end_) {
                        parent->left = min_node;
                        parent->right = min_node;
                    } else if (parent->left == node) {
                        parent->left = min_node;
                    } else {
                        parent->right = min_node;
                    }

                    BaseNode* min_node_parent = min_node->parent;
                    if (min_node_parent->left == min_node) {
                        min_node_parent->left = node;
                    } else if (min_node_parent->right == min_node) {
                        min_node_parent->right = node;
                    }
                    
                    if (min_node->right) {
                        min_node->right->parent = node;
                    }

                    std::swap(min_node->left, node->left);
                    std::swap(min_node->right, node->right);
                    std::swap(min_node->parent, node->parent);
                }
                erase(node);
            }
            return res;
        }

        iterator erase(iterator first, iterator second) {
            std::vector<iterator> iterators;
            while (first != second) {
                iterators.push_back(first);
                ++first;
            }
            for (auto iter : iterators) {
                erase(iter);
            }
            return second;
        }

        AllocType get_allocator() {
            return alloc_;
        }

        key_compare key_comp() {
            return comp_;
        }

        value_compare value_comp() {
            return comp_;
        }

        ~Bst() {
            clear();
        }
    private:
        const BaseNode* FindPreorderBegin() const {
            return end_.left;
        }

        const BaseNode* FindInorderBegin() const {
            const BaseNode* current = &end_;
            while (current->left) {
                current = current->left;
            }
            return current;
        }

        const BaseNode* FindPostorderBegin() const {
            const BaseNode* current = &end_;
            while (current->left || current->right) {
                if (current->left) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
            return current;
        }

        BaseNode end_;
        size_t sz_ = 0;

        AllocType alloc_;
        Compare comp_;
    };

} // namespace BinarySearchTree
