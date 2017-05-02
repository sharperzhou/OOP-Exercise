#include "StudentSystem.h"
#include <iostream>
#include <iomanip>
#include <fstream>
void CStudentSystem::mainPage()
{
    cout << "*************************************************"<< endl;
    cout << "*\t\t" << "1.   录       入" << "\t\t*" << endl;
    cout << "*\t\t" << "2.   读       取" << "\t\t*" << endl;
    cout << "*\t\t" << "3.   退       出" << "\t\t*" << endl;
    cout << "*************************************************"<< endl;
}

int CStudentSystem::display()
{
    if (!readFile()) return ERROR_OPENFILE;

    displayHead();
    for (vector<Student>::const_iterator iter = m_stuInfo.begin();
        iter != m_stuInfo.end(); ++iter) {
        cout << setw(6) << ((const Student) *iter).Id << "  "
            << setw(6) << ((const Student) *iter).Name << "  "
            << setw(5) << ((const Student) *iter).Sex << "  "
            << setw(5) << ((const Student) *iter).Age << "  "
            << setw(8) << ((const Student) *iter).Grade << endl;
    }
    return ERROR_SUCCESSFUL;
}

int CStudentSystem::insert(const Student &stu)
{
    if (!readFile()) return ERROR_OPENFILE;

    for (vector<Student>::const_iterator iter = m_stuInfo.begin();
        iter != m_stuInfo.end(); ++iter) {
            if (stu.Id == ((Student) *iter).Id)
                return ERROR_STUDENTEXIST;
    }

    if (!writeFile(stu)) return ERROR_OPENFILE;

    return ERROR_SUCCESSFUL;
}

bool CStudentSystem::readFile()
{
    ifstream ifs("stu_info.txt");
    if (!ifs.is_open()) return false;

    Student stu;
    m_stuInfo.clear();
    while (!ifs.eof()) {
        if (ifs >> stu.Id >> stu.Name >> stu.Sex >> stu.Age >> stu.Grade)
            m_stuInfo.push_back(stu);
    }
    return true;
}

bool CStudentSystem::writeFile(const Student& stu)
{
    ofstream ofs("stu_info.txt", ios_base::app | ios_base::out);
    if (!ofs.is_open()) return false;

    ofs << stu.Id << "\t"
        << stu.Name << "\t"
        << stu.Sex << "\t"
        << stu.Age << "\t"
        << stu.Grade << endl;

    return true;
}

void CStudentSystem::displayHead()
{
    cout << "学  号" << "  " << "姓  名" << "  " << "性 别" << "  "
         << "年 龄" << "  " << " 年  级 " << endl;
    cout << "------" << "  " << "------" << "  " << "-----" << "  "
         << "-----" << "  " << "--------" << endl;
}