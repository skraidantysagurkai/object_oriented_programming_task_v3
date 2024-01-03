// Student.h
#ifndef STUDENT_H
#define STUDENT_H

#include "libraries.h"
#include "Person.h"
#include <string>
#include <vector>

class Student : public Person {
public:

    // Constructor
    Student(std::string firstName, std::string lastName);

    Student(const Student &other);  // Copy Constructor

    // Destructor
    ~Student() override;

    // Copy Assignment Operator
    Student &operator=(const Student &other);


    const std::string &getFirstName() const override;

    const std::string &getLastName() const override;

    const std::vector<int> &getGradeData() const;

    void displayInfo() const override;

    // Function to add integers to the series
    void add_grade(int num);

    void setGradeData(const std::vector<int> &grades);

    // Function to calculate the average of the series
    double calculateAverageGrade() const;

    // Function to calculate the median of the series
    double calculateMedianGrade();

    // Function to randomly generate a random series of grades
    void generateRandomGrades(int num_of_grades = 0);

private:
    std::vector<int> grade_data;
    std::string first_name;
    std::string last_name;
};

// Comparator structure for Student structure
struct studentComp {
    bool operator()(const Student &a, const Student &b);
};

#endif // STUDENT_H
