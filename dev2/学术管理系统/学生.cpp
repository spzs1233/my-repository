#include "Head.h"


int register_student() {
	string name, id, password;
	cout << "������ѧ��(9λ����)��";

again:
	while (cin >> id) {
		if (id.length() == 9 && fileExists(id+".txt") == false) {
			ofstream file2("ѧ������.txt", ios::app);
			file2<<id<<endl;
			file2.close();
			break;
		}
		else
			cout << "ѧ�ų��Ȳ���ȷ���ѧ���ѱ�ע�ᣬ����������" << endl;
	}
	id = id + ".txt";
	if (fileExists(id) == true) {
		cout << "��ѧ���ѱ�ע�ᣬ����������" << endl;
		goto again;
	}
	createFile(id);

	ofstream file(id, ios::app);
	if (file.is_open()) {
		cout << "������������";
		cin >> name;
		file << "name=" << name << ",";

		cout << "���������룺";
		cin >> password;
		file << "password=" << password << ",";

		file.close();
	}

	return 0;
}






int remove_student(string id) {
	bool existed = fileExists(id + ".txt");
	if (!existed) {
		cout<<"�����ڸ�ѧ��������ע��"<<endl;
		return 0;
	}
	if (remove(id + ".txt") == 1) {
		cout << "ѧ�� " << id << " ע���ɹ�" << endl;
	}
	else {
		cout << "ע��ѧ�� " << id << " ʧ��" << endl;
	}
	return 0;
}

int student_menu(string id) {
	int choice;
	int out_of_system = 1;
	while (out_of_system) {
		cout << "ѧ�����ܲ˵�" << endl;
		cout << "-----------------------" << endl;
		cout << "1.�޸�����" << endl;
		cout << "2.ע���˺�" << endl;
		cout << "3.�˳��˺�" << endl;
		cout << "-----------------------" << endl;
		cout << "������ѡ�";
		cin >> choice;
		string new_password;
		switch (choice) {
		case 1:
			cout << "�����������룺" << endl;
			cin >> new_password;
			change_thing(id+".txt", "password", new_password);
			break;
		case 2:
			remove_student(id);
			removeLinesFromFile("ѧ������.txt", id);
			break;
		case 3:
			cout << "��ȷ��Ҫ�˳���ǰ�˺���(Y/N)";
			char c;
			cin >> c;
			if (c == 'Y' || c == 'y')
				out_of_system = 0;
			else
				break;
			break;
		default:
			cout << "�����������������" << endl;
			break;
		}
	}
	return 0;
}

int show_information(string id) {
	string id2 = id;
	id+= ".txt";
	ifstream read_file(id);
	string line;
	if (getline(read_file, line)) {
		size_t start = line.find("name=") + 5;
		size_t end = line.find(",", start);
		string name = line.substr(start, end - start);
		cout << "��ӭ����," << name << endl;
	}
	read_file.close();
	cout<<"���ѧ����:"<<id2<<endl;

	// ��ȡ��ǰʱ��
	auto now = chrono::system_clock::now();
	time_t nowTime = chrono::system_clock::to_time_t(now);
	tm* localTime = localtime(&nowTime);

	// ��ʽ����ǰʱ��
	char timeStr[20];
	strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localTime);
	cout << "��ǰʱ�䣺" << timeStr << endl;

	student_menu(id2);

	return 0;
}

int student_login() {
	string id, password;
	cout << "������ѧ�ţ�";
	while (!(cin >> id && fileExists(id + ".txt"))) {
		cout << "��ѧ�Ų����ڣ�����������" << endl;
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
	cout << "���������룺";
	while (cin >> input_password && input_password != password) {
		cout << "�����������������" << endl;
	}
	cout << "��¼�ɹ�" << endl;

	show_information(id);

	return 0;
}

int stu_menu() {
	int choice;
	int out_of_system = 1;
	while (out_of_system) {
		cout << "ѧ���˵�" << endl;
		cout << "1. ע��" << endl;
		cout << "2. ��¼" << endl;
		cout << "3. �˳�" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			register_student();
			break;
		case 2:
			student_login();
			break;
		case 3:
			cout << "��ȷ��Ҫ�˳�ϵͳ��(Y/N)";
			char c;
			cin >> c;
			if (c == 'Y' || c == 'y')
				out_of_system = 0;
			else
				break;
			break;
		default:
			cout << "�����������������" << endl;
			break;
		}
	}
	return 0;
}