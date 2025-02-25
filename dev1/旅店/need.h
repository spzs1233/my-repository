#define _CRT_SECURE_NO_WARNINGS
#define MAX_ROOM_NUM 15 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
void erect_part(const char*filename) {
	char new_name[20];
	sprintf(new_name, "%s.txt", filename);
	FILE* pf = fopen(new_name, "r");
	if (pf == NULL) {
		FILE* pf2 = fopen(new_name, "w");
		printf("�ļ���%s�����ɹ�\n", new_name);
		fclose(pf2);
	}
	else {
		fclose(pf);
	}
}
void menu() {
	printf("-------------------------\n");
	printf("��ӭ����Ƶ����ϵͳ\n");
	printf("1.��¼\n");
	printf("2.ע��\n");
	printf("0.�˳�\n");
	printf("--------------------------\n");

}

bool delete_thing(const char* filename, const char* thing) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		perror("�޷����ļ�");
		return false;
	}

	FILE* temp_file = tmpfile(); // ����һ����ʱ�ļ�
	if (temp_file == NULL) {
		perror("�޷�������ʱ�ļ�");
		fclose(file);
		return false;
	}

	char line[100];
	bool account_found = false;
	while (fgets(line, sizeof(line), file)) {
		// �Ƴ����з�
		line[strcspn(line, "\n")] = 0;

		// �����������Ҫɾ�����˺ţ���д����ʱ�ļ�
		if (strcmp(line, thing) != 0) {
			fputs(line, temp_file);
			fputs("\n", temp_file); // ����ԭ�ļ��ĸ�ʽ��ÿ��ĩβ�л��з�
		}
		else {
			account_found = true;
		}
	}

	fclose(file);

	// ����ʱ�ļ�����д��ԭ�ļ�
	rewind(temp_file); // ������ʱ�ļ��Ķ�дλ�õ���ͷ
	file = fopen(filename, "w"); // ��дģʽ���´�ԭ�ļ����������ļ�����
	if (file == NULL) {
		perror("�޷����´��ļ���д��");
		fclose(temp_file);
		return false;
	}

	char temp_line[100];
	while (fgets(temp_line, sizeof(temp_line), temp_file)) {
		fputs(temp_line, file);
	}

	fclose(file);
	fclose(temp_file); // ��ʱ�ļ����Զ�ɾ������Ϊ������tmpfile()������

	return account_found;
}

int find_out_spare_room() {
	FILE* pf = fopen("�շ�����.txt", "r");
	FILE* pf2 = fopen("�ǿշ�����.txt", "r");
	if (pf == NULL || pf2 == NULL) {
		perror("�ļ��򿪴���");
		fclose(pf);
		fclose(pf2);
		return 0;
	}
	int spare_room_num[15];
	int spare_count = 0;
	while (spare_count < MAX_ROOM_NUM && fscanf(pf, "%d", &spare_room_num[spare_count]) == 1) {
		spare_count++;
	}
	fclose(pf);

	printf("�շ�Ϊ:");
	for (int i = 0;i < spare_count;i++) {
		printf("%d ", spare_room_num[i]);
	}
	printf("\n");

	int not_spare_room_num[15];
	int not_spar_count = 0;
	while (not_spar_count < MAX_ROOM_NUM && fscanf(pf2, "%d", &not_spare_room_num[not_spar_count]) == 1) {
		not_spar_count++;
	}
	fclose(pf2);

	printf("����ס�ķ�Ϊ:");
	for (int i = 0;i < not_spar_count;i++) {
		printf("%d ", not_spare_room_num[i]);
	}
	printf("\n");

	return 0;
}

//��ѯ�Ƿ�����˺�
bool is_account_exist(const char* filename, const char* account_name) {
	FILE* file = fopen(filename, "r");

	if (file == NULL) {
		perror("�޷����ļ�");
		return false;
	}

	char line[50]; 
	while (fgets(line, sizeof(line), file)) {
		line[strcspn(line, "\n")] = 0;
		if (strcmp(line, account_name) == 0) {
			fclose(file);
			return true;
		}
	}

	fclose(file);
	return false;
}

