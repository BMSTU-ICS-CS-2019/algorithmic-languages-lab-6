#ifndef LAB_6_STACK_H
#define LAB_6_STACK_H

#include <cstddef>

using std::out_of_range;

namespace collections {

    template <typename T>
    class stack {

        /* ***************************************** Implementation details ***************************************** */

        class node {

            friend class stack;

            T value;
            node *next = nullptr;

            explicit node(const T value): value(value) {}
        };

        size_t size_ = 0;
        node *first_ = nullptr;

        /* ********************************************** API members ********************************************** */
    public:

        ~stack() {
            auto current = first_;
            while (current) {
                const auto next = current->next;
                delete current;
                current = next;
            }
        }

        [[nodiscard]] size_t size() const {
            return size_;
        }

        void push(const T value) {
            const auto pushed = new node(value);
            pushed->next = first_;
            first_ = pushed;

            ++size_;
        }

        T pop() {
            if (size_ == 0) throw out_of_range("Stack is empty so nothing can be popped from it");

            const auto popped = first_;
            if (popped) {
                first_ = popped->next;
                const auto value = popped->value;
                delete popped;

                --size_;

                return value;
            }
        }

        template <typename CONSUMER>
        void for_each(const CONSUMER consumer) {
            if (size_ == 0) return;

            auto current = first_;
            size_t index = 0;
            while (current) {
                consumer(current->value);

                current = current->next;
                ++index;
            }
        }

        template <typename BI_CONSUMER>
        void for_each_indexed(const BI_CONSUMER consumer) {
            if (size_ == 0) return;

            auto current = first_;
            size_t index = 0;
            while (current) {
                consumer(index, current->value);

                current = current->next;
                ++index;
            }
        }
    };
}

#endif //LAB_6_STACK_H
