#include "StudentSystem.h"
#include <iostream>
#include <iomanip>
#include <fstream>

/*****************************************************************************************\
* FuncName :   mainPage
* Usage    :   display the main page to console
* DataTime :   2017/05/07
* Access   :   public 
* Return   :   void
\*****************************************************************************************/
void CStudentSystem::mainPage()
{
    cout << "*************************************************"<< endl;
    cout << "*\t\t" << "1.   录       入" << "\t\t*" << endl;
    cout << "*\t\t" << "2.   读       取" << "\t\t*" << endl;
    cout << "*\t\t" << "3.   查       找" << "\t\t*" << endl;
    cout << "*\t\t" << "4.   更       新" << "\t\t*" << endl;
    cout << "*\t\t" << "5.   删       除" << "\t\t*" << endl;
    cout << "*\t\t" << "6.   退       出" << "\t\t*" << endl;
    cout << "*************************************************"<< endl;
}

/*****************************************************************************************\
* FuncName :   display
* Usage    :   display the result to console
* DataTime :   2017/05/07
* Access   :   public 
* Return   :   void
\*****************************************************************************************/
void CStudentSystem::display()
{
    displayHead();
    for (vector<Student>::const_iterator iter = m_stuInfo.begin();
        iter != m_stuInfo.end(); ++iter) {
        cout << setw(6) << ((const Student) *iter).Id << "  "
            << setw(6) << ((const Student) *iter).Name << "  "
            << setw(5) << ((const Student) *iter).Sex << "  "
            << setw(5) << ((const Student) *iter).Age << "  "
            << setw(8) << ((const Student) *iter).Grade << endl;
    }
}

/*****************************************************************************************\
* FuncName :   read
* Usage    :   read from file
* DataTime :   2017/05/07
* Access   :   public 
* Return   :   RESULT (ERROR_SUCCESSFUL, ERROR_OPENFILE)
\*****************************************************************************************/
RESULT CStudentSystem::read()
{
    return readFile() ? ERROR_SUCCESSFUL : ERROR_OPENFILE;
}

/*****************************************************************************************\
* FuncName :   insert
* Usage    :   insert the student information to the file
* DataTime :   2017/05/07
* Access   :   public 
* Return   :   RESULT (ERROR_OPENFILE, ERROR_STUDENTEXIST, ERROR_SUCCESSFUL)
* Params   :   const Student & stu
\*****************************************************************************************/
RESULT CStudentSystem::insert(const Student &stu)
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

/*****************************************************************************************\
* FuncName :   find
* Usage    :   through the Id to find the student information, only no error can you
               use display method to report the find result
* DataTime :   2017/05/07
* Access   :   public 
* Return   :   RESULT (ERROR_OPENFILE, ERROR_SUCCESSFUL, ERROR_NOFINDRESULT)
* Params   :   int Id
\*****************************************************************************************/
RESULT CStudentSystem::find(int Id)
{
    if (!readFile()) return ERROR_OPENFILE;

    Student temp;
    for (vector<Student>::const_iterator iter = m_stuInfo.begin();
        iter != m_stuInfo.end(); ++iter) {
            if (Id == ((Student) *iter).Id) {
                temp = (Student) *iter;
                m_stuInfo.clear();
                m_stuInfo.push_back(temp);
                return ERROR_SUCCESSFUL;
            }
    }
    return ERROR_NOFINDRESULT;
}

/*****************************************************************************************\
* FuncName :   update
* Usage    :   update the existing Id's student information
* DataTime :   2017/05/07
* Access   :   public 
* Return   :   RESULT (ERROR_OPENFILE, ERROR_SUCCESSFUL, ERROR_NOFINDRESULT)
* Params   :   const Student & stu
\*****************************************************************************************/
RESULT CStudentSystem::update(const Student& stu)
{
    if (!readFile()) return ERROR_OPENFILE;

    for (vector<Student>::iterator iter = m_stuInfo.begin();
        iter != m_stuInfo.end(); ++iter) {
            if (stu.Id == ((Student) *iter).Id) {
                *iter = stu;
                if (!writeFile()) return ERROR_OPENFILE;
                else return ERROR_SUCCESSFUL;
            }
    }
    return ERROR_NOFINDRESULT;
}

