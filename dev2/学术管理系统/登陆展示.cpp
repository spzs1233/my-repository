#include "Head.h"
int menu() {
	cout << "--------------------" << endl;
	cout << "---  1.��Ϊѧ��  ---" << endl;
	cout << "---  2.��Ϊ��ʦ  ---" << endl;
	cout << "--- 3.��Ϊ����Ա ---" << endl;
	cout << "---  4.�˳�ϵͳ  ---" << endl;
	cout << "--------------------" << endl;
	cout << "����������ѡ��";
	int choice;
	while (cin >> choice) {
		if (choice >= 1 && choice <= 4) {
			return choice;
		}
		cout << "����������������룺";
		cin.clear();
		cin.ignore(10000, '\n');
	}
	return 0;
}