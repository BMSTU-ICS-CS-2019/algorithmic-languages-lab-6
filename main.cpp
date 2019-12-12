#include <string>

#include "collections/stack.h"
#include "collections/queue.h"
#include "collections/linked_list.h"
#include "util/cli_util.h"

using collections::LinkedList;
using collections::Stack;
using collections::Queue;
using std::cin;
using std::string;
using std::cout;
using std::endl;

void queue_repl() noexcept;

void stack_repl() noexcept;

void linked_list_repl() noexcept;

int main() {
    while (true) {
        const auto mode = cli_read<string>(
                "Enter REPL-mode (`stack` (`s`), `queue` (`q`), `list` (`l`) or `exit` (`e`))"
        );

        if (mode == "s" || mode == "stack") stack_repl();
        else if (mode == "q" || mode == "queue") queue_repl();
        else if (mode == "l" || mode == "list") linked_list_repl();
        else if (mode == "e" || mode == " exit") {
            cout << "Have a nice day ;)" << endl;
            return 0;
        }
        else cout << "Unknown mode" << endl;
    }
}

void queue_repl() noexcept {
    Queue<string> queue;
    while (true) {
        const auto action = cli_read<string>(
                "Enter action (`push`, `pop`, `contains`, `size`, `print` or `exit`)"
        );

        if (action == "push") {
            const auto value = cli_read<string>("Enter value to push");
            queue.push(value);
            cout << "Pushed \"" << value << "\"" << endl;
        } else if (action == "pop") {
            string popped;
            try {
                popped = queue.pop();
            } catch (const out_of_range &e) {
                cout << "Could not pop any value: " << e.what() << endl;
                continue;
            }
            cout << "Popped \"" << popped << "\"" << endl;
        } else if (action == "contains") {
            const auto value = cli_read<string>("Enter value to check for containment");
            cout << (queue.contains(value) ? "List contains \"" : "List does not contain \"") << value << "\"" << endl;
        } else if (action == "size") cout << "Size is " << queue.size() << endl;
        else if (action == "print") queue.for_each_indexed([](const size_t &index, const string &value) {
            cout << "[" << index << "] = " << value << endl;
        });
        else if (action == "exit") break;
        else cout << "Unknown action" << endl;
    }
}

void stack_repl() noexcept {
    Stack<string> stack;
    while (true) {
        const auto action = cli_read<string>(
                "Enter action (`push`, `pop`, `contains`, `size`, `print` or `exit`)"
        );

        if (action == "push") {
            const auto value = cli_read<string>("Enter value to push");
            stack.push(value);
            cout << "Pushed \"" << value << "\"" << endl;
        } else if (action == "pop") {
            string popped;
            try {
                popped = stack.pop();
            } catch (const out_of_range &e) {
                cout << "Could not pop any value: " << e.what() << endl;
                continue;
            }
            cout << "Popped \"" << popped << "\"" << endl;
        } else if (action == "contains") {
            const auto value = cli_read<string>("Enter value to check for containment");
            cout << (stack.contains(value) ? "List contains \"" : "List does not contain \"") << value << "\"" << endl;
        } else if (action == "size") cout << "Size is " << stack.size() << endl;
        else if (action == "print") stack.for_each_indexed([](const size_t &index, const string &value) {
            cout << "[" << index << "] = " << value << endl;
        });
        else if (action == "exit") break;
        else cout << "Unknown action" << endl;
    }
}

void linked_list_repl() noexcept {
    LinkedList<string> list;
    while (true) {
        const auto action = cli_read<string>(
                "Enter action (`push_first`, `push_last`, `push_after`, `push_before`, `push_at`, "
                "`pop_first`, `pop_last`, `pop_at`, `pop`, `contains`, `index_of`, `size`, `print` or `exit`)"
        );
        if (action == "push_first") {
            const auto value = cli_read<string>("Enter value to push");
            list.push_first(value);
            cout << "Pushed \"" << value << "\"" << endl;
        } else if (action == "push_last") {
            const auto value = cli_read<string>("Enter value to push");
            list.push_last(value);
            cout << "Pushed \"" << value << "\"" << endl;
        } else if (action == "push_after") {
            const auto previous = cli_read<string>("Enter previous element's value");
            const auto value = cli_read<string>("Enter value to push");
            list.push_after(previous, value);
            cout << "Pushed \"" << value << "\"" << endl;
        } else if (action == "push_before") {
            const auto next = cli_read<string>("Enter next element's value");
            const auto value = cli_read<string>("Enter value to push");
            list.push_before(next, value);
            cout << "Pushed \"" << value << "\"" << endl;
        } else if (action == "push_at") {
            const auto index = cli_read<size_t>("Enter index at which to push");
            const auto value = cli_read<string>("Enter value to push");
            try {
                list.push_at(index, value);
            } catch (const out_of_range &e) {
                cout << "Could not push value \"" << value << "\" at index " << index << ": " << e.what();
                continue;
            }
            cout << "Pushed \"" << value << "\"" << endl;
        } else if (action == "pop_first") {
            string popped;
            try {
                popped = list.pop_first();
            } catch (const out_of_range &e) {
                cout << "Could not pop any value: " << e.what() << endl;
                continue;
            }
            cout << "Popped \"" << popped << "\"" << endl;
        } else if (action == "pop_last") {
            string popped;
            try {
                popped = list.pop_last();
            } catch (const out_of_range &e) {
                cout << "Could not pop any value: " << e.what() << endl;
                continue;
            }
            cout << "Popped \"" << popped << "\"" << endl;
        } else if (action == "pop_at") {
            const auto index = cli_read<size_t>("Enter index at which to pop");
            string popped;
            try {
                popped = list.pop_at(index);
            } catch (const out_of_range &e) {
                cout << "Could not pop value at index " << index << ": " << e.what() << endl;
                continue;
            }
            cout << "Popped \"" << popped << "\"" << endl;
        } else if (action == "pop") {
            const auto value = cli_read<string>("Enter value to pop");
            list.pop(value);
            cout << "Popped \"" << value << "\"" << endl;
        } else if (action == "contains") {
            const auto value = cli_read<string>("Enter value to check for containment");
            cout << (list.contains(value) ? "List contains \"" : "List does not contain \"") << value << "\"" << endl;
        } else if (action == "index_of") {
            const auto value = cli_read<string>("Enter element to locate");
            const auto index = list.index_of(value);
            if (index >= 0) cout << "Index of \"" << value << "\" is " << index << endl;
            else cout << "List does not contain \"" << value << "\"" << endl;
        } else if (action == "size") cout << "Size is " << list.size() << endl;
        else if (action == "print") list.for_each_indexed([](const size_t &index, const string &value) {
            cout << "[" << index << "] = " << value << endl;
        });
        else if (action == "exit") break;
        else cout << "Unknown action" << endl;
    }
}