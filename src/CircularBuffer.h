
#pragma once

#include "CircularBufferIterator.h"

#include <iostream>
#include <memory>
#include <algorithm>
#include <iterator>
#include <type_traits>

template<typename T, typename Alloc = std::allocator<T>>
class CircularBuffer {
public:

    typedef Alloc                                                                   allocator_type;
    typedef std::allocator_traits<allocator_type>                                   alloc_traits;
    typedef T                                                                       value_type;
    typedef alloc_traits::pointer                                                   pointer;
    typedef alloc_traits::const_pointer                                             const_pointer;
    typedef decltype(*pointer{})                                                    reference;
    typedef decltype(*const_pointer{})                                              const_reference;
    typedef alloc_traits::size_type                                                 size_type;
    typedef alloc_traits::difference_type                                           difference_type;
    typedef CircularBufferIterator<pointer, alloc_traits>                           iterator;
    typedef CircularBufferIterator<const_pointer, alloc_traits>                     const_iterator;
    typedef std::reverse_iterator<iterator>                                         reverse_iterator;
    typedef std::reverse_iterator<const_iterator>                                   const_reverse_iterator;


    CircularBuffer() {
        size_ = 0;
        data_ = alloc_traits::allocate(alloc_, size_);
        read_index_ = 1;
        write_index_ = 1;
        elements_count_ = 0;
    }

    explicit CircularBuffer (const value_type& size_buf) {
        size_ = size_buf + 1;
        data_ = alloc_traits::allocate(alloc_, size_);
        read_index_ = 1;
        write_index_ = 1;
        elements_count_ = 0;
    }


    ~CircularBuffer() {
        clear_buf();
        alloc_traits::deallocate(alloc_, data_, size_);
    }

    CircularBuffer(const CircularBuffer& copy_buf) {
        size_ = copy_buf.size_;
        read_index_ = 1;
        write_index_ = 1;
        elements_count_ = 0;
        data_ = alloc_traits::allocate(alloc_, size_);
        for (const auto& el : copy_buf) {
            push_back(el);
        }
    }

    CircularBuffer& operator=(const CircularBuffer& copy_buf) {
        size_ = copy_buf.size_;
        read_index_ = 1;
        write_index_ = 1;
        elements_count_ = 0;
        data_ = alloc_traits::allocate(alloc_, size_);
        for (const auto& el : copy_buf) {
            push_back(el);
        }

        return *this;
    }

    void swap(CircularBuffer& other_buf) {
        std::swap(size_, other_buf.size_);
        std::swap(data_, other_buf.data_);
        std::swap(read_index_, other_buf.read_index_);
        std::swap(write_index_, other_buf.write_index_);
        std::swap(elements_count_, other_buf.elements_count_);
    }

    void push_back(const value_type& number) {
        if (elements_count_ == size_ - 1) {
            pop_front();
            data_[write_index_] = number;
            MoveWrite();
        } else {
            data_[write_index_] = number;
            MoveWrite();
        }
    }

    void pop_front() {
        MoveRead();
    }

    friend bool operator==(const CircularBuffer& first, const CircularBuffer& second) {
        if (first.size_ != second.size_) {
            return false;
        }

        return std::equal(first.begin(), first.end(), second.begin(), second.end());
    }

    friend bool operator!=(const CircularBuffer& first, const CircularBuffer& second) {
        return !(first == second);
    }

    reference operator[](size_type n) {
        return data_[n];
    }

    const_reference operator[](size_type n) const {
        return data_[n];
    }

    reference front() {
        return data_[read_index_];
    }

    reference back() {
        write_index_--;
        int temp = write_index_;
        write_index_++;
        return data_[temp];
    }

    bool empty() {
        return begin() == end();
    }

    size_type max_size() {
        return size_ - 1;
    }

    size_type size() {
        return elements_count_;
    }

    iterator begin() noexcept {
        return iterator(data_, read_index_, size_, read_index_, write_index_);
    }

    iterator end() noexcept {
        return iterator(data_, write_index_, size_, read_index_, write_index_);
    }

    const_iterator begin() const noexcept {
        return const_iterator(data_, read_index_, size_, read_index_, write_index_);
    }

    const_iterator end() const noexcept {
        return const_iterator(data_, write_index_, size_, read_index_, write_index_);
    }

    const_iterator cbegin() const noexcept {
        return const_cast<CircularBuffer const&>(*this).begin();
    }

    const_iterator cend() const noexcept {
        return const_cast<CircularBuffer const&>(*this).end();
    }

    void clear_buf() {
        while(!empty()) {
            pop_front();
        }
    }


    value_type GetHead() {
        return read_index_;
    }

    value_type GetTail() {
        return write_index_;
    }

    value_type GetSize() {
        return size_;
    }


private:

    void MoveRead() {
        if (read_index_ == size_ - 1) {
            read_index_ = 0;
        } else if (elements_count_ - 1 == 0) {
            read_index_ = 0;
            write_index_ = 0;
        } else {
            ++read_index_;
        }
        --elements_count_;
    }

    void MoveWrite() {
        if (write_index_ == size_ - 1) {
            write_index_ = 0;
        } else {
            ++write_index_;
        }
        ++elements_count_;
    }

    pointer data_;
    value_type read_index_;
    value_type write_index_;
    value_type elements_count_;
    size_type size_;
    allocator_type alloc_;
};