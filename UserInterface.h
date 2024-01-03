//
// Created by Rokas Sabaitis on 2023-10-01.
//

#ifndef OP_USERINTERFACE_H
#define OP_USERINTERFACE_H

class Student;

class UserInterface {
public:
    UserInterface();

private:
    static void Greet();

    static std::string dataInsertMethod();

    static std::pair<std::string, std::string> userInsertMethod();

    static void manualGradeInsertion(Student &student);

    static bool checkIfGenerate();

    static void addUserGrades(Student &student);

    static std::pair<std::string, double> manualGradeAggregationOperation(Student &student);

    static void printUserContent(const Student &student, const std::pair<std::string, double> &aggregated_data);

    static void printFileContent(std::vector<Student> &student_list);
};

#endif //OP_USERINTERFACE_H
