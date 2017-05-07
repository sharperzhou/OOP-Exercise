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

enum RESULT
{
    ERROR_SUCCESSFUL = 0x00000001,      //无错误
    ERROR_OPENFILE = 0x00000010,        //打开文件失败
    ERROR_STUDENTEXIST = 0x00000100,    //增加的学生Id重复
    ERROR_NOFINDRESULT = 0x00001000     //未查找到指定Id的学生
};

class CStudentSystem
{
public:
    CStudentSystem() {};
    ~CStudentSystem() {};
    
public:
    void mainPage();
    void display();
    RESULT read();
    RESULT insert(const Student& stu);
    RESULT find(int Id);
    RESULT update(const Student& stu);
    RESULT remove(int Id);

private:
    bool readFile();
    bool writeFile(const Student& stu);
    bool writeFile();
    void displayHead();

private:
    vector<Student> m_stuInfo;
};