//ע��
int want_register() {
	FILE* pf_admin = fopen("������Ա�˺�����.txt", "a");
	FILE* pf_custome = fopen("�˿��˺�����.txt", "a");
	if (pf_admin == NULL || pf_custome == NULL) {
		perror("�˺Ŵ���ʧ��");
		return 1;
	}

	printf("���ǹ�����Ա���ǹ˿ͣ�(c/g)\n");
	char choose;
	scanf(" %c", &choose); 
	char account_name[50];
	if (choose == 'c') {
		printf("�����������Ա�˺���:\n");
		scanf("%49s", &account_name);
		fprintf(pf_admin, "%s\n", account_name);
		printf("�Ѵ���������Ա�˺�\n");
	}
	else if (choose == 'g') {
		printf("������˿��˺���:\n");
		scanf("%49s", &account_name);
		fprintf(pf_custome, "%s\n", account_name);
		printf("�Ѵ����˿��˺�\n");
	}
	else
		printf("��Чѡ��\n");

	fclose(pf_admin);
	fclose(pf_custome);
	return 0;
}


bool delete_account(const char* filename, const char* account_name) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("�޷����ļ�");
        return false;
    }

    FILE* temp_file = tmpfile(); // ����һ����ʱ�ļ�
    if (temp_file == NULL) {
        perror("�޷�������ʱ�ļ�");
        fclose(file);
        return false;
    }

    char line[100];
    bool account_found = false;
    while (fgets(line, sizeof(line), file)) {
        // �Ƴ����з�
        line[strcspn(line, "\n")] = 0;

        // �����������Ҫɾ�����˺ţ���д����ʱ�ļ�
        if (strcmp(line, account_name) != 0) {
            fputs(line, temp_file);
            fputs("\n", temp_file); // ����ԭ�ļ��ĸ�ʽ��ÿ��ĩβ�л��з�
        }
        else {
            account_found = true;
			printf("ע���ɹ�\n");
        }
    }

    fclose(file);

    // ����ʱ�ļ�����д��ԭ�ļ�
    rewind(temp_file); // ������ʱ�ļ��Ķ�дλ�õ���ͷ
    file = fopen(filename, "w"); // ��дģʽ���´�ԭ�ļ����������ļ�����
    if (file == NULL) {
        perror("�޷����´��ļ���д��");
        fclose(temp_file);
        return false;
    }

    char temp_line[100];
    while (fgets(temp_line, sizeof(temp_line), temp_file)) {
        fputs(temp_line, file);
    }

    fclose(file);
    fclose(temp_file); // ��ʱ�ļ����Զ�ɾ������Ϊ������tmpfile()������

    return account_found;
}

void admin_main_menu() {
	printf("-------------------------\n");
	printf("1.��ѯ�շ�\n");
	printf("2.���û����з�����ס�Ǽ�\n");
	printf("3.�˷�\n");
	printf("4.ע���˺�\n");
	printf("0.�˳���ǰ�˺�\n");
	printf("-------------------------\n");
	printf("ѡ��:>");
}

void guest_main_menu() {
	printf("-------------------------\n");
	printf("1.��ѯ�շ�\n");
	printf("2.����ס��\n");
	printf("3.�˷�\n");
	printf("4.ע���˺�\n");
	printf("0.�˳���ǰ�˺�\n");
	printf("-------------------------\n");
	printf("ѡ��:>");
}


int create_text_files() {
	char filename[20];
	int num_created = 0;

	FILE* check_file = fopen("15.txt", "r");
	if (check_file == NULL) {
		printf("���ڴ��������ļ�......\n");

		for (int i = 1; i <= 15; i++) {
			sprintf(filename, "%d.txt", i);
			FILE* pf = fopen(filename, "w");
			if (pf == NULL) {
				perror("�ļ���ʧ��");
				return 1; 
			}

			else {
				fprintf(pf, "0\n");
				fclose(pf);
				num_created++;
			}
		}

		if (num_created == 15) {
			printf("�����ļ������ɹ�\n");
		}
		else {
			printf("�����ļ�����ʧ��\n");
		}
	}
	return 0;
}

int spare_room() {
	FILE* pf = fopen("�շ�����.txt", "r");
	if (pf == NULL ) {
		perror("�ļ��򿪴���");
		fclose(pf);
		return 0;
	}
	int spare_room_num[15];
	int spare_count = 0;
	while (spare_count < MAX_ROOM_NUM && fscanf(pf, "%d", &spare_room_num[spare_count]) == 1) {
		spare_count++;
	}
	fclose(pf);

	printf("�շ�Ϊ:");
	for (int i = 0;i < spare_count;i++) {
		printf("%d ", spare_room_num[i]);
	}
	printf("\n");

	return 0;
}

