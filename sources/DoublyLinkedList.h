//
// Created by asaf7 on 6/4/2023.
//

#ifndef MAGICAL_ITERATORS_A_DOUBLYLINKEDLIST_H
#define MAGICAL_ITERATORS_A_DOUBLYLINKEDLIST_H

struct Node {
    int data;
    bool is_prime;
    Node *prev;
    Node *next;
    Node *next_prime;
    Node *prev_prime;
};

class DoublyLinkedList {
private:
    Node *head;
    Node *tail;
    Node *head_prime;
    Node *tail_prime;
    int size;
    int prime_size{};


    bool isPrime(int num);

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), head_prime(nullptr), tail_prime(nullptr), size(0) , prime_size(0)
                         {}

    ~DoublyLinkedList();

    void addElement(int element);

    void removeElement(int element);

    int getSize();
    int getPrimeSize();


    Node *getHead();

    Node *getTail();

    Node *getHeadPrime();

    void addElement2(int data);

    void removeElement2(int element);
};


#endif //MAGICAL_ITERATORS_A_DOUBLYLINKEDLIST_H
