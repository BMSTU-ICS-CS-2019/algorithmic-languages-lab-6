#include <iostream>

#include "collections/stack.h"
#include "collections/queue.h"
#include "collections/linked_list.h"

using collections::LinkedList;
using collections::stack;
using collections::queue;
using std::cin;
using std::cout;
using std::endl;

int main() {
    {
        cout << "Queue tests" << endl;
        queue<long> queue;
        queue.push(1);
        queue.push(2);
        queue.push(3);
        queue.push(4);
        queue.pop();
        queue.push(5);

        queue.for_each_indexed([](const size_t &index, const long& value) {
            cout << "[" << index << "] = " << value << endl;
        });
    }

    {
        cout << "Stack tests" << endl;
        stack<long> stack;
        stack.push(1);
        stack.push(2);
        stack.push(3);
        stack.push(4);
        stack.push(5);

        stack.for_each_indexed([](const size_t &index, const long& value) {
            cout << "[" << index << "] = " << value << endl;
        });
    }

    {
        cout << "Linked-List tests #1" << endl;
        LinkedList<long> list;
        list.push_last(1);
        list.push_last(2);
        list.push_first(3);
        cout << list[0] << " " << list[1] << " " << list[2] << endl;
        list += 13;
        list += 13;
        list += 13;
        list += 13;
        list += 1212;
        list += 17;
        list.for_each_indexed([](const size_t &index, const long& value) {
            cout << "[" << index << "] = " << value << endl;
        });
        cout << "Linked-List tests #2" << endl;
        list -= 13;
        list -= 13;
        list.pop_at(2);
        list.for_each_indexed([](const size_t &index, const long& value) {
            cout << "[" << index << "] = " << value << endl;
        });
    }

    return 0;
}
