#include <iostream>
#include <string>

#include "collections/stack.h"
#include "collections/queue.h"
#include "collections/linked_list.h"

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

#define MAIN_CLI_READ_VALUE_WITH_MESSAGE(type, variable_name, message) cout << message << endl;\
type variable_name;\
cin >> variable_name;

#define MAIN_CLI_READ_VALUE(type, variable_name) MAIN_CLI_READ_VALUE_WITH_MESSAGE(\
type, variable_name, "Enter " << #variable_name\
);

int main() {
    while (true) {
        MAIN_CLI_READ_VALUE_WITH_MESSAGE(
                string, mode, "Enter REPL-mode (`stack` (`s`), `queue` (`q`), `list` (`l`) or `exit` (`e`))"
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
        MAIN_CLI_READ_VALUE_WITH_MESSAGE(
                string, action, "Enter action (`push`, `pop`, `size`, `print` or `exit`)"
        )

        if (action == "push") {
            MAIN_CLI_READ_VALUE(string, value)
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
        MAIN_CLI_READ_VALUE_WITH_MESSAGE(
                string, action, "Enter action (`push`, `pop`, `size`, `print` or `exit`)"
        )

        if (action == "push") {
            MAIN_CLI_READ_VALUE(string, value)
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
        MAIN_CLI_READ_VALUE_WITH_MESSAGE(
                string, action,
                "Enter action (`push_first`, `push_last`, `push_after`, `push_before`, `push_at`, "
                "`pop_first`, `pop_last`, `pop_at`, `pop`, `contains`, `index_of`, `size`, `print` or `exit`)"
        )
        if (action == "push_first") {
            MAIN_CLI_READ_VALUE(string, value)
            list.push_first(value);
            cout << "Pushed \"" << value << "\"" << endl;
        } else if (action == "push_last") {
            MAIN_CLI_READ_VALUE(string, value)
            list.push_last(value);
            cout << "Pushed \"" << value << "\"" << endl;
        } else if (action == "push_after") {
            MAIN_CLI_READ_VALUE(string, previous)
            MAIN_CLI_READ_VALUE(string, value)
            list.push_after(previous, value);
            cout << "Pushed \"" << value << "\"" << endl;
        } else if (action == "push_before") {
            MAIN_CLI_READ_VALUE(string, next)
            MAIN_CLI_READ_VALUE(string, value)
            list.push_before(next, value);
            cout << "Pushed \"" << value << "\"" << endl;
        } else if (action == "push_at") {
            MAIN_CLI_READ_VALUE(size_t, index)
            MAIN_CLI_READ_VALUE(string, value)
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
            MAIN_CLI_READ_VALUE(size_t, index)
            string popped;
            try {
                popped = list.pop_at(index);
            } catch (const out_of_range &e) {
                cout << "Could not pop value at index " << index << ": " << e.what() << endl;
                continue;
            }
            cout << "Popped \"" << popped << "\"" << endl;
        } else if (action == "pop") {
            MAIN_CLI_READ_VALUE(string, value)
            list.pop(value);
            cout << "Popped \"" << value << "\"" << endl;
        } else if (action == "contains") {
            MAIN_CLI_READ_VALUE(string, value)
            cout << (list.contains(value) ? "List contains \"" : "List does not contain \"") << value << "\"" << endl;
        } else if (action == "index_of") {
            MAIN_CLI_READ_VALUE(string, value)
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