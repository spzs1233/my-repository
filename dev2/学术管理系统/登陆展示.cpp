#include "Head.h"
int menu() {
	cout << "--------------------" << endl;
	cout << "---  1.作为学生  ---" << endl;
	cout << "---  2.作为教师  ---" << endl;
	cout << "--- 3.作为管理员 ---" << endl;
	cout << "---  4.退出系统  ---" << endl;
	cout << "--------------------" << endl;
	cout << "请输入您的选择：";
	int choice;
	while (cin >> choice) {
		if (choice >= 1 && choice <= 4) {
			return choice;
		}
		cout << "输入错误，请重新输入：";
		cin.clear();
		cin.ignore(10000, '\n');
	}
	return 0;
}