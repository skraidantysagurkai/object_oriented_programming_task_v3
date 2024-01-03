#include "libraries.h"
#include "UserInterface.h"
#include "FileGenerator.h"
#include <filesystem>

#include <chrono>


void V01() {
    UserInterface();
}

void V02() {
    //  FileGenerator(1000, "../data/gen-1000.csv");
    //  FileGenerator(10000, 5000,"../data/gen-10000.csv");
    //  FileGenerator(100000, 5000,"../data/gen-100000.csv");
    //  FileGenerator(1000000, 20000,"../data/gen-1000000.csv");
    //  FileGenerator(10000000, 20000,"../data/gen-10000000.csv");

    std::vector<std::string> filePaths = {
            "../data/gen-1000.csv",
            "../data/gen-10000.csv",
            "../data/gen-100000.csv",
            "../data/gen-1000000.csv",
            "../data/gen-10000000.csv"
    };

    for (const std::string &filePath: filePaths) {
        std::cout << filePath << std::endl;

        auto start = std::chrono::high_resolution_clock::now();
        TextReader rd = TextReader(filePath);

        auto read_duration = std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::high_resolution_clock::now() - start);
        std::cout << "Read Time: " << read_duration.count() << " milliseconds" << std::endl;

        std::vector<Student> under_5_students;
        std::vector<Student> over_5_students;
        std::vector<Student> fileData = rd.getScrapedStudentData();
        //std::cout << fileData.size() << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for (const Student &student: fileData) {
            if (student.calculateAverageGrade() < 5) {
                under_5_students.push_back(student);
            } else {
                over_5_students.push_back(student);
            }
        }
        auto sort_to_groups_duration = std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::high_resolution_clock::now() - start);
        std::cout << "Sort Time: " << sort_to_groups_duration.count() << " milliseconds" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        FileGenerator(over_5_students, "../data/OverFiveStudents.csv");
        FileGenerator(under_5_students, "../data/UnderFiveStudents.csv");
        auto write_duration = std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::high_resolution_clock::now() - start);

        std::cout << "Write Time: " << write_duration.count() << " milliseconds" << std::endl;

        std::cout << "\n" << std::endl;
    }
}

void V03() {

    std::vector<std::string> filePaths = {
            "../data/gen-1000.csv",
            "../data/gen-10000.csv",
            "../data/gen-100000.csv",
            "../data/gen-1000000.csv",
            "../data/gen-10000000.csv"
    };
    for (const std::string &filePath: filePaths) {
        std::cout << filePath << std::endl;

        auto start = std::chrono::high_resolution_clock::now();
        TextReader rd = TextReader(filePath, false);

        auto read_duration = std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::high_resolution_clock::now() - start);
        std::cout << "Read Time: " << read_duration.count() << " milliseconds" << std::endl;

        std::list<Student> under_5_students;
        std::list<Student> over_5_students;
        std::list<Student> fileData = rd.getScrapedStudentDataList();
        //std::cout << fileData.size() << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for (const Student &student: fileData) {
            if (student.calculateAverageGrade() < 5) {
                under_5_students.push_back(student);
            } else {
                over_5_students.push_back(student);
            }
        }
        auto sort_to_groups_duration = std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::high_resolution_clock::now() - start);
        std::cout << "Sort Time: " << sort_to_groups_duration.count() << " milliseconds" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        FileGenerator(over_5_students, "../data/OverFiveStudents.csv");
        FileGenerator(under_5_students, "../data/UnderFiveStudents.csv");
        auto write_duration = std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::high_resolution_clock::now() - start);

        std::cout << "Write Time: " << write_duration.count() << " milliseconds" << std::endl;

        std::cout << "\n" << std::endl;
    }
}


template<typename T, typename Predicate>
void approach2(T &source, T &destination, Predicate predicate) {
    auto it = std::remove_if(source.begin(), source.end(), predicate);
    destination.insert(destination.end(), std::make_move_iterator(it), std::make_move_iterator(source.end()));
    source.erase(it, source.end());
}

template<typename T, typename Predicate>
void approach1(T &source, T &destination1, T &destination2, Predicate predicate) {
    for (const auto &element: source) {
        if (predicate(element)) {
            destination1.push_back(element);
        } else {
            destination2.push_back(element);
        }
    }
}

