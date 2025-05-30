#include "Head.h"




int register_tea() {
	string name, id, password;
	cout << "请输入编号(4位数字)：";

again:
	while (cin >> id) {
		if (id.length() == 4 && fileExists(id + ".txt") == false) {
			ofstream file2("老师名单.txt", ios::app);
			file2 << id << endl;
			file2.close();
			break;
		}
		else
			cout << "编号长度不正确或该编号已被注册，请重新输入" << endl;
	}
	string id2 = id + ".txt";
	if (fileExists(id) == true) {
		cout << "该编号已被注册，请重新输入" << endl;
		goto again;
	}
	createFile(id2);

	ofstream file(id2, ios::app);
	if (file.is_open()) {
		cout << "请输入姓名：";
		cin >> name;
		file << "name=" << name << ",";

		cout << "请输入密码：";
		cin >> password;
		file << "password=" << password << ",";

		file.close();
	}

	return 0;
	return 0;
}


void show_information(string id) {
	string id2 = id;
	id += ".txt";
	ifstream read_file(id);
	string line;
	if (getline(read_file, line)) {
		size_t start = line.find("name=") + 5;
		size_t end = line.find(",", start);
		string name = line.substr(start, end - start);
		cout << "欢迎回来," << name << endl;
	}
	read_file.close();
	cout << "你的老师编号是:" << id2 << endl;

	// 获取当前时间
	auto now = chrono::system_clock::now();
	time_t nowTime = chrono::system_clock::to_time_t(now);
	tm* localTime = localtime(&nowTime);

	// 格式化当前时间
	char timeStr[20];
	strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localTime);
	cout << "当前时间：" << timeStr << endl;

	teacher_menu(id2);
}

int remove_teacher(string id) {
	bool existed = fileExists(id + ".txt");
	if (!existed) {
		cout << "不存在该教师，无需注销" << endl;
		return 1;
	}
	char choice = 0;
	cout << "你确定要注销教师 " << id << " 吗？(Y/N)";
	cin >> choice;
	if (choice!= 'Y' && choice!= 'y') {
		cout << "取消注销" << endl;
		return 1;
	}
	if (remove(id + ".txt") == 1) {
		cout << "教师 " << id << " 注销成功" << endl;
	}
	else {
		cout << "注销教师 " << id << " 失败" << endl;
	}
	return 0;
}

int teacher_menu(string id) {
	int choice;
	int out_of_system = 1;
	while (out_of_system) {
		cout << "老师功能菜单" << endl;
		cout << "-----------------------" << endl;
		cout << "1.修改密码" << endl;
		cout << "2.注销账号" << endl;
		cout << "3.退出账号" << endl;
		cout << "-----------------------" << endl;
		cout << "请输入选项：";
		cin >> choice;
		string new_password;
		switch (choice) {
		case 1:
			cout << "请输入新密码：" << endl;
			cin >> new_password;
			change_thing(id + ".txt", "password", new_password);
			break;
		case 2:
			out_of_system = remove_teacher(id);
			if (out_of_system == 1) {
				cout<<"用户取消注销"<<endl;
				break;
			}
			removeLinesFromFile("老师名单.txt", id);
			break;
		case 3:
			cout << "你确定要退出当前账号吗？(Y/N)";
			char c;
			cin >> c;
			if (c == 'Y' || c == 'y')
				out_of_system = 0;
			else
				break;
			break;
		default:
			cout << "输入错误，请重新输入" << endl;
			break;
		}
	}
	return 0;
}

int teacher_login() {
	string id, password;
	cout << "请输入编号：";
	while (!(cin >> id && fileExists(id + ".txt"))) {
		cout << "该编号不存在，请重新输入" << endl;
	}
	ifstream read_file(id + ".txt");
	string line;
	if (getline(read_file, line)) {
		size_t start = line.find("password=") + 9;
		size_t end = line.find(",", start);
		password = line.substr(start, end - start);
	}
	read_file.close();
	string input_password;
	cout << "请输入密码：";
	while (cin >> input_password && input_password != password) {
		cout << "密码错误，请重新输入" << endl;
	}
	cout << "登录成功" << endl;

	show_information(id);

	return 0;
}

int tea_menu() {
	int choice;
	int out_of_system = 1;
	while (out_of_system) {
		cout << "老师菜单" << endl;
		cout << "1. 注册" << endl;
		cout << "2. 登录" << endl;
		cout << "3. 退出" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			register_tea();
			break;
		case 2:
			teacher_login();
			break;
		case 3:
			cout << "你确定要退出系统吗？(Y/N)";
			char c;
			cin >> c;
			if (c == 'Y' || c == 'y')
				out_of_system = 0;
			else
				break;
			break;
		default:
			cout << "输入错误，请重新输入" << endl;
			break;
		}
	}
	return 0;
}