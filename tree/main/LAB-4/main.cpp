#include <iostream>
using namespace std;

const int SIZE = 5;

struct package {
    string packageID;
    string destination;
    int dimension[3];
};

struct packageNode {
    package data;
    packageNode* next;
};

struct courier {
    string name;
    string carType;
};

packageNode* top = nullptr;

courier courierQueue[SIZE];
int front = 0, rear = 0, count = 0;

void pushPackage() {
    package p;
    cout << "Package ID: ";
    cin >> p.packageID;
    cout << "Destination: ";
    cin >> p.destination;
    cout << "Dimensions (L W H): ";
    cin >> p.dimension[0] >> p.dimension[1] >> p.dimension[2];

    packageNode* newNode = new packageNode();
    newNode->data = p;
    newNode->next = top;
    top = newNode;
    cout << "Done!\n";
}

void enqueueCourier() {
    if (count == SIZE) {
        cout << "Queue is full.\n";
        return;
    }
    courier c;
    cout << "Courier name: ";
    cin >> c.name;
    cout << "Car type: ";
    cin >> c.carType;

    courierQueue[rear] = c;
    rear = (rear + 1) % SIZE;
    count++;
    cout << "Done!\n";
}

void dispatch() {
    if (top == nullptr) {
        cout << "No packages available.\n";
        return;
    }
    if (count == 0) {
        cout << "No couriers available.\n";
        return;
    }

    courier c = courierQueue[front];
    front = (front + 1) % SIZE;
    count--;

    packageNode* temp = top;
    top = top->next;

    cout << c.name << " (" << c.carType << ") is delivering "
         << temp->data.packageID << " to " << temp->data.destination << "\n";

    delete temp;
}

void displayAll() {
    cout << "\nPackages:\n";
    packageNode* current = top;
    if (current == nullptr) cout << "No packages.\n";
    while (current != nullptr) {
        cout << current->data.packageID << " -> " << current->data.destination
             << " [" << current->data.dimension[0] << "x"
             << current->data.dimension[1] << "x"
             << current->data.dimension[2] << "]\n";
        current = current->next;
    }

    cout << "\nCouriers:\n";
    if (count == 0) cout << "No couriers.\n";
    int i = front;
    for (int j = 0; j < count; j++) {
        cout << courierQueue[i].name << " - " << courierQueue[i].carType << "\n";
        i = (i + 1) % SIZE;
    }
}

int main() {
    int choice;
    do {
        cout << "\n1. Package arrival\n2. Courier register\n3. Dispatch\n4. Display all\n5. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) pushPackage();
        else if (choice == 2) enqueueCourier();
        else if (choice == 3) dispatch();
        else if (choice == 4) displayAll();

    } while (choice != 5);

    return 0;
}
