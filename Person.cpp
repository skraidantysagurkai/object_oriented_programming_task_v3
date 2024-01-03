//
// Created by Rokas Sabaitis on 2023-12-29.
//

#include "Person.h"
#include <iostream>

Person::Person(const std::string &firstName, const std::string &lastName)
        : first_name(firstName), last_name(lastName) {}

Person::~Person() = default;

Person::Person(const Person &other)
        : first_name(other.first_name), last_name(other.last_name) {}

Person &Person::operator=(const Person &other) {
    if (this != &other) {
        first_name = other.first_name;
        last_name = other.last_name;
    }
    return *this;
}

const std::string &Person::getFirstName() const {
    return first_name;
}

const std::string &Person::getLastName() const {
    return last_name;
}

bool PersonComp::operator()(const Person &a, const Person &b) {
    if (a.getFirstName() == b.getFirstName()) {
        return a.getLastName() < b.getLastName();
    } else {
        return a.getFirstName() < b.getFirstName();
    }
}

