#include "Head.h"




int register_tea() {
	string name, id, password;
	cout << "��������(4λ����)��";

again:
	while (cin >> id) {
		if (id.length() == 4 && fileExists(id + ".txt") == false) {
			ofstream file2("��ʦ����.txt", ios::app);
			file2 << id << endl;
			file2.close();
			break;
		}
		else
			cout << "��ų��Ȳ���ȷ��ñ���ѱ�ע�ᣬ����������" << endl;
	}
	string id2 = id + ".txt";
	if (fileExists(id) == true) {
		cout << "�ñ���ѱ�ע�ᣬ����������" << endl;
		goto again;
	}
	createFile(id2);

	ofstream file(id2, ios::app);
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
		cout << "��ӭ����," << name << endl;
	}
	read_file.close();
	cout << "�����ʦ�����:" << id2 << endl;

	// ��ȡ��ǰʱ��
	auto now = chrono::system_clock::now();
	time_t nowTime = chrono::system_clock::to_time_t(now);
	tm* localTime = localtime(&nowTime);

	// ��ʽ����ǰʱ��
	char timeStr[20];
	strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localTime);
	cout << "��ǰʱ�䣺" << timeStr << endl;

	teacher_menu(id2);
}

int remove_teacher(string id) {
	bool existed = fileExists(id + ".txt");
	if (!existed) {
		cout << "�����ڸý�ʦ������ע��" << endl;
		return 1;
	}
	char choice = 0;
	cout << "��ȷ��Ҫע����ʦ " << id << " ��(Y/N)";
	cin >> choice;
	if (choice!= 'Y' && choice!= 'y') {
		cout << "ȡ��ע��" << endl;
		return 1;
	}
	if (remove(id + ".txt") == 1) {
		cout << "��ʦ " << id << " ע���ɹ�" << endl;
	}
	else {
		cout << "ע����ʦ " << id << " ʧ��" << endl;
	}
	return 0;
}

int teacher_menu(string id) {
	int choice;
	int out_of_system = 1;
	while (out_of_system) {
		cout << "��ʦ���ܲ˵�" << endl;
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
			change_thing(id + ".txt", "password", new_password);
			break;
		case 2:
			out_of_system = remove_teacher(id);
			if (out_of_system == 1) {
				cout<<"�û�ȡ��ע��"<<endl;
				break;
			}
			removeLinesFromFile("��ʦ����.txt", id);
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

int teacher_login() {
	string id, password;
	cout << "�������ţ�";
	while (!(cin >> id && fileExists(id + ".txt"))) {
		cout << "�ñ�Ų����ڣ�����������" << endl;
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

int tea_menu() {
	int choice;
	int out_of_system = 1;
	while (out_of_system) {
		cout << "��ʦ�˵�" << endl;
		cout << "1. ע��" << endl;
		cout << "2. ��¼" << endl;
		cout << "3. �˳�" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			register_tea();
			break;
		case 2:
			teacher_login();
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