//
// Created by Rokas Sabaitis on 2023-10-01.
//

#include "libraries.h"
#include "UserInterface.h"
#include "Student.h"

UserInterface::UserInterface() {
    Greet();
    std::string insert_method = dataInsertMethod();

    if (insert_method == "manual") {
        // Executing a series of events if the user chooses manual insertion
        std::pair<std::string, std::string> user_output = userInsertMethod();

        Student student(user_output.first, user_output.second);
        manualGradeInsertion(student);

        std::pair<std::string, double> aggregated_data = manualGradeAggregationOperation(student);
        printUserContent(student, aggregated_data);
    } else {
        TextReader parser;
        printFileContent(parser.scraped_student_data);
    }
}

void UserInterface::Greet() {
    std::cout << "Hello, this program is made for a University project\n\n";
}

std::string UserInterface::dataInsertMethod() {
    std::string input;

    while (true) {
        std::cout << "Please choose an insert method, either manual or file: ";
        std::getline(std::cin, input);

        if (input == "manual" || input == "file") {
            break;
        } else {
            std::cout << "Invalid Input, check that you wrote manual or file correctly." << std::endl;
        }
    }
    return input;
}

std::pair<std::string, std::string> UserInterface::userInsertMethod() {
    std::string first_name;
    std::string last_name;
    std::string input;

    std::cout << "Please insert your first name and last name: ";
    std::getline(std::cin, input);

    // Create a string stream to separate the full name into parts
    std::istringstream iss(input);

    // Extract the first part (the name) from the string stream
    iss >> first_name;

    // Use the remaining part of the string stream as the last_name
    std::getline(iss, last_name);

    // Trim any leading whitespace from the last_name
    size_t pos = last_name.find_first_not_of(" \t");
    if (pos != std::string::npos) {
        last_name = last_name.substr(pos);
    }

    return std::make_pair(first_name, last_name);
}

void UserInterface::manualGradeInsertion(Student &student) {
    bool is_generate = checkIfGenerate();

    if (is_generate) {
        student.generateRandomGrades();
    } else {
        addUserGrades(student);
    }
}

bool UserInterface::checkIfGenerate() {
    std::string input;

    while (true) {
        std::cout << "Enter an insert method: manual or generate: ";
        std::getline(std::cin, input);

        if (input == "generate") {
            return true;
        } else if (input == "manual") {
            return false;
        } else {
            std::cout << "Invalid input. Please enter either manual or generate." << std::endl;
        }
    }
}

void UserInterface::addUserGrades(Student &student) {
    int consecutiveEmptyLines = 0;
    int grade;

    while (true) {
        std::cout << "Enter an integer or press Enter twice to finish: ";
        std::string input;

        // Read a line of input from the user
        std::getline(std::cin, input);

        // Check if the input is empty (an empty line)
        if (input.empty()) {
            consecutiveEmptyLines++;
            if (consecutiveEmptyLines == 2) {
                break; // Exit the loop if two consecutive empty lines are entered
            }
        } else {
            consecutiveEmptyLines = 0; // Reset the consecutive empty lines counter

            // Use a string stream to convert the input to an integer
            std::stringstream ss(input);
            if (ss >> grade) {
                student.add_grade(grade);
            } else {
                std::cout << "Invalid input. Please enter a valid integer." << std::endl;
            }
        }
    }
}

std::pair<std::string, double> UserInterface::manualGradeAggregationOperation(Student &student) {
    std::string operation;

    while (true) {
        std::cout << "Choose an operation (average or median) or 'quit' to exit: ";
        std::cin >> operation;

        if (operation == "average") {
            return std::make_pair(operation, student.calculateAverageGrade());
        } else if (operation == "median") {
            return std::make_pair(operation, student.calculateMedianGrade());
        } else if (operation == "quit") {
            std::cout << "Exiting the program, goodbye." << std::endl;
            std::exit(0);
        } else {
            std::cerr << "Invalid operation. Please enter 'average', 'median', or 'quit'." << std::endl;
        }
    }
}

void UserInterface::printUserContent(const Student &student, const std::pair<std::string, double> &aggregated_data) {
    // Print the table header
    std::cout << std::left << std::setw(30) << "Name" << "|"
              << std::right << std::setw(30) << "Surname" << "|"
              << std::right << std::setw(15) << aggregated_data.first << std::endl;

    // Print the separator line
    std::cout << std::setfill('_') << std::setw(30) << "" << "|"
              << std::setw(30) << "" << "|"
              << std::setw(15) << "" << std::setfill(' ') << std::endl;

    // Print the data
    std::cout << std::left << std::setw(30) << student.getFirstName() << "|"
              << std::right << std::setw(30) << student.getLastName() << "|"
              << std::right << std::setw(15) << std::setprecision(2) << aggregated_data.second << std::endl;
}

void UserInterface::printFileContent(std::vector<Student> &student_list) {
    // Sort the vector by first_name and last_name
    std::sort(student_list.begin(), student_list.end(), studentComp());

    // Print header
    std::cout << std::left << std::setw(30) << "Name" << "|"
              << std::right << std::setw(30) << "Surname" << "|"
              << std::right << std::setw(15) << "Avg. Grade" << "|"
              << std::right << std::setw(15) << "Med. Grade" << std::endl;

    for (Student &student: student_list) {
        // Print the separator line
        std::cout << std::setfill('_') << std::setw(30) << "" << "|"
                  << std::setw(30) << "" << "|"
                  << std::setw(15) << "" << "|"
                  << std::setw(15) << "" << std::setfill(' ') << std::endl;

        // Print the data
        std::cout << std::left << std::setw(30) << student.getFirstName() << "|"
                  << std::right << std::setw(30) << student.getLastName() << "|"
                  << std::right << std::setw(15) << std::setprecision(2) << student.calculateAverageGrade() << "|"
                  << std::right << std::setw(15) << std::setprecision(2) << student.calculateMedianGrade() << std::endl;
    }
}
