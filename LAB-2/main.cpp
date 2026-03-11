#include <iostream>
#include <string>

using namespace std;

struct Node {
    string data;
    Node* next;
    Node(string w) { data = w; next = nullptr; }
};

void appendWord(Node*& head, string word) {
    Node* newNode = new Node(word);
    if (head == nullptr) {
        head = newNode;
        return;
    }
    Node* cur = head;
    while (cur->next != nullptr) {
        cur = cur->next;
    }
    cur->next = newNode;
}

void undoLast(Node*& head) {
    if (head == nullptr) {
        cout << "Nothing to undo\n";
        return;
    }
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }
    Node* cur = head;
    while (cur->next->next != nullptr) {
        cur = cur->next;
    }
    delete cur->next;
    cur->next = nullptr;
}

void displayList(Node* head) {
    Node* cur = head;
    while (cur) {
        cout << "[" << cur->data << "]";
        if (cur->next) cout << " -> ";
        cur = cur->next;
    }
    cout << " -> NULL\n";
}

int main() {
    Node* head = nullptr;
    string word;

    cout << "Enter words. UNDO to erase last. EXIT to quit\n";
    displayList(head);
    
    while (true) {
        cout << "> ";
        if (!(cin >> word)) break;
        if (word == "EXIT") break;
        else if (word == "UNDO") undoLast(head);
        else appendWord(head, word);
        displayList(head);
    }
   
    while (head) {
        Node* t = head;
        head = head->next;
        delete t;
    }
    cout << "Bye\n";
    return 0;
}
