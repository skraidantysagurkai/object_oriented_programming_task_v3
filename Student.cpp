//
// Created by Rokas Sabaitis on 2023-10-01.
//
#include "libraries.h"
#include "Student.h"
#include <mutex>

std::mutex gradeMutex;

// Destructor
Student::~Student() = default;

// Copy Constructor
Student::Student(const Student &other)
        : Person(other), grade_data(other.grade_data) {}

// Copy Assignment Operator
Student &Student::operator=(const Student &other) {
    if (this != &other) {
        Person::operator=(other);
        grade_data = other.grade_data;
    }
    return *this;
}

Student::Student(std::string firstName, std::string lastName)
        : Person(firstName, lastName) {}


const std::string &Student::getFirstName() const {
    return Person::getFirstName();
}

const std::string &Student::getLastName() const {
    return Person::getLastName();
}

const std::vector<int> &Student::getGradeData() const {
    return grade_data;
}

void Student::add_grade(int num) {
    std::lock_guard<std::mutex> lock(gradeMutex);
    grade_data.push_back(num);
}

void Student::setGradeData(const std::vector<int> &grades) {
    grade_data = grades;
}

double Student::calculateAverageGrade() const {
    if (grade_data.empty()) {
        std::cerr << "Error: Cannot calculate average of an empty series." << std::endl;
        return 0.0; // Return 0 in case of an empty series
    }

    int sum = 0;
    for (int num: grade_data) {
        sum += num;
    }
    return static_cast<double>(sum) / grade_data.size(); // NOLINT(*-narrowing-conversions)
}

double Student::calculateMedianGrade() {
    if (grade_data.empty()) {
        std::cerr << "Error: Cannot calculate median of an empty vector." << std::endl;
        return 0.0; // Return 0 in case of an empty vector
    }

    std::sort(grade_data.begin(), grade_data.end());

    size_t size = grade_data.size();
    if (size % 2 == 0) {
        double middle1 = grade_data[size / 2 - 1];
        double middle2 = grade_data[size / 2];
        return (middle1 + middle2) / 2.0;
    } else {
        return grade_data[size / 2];
    }
}

void Student::generateRandomGrades(int num_of_grades) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 10);

    if (num_of_grades == 0) {
        num_of_grades = distribution(gen);
    }

    for (int i = 0; i < num_of_grades; ++i) {
        int randomNum = distribution(gen);
        add_grade(randomNum);
    }
}


void Student::displayInfo() const {
    std::cout << "Student: " << getFirstName() << " " << getLastName() << " " << calculateAverageGrade() << std::endl;
}

bool studentComp::operator()(const Student &a, const Student &b) {
    if (a.getFirstName() == b.getFirstName()) {
        return a.getLastName() < b.getLastName();
    } else {
        return a.getFirstName() < b.getFirstName();
    }
}