#include "Head.h"

int show_information_teacher(string id) {
	string id2 = id;
	id += ".txt";
	if (fileExists(id) == false) {
		cout << "该教师不存在" << endl;
		return 0;
	}
	cout << "------------------------------------" << endl;
	cout << "编号是:" << id2 << endl;
	ifstream read_file(id);
	string line;
	if (getline(read_file, line)) {
		size_t start = line.find("name=") + 5;
		size_t end = line.find(",", start);
		string name = line.substr(start, end - start);
		cout << "姓名是:" << name << endl;
		size_t start2 = line.find("password=") + 9;
		size_t end2 = line.find(",", start);
		string password = line.substr(start2, end2 - start2);
		cout << "密码是:" << password << endl;
	}
	read_file.close();
	cout << "------------------------------------" << endl;
	return 0;
}



int read_tea() {
	ifstream file("老师名单.txt");
	if (isFileEmptyOrWhitespace(file)) {
		cout << "------------------------------------" << endl;
		cout << "老师名单为空" << endl;
		file.close();
		return 0;
	}
	file.clear();
	file.seekg(0);


	string line;
	bool flag = false;
	int num = 0;
	cout << "------------------------------------" << endl;
	while (getline(file, line)) {
		if (line.empty()) {
			flag = true;
			continue;
		}
		else {
			flag = false;
			num++;
			cout << "     老师:>   " << line << endl;
			cout << "------------------------------------" << endl;
		}
	}
	file.close();
	return 1;
}

int choice_tea() {
	string id;
	bool out_of_system = true;
	while (out_of_system) {


		cout << "-----------------------------------" << endl;
		// 获取当前时间
		auto now = chrono::system_clock::now();
		time_t nowTime = chrono::system_clock::to_time_t(now);
		tm* localTime = localtime(&nowTime);

		// 格式化当前时间
		char timeStr[20];
		strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localTime);
		cout << "-----------------------------------" << endl;
		cout << "当前时间：" << timeStr << endl;
		cout << "1. 查看教师信息" << endl;
		cout << "2. 编辑教师信息" << endl;
		cout << "3. 删除教师信息" << endl;
		cout << "4. 退出" << endl;
		cout << "-----------------------------------" << endl;


		int choice;
		cin >> choice;
		switch (choice) {
		case 1:
			read_tea();
			cout << "请输入教师编号:" << endl;
			cin >> id;
			show_information_teacher(id);
			break;
		case 2:
			cout << "请输入教师编号:" << endl;
			cin >> id;
			show_information_teacher(id);
			cout << "1.修改姓名" << endl;
			cout << "2.修改密码" << endl;
			int choice2;
			cin >> choice2;
			if (choice2 == 1) {
				cout << "请输入新名字：";
				string new_name;
				cin >> new_name;
				change_thing(id + ".txt", "name", new_name);
			}
			else if (choice2 == 2) {
				cout << "请输入新密码：";
				string new_password;
				cin >> new_password;
				change_thing(id + ".txt", "password", new_password);
			}
			break;
		case 3:
			break;
		case 4:
			cout << "你确定要退出当前系统吗？(Y/N)";
			char c;
			cin >> c;
			if (c == 'Y' || c == 'y')
				out_of_system = false;
			break;
		default:
			cout << "输入错误，请重新输入" << endl;
			break;
		}
	}
	return 0;
}