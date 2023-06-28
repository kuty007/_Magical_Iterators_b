//
// Created by asaf7 on 6/4/2023.
//
#include <stdexcept>
#include <cmath>
#include "DoublyLinkedList.h"

using namespace std;

DoublyLinkedList::~DoublyLinkedList() {
    Node *current = this->head;
    while (current != nullptr) {
        Node *next = current->next;
        delete current;
        current = next;
    }
}



void DoublyLinkedList::addElement(int data) {
    Node *new_node = new Node{data, isPrime(data), nullptr, nullptr, nullptr};
    // if list is empty
    if (this->head == nullptr) {
        this->head = new_node;
        this->tail = new_node;
        this->head_prime = new_node->is_prime ? new_node : nullptr;
        this->tail_prime = new_node->is_prime ? new_node : nullptr;
        this->prime_size += new_node->is_prime ? 1 : 0;
        this->size++;
        new_node->ascIndex = 0;
        new_node->crossIndex = 0;
        return;
    }
    if (new_node->is_prime) {
        prime_size++;
        addPrimeElement(new_node);
    }
    Node *current = this->head;
    while (current != nullptr) {
        if (current->data == data) {
            return;
        }
        if (data < current->data) {
            if (current == this->head) {
                new_node->next = this->head;
                this->head->prev = new_node;
                this->head = new_node;
                this->size++;
                return;
            }
            new_node->next = current;
            new_node->prev = current->prev;
            current->prev->next = new_node;
            current->prev = new_node;
            this->size++;
            return;
        }
        current = current->next;
    }
    new_node->prev = this->tail;
    this->tail->next = new_node;
    this->tail = new_node;
    this->size++;
}


Node *DoublyLinkedList::getHeadPrime() {
    return this->head_prime;
}

Node *DoublyLinkedList::getTail() {
    return this->tail;
}

Node *DoublyLinkedList::getHead() {
    return this->head;
}


int DoublyLinkedList::getSize() {
    return this->size;
}


void DoublyLinkedList::removeElement(int data) {
    // If the list is empty
    Node *current = this->head;
    while (current != nullptr) {
        if (current->data == data) {
            // Update previous and next pointers
            if (current == this->head) {
                this->head = current->next;
            } else {
                current->prev->next = current->next;
            }

            if (current == this->tail) {
                this->tail = current->prev;
            } else {
                current->next->prev = current->prev;
            }

            // Update prime list pointers
            if (current->is_prime) {
                if (current == this->head_prime) {
                    this->head_prime = current->next_prime;
                } else {
                    current->prev_prime->next_prime = current->next_prime;
                }

                if (current == this->tail_prime) {
                    this->tail_prime = current->prev_prime;
                } else {
                    current->next_prime->prev_prime = current->prev_prime;
                }

                prime_size--;
            }

            delete current;
            this->size--;

            return;
        }
        current = current->next;
        if (current == nullptr) {
            //throw "Element not found";
            throw std::runtime_error("Element not found");
        }
    }
}

/// Returns true if the number is prime, false otherwise
bool DoublyLinkedList::isPrime(int num) {
    if (num <= 1) {
        return false;
    }
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int DoublyLinkedList::getPrimeSize() const {
    return this->prime_size;
}
///
/// \param element
///set the element in the prime list
void DoublyLinkedList::addPrimeElement(Node *element) {
    if (this->head_prime == nullptr) {
        this->head_prime = element;
        this->tail_prime = element;
        return;
    }
    Node *current = this->head_prime;
    while (current != nullptr) {
        if (current->data == element->data) {
            return;
        }
        if (element->data < current->data) {
            if (current == this->head_prime) {
                element->next_prime = this->head_prime;
                this->head_prime->prev_prime = element;
                this->head_prime = element;
                return;
            }
            element->next_prime = current;
            element->prev_prime = current->prev_prime;
            current->prev_prime->next_prime = element;
            current->prev_prime = element;
            return;
        }
        current = current->next_prime;
    }
    element->prev_prime = this->tail_prime;
    this->tail_prime->next_prime = element;
    this->tail_prime = element;
}

void DoublyLinkedList::updateAscIndex() {
    Node *current = this->head;
    int index = 0;
    while (current != nullptr) {
        current->ascIndex = index;
        index++;
        current = current->next;
    }

}

void DoublyLinkedList::updateCrossIndex() {
    Node *currentStart = this->head;
    Node *currentEnd = this->tail;
    Node *current = currentStart;
    int index = 0;
    while (index < this->size) {
        current->crossIndex = index;
        if (index % 2 == 0) {
            current = currentEnd;
            currentStart = currentStart->next;
        } else {
            current = currentStart;
            currentEnd = currentEnd->prev;
        }
        index++;
    }
}





