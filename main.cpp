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

}