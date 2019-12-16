#pragma once

#include <algorithm>
#include <utility>
#include <vector>

// Flat map. Right now, we construct once and then lookup keys, and that's it.
template <class Key, class T, class Compare = std::less<Key>>
class LBFlatMap {
    using value_type = std::pair<Key, T>;
    using container_type = typename std::vector<value_type>;
    container_type container;
    Compare key_compare;
public:
    using iterator = typename container_type::iterator;
    using const_iterator = typename container_type::const_iterator;
protected:

    class value_compare {
        Compare comp;
    public:
        value_compare(Compare c) : comp(c) {}
        bool operator()(const value_type & i1, const value_type & i2) {
            return comp(i1.first, i2.first);
        }
    };
public:
    LBFlatMap() {}

    template <class Iterator>
    LBFlatMap(Iterator it1, Iterator it2) : container(it1, it2) {
        //must search keys
        std::sort(it1, it2, value_compare());
    }

    void reserve(size_t count) { container.reserve(count); }

    iterator begin() { return container.begin(); }
    const_iterator begin() const { return container.begin(); }
    const_iterator cbegin() const { return container.cbegin(); }

    iterator end() { return container.end(); }
    const_iterator end() const { return container.end(); }
    const_iterator cend() const { return container.cend(); }

    iterator lower_bound(const Key & key) {
        return std::lower_bound(begin(), end(), value_type(key, {}), value_compare(key_compare));
    }

    const_iterator lower_bound(const Key & key) const {
        return std::lower_bound(cbegin(), cend(), value_type(key, {}), value_compare(key_compare));
    }

    iterator find(const Key & key) {
        return lower_bound(key);
    }

    const const_iterator find(const Key & key) const {
        return lower_bound(key);
    }

    std::pair<iterator, bool> insert(std::pair<Key, T> && value) {
        iterator it = lower_bound(value.first);
        if(it != end() && it->first == value.first) {
            return {it, false};
        }
        return {container.insert(it, value), true};
    }

    template <class Iterator>
    void insert(Iterator first, Iterator last) {
        for(Iterator it = first; it != last; it++) {
            insert(*it);
        }
    }
};
