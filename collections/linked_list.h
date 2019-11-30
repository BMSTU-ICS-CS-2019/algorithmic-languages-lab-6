#ifndef LAB_6_LINKED_LIST_H
#define LAB_6_LINKED_LIST_H

#include <cstddef>
#include <stdexcept>

using std::out_of_range;

namespace collections {

    template <typename T>
    class linked_list {

        /* ***************************************** Implementation details ***************************************** */

        class node {

            friend class linked_list;

            T value_;
            node *previous_ = nullptr, *next_ = nullptr;

            explicit node(const T value): value_(value) {}
        };

        size_t size_ = 0;
        node *first_ = nullptr, *last_ = nullptr;

    protected:

        node * at_(const size_t index) const {
            const auto size = size_;

            if (index >= size) throw out_of_range("Index is out of range");

            if (index <= size << 1) { // lookup from head
                auto current = first_;
                size_t current_index = 0;
                while (current) {
                    if (current_index == index) return current;

                    current = current->next_;
                    ++current_index;
                }
            } else { // lookup from tail
                auto current = last_;
                size_t current_index = size;
                while (current) {
                    --current_index;
                    if (current_index == index) return current;

                    current = current->next_;
                }
            }
        }

        inline void push_first_(node * const pushed) {
            if (size_ == 0) first_ = last_ = pushed;
            else {
                // double-link head
                pushed->next_ = first_;
                first_->previous_ = pushed;
                first_ = pushed;
            }

            ++size_;
        }

        inline void push_last_(node * const pushed) {
            if (size_ == 0) first_ = last_ = pushed;
            else {
                pushed->previous_ = last_;
                last_->next_ = pushed;
                last_ = pushed;
            }

            ++size_;
        }

        inline void push_after_(node * const previous, node * const pushed) {
            const auto old_next = previous->next_;
            if (old_next) old_next->previous_ = pushed;
            else last_ = pushed;

            pushed->previous_ = previous;
            pushed->next_ = old_next;
            previous->next_ = pushed;

            ++size_;
        }

        inline void push_before_(const node *next, const node *pushed) {
            const auto old_previous = next->previous_;
            if (old_previous) old_previous->next_ = pushed;
            else first_ = pushed;

            pushed->next_ = next;
            pushed->previous_ = old_previous;
            next->previous_ = pushed;

            ++size_;
        }

        inline T pop_first_() {
            switch (size_) {
                case 0: throw out_of_range("Attempt to pop a value from a non-empty collection");
                case 1: {
                    const auto popped = first_;
                    first_ = last_ = nullptr;

                    size_ = 0;
                    const auto value = popped->value_;
                    delete popped;

                    return value;
                }
                default: {
                    const auto popped = first_;
                    first_ = popped->next_;

                    --size_;
                    const auto value = popped->value_;
                    delete popped;

                    return value;
                }
            }
        }

        inline void pop_first_no_return_() {
            switch (size_) {
                case 0: throw out_of_range("Attempt to pop a value from a non-empty collection");
                case 1: {
                    const auto popped = first_;
                    first_ = last_ = nullptr;

                    size_ = 0;
                    delete popped;
                }
                default: {
                    const auto popped = first_;
                    first_ = popped->next_;

                    --size_;
                    delete popped;
                }
            }
        }

        inline T pop_last_() {
            switch (size_) {
                case 0: throw out_of_range("Attempt to pop a value from a non-empty collection");
                case 1: {
                    const auto popped = last_;
                    first_ = last_ = nullptr;

                    size_ = 0;
                    const auto value = popped->value_;
                    delete popped;

                    return value;
                }
                default: {
                    const auto popped = last_;
                    last_ = popped->previous_;

                    --size_;
                    const auto value = popped->value_;
                    delete popped;

                    return value;
                }
            }
        }

        inline void pop_last_no_return_() {
            switch (size_) {
                case 0: throw out_of_range("Attempt to pop a value from a non-empty collection");
                case 1: {
                    const auto popped = last_;
                    first_ = last_ = nullptr;

                    size_ = 0;
                    delete popped;
                }
                default: {
                    const auto popped = last_;
                    last_ = popped->previous_;

                    --size_;
                    delete popped;
                }
            }
        }

