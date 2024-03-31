#include <iostream>
#include <string>
#include <list>
#include <ctime>
#include <cstdlib>

class TodoItem {
private:
    static int nextId;
    int id;
    std::string description;
    bool completed;

public:
    TodoItem() : id(0), description(""), completed(false) {}
    TodoItem(const std::string& desc) : id(++nextId), description(desc), completed(false) {}

    int getId() const { return id; }
    std::string getDescription() const { return description; }
    bool isCompleted() const { return completed; }

    void setCompleted(bool val) { completed = val; }
};

int TodoItem::nextId = 0;

class TodoList {
private:
    std::list<TodoItem> todoItems;

public:
    void addTodoItem(const std::string& description) {
        TodoItem newItem(description);
        todoItems.push_back(newItem);
    }

    void markCompleted(int id) {
        for (auto& item : todoItems) {
            if (item.getId() == id) {
                item.setCompleted(true);
                return;
            }
        }
        std::cout << "No item found with ID " << id << std::endl;
    }

    void displayTodoList() const {
        std::cout << "Todo List:" << std::endl;
        if (todoItems.empty()) {
            std::cout << "Empty" << std::endl;
            return;
        }
        for (const auto& item : todoItems) {
            std::string completed = item.isCompleted() ? "done" : "not done";
            std::cout << item.getId() << " | " << item.getDescription() << " | " << completed << std::endl;
        }
    }

    bool isEmpty() const {
        return todoItems.empty();
    }
};

int main() {
    char input_option;
    int input_id;
    std::string input_description;
    TodoList todoList;
    std::string version = "v0.2.0";

    srand(time(NULL));

    while (true) {
        system("cls");
        std::cout << "Todo List Maker - " << version << std::endl << std::endl;

        todoList.displayTodoList();

        if (todoList.isEmpty()) {
            std::cout << "Add your first todo!" << std::endl;
        }

        std::cout << std::endl;
        std::cout << "[a]dd a new Todo" << std::endl;
        std::cout << "[c]omplete a Todo" << std::endl;
        std::cout << "[q]uit" << std::endl;

        std::cout << "choice: ";
        std::cin >> input_option;

        if (input_option == 'q') {
            std::cout << "Have a great day now!" << std::endl;
            break;
        } else if (input_option == 'a') {
            std::cout << "Add a new description: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, input_description);
            todoList.addTodoItem(input_description);
        } else if (input_option == 'c') {
            std::cout << "Enter id to mark completed: ";
            std::cin >> input_id;
            todoList.markCompleted(input_id);
        }
    }
    return 0;
}
