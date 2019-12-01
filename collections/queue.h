#ifndef LAB_6_QUEUE_H
#define LAB_6_QUEUE_H

#include <cstddef>
#include <stdexcept>

using std::out_of_range;

namespace collections {

    template <typename T>
    class Queue {

        /* ***************************************** Implementation details ***************************************** */

        class Node {

            friend class Queue;

            T value;
            Node *next = nullptr;

            explicit Node(const T value): value(value) {}
        };

        size_t size_ = 0;
        Node *first_ = nullptr, *last_ = nullptr;

        /* ********************************************** API members ********************************************** */
    public:

        ~Queue() {
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
            const auto pushed = new Node(value);
            if (first_) {
                last_->next = pushed;
                last_ = pushed;
            } else first_ = last_ = pushed;

            ++size_;
        }

        T pop() {
            if (size_ == 0) throw out_of_range("Queue is empty so nothing can be popped from it");

            const auto popped = first_;
            if (popped) {
                first_ = popped->next;
                if (!first_) last_ = nullptr;

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

#endif //LAB_6_QUEUE_H
