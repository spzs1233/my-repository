#include "Head.h"


int to_create_file() {
	createFile("学生名单");
	createFile("老师名单");
	createFile("管理员名单");
	createFile("管理员密码");
	return 0;
}
int main() {
	to_create_file();
	int out_of_system = 1;
	while (out_of_system) {
		int choice = menu();
		switch (choice) {
		case 1:
			stu_menu();
			break;
		case 2:
			tea_menu();
			break;
		case 3:
			admin_menu();
			break;
		case 4:
			cout << "你确定要退出系统吗？(Y/N)";
			char c;
			cin >> c;
			if (c == 'Y' || c == 'y')
				out_of_system = 0;
			else
				break;
			break;
		default:
			printf("输入错误，请重新输入！");
			break;
		}
	}
	return 0;
}