int register_room() {
	FILE* pf = fopen("�շ�����.txt", "r");
	if (pf == NULL) {
		perror("�ļ��򿪴���");
		fclose(pf);
	}
	int c = fgetc(pf);
	fclose(pf);
	if (c == EOF && !feof(pf) && !ferror(pf)) {
		printf("��ǰû�пշ�\n");
		return 0;
	}

	spare_room();
	printf("�����û�����:>");
	char guest_name[50];
	scanf("%s", guest_name);

	FILE* pf5 = fopen("ס�������.txt", "r");
	char who_want_room[15][50];
	int k = 0;
	while (k < MAX_ROOM_NUM && fscanf(pf, "%s", who_want_room[k]) == 1) {
		k++;
	}
	fclose(pf5);
	int a = 1;
	for (int i = 0;i < k;i++) {
		if (strcmp(guest_name, who_want_room[i]) == 0) {
			a = 0;
			delete_thing("ס�������.txt", guest_name);
			break;
		}
	}
	if (a) {
		printf("���û�������Ҫס��\n");
		return 0;
	}

jump:
	printf("������ס�ķ����:>");
	char num[3];
	scanf(" %2s", num);

	char room_num[10];
	sprintf(room_num, "%s.txt", num);
	FILE* pf7 = fopen(room_num, "r");
	char what_get_from_file = fgetc(pf7);
	if (what_get_from_file != '0') {
		printf("�÷��������˾�ס\n");
		goto jump;
	}

	char filename[10];
	sprintf(filename, "%s.txt", num);
	FILE* pf2 = fopen(filename, "r");
	if (pf2 == NULL) {
		perror("�ļ��򿪴���");
		printf("û���������\n");
		return 0;
	}
	fclose(pf2);
	FILE* pf3 = fopen(filename, "w");
	fprintf(pf3, "%s", guest_name);
	fclose(pf3);
	FILE* pf4 = fopen("�ǿշ�����.txt", "a");
	fprintf(pf4, "%s\n", num);
	fclose(pf4);


	delete_thing("�շ�����.txt", num);

	char Guest_file[50];
	sprintf(Guest_file, "%s.txt", guest_name);
	FILE* pf6 = fopen(Guest_file, "w");
	fprintf(pf6, "%s\n", num);
	fclose(pf6);

	return 0;
}

int compare(const void* a, const void* b) {
	int num1 = *(int*)a;
	int num2 = *(int*)b;
	if (num1 == 0 && num2 != 0) return -1; 
	if (num1 != 0 && num2 == 0) return 1; 
	return num1 - num2;                    
}

int sequence(const char* filename) {
	FILE* pf = fopen(filename, "r");
	if (pf == NULL) {
		perror("�ļ���ʧ��");
		return 1;
	}
	int arr[15] = { 0 };
	int count = 0;    
	while (count < 15 && fscanf(pf, "%d", &arr[count]) == 1) {
		count++;
	}

	qsort(arr, count, sizeof(int), compare);
	printf("\n");
	fclose(pf);

	FILE* pf2 = fopen(filename, "w");
	for (int i = 0;i < count;i++) {
		fprintf(pf2, "%d\n", arr[i]);
	}
	fclose(pf2);
	return 0;
}

int back_room(const char* roomnum) {
	char filename[20];
	sprintf(filename, "%s.txt", roomnum);

	FILE* pf3 = fopen(filename, "r");
	char a = fgetc(pf3);
	if (a == '0') {
		printf("�÷������˾�ס�������˷�\n");
		fclose(pf3);
		return 0;
	}

	char host_name[50 + 4];
	FILE* pf4 = fopen(filename, "r");
	fscanf(pf4, "%49s", host_name);

	printf("�÷����û�%s���ھ�ס,�Ƿ��˷�(y/n)\n", host_name);
	char choose;
again:
	scanf(" %c", &choose);
	if (choose == 'n') {
		printf("ȡ���˷��ɹ�\n");
		return 0;
	}
	else if (choose != 'y' && choose != 'n') {
		printf("������ѡ��\n");
		goto again;
	}
	printf("�˷��ɹ�\n");

	char host_room[60];
	sprintf(host_room, "%s.txt", host_name);
	fclose(pf4);

	FILE* pf5 = fopen(host_room, "w");
	fclose(pf5);

	FILE* pf = fopen(filename, "w");
	fprintf(pf, "0");
	fclose(pf);

	FILE* pf2 = fopen("�շ�����.txt", "a");
	fprintf(pf2, "%s\n", roomnum);
	fclose(pf2);
	sequence("�շ�����.txt");
	delete_thing("�ǿշ�����.txt", roomnum);
	return 0;
}


