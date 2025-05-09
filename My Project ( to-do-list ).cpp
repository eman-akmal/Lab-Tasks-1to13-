#include <iostream>
#include <stack>
using namespace std;

// 										Task class 

class Task {
public:
    string description;
    bool isCompleted;
    Task* next;

    Task(string desc) {
        description = desc;
        isCompleted = false;
        next = nullptr;
    }
};

// 										ToDoList class 

class ToDoList {
private:
    Task* head;
    stack<string> undoStack;

public:
    ToDoList() {
        head = nullptr;
    }

//										 Add Task

    void addTask(string desc) {
        Task* newTask = new Task(desc);
        undoStack.push(desc); 

        if (head == nullptr) {
            head = newTask;
        } else {
            Task* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newTask;
        }
        cout << " Task added successfully!\n ";
    }

    // View all tasks
    
    void viewTasks() {
        if (head == nullptr) {
            cout << " No tasks found!\n ";
            return;
        }

        Task* temp = head;
        int index = 1;
        while (temp != nullptr) {
            cout << index << " . " << temp->description;
            if (temp->isCompleted) {
                cout << " [Completed] ";
            }
            cout << endl;
            temp = temp->next;
            index++;
        }
    }

//										 Delete a task by position
    
    void deleteTask(int position) {
        if (head == nullptr) {
            cout << " List is empty!\n ";
            return;
        }

        if (position == 1) {
            Task* toDelete = head;
            head = head->next;
            delete toDelete;
            cout << " Task deleted!\n ";
            return;
        }

        Task* temp = head;
        for (int i = 1; temp != nullptr && i < position - 1; i++) {
            temp = temp->next;
        }

        if (temp == nullptr || temp->next == nullptr) {
            cout << " Invalid position!\n ";
            return;
        }

        Task* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
        cout << " Task deleted!\n ";
    }

    // Mark a task as completed
    
    void markComplete(int position) {
        Task* temp = head;
        int count = 1;

        while (temp != nullptr) {
            if (count == position) {
                temp->isCompleted = true;
                cout << " Task marked as completed!\n ";
                return;
            }
            temp = temp->next;
            count++;
        }

        cout << " Invalid task number!\n ";
    }

// 										Undo the last added task
    
    void undoLastAdd() {
        if (undoStack.empty() || head == nullptr) {
            cout << " Nothing to undo!\n ";
            return;
        }

        string lastTask = undoStack.top();
        undoStack.pop();
        
        
          if (head->next == nullptr) {
        delete head;
        head = nullptr;
        cout << "? Undo: Last task removed - " << lastTask << endl;
        return;
    }


        Task* temp = head;
        Task* prev = nullptr;

        while (temp->next != nullptr) {
            prev = temp;
            temp = temp->next;
        }

       prev->next = nullptr;
       delete temp;
       
        cout << " Undo: Last task removed - " << lastTask << endl;
    }
};

// 											Main Menu

int main() {
    ToDoList myList;
    int choice;
    string taskDesc;
    int taskNum;

    do {
        cout << " \n---------- TO-DO LIST MENU ----------\n ";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Delete Task\n";
        cout << "4. Mark Task as Completed\n";
        cout << "5. Exit\n";
        cout << "6. Undo Last Added Task\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
            case 1:
                cout << " Enter task description: ";
                getline(cin, taskDesc);
                myList.addTask(taskDesc);
                break;

            case 2:
                myList.viewTasks();
                break;

            case 3:
                cout << " Enter task number to delete: ";
                cin >> taskNum;
                myList.deleteTask(taskNum);
                break;

            case 4:
                cout << " Enter task number to mark completed: ";
                cin >> taskNum;
                myList.markComplete(taskNum);
                break;

            case 5:
                cout << " Exiting program. Good luck for your finals!\n ";
                break;

            case 6:
                myList.undoLastAdd();
                break;

            default:
                cout << " Invalid choice. Try again!\n ";
        }
    } while (choice != 5);

    return 0;
}