        inline T pop_(const node *popped) {
            const auto first = first_;
            if (popped == first) {
                if (popped == last_) first_ = last_ = nullptr; // pop the only one
                else { // simply pop the first
                    first_ = first->next_;
                    first->next_->previous_ = nullptr;
                }
            } else {
                auto last = last_;
                if (popped == last) { // simply pop the last
                    // popped != first
                    last = last->previous_;
                    last->previous_->next_ = nullptr;
                } else { // pop non-border
                    const auto previous = popped->previous_, next = popped->next_;
                    previous->next_ = next;
                    next->previous_ = previous;
                }
            }

            --size_;
            const auto value = popped->value_;
            delete popped;
            return value;
        }

        inline void pop_no_return_(const node * popped) {
            const auto first = first_;
            if (popped == first) {
                if (popped == last_) first_ = last_ = nullptr; // pop the only one
                else { // simply pop the first
                    first_ = first->next_;
                    first->next_->previous_ = nullptr;
                }
            } else {
                auto last = last_;
                if (popped == last) { // simply pop the last
                    // popped != first
                    last = last->previous_;
                    last->previous_->next_ = nullptr;
                } else { // pop non-border
                    const auto previous = popped->previous_, next = popped->next_;
                    previous->next_ = next;
                    next->previous_ = previous;
                }
            }


            --size_;
            delete popped;
        }

        /* ********************************************** API members ********************************************** */
    public:

        ~linked_list() {
            auto current = first_;
            while (current) {
                const auto next = current->next_;
                delete current;
                current = next;
            }
        }

        [[nodiscard]] size_t size() const {
            return size_;
        }

        void push_first(const T value) {
            push_first_(new node(value));
        }

        void push_last(const T value) {
            push_last_(new node(value));
        }

        void push_after(const T value, const T& previous) {
            if (size_ == 0) return;

            auto current = first_;
            while (current) {
                if (current->value_ == previous) {
                    push_after_(current, new node(value));

                    return;
                }

                current = current->next_;
            }
        }

        void push_before(const T value, const T &next) {
            if (size_ == 0) return;

            auto current = first_;
            while (current) {
                if (current->value_ == next) {
                    push_before_(current, new node(value));

                    return;
                }

                current = current->next_;
            }
        }

        void push_at(const T value, const size_t index) {
            const auto size = size_;

            if (index == 0) push_first_(new node(value));
            else if (index == size) push_last_(new node(value));
            else if (index > size) throw out_of_range("Index is greater than size");
            else {
                if (index <= size << 1) {
                    // go from the head
                    auto current = first_;
                    size_t next_index = 1;
                    while (true) {
                        if (next_index == index) {
                            push_after_(current, new node(value));
                            return;
                        }

                        current = current->next_;
                        ++next_index;
                    }
                } else {
                    // go from the tail
                    auto current = last_;
                    size_t current_index = size - 1;
                    while (true) {
                        if (current_index == index) {
                            push_before_(current, new node(value));
                            return;
                        }

                        current = current->previous_;
                        --current_index;
                    }
                }
            }
        }

        T pop_first() {
            return pop_first_();
        }

        T pop_last() {
            return pop_last_();
        }

        void pop_one(const T &value) {
            if (size_ == 0) return;

            auto current = first_;
            while (current) {
                if (current->value_ == value) {
                    pop_no_return_(current);
                    return;
                }

                current = current->next_;
            }
        }

        T pop_at(const size_t index) {
            return pop_(at_(index));
        }

        bool contains(const T &value) const {
            auto current = first_;
            while (current) {
                if (current->value_ == value) return true;

                current = current->next_;
            }

            return false;
        }

        size_t indexOf(const T &value) const {
            auto current = first_;
            size_t index = 0;
            while (current) {
                if (current->value_ == value) return index;

                current = current->next_;
                ++index;
            }

            return -1;
        }

        inline T at(const size_t index) const {
            return at_(index)->value_;
        }

        template <typename CONSUMER>
        void for_each(const CONSUMER consumer) {
            if (size_ == 0) return;

            auto current = first_;
            size_t index = 0;
            while (current) {
                consumer(current->value_);

                current = current->next_;
                ++index;
            }
        }

        template <typename BI_CONSUMER>
        void for_each_indexed(const BI_CONSUMER consumer) {
            if (size_ == 0) return;

            auto current = first_;
            size_t index = 0;
            while (current) {
                consumer(index, current->value_);

                current = current->next_;
                ++index;
            }
        }

        /* *********************************************** Operators *********************************************** */

        inline T operator [](const size_t index) const {
            return at(index);
        }

        inline void operator +=(const T popped) {
            push_last(popped);
        }

        inline void operator -=(const T popped) {
            pop_one(popped);
        }

        inline explicit operator size_t() const {
            return size_;
        }
    };
}

#endif //LAB_6_LINKED_LIST_H