template<typename T, typename Predicate>
void approach3(T &source, T &destination1, T &destination2, Predicate predicate) {
    auto partition_point = std::partition(source.begin(), source.end(), predicate);
    destination1.insert(destination1.end(), std::make_move_iterator(source.begin()),
                        std::make_move_iterator(partition_point));
    destination2.insert(destination2.end(), std::make_move_iterator(partition_point),
                        std::make_move_iterator(source.end()));
}


void V10() {
    std::vector<std::string> filePaths = {
            "../data/gen-1000.csv",
            "../data/gen-10000.csv",
            "../data/gen-100000.csv",
            "../data/gen-1000000.csv",
            "../data/gen-10000000.csv"
    };

    bool allFilesExist = true;

    for (const std::string &filePath: filePaths) {
        std::ifstream file(filePath);

        if (!file.good()) {
            allFilesExist = false;
        }
    }

    // Generating files
    if (!allFilesExist) {
        FileGenerator(1000, "../data/gen-1000.csv");
        FileGenerator(10000, "../data/gen-10000.csv");
        FileGenerator(100000, "../data/gen-100000.csv");
        FileGenerator(1000000, "../data/gen-1000000.csv");
        FileGenerator(10000000, "../data/gen-10000000.csv");
    }


    std::cout << "Strategy 1" << std::endl;
    std::cout << "LISTS" << std::endl;
    for (const std::string &filePath: filePaths) {
        std::cout << filePath << std::endl;

        TextReader rd = TextReader(filePath, false);

        std::list<Student> fileData = rd.getScrapedStudentDataList();
        std::list<Student> under5students;
        std::list<Student> over5students;

        auto start = std::chrono::high_resolution_clock::now();

        // Define your criteria using a lambda function
        auto criteria = [](Student student) { return student.calculateAverageGrade() < 5; };
        // Move elements from sourceList to destinationList based on the criteria
        approach1(fileData, under5students, over5students, criteria);

        auto sort_to_groups_duration = std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::high_resolution_clock::now() - start);
        std::cout << "Sort Time: " << sort_to_groups_duration.count() << " milliseconds" << std::endl;

    }

    std::cout << "VECTOR" << std::endl;
    for (const std::string &filePath: filePaths) {
        std::cout << filePath << std::endl;

        TextReader rd = TextReader(filePath);

        std::vector<Student> fileData = rd.getScrapedStudentData();
        std::vector<Student> under5students;
        std::vector<Student> over5students;

        auto start = std::chrono::high_resolution_clock::now();

        // Define your criteria using a lambda function
        auto criteria = [](Student student) { return student.calculateAverageGrade() < 5; };
        // Move elements from sourceList to destinationList based on the criteria
        approach1(fileData, under5students, over5students, criteria);

        auto sort_to_groups_duration = std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::high_resolution_clock::now() - start);

        std::cout << "Sort Time: " << sort_to_groups_duration.count() << " milliseconds" << std::endl;
    }


    std::cout << "Strategy 2" << std::endl;
    std::cout << "LISTS" << std::endl;
    for (const std::string &filePath: filePaths) {
        std::cout << filePath << std::endl;

        TextReader rd = TextReader(filePath, false);

        std::list<Student> fileData = rd.getScrapedStudentDataList();
        std::list<Student> under5students;

        auto start = std::chrono::high_resolution_clock::now();

        // Define your criteria using a lambda function
        auto criteria = [](Student &student) { return student.calculateAverageGrade() < 5; };
        // Move elements from sourceList to destinationList based on the criteria
        approach2(fileData, under5students, criteria);

        auto sort_to_groups_duration = std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::high_resolution_clock::now() - start);
        std::cout << "Sort Time: " << sort_to_groups_duration.count() << " milliseconds" << std::endl;

    }

    std::cout << "VECTOR" << std::endl;
    for (const std::string &filePath: filePaths) {
        std::cout << filePath << std::endl;

        TextReader rd = TextReader(filePath);

        std::vector<Student> fileData = rd.getScrapedStudentData();
        std::vector<Student> under5students;

        auto start = std::chrono::high_resolution_clock::now();

        // Define your criteria using a lambda function
        auto criteria = [](Student &student) { return student.calculateAverageGrade() < 5; };
        // Move elements from sourceList to destinationList based on the criteria
        approach2(fileData, under5students, criteria);

        auto sort_to_groups_duration = std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::high_resolution_clock::now() - start);

        std::cout << "Sort Time: " << sort_to_groups_duration.count() << " milliseconds" << std::endl;
    }


    std::cout << "Strategy 3" << std::endl;
    std::cout << "LISTS" << std::endl;
    for (const std::string &filePath: filePaths) {
        std::cout << filePath << std::endl;

        TextReader rd = TextReader(filePath, false);

        std::list<Student> fileData = rd.getScrapedStudentDataList();
        std::list<Student> under5students;
        std::list<Student> over5students;

        auto start = std::chrono::high_resolution_clock::now();

        // Define your criteria using a lambda function
        auto criteria = [](Student &student) { return student.calculateAverageGrade() < 5; };
        // Move elements from sourceList to destinationList based on the criteria
        approach3(fileData, under5students, over5students, criteria);

        auto sort_to_groups_duration = std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::high_resolution_clock::now() - start);
        std::cout << "Sort Time: " << sort_to_groups_duration.count() << " milliseconds" << std::endl;

    }

    std::cout << "VECTOR" << std::endl;
    for (const std::string &filePath: filePaths) {
        std::cout << filePath << std::endl;

        TextReader rd = TextReader(filePath);

        std::vector<Student> fileData = rd.getScrapedStudentData();
        std::vector<Student> under5students;
        std::vector<Student> over5students;

        auto start = std::chrono::high_resolution_clock::now();

        // Define your criteria using a lambda function
        auto criteria = [](Student &student) { return student.calculateAverageGrade() < 5; };
        // Move elements from sourceList to destinationList based on the criteria
        approach3(fileData, under5students, over5students, criteria);

        auto sort_to_groups_duration = std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::high_resolution_clock::now() - start);

        std::cout << "Sort Time: " << sort_to_groups_duration.count() << " milliseconds" << std::endl;
    }
}

