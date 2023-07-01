
#pragma once

#include <iostream>
#include <memory>
#include <algorithm>
#include <iterator>
#include <type_traits>

template<typename Ptr, typename Alloc_Traits>
class CircularBufferIterator {
public:

    typedef std::random_access_iterator_tag	    iterator_category;
    typedef Alloc_Traits::value_type		    value_type;
    typedef Ptr				                    pointer;
    typedef decltype(*pointer{})				reference;
    typedef Alloc_Traits::size_type				size_type;
    typedef Alloc_Traits::difference_type	    difference_type;
    typedef CircularBufferIterator              self_type;

    constexpr CircularBufferIterator() noexcept = default;

    CircularBufferIterator(pointer array, size_type pos, size_type size, size_type head, size_type tail) {
        array_ = array;
        pos_ = pos;
        size_ = size;
        head_ = head;
        tail_ = tail;
    };

    operator CircularBufferIterator<typename Alloc_Traits::const_pointer, Alloc_Traits>() const {
        return CircularBufferIterator<typename Alloc_Traits::const_pointer, Alloc_Traits>(array_, pos_, size_, head_, tail_);
    }

    reference operator*() const {
        return *(array_ + pos_);
    }

    pointer operator->() const noexcept {
        return &(operator*());
    }


    self_type& operator++() noexcept {
        pos_ = (pos_ + 1) % size_;
        return *this;
    }

    self_type operator++(int) noexcept {
        self_type temp(*this);
        operator++();
        return temp;
    }

    self_type& operator--() noexcept {
        if (pos_ == 0) {
            pos_ = size_ - 1;
        } else {
            pos_ = (pos_ - 1) % size_;
        }
        return *this;
    }

    self_type operator--(int) noexcept {
        self_type temp(*this);
        operator--();
        return temp;
    }


    self_type operator+(difference_type n) const noexcept {
        return self_type(array_, (pos_ + n) % size_, size_, head_, tail_);
    }

    self_type operator-(difference_type n) const noexcept {
        int temp_pos;
        if (n >= pos_) {
            temp_pos = (size_ - (n - pos_)) % size_;
        } else {
            temp_pos = (pos_ - n) % size_;
        }
        return self_type(array_, temp_pos, size_, head_, tail_);
    }

    self_type& operator+=(difference_type n) noexcept {
        pos_ = (pos_ + n) % size_;
        return *this;
    }

    self_type& operator-=(difference_type n) noexcept {
        if (n > pos_) {
            pos_ = size_ - (n - pos_) % size_;
        } else {
            pos_ = (pos_ - n) % size_;
        }
        return *this;
    }

    reference operator[](difference_type n) const {
        return *(*this + n);
    }


    friend difference_type operator-(const self_type& first, const self_type& second) noexcept {

        if (first.head_ > first.tail_) {

            if (first.pos_ > first.tail_ && second.pos_ > first.tail_) {
                if (first.pos_ > second.pos_) {
                    return first.pos_ - second.pos_;
                } else {
                    return second.pos_ - first.pos_;
                }
            } else if (first.pos_ < first.tail_ && second.pos_ < first.tail_) {
                if (first.pos_ > second.pos_) {
                    return first.pos_ - second.pos_;
                } else {
                    return second.pos_ - first.pos_;
                }
            } else {
                if (first.pos_ > second.pos_) {
                    return (first.size_ - first.pos_ + second.pos_);
                } else {
                    return (second.size_ - second.pos_ + first.pos_);
                }
            }
        } else {
            if (first.pos_ > second.pos_) {
                return first.pos_ - second.pos_;
            } else {
                return second.pos_ - first.pos_;
            }
        }

    }


    friend difference_type operator+(difference_type n, const self_type& it) noexcept {
        return it + n;
    }

    friend bool operator<(const self_type& first, const self_type& second) noexcept {

        if (first.head_ > first.tail_) {
            if (first.pos_ > second.pos_) {
                return true;
            } else {
                return false;
            }
        } else {
            if (first.pos_ > second.pos_) {
                return false;
            } else {
                return true;
            }
        }

    }

    friend bool operator>(const self_type& first, const self_type& second) noexcept {
        return second < first;
    }

    friend bool operator<=(const self_type& first, const self_type& second) noexcept {
        return !(second < first);
    }

    friend bool operator>=(const self_type& first, const self_type& second) noexcept {
        return !(first < second);
    }

    friend bool operator==(const self_type& first, const self_type& second) noexcept {
        return first.pos_ == second.pos_;
    }

    friend bool operator!=(const self_type& first, const self_type& second) noexcept {
        return !(first == second);
    }

private:
    pointer array_;
    size_type pos_;
    size_type size_;
    size_type head_;
    size_type tail_;
};
