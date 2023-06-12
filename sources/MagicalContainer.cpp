//
// Created by asaf7 on 6/4/2023.
//

#include <stdexcept>
#include "MagicalContainer.hpp"

namespace ariel {
    // implementation of MagicalContainer
    MagicalContainer::MagicalContainer() : container() {}

    MagicalContainer::~MagicalContainer() {}

    void MagicalContainer::addElement(int element) {
        this->container.addElement(element);
    }

    void MagicalContainer::removeElement(int element) {
        this->container.removeElement(element);
    }

    int MagicalContainer::size() {
        return this->container.getSize();
    }

    // implementation of AscendingIterator
    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container, Node *current, int index)
            : container(
            container), current(current), index(index) {}

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other) : container(other.container),
                                                                                             current(other.current),
                                                                                             index(other.index) {}

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(
            const MagicalContainer::AscendingIterator &other) {
        if(!(this->container == other.container)){
            throw std::runtime_error("not the same container");
        }
        this->current = other.current;
        this->index = other.index;
        return *this;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
        if (this->current == nullptr) {
            throw std::runtime_error("out of range");
        }
        this->current = this->current->next;
        this->index++;
        return *this;
    }

    int MagicalContainer::AscendingIterator::operator*() {
        if (this->current == nullptr) {
            throw std::runtime_error("out of range");
        }
        return this->current->data;
    }

    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const {
        return this->index == other.index;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const {
        return !(*this == other);
    }


    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
        return AscendingIterator(this->container, this->container.container.getHead(), 0);
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
        return AscendingIterator(this->container, nullptr, this->container.size());
    }

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container) : container(container),
                                                                                          current(
                                                                                                  container.container.getHead()),
                                                                                          index(0) {

    }

    bool MagicalContainer::AscendingIterator::operator<(const MagicalContainer::AscendingIterator &other) const {
        if (this->current == nullptr && other.current == nullptr) {
            return false;
        }
        return this->current->data < other.current->data;
    }

    bool MagicalContainer::AscendingIterator::operator>(const MagicalContainer::AscendingIterator &other) const {
        if (this->current == nullptr && other.current == nullptr) {
            return false;
        }
        return this->current->data > other.current->data;
    }

    // implementation of SideCrossIterator
    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container, Node *current, int index)
            : container(
            container), current(current), index(index) {}

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) : container(other.container),
                                                                                             current(other.current) {}


    MagicalContainer::SideCrossIterator &
    MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other) {
        if(!(this->container == other.container)){
            throw std::runtime_error("not the same container");
        }
        this->current = other.current;
        this->index = other.index;
        return *this;

    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
        if (this->current == nullptr) {
            throw std::runtime_error("out of range");
        }
        if (index == container.size()) {
            throw std::runtime_error("out of range");

        }
        //should return one from the left and one from the right alternatively for exmaple: if i have 1,2,3,4,5, i should return 1,5,2,4,3
        if (index % 2 == 0) {
            this->current = right;
            left = left->next;
        } else {
            this->current = left;
            right = right->prev;
        }
        index++;
        return *this;

    }

    int MagicalContainer::SideCrossIterator::operator*() {
        if (this->current == nullptr) {
            throw std::runtime_error("out of range");
        }
        return this->current->data;
    }

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const {

        return this->index == other.index;
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const {
        return !(*this == other);
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
        return {this->container, this->container.container.getHead() , 0};
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
        return {this->container, nullptr , this->container.size()};
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container) : container(container),
                                                                                          current(container.container.getHead()),
                                                                                          left(container.container.getHead()),
                                                                                          right(container.container.getTail()),
                                                                                          index(0) {

    }

    bool MagicalContainer::SideCrossIterator::operator<(const MagicalContainer::SideCrossIterator &other) const {
//
        return this->index < other.index;
    }

    bool MagicalContainer::SideCrossIterator::operator>(const MagicalContainer::SideCrossIterator &other) const {
//
        return this->index > other.index;
    }

    // implementation of PrimeIterator
    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container, Node *current ,int index) : container(
            container), current(current), index(index) {}



    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other) : container(other.container),
                                                                                 current(other.current) ,index(other.index){}

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other) {
        if(!(this->container == other.container)){
            throw std::runtime_error("not the same container");
        }
        this->current = other.current;
        this->index = other.index;
        return *this;

    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
        if (this->current == nullptr) {
            throw std::runtime_error("out of range");
        }
        this->current = this->current->next_prime;
        index++;
        return *this;

    }

    int MagicalContainer::PrimeIterator::operator*() {
        if (this->current == nullptr) {
            throw std::runtime_error("out of range");
        }
        return this->current->data;
    }

    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const {
        return this->index == other.index;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const {
        return !(*this == other);
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
        return {this->container, this->container.container.getHeadPrime() , 0};
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
        return {this->container, nullptr , this->container.container.getPrimeSize()};
    }

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container) : container(container),
                                                                                  current(container.container.getHeadPrime()),index(0) {
    }

    bool MagicalContainer::PrimeIterator::operator<(const MagicalContainer::PrimeIterator &other) const {

        return this->index < other.index;
    }

    bool MagicalContainer::PrimeIterator::operator>(const MagicalContainer::PrimeIterator &other) const {
        return this->index > other.index;
   }


} // ariel