void V11() {
    std::vector<std::string> filePaths = {
            "../data/gen-1000.csv",
            "../data/gen-10000.csv",
            "../data/gen-100000.csv",
            "../data/gen-1000000.csv",
            "../data/gen-10000000.csv"
    };

    bool allFilesExist = true;

    for (const std::string &filePath: filePaths) {
        std::ifstream file(filePath);

        if (!file.good()) {
            allFilesExist = false;
        }
    }

    // Generating files
    if (!allFilesExist) {
        FileGenerator(1000, "../data/gen-1000.csv");
        FileGenerator(10000, "../data/gen-10000.csv");
        FileGenerator(100000, "../data/gen-100000.csv");
        FileGenerator(1000000, "../data/gen-1000000.csv");
        FileGenerator(10000000, "../data/gen-10000000.csv");
    }

    for (const std::string &filePath: filePaths) {
        std::cout << filePath << std::endl;

        TextReader rd = TextReader(filePath);

        std::vector<Student> fileData = rd.getScrapedStudentData();
        std::vector<Student> under5students;
        std::vector<Student> over5students;

        auto start = std::chrono::high_resolution_clock::now();

        // Define your criteria using a lambda function
        auto criteria = [](Student &student) { return student.calculateAverageGrade() < 5; };
        // Move elements from sourceList to destinationList based on the criteria
        approach3(fileData, under5students, over5students, criteria);

        auto sort_to_groups_duration = std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::high_resolution_clock::now() - start);

        std::cout << "Sort Time: " << sort_to_groups_duration.count() << " milliseconds" << std::endl;
    }
}

void V12() {
    std::vector<int> grades{1, 2, 3, 4, 5, 6, 7, 8, 9};
    Student student1 = Student("Jonas", "Jonaitis");

    student1.setGradeData(grades);
    student1.displayInfo();

    Student student2 = Student(student1);
    student2.displayInfo();

    Student student3 = student1;
    student3.displayInfo();

    // This line is impossible to build as Person is an abstract class and cannot be constructed.
    // Person person = Person("Jonas", "Ponaitis");
}


int main() {
    std::string input;

    while (true) {
        std::cout << "Please choose which release to launch?\n"
                     "v.01 : 1, v.02 : 2, v.03 : 3, v1.0 : 4, v1.1 : 5, v1.2/v1.5 : 6\n";

        std::getline(std::cin, input);

        if (input == "1") {
            V01();
            break;
        } else if (input == "2") {
            V02();
            break;
        } else if (input == "3") {
            V03();
            break;
        } else if (input == "4") {
            V10();
            break;
        } else if (input == "5") {
            V11();
            break;
        } else if (input == "6") {
            V12();
            break;
        } else {
            std::cout << "Invalid Input.\n" << std::endl;
        }
    }
    return 0;
}