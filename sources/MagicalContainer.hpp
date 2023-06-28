//
// Created by asaf7 on 6/4/2023.
//

#ifndef MAGICAL_ITERATORS_A_MAGICALCONTAINER_HPP
#define MAGICAL_ITERATORS_A_MAGICALCONTAINER_HPP

#include "DoublyLinkedList.h"

using namespace std;

namespace ariel {

    class MagicalContainer {
    private:

    public:
        DoublyLinkedList container;

        MagicalContainer();

        ~MagicalContainer();

        void addElement(int element);

        void removeElement(int element);
        bool operator==(const MagicalContainer &other) const{
            return &this->container == &other.container;};


        int size();

        class AscendingIterator {
        private:
            MagicalContainer &container;
            Node *current;

        public:

            // LT and GT
            bool operator<(const AscendingIterator &other) const;

            bool operator>(const AscendingIterator &other) const;

            explicit AscendingIterator(MagicalContainer &container);

            AscendingIterator begin();

            AscendingIterator end();

            AscendingIterator(MagicalContainer &container, Node *current );

            AscendingIterator(const AscendingIterator &other);

            AscendingIterator& operator=(const AscendingIterator&);

            AscendingIterator &operator++();

            int operator*();

            bool operator==(const AscendingIterator &other) const;

            bool operator!=(const AscendingIterator &other) const;


        };

        class SideCrossIterator {
        private:
            MagicalContainer &container;
            Node *current , *left , *right;
        public:
            SideCrossIterator begin();

            SideCrossIterator end();

            explicit SideCrossIterator(MagicalContainer &container);

            SideCrossIterator(MagicalContainer &container, Node *current);

            SideCrossIterator(const SideCrossIterator &other);

            SideCrossIterator &operator=(const SideCrossIterator &other);

            SideCrossIterator &operator++();

            int operator*();

            bool operator==(const SideCrossIterator &other) const;

            bool operator!=(const SideCrossIterator &other) const;

            // LT and GT
            bool operator<(const SideCrossIterator &other) const;

            bool operator>(const SideCrossIterator &other) const;
        };

        class PrimeIterator {
        private:
            MagicalContainer &container;
            Node *current;
        public:
            explicit PrimeIterator(MagicalContainer &container);

            PrimeIterator begin();

            PrimeIterator end();

            PrimeIterator(MagicalContainer &container, Node *current);

            PrimeIterator(const PrimeIterator &other);

            PrimeIterator &operator=(const PrimeIterator &other);

            PrimeIterator &operator++();

            int operator*();

            bool operator==(const PrimeIterator &other) const;

            bool operator!=(const PrimeIterator &other) const;

            // LT and GT
            bool operator<(const PrimeIterator &other) const;

            bool operator>(const PrimeIterator &other) const;
        };


    }; // ariel

#endif //MAGICAL_ITERATORS_A_MAGICALCONTAINER_HPP
}