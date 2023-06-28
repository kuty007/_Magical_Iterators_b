//
// Created by asaf7 on 6/4/2023.
//

#include <stdexcept>

#include "MagicalContainer.hpp"

namespace ariel {
    // implementation of MagicalContainer
    ///
    /// \brief constructor
    ///
    MagicalContainer::MagicalContainer() : container() {}

///
/// \brief destructor
///
    MagicalContainer::~MagicalContainer() {}

/// \brief add element to the container
/// \param element
    void MagicalContainer::addElement(int element) {
        this->container.addElement(element);
        this->container.updateCrossIndex(); // update the cross index
        this->container.updateAscIndex(); // update the asc index
    }

/// \brief remove element from the container
/// \param element
///
    void MagicalContainer::removeElement(int element) {
        this->container.removeElement(element); // remove the element
        this->container.updateCrossIndex(); // update the cross index
        this->container.updateAscIndex(); // update the asc index
    }

    /// \brief return the size of the container
    ///
    /// \return int
    int MagicalContainer::size() {
        return this->container.getSize();
    }

    // implementation of AscendingIterator
    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container, Node *current)
            : container(
            container), current(current) {}

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other) : container(other.container),
                                                                                             current(other.current) {}

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(
            const MagicalContainer::AscendingIterator &other) {
        if (this == &other) {
            return *this;
        }
        if (!(this->container == other.container)) {
            throw std::runtime_error("not the same container");
        }
        this->current = other.current;
        return *this;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {

        if (this->current == nullptr) {
            throw std::runtime_error("out of range");
        }
        this->current = this->current->next;
        return *this;
    }

    int MagicalContainer::AscendingIterator::operator*() {

        if (this->current == nullptr) {
            throw std::runtime_error("out of range");
        }
        return this->current->data;
    }

    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const {
        if (this->current == nullptr && other.current == nullptr) {
            return true;
        } else if (this->current == nullptr || other.current == nullptr) {
            return false;
        }

        return this->current->ascIndex == other.current->ascIndex;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const {
        return !(*this == other);
    }


    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
        return {this->container, this->container.container.getHead()};
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
        return {this->container, nullptr};
    }



MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container) : container(container),
                                                                                      current(
                                                                                              container.container.getHead()) {

}

bool MagicalContainer::AscendingIterator::operator<(const MagicalContainer::AscendingIterator &other) const {
    if (&this->container != &other.container) {
        throw std::runtime_error("not the same container");
    }
    if (this->current == nullptr && other.current == nullptr) {
        return false;
    }
    return this->current->data < other.current->data;
}

bool MagicalContainer::AscendingIterator::operator>(const MagicalContainer::AscendingIterator &other) const {
    if (&this->container != &other.container) {
        throw std::runtime_error("not the same container");
    }
    if (this->current == nullptr && other.current == nullptr) {
        return false;
    }
    return this->current->data > other.current->data;
}

// implementation of SideCrossIterator
MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container, Node *current)
        : container(
        container), current(current), left(container.container.getHead()),
          right(container.container.getTail()) {}

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) : container(other.container),
                                                                                         current(other.current),
                                                                                         left(other.left),
                                                                                         right(other.right) {}


MagicalContainer::SideCrossIterator &
MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other) {
    if (this == &other) {
        return *this;
    }
    if (!(this->container == other.container)) {
        throw std::runtime_error("not the same container");
    }
    this->current = other.current;
    this->left = other.left;
    this->right = other.right;
    return *this;
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
    if (this->current == nullptr) {
        throw std::runtime_error("out of range");
    }
//        if (index == container.size()) {
//            throw std::runtime_error("out of range");
//        }
    //should return one from the left and one from the right alternatively for exmaple: if i have 1,2,3,4,5, i should return 1,5,2,4,3
    if (current->crossIndex == container.size() - 1) {
        *this = this->end();
        return *this;
    }

    if (current->crossIndex % 2 == 0) {
        this->current = right;
        left = left->next;
    } else {
        this->current = left;
        right = right->prev;
    }


    return *this;
}

