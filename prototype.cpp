#include <iostream>
using namespace std;

// Badge structure (can be expanded with more fields)
struct Badge {
    int id;
    // Add more fields like timestamp, name, etc. if needed
};

// Node structure for CSLL
struct Node {
    Badge data;
    Node* next;
};

// Circular Singly Linked List Queue
class CSLLQueue {
private:
    Node* front;
    Node* rear;

public:
    CSLLQueue() : front(nullptr), rear(nullptr) {}

    // Enqueue: Add badge to rear
    void enqueue(Badge b) {
        Node* newNode = new Node{b, nullptr};
        if (!front) {
            front = rear = newNode;
            rear->next = front; // Circular link
        } else {
            rear->next = newNode;
            rear = newNode;
            rear->next = front;
        }
    }

    // Dequeue: Remove badge from front
    Badge dequeue() {
        if (!front) {
            throw runtime_error("Queue is empty");
        }

        Badge result = front->data;

        if (front == rear) {
            delete front;
            front = rear = nullptr;
        } else {
            Node* temp = front;
            front = front->next;
            rear->next = front;
            delete temp;
        }

        return result;
    }

    // Peek: View front badge without removing
    Badge peek() const {
        if (!front) {
            throw runtime_error("Queue is empty");
        }
        return front->data;
    }

    // Check if queue is empty
    bool isEmpty() const {
        return front == nullptr;
    }

    // Display queue contents (for debugging)
    void display() const {
        if (!front) {
            cout << "Queue is empty\n";
            return;
        }

        Node* temp = front;
        do {
            cout << "Badge ID: " << temp->data.id << "\n";
            temp = temp->next;
        } while (temp != front);
    }

    // Destructor: Clean up memory
    ~CSLLQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

// Sample usage
int main() {
    CSLLQueue badgeQueue;

    // Simulate badge scans
    badgeQueue.enqueue({101});
    badgeQueue.enqueue({102});
    badgeQueue.enqueue({103});

    cout << "Queue after 3 badge scans:\n";
    badgeQueue.display();

    // Process one badge
    Badge granted = badgeQueue.dequeue();
    cout << "\nAccess granted to Badge ID: " << granted.id << "\n";

    // Peek at next badge
    cout << "Next in line: " << badgeQueue.peek().id << "\n";

    cout << "\nQueue after one dequeue:\n";
    badgeQueue.display();

    return 0;
}