/*****************************************************************************************\
* FuncName :   remove
* Usage    :   remove the student information according to the Id
* DataTime :   2017/05/07
* Access   :   public 
* Return   :   RESULT
* Params   :   int Id
\*****************************************************************************************/
RESULT CStudentSystem::remove(int Id)
{
    if (!readFile()) return ERROR_OPENFILE;

    for (vector<Student>::iterator iter = m_stuInfo.begin();
        iter != m_stuInfo.end(); ++iter) {
            if (Id == ((Student) *iter).Id) {
                m_stuInfo.erase(iter);
                if (!writeFile()) return ERROR_OPENFILE;
                else return ERROR_SUCCESSFUL;
            }
    }
    return ERROR_NOFINDRESULT;
}

/*****************************************************************************************\
* FuncName :   readFile
* Usage    :   read the student from file to a vector
* DataTime :   2017/05/07
* Access   :   private 
* Return   :   bool
\*****************************************************************************************/
bool CStudentSystem::readFile()
{
    ifstream ifs("stu_info.dat", ios::binary);
    if (!ifs.is_open()) return false;

    Student stu;
    m_stuInfo.clear();
    while (!ifs.eof()) {
        //if (ifs >> stu.Id >> stu.Name >> stu.Sex >> stu.Age >> stu.Grade)
        //    m_stuInfo.push_back(stu);
        if (ifs.read((char*) &stu, sizeof(Student)))
            m_stuInfo.push_back(stu);
    }
    return true;
}

/*****************************************************************************************\
* FuncName :   writeFile
* Usage    :   write the student information from console, which the user input, to file
* DataTime :   2017/05/07
* Access   :   private 
* Return   :   bool
* Params   :   const Student & stu
\*****************************************************************************************/
bool CStudentSystem::writeFile(const Student& stu)
{
    ofstream ofs("stu_info.dat", ios::app | ios::binary);
    if (!ofs.is_open()) return false;

    //ofs << stu.Id << "\t"
    //    << stu.Name << "\t"
    //    << stu.Sex << "\t"
    //    << stu.Age << "\t"
    //    << stu.Grade << "\r"
    //    << endl;

    ofs.write((char*) &stu, sizeof(Student));

    return true;
}

/*****************************************************************************************\
* FuncName :   writeFile
* Usage    :   write student information from vector
* DataTime :   2017/05/07
* Access   :   private 
* Return   :   bool
\*****************************************************************************************/
bool CStudentSystem::writeFile()
{
    ofstream ofs("stu_info.dat", ios::binary);
    if (!ofs.is_open()) return false;

    for (vector<Student>::const_iterator iter = m_stuInfo.begin();
        iter != m_stuInfo.end(); ++iter) {
            //ofs << ((Student) *iter).Id << "\t"
            //    << ((Student) *iter).Name << "\t"
            //    << ((Student) *iter).Sex << "\t"
            //    << ((Student) *iter).Age << "\t"
            //    << ((Student) *iter).Grade << "\r"
            //    << endl;

            ofs.write((const char*) &*iter, sizeof(Student));
    }
    return true;
}

/*****************************************************************************************\
* FuncName :   displayHead
* Usage    :   display the column name to console
* DataTime :   2017/05/07
* Access   :   private 
* Return   :   void
\*****************************************************************************************/
void CStudentSystem::displayHead()
{
    cout << "学  号" << "  " << "姓  名" << "  " << "性 别" << "  "
         << "年 龄" << "  " << " 年  级 " << endl;
    cout << "------" << "  " << "------" << "  " << "-----" << "  "
         << "-----" << "  " << "--------" << endl;
}