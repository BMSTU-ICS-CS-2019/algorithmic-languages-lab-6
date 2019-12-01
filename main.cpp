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

int main() {
    while (true) {
        cout << "Enter REPL-mode (`stack` (`s`), `queue` (`q`), `list` (`l`) or `exit` (`e`))" << endl;
        string mode;
        cin >> mode;
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
        cout << "Enter action (`push`, `pop`, `print` or `exit`)" << endl;
        string action;
        cin >> action;

        if (action == "push") {
            cout << "Enter value" << endl;
            string value;
            cin >> value;
            queue.push(value);
            cout << "Pushed \"" << value << "\"" << endl;
        } else if (action == "pop") try {
                const string popped = queue.pop();
                cout << "Popped " << queue.pop() << endl;
            } catch (const out_of_range &e) {
                cout << "Could not pop a value from an empty queue" << endl;
            } else if (action == "print") queue.for_each_indexed([](const size_t &index, const string &value) {
                cout << "[" << index << "] = " << value << endl;
            });
        else if (action == "exit") break;
        else cout << "Unknown action" << endl;
    }
}

void stack_repl() noexcept {
    Stack<string> stack;
    while (true) {
        cout << "Enter action (`push`, `pop`, `print` or `exit`)" << endl;
        string action;
        cin >> action;

        if (action == "push") {
            cout << "Enter value" << endl;
            string value;
            cin >> value;
            stack.push(value);
            cout << "Pushed \"" << value << "\"" << endl;
        } else if (action == "pop") try {
            const string popped = stack.pop();
            cout << "Popped " << stack.pop() << endl;
        } catch (const out_of_range &e) {
            cout << "Could not pop a value from an empty stack" << endl;
        } else if (action == "print") stack.for_each_indexed([](const size_t &index, const string &value) {
            cout << "[" << index << "] = " << value << endl;
        });
        else if (action == "exit") break;
        else cout << "Unknown action" << endl;
    }
}

void linked_list_repl() noexcept {

}