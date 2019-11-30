#ifndef LAB_6_STACK_H
#define LAB_6_STACK_H

#include <cstddef>

namespace collections {

    template <typename T>
    class stack {

        /* ***************************************** Implementation details ***************************************** */

        class node {

            friend class stack;

            T value_;
            node *next_ = nullptr;

            explicit node(const T value): value_(value) {}
        };

        size_t size_ = 0;
        node *first_ = nullptr;

        /* ********************************************** API members ********************************************** */
    public:

        ~stack() {
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

        void push(const T value) {
            const auto pushed = new node(value);
            pushed->next_ = first_;
            first_ = pushed;

            ++size_;
        }

        T pop(const T default_value) {
            const auto popped = first_;
            if (popped) {
                first_ = popped->next_;
                const auto value = popped->value_;
                delete popped;

                --size_;

                return value;
            }
        }
    };
}

#endif //LAB_6_STACK_H