int want_to_do(const char* filename,const char* name) {
	printf("��ǰ�˺�Ϊ:%s\n", name);
	int input_2;

again:
	erect_part("ס�������");
	FILE* pf = fopen("ס�������.txt", "r");
	char who_want_room[15][50];
	int num = 0;
	while (num < MAX_ROOM_NUM && fscanf(pf, "%s", who_want_room[num]) == 1) {
		num++;
	}
	fclose(pf);
	for (int i = 0;i < num;i++) {
		printf("�û�%s��Ҫס��\n", who_want_room[i]);
	}


	admin_main_menu();

	int a = 1;
	scanf("%d", &input_2);
	switch (input_2) {
	case 1:
		sequence("�շ�����.txt");
		sequence("�ǿշ�����.txt");
		find_out_spare_room();
		break;
	case 2:
		sequence("�շ�����.txt");
		register_room();
		sequence("�ǿշ�����.txt");
		break;
	case 3:
		char roomnum[3];
		printf("������Ҫ�˵ķ��ķ����:>");
		scanf("%s", roomnum);
		back_room(roomnum);
		break;
	case 4:
		printf("�Ƿ�ע�����˺�(y/n)\n");
		char choose;
		scanf(" %c", &choose);
		if (choose == 'y') {
			delete_thing(filename, name);
			printf("ע���ɹ�\n");
			a = 0;
			break;
		}
		break;
	case 0:
		a = 0;
		printf("�˳��ɹ�\n");
		break;
	default:
		printf("����ѡ��:>");
	}
	if(a)
		goto again;
	return 0;
}



int want_room(const char* name) {
	erect_part("ס�������");

	FILE* pf3 = fopen("ס�������.txt", "r");
	if (pf3 == NULL) {
		perror("�ļ���ʧ��");
		return 1;
	}
	char get_name[15][50];
	int point = 0;
	while (point<MAX_ROOM_NUM &&fscanf(pf3, "%s", get_name[point]) == 1) {
		point++;
		if (point >= 14) {
			printf("��ǰס�������ѳ����õ����ܳ��ܷ�Χ���޷����ɸ���ͻ������½�\n");
			return 0;
		}
	}
	fclose(pf3);
	for (int i = 0;i <= point;i++) {
		if (strcmp(name, get_name[i]) == 0) {
			printf("���Ѿ���һ��ס�����������\n");
		again:
			printf("���Ƿ��볷��ס������(y/n)\n");
			char choose_new;
			scanf(" %c", &choose_new);
			if (choose_new == 'y') {
				delete_thing("ס�������.txt", name);
				printf("�ѳ�������\n");
				return 0;
			}
			else if (choose_new == 'n') {
				printf("�����˻ز˵�\n");
				return 0;
			}
			else {
				printf("������ѡ��\n");
				goto again;
			}
		}
	}

	FILE* pf2 = fopen("�շ�����.txt", "r");
	int a;
	a = fgetc(pf2);
	if (a == EOF) {
		printf("��Ǹ����ǰû�пշ������½�\n");
		return 0;
	}
	rewind(pf2);
	fclose(pf2);

	FILE* pf = fopen("ס�������.txt", "a");
	if (pf == NULL) {
		perror("�ļ��򿪴���");
		return 0;
	}
	rewind(pf);
	fprintf(pf, "%s\n", name);
	printf("����ɹ�,��ȴ�������ԱΪ����䷿��\n");
	fclose(pf);
	return 0;
}



int judge(const char* name) {
	char file_name[10];
	sprintf(file_name, "%s.txt", name);
	char num[3];
	FILE* pf = fopen(file_name, "r");
	if (fscanf(pf, "%s", num) == 1) {
		return 0;
	}
	else
		return 1;
}

