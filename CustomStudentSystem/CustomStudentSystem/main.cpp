#include "StudentSystem.h"
#include <iostream>
using namespace std;

int main()
{
    CStudentSystem stuSys;
    int num, ret;
    Student stu;

    while (1) {
        system("cls");
        stuSys.mainPage();
        cout << "请选择项目进行操作:";
        if (!(cin >> num)) {
            cin.clear();
            cin.sync();
            cout << "选择项目出错，请重新选择" << endl;
            system("pause");
        }
        else {
            cout << endl;
            switch (num) {
                case 1:
                    cout << "请输入学生信息，按学号 姓名 性别 年龄 年级的方式输入" << endl;
                    if (!(cin >> stu.Id >> stu.Name >> stu.Sex >> stu.Age >> stu.Grade)) {
                        cin.clear();
                        cin.sync();
                        cout << "学生信息输入出错，请重新录入" << endl;
                        system("pause");
                        break;
                    }
                    ret = stuSys.insert(stu);
                    if (ret == ERROR_OPENFILE)
                        cout << "Error." << ERROR_OPENFILE << ": 文件打开失败" << endl;
                    else if (ret == ERROR_STUDENTEXIST)
                        cout << "Error." << ERROR_STUDENTEXIST << ": 该学号的学生已存在" << endl;
                    else
                        cout << "成功增加一条学生信息" << endl;

                    cout << endl;
                    system("pause");
                    break;

                case 2:
                    ret = stuSys.display();
                    if (ret == ERROR_OPENFILE)
                        cout << "Error." << ERROR_OPENFILE << ": 文件打开失败" << endl;

                    cout << endl;
                    system("pause");
                    break;

                case 3:
                    return 0;

                default:
                    cout << "您选择的项目不在上述范围内，请重新输入数字进行操作" << endl;

                    cout << endl;
                    system("pause");
                    break;
            }
        }
    }

    return 0;
}