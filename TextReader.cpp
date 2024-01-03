//
// Created by Rokas Sabaitis on 2023-10-01.
//
#include "libraries.h"
#include "TextReader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <algorithm>    // std::min


// File stream parser.
// Note: Haven't tried to open other format files than .txt, however structure should work with most text documents
// with minimal adjustment.
TextReader::TextReader() {
    std::cout << "Enter the filename (Absolute path): ";
    std::cin >> file_path;

    try {
        // Call the function to read the text file
        readTextFile(file_path);
    } catch (const std::exception &e) {
        // Catch and print any exceptions that occurred
        std::cerr << e.what() << std::endl;
    }
}

TextReader::TextReader(const std::string &fileName, bool vector) {

    if (vector) {
        try {
            // Call the function to read the text file
            readStudentDataFromCSV(fileName);
        } catch (const std::exception &e) {
            // Catch and print any exceptions that occurred
            std::cerr << e.what() << std::endl;
        }
    } else {
        try {
            // Call the function to read the text file
            readStudentDataFromCSV_list(fileName);
        } catch (const std::exception &e) {
            // Catch and print any exceptions that occurred
            std::cerr << e.what() << std::endl;
        }
    }
}

void TextReader::readTextFile(const std::string &file_name) {
    // Attempt to open the file
    std::ifstream file(file_name);

    // Check if the file is open
    if (!file.is_open()) {
        throw std::runtime_error("Error: Unable to open file.");
    }

    // Skip the first line
    std::string dummyLine;
    std::getline(file, dummyLine);

    std::string line;
    // Read contents of file
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, surname;

        // Extract name and surname
        if (iss >> name >> surname) {
            int grade;
            Student student(name, surname);
            // Extract grades
            while (iss >> grade) {
                student.add_grade(grade);
            }

            // Create a Student object and add it to the vector
            scraped_student_data.push_back(student);
        }
    }
    // Close the file
    file.close();
}

std::mutex dataMutex;

void readCSV(const std::string &filename, std::vector<Student> &data, int startLine, int endLine) {
    std::ifstream file(filename);
    std::string line;

    int lineCount = 0;

    while (std::getline(file, line)) {

        // Check if the current line is within the specified range for this thread
        if (lineCount >= startLine && lineCount < endLine) {
            std::stringstream ss(line);
            std::string firstName, lastName;
            std::vector<int> grades;

            // Extract first and last names
            std::getline(ss, firstName, ',');
            std::getline(ss, lastName, ',');

            // Extract grades
            int grade;
            while (ss >> grade) {
                grades.push_back(grade);

                // Check for comma and ignore it
                if (ss.peek() == ',') {
                    ss.ignore();
                }
            }

            Student student = Student(firstName, lastName);
            student.setGradeData(grades);
            // Use a lock to protect the shared data (students vector)
            std::lock_guard<std::mutex> lock(dataMutex);
            data.emplace_back(student);
        }

        ++lineCount;

        // Break out of the loop if we have reached the endLine
        if (lineCount == endLine) {
            break;
        }
    }
}

void TextReader::readStudentDataFromCSV(const std::string &fileName) {

    const int totalThreads = 4;  // Adjust based on the desired number of threads

    // Calculate the number of lines each thread should read
    int linesPerThread = 0;
    {
        std::ifstream file(fileName);
        std::string line;
        while (std::getline(file, line)) {
            ++linesPerThread;
        }
    }
    linesPerThread /= totalThreads;

    // Create threads
    std::vector<std::thread> threads;
    for (int i = 0; i < totalThreads; ++i) {
        int startLine = i * linesPerThread;
        int endLine = (i == totalThreads - 1) ? INT_MAX : (i + 1) * linesPerThread;


        threads.emplace_back(readCSV, std::ref(fileName), std::ref(scraped_student_data), startLine, endLine);
    }

    // Wait for threads to finish
    for (auto &thread: threads) {
        thread.join();
    }
}

std::vector<Student> &TextReader::getScrapedStudentData() {
    return scraped_student_data;
}

std::list<Student> &TextReader::getScrapedStudentDataList() {
    return scraped_student_data_list;
}

void readCSV_list(const std::string &filename, std::list<Student> &data, int startLine, int endLine) {
    std::ifstream file(filename);
    std::string line;

    int lineCount = 0;

    while (std::getline(file, line)) {

        // Check if the current line is within the specified range for this thread
        if (lineCount >= startLine && lineCount < endLine) {
            std::stringstream ss(line);
            std::string firstName, lastName;
            std::vector<int> grades;

            // Extract first and last names
            std::getline(ss, firstName, ',');
            std::getline(ss, lastName, ',');

            // Extract grades
            int grade;
            while (ss >> grade) {
                grades.push_back(grade);

                // Check for comma and ignore it
                if (ss.peek() == ',') {
                    ss.ignore();
                }
            }

            Student student = Student(firstName, lastName);
            student.setGradeData(grades);
            // Use a lock to protect the shared data (students vector)
            std::lock_guard<std::mutex> lock(dataMutex);
            data.emplace_back(student);
        }

        ++lineCount;

        // Break out of the loop if we have reached the endLine
        if (lineCount == endLine) {
            break;
        }
    }
}

void TextReader::readStudentDataFromCSV_list(const std::string &fileName) {

    const int totalThreads = 4;  // Adjust based on the desired number of threads

    // Calculate the number of lines each thread should read
    int linesPerThread = 0;
    {
        std::ifstream file(fileName);
        std::string line;
        while (std::getline(file, line)) {
            ++linesPerThread;
        }
    }
    linesPerThread /= totalThreads;

    // Create threads
    std::vector<std::thread> threads;
    for (int i = 0; i < totalThreads; ++i) {
        int startLine = i * linesPerThread;
        int endLine = (i == totalThreads - 1) ? INT_MAX : (i + 1) * linesPerThread;


        threads.emplace_back(readCSV_list, std::ref(fileName), std::ref(scraped_student_data_list), startLine, endLine);
    }

    // Wait for threads to finish
    for (auto &thread: threads) {
        thread.join();
    }
}