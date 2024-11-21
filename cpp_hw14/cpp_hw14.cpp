#include <iostream>
#include <stdexcept>

using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class Stack {
private:
    Node* top; 
    int size;  

public:
    Stack() : top(nullptr), size(0) {}

    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
        size++;
    }

    void pop() {
        if (isEmpty()) {
            throw runtime_error("Стек пуст, невозможно выполнить pop");
        }
        Node* temp = top;
        top = top->next;
        delete temp;
        size--;
    }

    int peek() const {
        if (isEmpty()) {
            throw runtime_error("Стек пуст, невозможно выполнить peek");
        }
        return top->data;
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    int getSize() const {
        return size;
    }

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void add(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    void print() const {
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    LinkedList clone() const {
        LinkedList newList;

        if (!head) return newList;

        Node* current = head;
        Node* tail = nullptr;

        while (current) {
            Node* newNode = new Node(current->data);
            if (!newList.head) {
                newList.head = tail = newNode;
            }
            else {
                tail->next = newNode;
                tail = newNode;
            }
            current = current->next;
        }

        return newList;
    }

    LinkedList operator+(const LinkedList& other) const {
        LinkedList result;

        Node* current = head;
        while (current) {
            result.add(current->data);
            current = current->next;
        }

        current = other.head;
        while (current) {
            result.add(current->data);
            current = current->next;
        }

        return result;
    }

    LinkedList operator*(const LinkedList& other) const {
        LinkedList result;

        Node* currentA = head;
        while (currentA) {
            Node* currentB = other.head;
            while (currentB) {
                if (currentA->data == currentB->data) {
                    result.add(currentA->data);
                    break;
                }
                currentB = currentB->next;
            }
            currentA = currentA->next;
        }

        return result;
    }

    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    cout << "=== Задание 1: Стек ===" << endl;

    Stack stack;

    stack.push(10);
    stack.push(20);
    stack.push(30);

    cout << "Верхний элемент: " << stack.peek() << endl;
    cout << "Размер стека: " << stack.getSize() << endl;

    stack.pop();
    cout << "После pop, верхний элемент: " << stack.peek() << endl;


    cout << "\n=== Задание 2: Односвязный список ===" << endl;

    LinkedList list1, list2;

    list1.add(1);
    list1.add(2);
    list1.add(3);

    list2.add(3);
    list2.add(4);
    list2.add(5);

    cout << "Список 1: ";
    list1.print();

    cout << "Список 2: ";
    list2.print();

    LinkedList clonedList = list1.clone();
    cout << "Клонированный список 1: ";
    clonedList.print();

    LinkedList sumList = list1 + list2;
    cout << "Список после сложения: ";
    sumList.print();

    LinkedList intersectionList = list1 * list2;
    cout << "Список пересечения: ";
    intersectionList.print();

    return 0;
}
