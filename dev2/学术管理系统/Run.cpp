#include "Head.h"


int to_create_file() {
	createFile("ѧ������");
	createFile("��ʦ����");
	createFile("����Ա����");
	createFile("����Ա����");
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
			cout << "��ȷ��Ҫ�˳�ϵͳ��(Y/N)";
			char c;
			cin >> c;
			if (c == 'Y' || c == 'y')
				out_of_system = 0;
			else
				break;
			break;
		default:
			printf("����������������룡");
			break;
		}
	}
	return 0;
}