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

void DoublyLinkedList::addElement2(int data) {
    Node *new_node = new Node{data, isPrime(data), nullptr, nullptr, nullptr};
    this->prime_size += new_node->is_prime ? 1 : 0;
    Node *last_prime = this->head_prime;
    // if list is empty
    if (this->head == nullptr) {
        this->head = new_node;
        this->tail = new_node;
        this->head_prime = new_node->is_prime ? new_node : nullptr;
        this->tail_prime = new_node->is_prime ? new_node : nullptr;
        this->size++;
        return;
    }
    if (head_prime == nullptr) {
        this->head_prime = new_node->is_prime ? new_node : nullptr;
        this->tail_prime = new_node->is_prime ? new_node : nullptr;
    }
    // if list is not empty add in ascending order to the list and if the new node is prime add it to the prime list and update the pointers if it is already exist do nothing
    Node *current = this->head;
    while (current != nullptr) {
        if (current->data == data) {
            if (new_node->is_prime) {
                this->prime_size--;
            }
            return;
        }
        if (current->is_prime && current->data < data) {
            last_prime = current;
        }
        if (data < current->data) {
            if (current == this->head) {
                new_node->next = this->head;
                this->head->prev = new_node;
                this->head = new_node;
                this->size++;
                if (new_node->is_prime) {
                    new_node->next_prime = this->head_prime;
                    this->head_prime = new_node;
                }
                return;
            }
            new_node->next = current;
            new_node->prev = current->prev;
            current->prev->next = new_node;
            current->prev = new_node;
            this->size++;
            if (new_node->is_prime && last_prime != nullptr) {
                if (last_prime->data < new_node->data) {
                    new_node->next_prime = last_prime->next_prime;
                    last_prime->next_prime = new_node;
                }
                if (current == this->head_prime) {
                    new_node->next_prime = this->head_prime;
                    this->head_prime = new_node;
                }
            }
            return;
        }
        current = current->next;
    }
    // if the new node is the biggest in the list
    new_node->prev = this->tail;
    this->tail->next = new_node;
    this->tail = new_node;
    this->size++;
    if (new_node->is_prime) {
        if (this->tail_prime != new_node) {
            this->tail_prime->next_prime = new_node;
        }
        this->tail_prime = new_node;

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
        this->size++;
        return;
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
    new_node -> prev = this->tail;
    this->tail->next = new_node;
    this->tail = new_node;
    this->size++;
    // do same for prime list
    if (new_node->is_prime) {
        prime_size++;
        if (this->head_prime == nullptr) {
            this->head_prime = new_node;
            this->tail_prime = new_node;
            return;
        }
        Node *current_prime = this->head_prime;
        while (current_prime != nullptr) {
            if (current_prime->data == data) {
                return;
            }
            if (data < current_prime->data) {
                if (current_prime == this->head_prime) {
                    new_node->next_prime = this->head_prime;
                    this->head_prime->prev_prime = new_node;
                    this->head_prime = new_node;
                    return;
                }
                new_node->next_prime = current_prime;
                new_node->prev_prime = current_prime->prev_prime;
                current_prime->prev_prime->next_prime = new_node;
                current_prime->prev_prime = new_node;
                return;
            }
            current_prime = current_prime->next_prime;
        }
        new_node->prev_prime = this->tail_prime;
        this->tail_prime->next_prime = new_node;
        this->tail_prime = new_node;
    }

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

void DoublyLinkedList::removeElement(int element) {
    Node *current = this->head;
    while (current != nullptr) {
        if (current->data == element) {
            if (current == this->head) {
                this->head = current->next;
                if (this->head != nullptr) {
                    this->head->prev = nullptr;
                }
                if (current->is_prime) {
                    this->head_prime = current->next_prime;
                    if (this->head_prime != nullptr) {
                        this->head_prime->prev->next_prime = nullptr;
                        this->head_prime->prev = nullptr;
                    }
                }
                delete current;
                this->size--;

                return;
            }
            if (current == this->tail) {
                this->tail = current->prev;
                this->tail->next = nullptr;
                if (current->is_prime) {
                    this->tail->next_prime = nullptr;
                }
                delete current;
                this->size--;

                return;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            if (current->is_prime) {
                current->prev->next_prime = current->next_prime;
                current->next_prime->prev = current->prev;
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
void DoublyLinkedList::removeElement2(int element) {
    Node *current = this->head;
    while (current != nullptr) {
        if (current->data == element) {
            if (current== this->head){
                this->head = current->next;
                if (this->head != nullptr) {
                    this->head->prev = nullptr;
                }
                if (current->is_prime) {
                    this->head_prime = current->next_prime;
                    if (this->head_prime != nullptr) {
                        this->head_prime->prev->next_prime = nullptr;
                        this->head_prime->prev = nullptr;
                    }
                    this->prime_size--;
                }
                delete current;
                this->size--;
                return;
            }
            if (current == this->tail) {
                this->tail = current->prev;
                this->tail->next = nullptr;
                if (current->is_prime) {
                    this->tail->next_prime = nullptr;
                    prime_size--;
                }
                delete current;
                this->size--;
                return;
            }
            current->prev->next = current->next;
        }
        }


}


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

int DoublyLinkedList::getPrimeSize() {
    return this->prime_size;
}
