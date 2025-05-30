#include "Head.h"

int show_information_teacher(string id) {
	string id2 = id;
	id += ".txt";
	if (fileExists(id) == false) {
		cout << "�ý�ʦ������" << endl;
		return 0;
	}
	cout << "------------------------------------" << endl;
	cout << "�����:" << id2 << endl;
	ifstream read_file(id);
	string line;
	if (getline(read_file, line)) {
		size_t start = line.find("name=") + 5;
		size_t end = line.find(",", start);
		string name = line.substr(start, end - start);
		cout << "������:" << name << endl;
		size_t start2 = line.find("password=") + 9;
		size_t end2 = line.find(",", start);
		string password = line.substr(start2, end2 - start2);
		cout << "������:" << password << endl;
	}
	read_file.close();
	cout << "------------------------------------" << endl;
	return 0;
}



int read_tea() {
	ifstream file("��ʦ����.txt");
	if (isFileEmptyOrWhitespace(file)) {
		cout << "------------------------------------" << endl;
		cout << "��ʦ����Ϊ��" << endl;
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
			cout << "     ��ʦ:>   " << line << endl;
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
		// ��ȡ��ǰʱ��
		auto now = chrono::system_clock::now();
		time_t nowTime = chrono::system_clock::to_time_t(now);
		tm* localTime = localtime(&nowTime);

		// ��ʽ����ǰʱ��
		char timeStr[20];
		strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localTime);
		cout << "-----------------------------------" << endl;
		cout << "��ǰʱ�䣺" << timeStr << endl;
		cout << "1. �鿴��ʦ��Ϣ" << endl;
		cout << "2. �༭��ʦ��Ϣ" << endl;
		cout << "3. ɾ����ʦ��Ϣ" << endl;
		cout << "4. �˳�" << endl;
		cout << "-----------------------------------" << endl;


		int choice;
		cin >> choice;
		switch (choice) {
		case 1:
			read_tea();
			cout << "�������ʦ���:" << endl;
			cin >> id;
			show_information_teacher(id);
			break;
		case 2:
			cout << "�������ʦ���:" << endl;
			cin >> id;
			show_information_teacher(id);
			cout << "1.�޸�����" << endl;
			cout << "2.�޸�����" << endl;
			int choice2;
			cin >> choice2;
			if (choice2 == 1) {
				cout << "�����������֣�";
				string new_name;
				cin >> new_name;
				change_thing(id + ".txt", "name", new_name);
			}
			else if (choice2 == 2) {
				cout << "�����������룺";
				string new_password;
				cin >> new_password;
				change_thing(id + ".txt", "password", new_password);
			}
			break;
		case 3:
			break;
		case 4:
			cout << "��ȷ��Ҫ�˳���ǰϵͳ��(Y/N)";
			char c;
			cin >> c;
			if (c == 'Y' || c == 'y')
				out_of_system = false;
			break;
		default:
			cout << "�����������������" << endl;
			break;
		}
	}
	return 0;
}