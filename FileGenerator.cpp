//
// Created by Rokas Sabaitis on 2023-10-13.
//

#include "FileGenerator.h"

std::mutex fileMutex;  // Mutex to synchronize file writing

FileGenerator::FileGenerator(int len, string fileName) {
    generateData(len);
    exportStudentDataToCSV(generated_data, fileName);
}

FileGenerator::FileGenerator(std::vector<Student> data, string fileName) {
    exportStudentDataToCSV(data, fileName);
}

// Would like to use abstract Container type, but for some reason it does not work :((
FileGenerator::FileGenerator(std::list<Student> data, string fileName) {
    exportStudentDataToCSV(data, fileName);
}

void FileGenerator::generateData(int student_num) {
    for (int i = 0; i < student_num; ++i) {
        std::ostringstream oss;
        oss << "FirstName_" << i + 1;
        std::string name = oss.str();

        std::ostringstream pss;
        pss << "LastName_" << i + 1;
        std::string last_name = pss.str();

        Student student = Student(name, last_name);
        student.generateRandomGrades(15);
        generated_data.push_back(student);
    }
}

void FileGenerator::writeStudentToCSV(const Student &student, std::ofstream &outputFile) {
    outputFile << student.getFirstName() << "," << student.getLastName();
    for (int grade: student.getGradeData()) {
        outputFile << "," << grade;
    }
    outputFile << "\n";
}

void FileGenerator::writeChunkToCSV(const std::vector<Student> &students, std::ofstream &outputFile) {
    // Acquire lock to ensure exclusive access to the file
    std::lock_guard<std::mutex> lock(fileMutex);

    // Write student data to the file
    for (const auto &student: students) {
        writeStudentToCSV(student, outputFile);
    }
}

void FileGenerator::writeChunkToCSVList(const std::list<Student> &students, std::ofstream &outputFile) {
    // Acquire lock to ensure exclusive access to the file
    std::lock_guard<std::mutex> lock(fileMutex);

    // Write student data to the file
    for (const auto &student: students) {
        writeStudentToCSV(student, outputFile);
    }
}

void FileGenerator::exportStudentDataToCSV(const std::vector<Student> &studentData, const std::string &fileName) {
    std::remove(fileName.c_str());  // Remove the file if it exists to start fresh

    std::ofstream outputFile(fileName);

    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return;
    }

    // Calculate the number of chunks
    const std::size_t dataSize = studentData.size();

    const int totalThreads = 4;  // Adjust based on the desired number of threads

    // Calculate the number of lines each thread should read
    int linesPerThread = dataSize / totalThreads;



    // Create threads for each chunk
    std::vector<std::thread> threads;
    for (std::size_t i = 0; i < totalThreads; ++i) {
        std::size_t startIdx = i * linesPerThread;
        std::size_t endIdx = std::min((i + 1) * linesPerThread, dataSize);

        threads.emplace_back(writeChunkToCSV,
                             std::vector<Student>(studentData.begin() + startIdx, studentData.begin() + endIdx),
                             std::ref(outputFile));
    }

    // Join threads
    for (auto &thread: threads) {
        thread.join();
    }

    outputFile.close();

    std::cout << "CSV file written successfully." << std::endl;
}

void FileGenerator::exportStudentDataToCSV(const std::list<Student> &studentData, const std::string &fileName) {
    std::remove(fileName.c_str());  // Remove the file if it exists to start fresh

    std::ofstream outputFile(fileName);

    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return;
    }

    // Calculate the number of chunks
    const std::size_t dataSize = studentData.size();

    const int totalThreads = 4;  // Adjust based on the desired number of threads

    // Calculate the number of lines each thread should read
    int linesPerThread = dataSize / totalThreads;



    // Create threads for each chunk
    std::vector<std::thread> threads;
    for (std::size_t i = 0; i < totalThreads; ++i) {
        auto startIdx = i * linesPerThread;
        auto endIdx = (i == totalThreads - 1) ? dataSize : (i + 1) * linesPerThread; // if last iter, endIDX = datasize

        // Use std::advance to move the iterator to the starting position
        auto startIterator = studentData.begin();
        std::advance(startIterator, startIdx);

        auto endIterator = startIterator;
        std::advance(endIterator, endIdx - startIdx);

        threads.emplace_back(writeChunkToCSVList, std::list<Student>(startIterator, endIterator), std::ref(outputFile));
    }

    // Join threads
    for (auto &thread: threads) {
        thread.join();
    }

    outputFile.close();

    std::cout << "CSV file written successfully." << std::endl;
}