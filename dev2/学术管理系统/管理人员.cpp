#include "Head.h"

bool isFileEmptyOrWhitespace(ifstream& file) {
	file.seekg(0, ios::end);
	if (file.tellg() == 0) {
		return true; 
	}

	file.seekg(0, ios::beg);
	char ch;
	while (file.get(ch)) {
		if (!isspace(static_cast<unsigned char>(ch))) {
			return false; 
		}
	}
	return true; 
}

int show_information_student(string id) {
	string id2 = id;
	id += ".txt";
	if (fileExists(id) == false) {
		cout << "该学生不存在" << endl;
		return 0;
	}
	cout << "------------------------------------" << endl;
	cout << "学号是:" << id2 << endl;
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

int read_stu() {
	ifstream file("学生名单.txt");
	if (isFileEmptyOrWhitespace(file)) {
		cout << "------------------------------------" << endl;
		cout << "学生名单为空" << endl;
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
			cout<<"     学生:>   "<<line<<endl;
			cout << "------------------------------------" << endl;
		}
	}
	file.close();
	return 1;
}

int choice_stu() {
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
		cout << "1. 查看学生信息" << endl;
		cout << "2. 编辑学生信息" << endl;
		cout << "3. 删除学生信息" << endl;
		cout << "4. 退出" << endl;
		cout << "-----------------------------------" << endl;


		int choice;
		cin >> choice;
		switch (choice) {
		case 1:
			read_stu();
			cout << "请输入学生学号:" << endl;
			cin >> id;
			show_information_student(id);
			break;
		case 2:
			cout << "请输入学生学号:" << endl;
			cin >> id;
			show_information_student(id);
			cout<<"1.修改姓名"<<endl;
			cout<<"2.修改密码"<<endl;
			int choice2;
			cin>>choice2;
			if (choice2 == 1) {
				cout << "请输入新名字：";
				string new_name;
				cin >> new_name;
				change_thing(id + ".txt", "name",new_name);
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

int admin_login() {
	int out_of_system = 1;
	while (out_of_system) {

		cout << "欢迎回来，管理人员" << endl;
		cout << "1. 管理所有学生信息" << endl;
		cout << "2. 管理所有教师信息" << endl;
		cout << "3. 退出" << endl;

		int choice;
		cin >> choice;
		switch (choice) {
		case 1:
			if (read_stu()) {
				choice_stu();
			}
			break;
		case 2:
			if (read_tea()) {
				choice_tea();
			}
			break;
		case 3:
			cout << "你确定要退出当前系统吗？(Y/N)";
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


int admin_menu() {
	int out_of_system = 1;
	cout << "管理人员菜单" << endl;
	cout << "请输入密码:";
	ifstream file("管理员密码.txt");
	string line;
	getline(file, line);
again:
	string input_password;
	cin >> input_password;
	if (input_password == line) {
		cout << "密码正确，进入管理人员菜单" << endl;
		admin_login();

	}
	else {
		cout << "密码错误，请重新输入" << endl;
		goto again;
	}
	return 0;
}