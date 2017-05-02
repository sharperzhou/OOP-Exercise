#pragma once
#include <string>
#include <vector>
using namespace std;

struct Student
{
    unsigned int Id;  //学号
    unsigned int Age; //年龄
    string Name;      //姓名
    string Sex;       //性别
    string Grade;     //年级
};

enum ErrorHandler
{
    ERROR_SUCCESSFUL = 0,  //无错误
    ERROR_OPENFILE,        //打开文件失败
    ERROR_STUDENTEXIST     //增加的学生Id重复
};

class CStudentSystem
{
public:
    CStudentSystem() {};
    ~CStudentSystem() {};
    
public:
    void mainPage();
    int insert(const Student& stu);
    int display();

private:
    bool readFile();
    bool writeFile(const Student& stu);
    void displayHead();

private:
    vector<Student> m_stuInfo;
};