int want_back_room(const char* name) {

	char file_name[50];
	sprintf(file_name, "%s.txt", name);
	FILE* pf = fopen(file_name, "r");
	if (judge(name)) {
		printf("�㵱ǰû��ס��,�����˷�\n");
		return 0;
	}
	else {
		char room_num[5];
		fscanf(pf, "%s\n", room_num);
		fclose(pf);

	again:
		printf("�����ھ�ס�ķ�����%s�ŷ��䣬�Ƿ��˷�(y/n)\n",room_num);
		char choose;
		scanf(" %c", &choose);
		if (choose == 'y') {
			printf("����Ϊ���˷�\n");
			char room_file[10];
			sprintf(room_file, "%s.txt", room_num);
			FILE* pf2 = fopen(room_file, "w");
			fprintf(pf2, "0\n");
			fclose(pf2);
			delete_thing("�ǿշ�����.txt", room_num);
			FILE* pf3 = fopen("�շ�����.txt", "a");
			fprintf(pf3, "%s\n", room_num);
			fclose(pf3);
			FILE* pf4 = fopen(file_name, "w");
			fclose(pf4);
		}

		else if (choose == 'n') {
			return 0;
		}

		else {
			goto again;
		}
	}
	return 0;
}


int want_to_do_guest(const char* filename, const char* name) {
	printf("��ǰ�˺�Ϊ:%s\n", name);
	int input;
again:
	guest_main_menu();

	int a = 1;
	scanf("%d", &input);
	switch (input) {
	case 1:
		sequence("�շ�����.txt");
		find_out_spare_room();
		break;
	case 2:
		want_room(name);
		break;
	case 3:
		erect_part(name);
		want_back_room(name);
		break;
	case 4:
		printf("�Ƿ�ע�����˺�(y/n)\n");
		char choose;
		scanf(" %c", &choose);
		if (choose == 'y') {
			delete_thing(filename, name);
			printf("ע���ɹ�\n");
			a = 0;
			break;
		}
		break;
	case 0:
		a = 0;
		printf("�˳��ɹ�\n");
		break;
	default:
		printf("����ѡ��:>");
	}
	if (a)
		goto again;
	return 0;
}


//��¼
char login() {

	printf("���ǹ�����Ա���ǹ˿ͣ�(c/g)\n");
	int character;
	char c[50];
	char choose;
	scanf(" %c", &choose);

	if (choose != 'c' && choose != 'g') {
		printf("��Ч�Ľ�ɫѡ��\n");
		return 1;
	}

	char account_name[50];

	printf("��������˺���\n");
	scanf("%49s", &account_name);

	if (choose == 'g') {
		if (is_account_exist("�˿��˺�����.txt", account_name)) {
			printf("��¼�ɹ�����ӭ�������˿�%s��\n", account_name);
			strcpy(c, "�˿��˺�����.txt");
			character = 0;
		}
		else {
			printf("�˺����������˺Ų����ڡ�\n");
			return 1;
		}
	}
	else if (choose == 'c') {
		if (is_account_exist("������Ա�˺�����.txt", account_name)) {
			printf("��¼�ɹ�����ӭ������������Ա%s��\n", account_name);
			strcpy(c, "������Ա�˺�����.txt");
			character = 1;
		}
		else {
			printf("�˺����������˺Ų����ڡ�\n");
			return 1;
		}
	}
	
	if (character == 1)
		want_to_do(c, account_name);
	else if (character == 0)
		want_to_do_guest(c, account_name);
	return 0;
}


int whether_erect() {
	FILE* pf3 = fopen("�ǿշ�����.txt", "r");
	if (pf3 != NULL) {
		return 0;
	}

	FILE* pf = fopen("�ǿշ�����.txt", "w");
	FILE* pf2 = fopen("�շ�����.txt", "w");
	if (pf == NULL || pf2 == NULL) {
		perror("�ļ��򿪴���");
		if (pf != NULL) fclose(pf);
		if (pf2 != NULL) fclose(pf2);
		return 1;
	}
	for (int i = 1;i <= 15;i++) {
		fprintf(pf2, "%d\n", i);
	}
	fclose(pf);
	fclose(pf2);
	return 0;
}



//������
int main() {
again:
	menu();
	create_text_files();
	int input = 0;
	whether_erect();
	int a = 0;
	while (scanf("%d", &input)) {

		if (input == 0) {
			printf("���˳�\n");
			break;
		}

		switch (input) {

		case 1:
			a = login();
			menu();
			if (a)
				goto again;
			break;
		case 2:
			want_register();
			menu();
			break;

		default:
			break;
		}
	}
	return 0;
}