#include "StudentSystem.h"
#include <iostream>
using namespace std;

void printError(RESULT fRet)
{
    switch (fRet) {
        case ERROR_NOFINDRESULT:
            cout << "Error." << ERROR_NOFINDRESULT << ": 未找到该学号的学生信息" << endl;
            break;
        case ERROR_OPENFILE:
            cout << "Error." << ERROR_OPENFILE << ": 文件打开失败" << endl;
            break;
        case ERROR_STUDENTEXIST:
            cout << "Error." << ERROR_STUDENTEXIST << ": 该学号的学生已存在" << endl;
            break;
        default:
            break;
    }
}

int main()
{
    CStudentSystem stuSys;
    int num;
    RESULT ret;
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
                case 1:  //录入
                    cout << "请输入学生信息，按学号 姓名 性别 年龄 年级的方式输入" << endl;
                    if (!(cin >> stu.Id >> stu.Name >> stu.Sex >> stu.Age >> stu.Grade)) {
                        cin.clear();
                        cin.sync();
                        cout << "学生信息输入出错，请重新录入" << endl;
                        system("pause");
                        break;
                    }
                    ret = stuSys.insert(stu);
                    if (ret & ERROR_SUCCESSFUL)
                        cout << "成功增加一条学生信息" << endl;
                    else
                        printError(ret);

                    cout << endl;
                    system("pause");
                    break;

                case 2:  //读取
                    ret = stuSys.read();
                    if (ret & ERROR_SUCCESSFUL)
                        stuSys.display();
                    else
                        printError(ret);

                    cout << endl;
                    system("pause");
                    break;

                case 3:  //查找
                    cout << "请输入学号：";
                    if (!(cin >> num)) {
                        cin.clear();
                        cin.sync();
                        cout << "学号输入错误，请重新录入" << endl;
                        system("pause");
                        break;
                    }
                    ret = stuSys.find(num);
                    if (ret & ERROR_SUCCESSFUL)
                        stuSys.display();
                    else
                        printError(ret);

                    cout << endl;
                    system("pause");
                    break;

                case 4:  //更新
                    cout << "请输入需要更新的学生信息，按学号 姓名 性别 年龄 年级的方式输入" << endl;
                    if (!(cin >> stu.Id >> stu.Name >> stu.Sex >> stu.Age >> stu.Grade)) {
                        cin.clear();
                        cin.sync();
                        cout << "学生信息输入出错，请重新录入" << endl;
                        system("pause");
                        break;
                    }
                    ret = stuSys.update(stu);
                    if (ret & ERROR_SUCCESSFUL)
                        cout << "成功更新一条学生信息" << endl;
                    else
                        printError(ret);

                    cout << endl;
                    system("pause");
                    break;

                case 5:  //删除
                    cout << "请输入学号：";
                    if (!(cin >> num)) {
                        cin.clear();
                        cin.sync();
                        cout << "学号输入错误，请重新录入" << endl;
                        system("pause");
                        break;
                    }
                    ret = stuSys.remove(num);
                    if (ret & ERROR_SUCCESSFUL)
                        cout << "成功删除一条学生信息，学号为" << num << endl;
                    else
                        printError(ret);

                    cout << endl;
                    system("pause");
                    break;

                case 6:  //退出
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