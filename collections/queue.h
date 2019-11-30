#ifndef LAB_6_QUEUE_H
#define LAB_6_QUEUE_H

#include <cstddef>

namespace collections {

    template <typename T>
    class queue {

        /* ***************************************** Implementation details ***************************************** */

        class node {

            friend class queue;

            T value_;
            node *next_ = nullptr;

            explicit node(const T value): value_(value) {}
        };

        size_t size_ = 0;
        node *first_ = nullptr, *last_ = nullptr;

        /* ********************************************** API members ********************************************** */
    public:

        ~queue() {
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
            if (first_) {
                last_->next_ = pushed;
                last_ = pushed;
            } else first_ = last_ = pushed;

            ++size_;
        }

        T pop(const T default_value) {
            const auto popped = first_;
            if (popped) {
                first_ = popped->next_;
                if (!first_) last_ = nullptr;

                const auto value = popped->value_;
                delete popped;

                --size_;


                return value;
            }
        }
    };
}

#endif //LAB_6_QUEUE_H
