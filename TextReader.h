//
// Created by Rokas Sabaitis on 2023-10-01.
//

#ifndef OP_TEXTREADER_H
#define OP_TEXTREADER_H

#include "Student.h"
#include "libraries.h"
#include <list>

class TextReader {
public:
    explicit TextReader(const std::string &fileName, bool vector = true);

    TextReader();

    std::vector<Student> scraped_student_data;
    std::list<Student> scraped_student_data_list;
    std::string file_path;

    std::vector<Student> &getScrapedStudentData();

    std::list<Student> &getScrapedStudentDataList();

private:
    void readTextFile(const std::string &file_name);

    void readStudentDataFromCSV(const std::string &fileName);

    void readTextFile_list(const std::string &file_name);

    void readStudentDataFromCSV_list(const std::string &fileName);
};

#endif //OP_TEXTREADER_H
