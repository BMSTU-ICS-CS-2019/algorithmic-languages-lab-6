#ifndef LAB_6_STACK_H
#define LAB_6_STACK_H

#include "abstract_collection.h"
#include <cstddef>
#include <stdexcept>

using std::out_of_range;

namespace collections {

    template <typename T>
    class Stack : AbstractCollection<T> {

        /* ***************************************** Implementation details ***************************************** */

        class Node {

            friend class Stack;

            T value_;
            Node *next_ = nullptr;

            explicit Node(const T value): value_(value) {}
        };

        Node *first_ = nullptr;

        /* ********************************************** API members ********************************************** */
    public:

        ~Stack() {
            auto current = first_;
            while (current) {
                const auto next = current->next_;
                delete current;
                current = next;
            }
        }

        [[nodiscard]] size_t size() const {
            return this->size_;
        }

        void push(const T value) {
            const auto pushed = new Node(value);
            pushed->next_ = first_;
            first_ = pushed;

            ++this->size_;
        }

        T pop() {
            if (this->size_ == 0) throw out_of_range("Stack is empty so nothing can be popped from it");

            const auto popped = first_;
            if (popped) {
                first_ = popped->next_;
                const auto value = popped->value_;
                delete popped;

                --this->size_;

                return value;
            }
        }

        bool contains(const T &value) const override {
            auto current = first_;
            while (current) {
                if (current->value_ == value) return true;
                current = current->next_;
            }

            return false;
        }

        template <typename CONSUMER>
        void for_each(const CONSUMER consumer) {
            if (this->size_ == 0) return;

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
            if (this->size_ == 0) return;

            auto current = first_;
            size_t index = 0;
            while (current) {
                consumer(index, current->value_);

                current = current->next_;
                ++index;
            }
        }
    };
}

#endif //LAB_6_STACK_H