int MagicalContainer::SideCrossIterator::operator*() {
    if (this->current == nullptr) {
        throw std::runtime_error("out of range ");
    }

    return this->current->data;
}

bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const {

    if (this->current == nullptr && other.current == nullptr) {
        return true;
    } else if (this->current == nullptr || other.current == nullptr) {
        return false;
    }
    return this->current->crossIndex == other.current->crossIndex;
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const {
    return !(*this == other);
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
    return {this->container, this->container.container.getHead()};
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
    return {this->container, nullptr};
}

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container) : container(container),
                                                                                      current(container.container.getHead()),
                                                                                      left(container.container.getHead()),
                                                                                      right(container.container.getTail()) {

}

bool MagicalContainer::SideCrossIterator::operator<(const MagicalContainer::SideCrossIterator &other) const {
    if (&this->container != &other.container) {
        throw std::runtime_error("not the same container");
    }
    if (this->current == nullptr && other.current == nullptr) {
        return false;
    }
    if (other.current == nullptr && this->current != nullptr) {
        return true;
    }
    if (this->current == nullptr && other.current != nullptr) {
        return false;
    }
    return this->current->crossIndex < other.current->crossIndex;
}

bool MagicalContainer::SideCrossIterator::operator>(const MagicalContainer::SideCrossIterator &other) const {
    if (&this->container != &other.container) {
        throw std::runtime_error("not the same container");
    }
    if (this->current == nullptr && other.current == nullptr) {
        return false;
    }
    if (other.current == nullptr && this->current != nullptr) {
        return false;
    }
    if (this->current == nullptr && other.current != nullptr) {
        return true;
    }
//
    return this->current->crossIndex > other.current->crossIndex;
}

// implementation of PrimeIterator
MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container, Node *current) : container(
        container), current(current) {}


MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other) : container(other.container),
                                                                             current(other.current) {}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other) {
    if (this == &other) {
        return *this;
    }
    if (!(this->container == other.container)) {
        throw std::runtime_error("not the same container");
    }
    this->current = other.current;
    return *this;

}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
    if (this->current == nullptr) {
        throw std::runtime_error("out of range");
    }
    this->current = this->current->next_prime;
    return *this;

}

int MagicalContainer::PrimeIterator::operator*() {
    if (this->current == nullptr) {
        throw std::runtime_error("out of range");
    }
    return this->current->data;
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const {
    if (&this->container != &other.container) {
        throw std::runtime_error("not the same container");
    }
    if (this->current == nullptr && other.current == nullptr) {
        return true;
    } else if (this->current == nullptr || other.current == nullptr) {
        return false;
    }

    return this->current->ascIndex == other.current->ascIndex;

}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const {
    return !(*this == other);
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
    return {this->container, this->container.container.getHeadPrime()};
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
    return {this->container, nullptr,};
}

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container) : container(container),
                                                                              current(container.container.getHeadPrime()) {
}

bool MagicalContainer::PrimeIterator::operator<(const MagicalContainer::PrimeIterator &other) const {
    if (&this->container != &other.container) {
        throw std::runtime_error("not the same container");
    }
    if (this->current == nullptr && other.current == nullptr) {
        return false;
    }
    if (other.current == nullptr && this->current != nullptr) {
        return true;
    }
    if (this->current == nullptr && other.current != nullptr) {
        return false;
    }
    return this->current->ascIndex < other.current->ascIndex;
}

bool MagicalContainer::PrimeIterator::operator>(const MagicalContainer::PrimeIterator &other) const {
    if (&this->container != &other.container) {
        throw std::runtime_error("not the same container");
    }
    if (this->current == nullptr && other.current == nullptr) {
        return false;
    }
    if (this->current == nullptr && other.current != nullptr) {
        return true;
    }
    return this->current->ascIndex > other.current->ascIndex;
}


} // ariel
