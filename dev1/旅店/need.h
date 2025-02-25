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
		printf("文件：%s创建成功\n", new_name);
		fclose(pf2);
	}
	else {
		fclose(pf);
	}
}
void menu() {
	printf("-------------------------\n");
	printf("欢迎进入酒店管理系统\n");
	printf("1.登录\n");
	printf("2.注册\n");
	printf("0.退出\n");
	printf("--------------------------\n");

}

bool delete_thing(const char* filename, const char* thing) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		perror("无法打开文件");
		return false;
	}

	FILE* temp_file = tmpfile(); // 创建一个临时文件
	if (temp_file == NULL) {
		perror("无法创建临时文件");
		fclose(file);
		return false;
	}

	char line[100];
	bool account_found = false;
	while (fgets(line, sizeof(line), file)) {
		// 移除换行符
		line[strcspn(line, "\n")] = 0;

		// 如果不是我们要删除的账号，则写入临时文件
		if (strcmp(line, thing) != 0) {
			fputs(line, temp_file);
			fputs("\n", temp_file); // 保持原文件的格式，每行末尾有换行符
		}
		else {
			account_found = true;
		}
	}

	fclose(file);

	// 将临时文件内容写回原文件
	rewind(temp_file); // 重置临时文件的读写位置到开头
	file = fopen(filename, "w"); // 以写模式重新打开原文件，这会清空文件内容
	if (file == NULL) {
		perror("无法重新打开文件以写入");
		fclose(temp_file);
		return false;
	}

	char temp_line[100];
	while (fgets(temp_line, sizeof(temp_line), temp_file)) {
		fputs(temp_line, file);
	}

	fclose(file);
	fclose(temp_file); // 临时文件会自动删除，因为它是用tmpfile()创建的

	return account_found;
}

int find_out_spare_room() {
	FILE* pf = fopen("空房名单.txt", "r");
	FILE* pf2 = fopen("非空房名单.txt", "r");
	if (pf == NULL || pf2 == NULL) {
		perror("文件打开错误");
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

	printf("空房为:");
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

	printf("已入住的房为:");
	for (int i = 0;i < not_spar_count;i++) {
		printf("%d ", not_spare_room_num[i]);
	}
	printf("\n");

	return 0;
}

//查询是否存在账号
bool is_account_exist(const char* filename, const char* account_name) {
	FILE* file = fopen(filename, "r");

	if (file == NULL) {
		perror("无法打开文件");
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

//注册
int want_register() {
	FILE* pf_admin = fopen("管理人员账号名单.txt", "a");
	FILE* pf_custome = fopen("顾客账号名单.txt", "a");
	if (pf_admin == NULL || pf_custome == NULL) {
		perror("账号创建失败");
		return 1;
	}

	printf("你是管理人员还是顾客：(c/g)\n");
	char choose;
	scanf(" %c", &choose); 
	char account_name[50];
	if (choose == 'c') {
		printf("请输入管理人员账号名:\n");
		scanf("%49s", &account_name);
		fprintf(pf_admin, "%s\n", account_name);
		printf("已创建管理人员账号\n");
	}
	else if (choose == 'g') {
		printf("请输入顾客账号名:\n");
		scanf("%49s", &account_name);
		fprintf(pf_custome, "%s\n", account_name);
		printf("已创建顾客账号\n");
	}
	else
		printf("无效选择\n");

	fclose(pf_admin);
	fclose(pf_custome);
	return 0;
}


bool delete_account(const char* filename, const char* account_name) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("无法打开文件");
        return false;
    }

    FILE* temp_file = tmpfile(); // 创建一个临时文件
    if (temp_file == NULL) {
        perror("无法创建临时文件");
        fclose(file);
        return false;
    }

    char line[100];
    bool account_found = false;
    while (fgets(line, sizeof(line), file)) {
        // 移除换行符
        line[strcspn(line, "\n")] = 0;

        // 如果不是我们要删除的账号，则写入临时文件
        if (strcmp(line, account_name) != 0) {
            fputs(line, temp_file);
            fputs("\n", temp_file); // 保持原文件的格式，每行末尾有换行符
        }
        else {
            account_found = true;
			printf("注销成功\n");
        }
    }

    fclose(file);

    // 将临时文件内容写回原文件
    rewind(temp_file); // 重置临时文件的读写位置到开头
    file = fopen(filename, "w"); // 以写模式重新打开原文件，这会清空文件内容
    if (file == NULL) {
        perror("无法重新打开文件以写入");
        fclose(temp_file);
        return false;
    }

    char temp_line[100];
    while (fgets(temp_line, sizeof(temp_line), temp_file)) {
        fputs(temp_line, file);
    }

    fclose(file);
    fclose(temp_file); // 临时文件会自动删除，因为它是用tmpfile()创建的

    return account_found;
}

void admin_main_menu() {
	printf("-------------------------\n");
	printf("1.查询空房\n");
	printf("2.帮用户进行房间入住登记\n");
	printf("3.退房\n");
	printf("4.注销账号\n");
	printf("0.退出当前账号\n");
	printf("-------------------------\n");
	printf("选择:>");
}

void guest_main_menu() {
	printf("-------------------------\n");
	printf("1.查询空房\n");
	printf("2.申请住房\n");
	printf("3.退房\n");
	printf("4.注销账号\n");
	printf("0.退出当前账号\n");
	printf("-------------------------\n");
	printf("选择:>");
}


int create_text_files() {
	char filename[20];
	int num_created = 0;

	FILE* check_file = fopen("15.txt", "r");
	if (check_file == NULL) {
		printf("正在创建房间文件......\n");

		for (int i = 1; i <= 15; i++) {
			sprintf(filename, "%d.txt", i);
			FILE* pf = fopen(filename, "w");
			if (pf == NULL) {
				perror("文件打开失败");
				return 1; 
			}

			else {
				fprintf(pf, "0\n");
				fclose(pf);
				num_created++;
			}
		}

		if (num_created == 15) {
			printf("所有文件创建成功\n");
		}
		else {
			printf("部分文件创建失败\n");
		}
	}
	return 0;
}

int spare_room() {
	FILE* pf = fopen("空房名单.txt", "r");
	if (pf == NULL ) {
		perror("文件打开错误");
		fclose(pf);
		return 0;
	}
	int spare_room_num[15];
	int spare_count = 0;
	while (spare_count < MAX_ROOM_NUM && fscanf(pf, "%d", &spare_room_num[spare_count]) == 1) {
		spare_count++;
	}
	fclose(pf);

	printf("空房为:");
	for (int i = 0;i < spare_count;i++) {
		printf("%d ", spare_room_num[i]);
	}
	printf("\n");

	return 0;
}

int register_room() {
	FILE* pf = fopen("空房名单.txt", "r");
	if (pf == NULL) {
		perror("文件打开错误");
		fclose(pf);
	}
	int c = fgetc(pf);
	fclose(pf);
	if (c == EOF && !feof(pf) && !ferror(pf)) {
		printf("当前没有空房\n");
		return 0;
	}

	spare_room();
	printf("输入用户名字:>");
	char guest_name[50];
	scanf("%s", guest_name);

	FILE* pf5 = fopen("住房申请表.txt", "r");
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
			delete_thing("住房申请表.txt", guest_name);
			break;
		}
	}
	if (a) {
		printf("该用户并不需要住房\n");
		return 0;
	}

jump:
	printf("输入入住的房间号:>");
	char num[3];
	scanf(" %2s", num);

	char room_num[10];
	sprintf(room_num, "%s.txt", num);
	FILE* pf7 = fopen(room_num, "r");
	char what_get_from_file = fgetc(pf7);
	if (what_get_from_file != '0') {
		printf("该房间已有人居住\n");
		goto jump;
	}

	char filename[10];
	sprintf(filename, "%s.txt", num);
	FILE* pf2 = fopen(filename, "r");
	if (pf2 == NULL) {
		perror("文件打开错误");
		printf("没有这个房间\n");
		return 0;
	}
	fclose(pf2);
	FILE* pf3 = fopen(filename, "w");
	fprintf(pf3, "%s", guest_name);
	fclose(pf3);
	FILE* pf4 = fopen("非空房名单.txt", "a");
	fprintf(pf4, "%s\n", num);
	fclose(pf4);


	delete_thing("空房名单.txt", num);

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
		perror("文件打开失败");
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
		printf("该房间无人居住，无需退房\n");
		fclose(pf3);
		return 0;
	}

	char host_name[50 + 4];
	FILE* pf4 = fopen(filename, "r");
	fscanf(pf4, "%49s", host_name);

	printf("该房间用户%s正在居住,是否退房(y/n)\n", host_name);
	char choose;
again:
	scanf(" %c", &choose);
	if (choose == 'n') {
		printf("取消退房成功\n");
		return 0;
	}
	else if (choose != 'y' && choose != 'n') {
		printf("请重新选择\n");
		goto again;
	}
	printf("退房成功\n");

	char host_room[60];
	sprintf(host_room, "%s.txt", host_name);
	fclose(pf4);

	FILE* pf5 = fopen(host_room, "w");
	fclose(pf5);

	FILE* pf = fopen(filename, "w");
	fprintf(pf, "0");
	fclose(pf);

	FILE* pf2 = fopen("空房名单.txt", "a");
	fprintf(pf2, "%s\n", roomnum);
	fclose(pf2);
	sequence("空房名单.txt");
	delete_thing("非空房名单.txt", roomnum);
	return 0;
}


int want_to_do(const char* filename,const char* name) {
	printf("当前账号为:%s\n", name);
	int input_2;

again:
	erect_part("住房申请表");
	FILE* pf = fopen("住房申请表.txt", "r");
	char who_want_room[15][50];
	int num = 0;
	while (num < MAX_ROOM_NUM && fscanf(pf, "%s", who_want_room[num]) == 1) {
		num++;
	}
	fclose(pf);
	for (int i = 0;i < num;i++) {
		printf("用户%s需要住房\n", who_want_room[i]);
	}


	admin_main_menu();

	int a = 1;
	scanf("%d", &input_2);
	switch (input_2) {
	case 1:
		sequence("空房名单.txt");
		sequence("非空房名单.txt");
		find_out_spare_room();
		break;
	case 2:
		sequence("空房名单.txt");
		register_room();
		sequence("非空房名单.txt");
		break;
	case 3:
		char roomnum[3];
		printf("输入需要退的房的房间号:>");
		scanf("%s", roomnum);
		back_room(roomnum);
		break;
	case 4:
		printf("是否注销本账号(y/n)\n");
		char choose;
		scanf(" %c", &choose);
		if (choose == 'y') {
			delete_thing(filename, name);
			printf("注销成功\n");
			a = 0;
			break;
		}
		break;
	case 0:
		a = 0;
		printf("退出成功\n");
		break;
	default:
		printf("重新选择:>");
	}
	if(a)
		goto again;
	return 0;
}



int want_room(const char* name) {
	erect_part("住房申请表");

	FILE* pf3 = fopen("住房申请表.txt", "r");
	if (pf3 == NULL) {
		perror("文件打开失败");
		return 1;
	}
	char get_name[15][50];
	int point = 0;
	while (point<MAX_ROOM_NUM &&fscanf(pf3, "%s", get_name[point]) == 1) {
		point++;
		if (point >= 14) {
			printf("当前住房申请已超过旅店所能承受范围，无法容纳更多客户，请谅解\n");
			return 0;
		}
	}
	fclose(pf3);
	for (int i = 0;i <= point;i++) {
		if (strcmp(name, get_name[i]) == 0) {
			printf("你已经有一个住房申请待处理\n");
		again:
			printf("你是否想撤销住房申请(y/n)\n");
			char choose_new;
			scanf(" %c", &choose_new);
			if (choose_new == 'y') {
				delete_thing("住房申请表.txt", name);
				printf("已撤销申请\n");
				return 0;
			}
			else if (choose_new == 'n') {
				printf("现在退回菜单\n");
				return 0;
			}
			else {
				printf("请重新选择\n");
				goto again;
			}
		}
	}

	FILE* pf2 = fopen("空房名单.txt", "r");
	int a;
	a = fgetc(pf2);
	if (a == EOF) {
		printf("抱歉，当前没有空房，请谅解\n");
		return 0;
	}
	rewind(pf2);
	fclose(pf2);

	FILE* pf = fopen("住房申请表.txt", "a");
	if (pf == NULL) {
		perror("文件打开错误");
		return 0;
	}
	rewind(pf);
	fprintf(pf, "%s\n", name);
	printf("申请成功,请等待管理人员为你分配房间\n");
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
		printf("你当前没有住房,无需退房\n");
		return 0;
	}
	else {
		char room_num[5];
		fscanf(pf, "%s\n", room_num);
		fclose(pf);

	again:
		printf("你现在居住的房间是%s号房间，是否退房(y/n)\n",room_num);
		char choose;
		scanf(" %c", &choose);
		if (choose == 'y') {
			printf("正在为你退房\n");
			char room_file[10];
			sprintf(room_file, "%s.txt", room_num);
			FILE* pf2 = fopen(room_file, "w");
			fprintf(pf2, "0\n");
			fclose(pf2);
			delete_thing("非空房名单.txt", room_num);
			FILE* pf3 = fopen("空房名单.txt", "a");
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
	printf("当前账号为:%s\n", name);
	int input;
again:
	guest_main_menu();

	int a = 1;
	scanf("%d", &input);
	switch (input) {
	case 1:
		sequence("空房名单.txt");
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
		printf("是否注销本账号(y/n)\n");
		char choose;
		scanf(" %c", &choose);
		if (choose == 'y') {
			delete_thing(filename, name);
			printf("注销成功\n");
			a = 0;
			break;
		}
		break;
	case 0:
		a = 0;
		printf("退出成功\n");
		break;
	default:
		printf("重新选择:>");
	}
	if (a)
		goto again;
	return 0;
}


//登录
char login() {

	printf("你是管理人员还是顾客：(c/g)\n");
	int character;
	char c[50];
	char choose;
	scanf(" %c", &choose);

	if (choose != 'c' && choose != 'g') {
		printf("无效的角色选择\n");
		return 1;
	}

	char account_name[50];

	printf("输入你的账号名\n");
	scanf("%49s", &account_name);

	if (choose == 'g') {
		if (is_account_exist("顾客账号名单.txt", account_name)) {
			printf("登录成功！欢迎回来，顾客%s。\n", account_name);
			strcpy(c, "顾客账号名单.txt");
			character = 0;
		}
		else {
			printf("账号名错误或该账号不存在。\n");
			return 1;
		}
	}
	else if (choose == 'c') {
		if (is_account_exist("管理人员账号名单.txt", account_name)) {
			printf("登录成功！欢迎回来，管理人员%s。\n", account_name);
			strcpy(c, "管理人员账号名单.txt");
			character = 1;
		}
		else {
			printf("账号名错误或该账号不存在。\n");
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
	FILE* pf3 = fopen("非空房名单.txt", "r");
	if (pf3 != NULL) {
		return 0;
	}

	FILE* pf = fopen("非空房名单.txt", "w");
	FILE* pf2 = fopen("空房名单.txt", "w");
	if (pf == NULL || pf2 == NULL) {
		perror("文件打开错误");
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



//主程序
int main() {
again:
	menu();
	create_text_files();
	int input = 0;
	whether_erect();
	int a = 0;
	while (scanf("%d", &input)) {

		if (input == 0) {
			printf("已退出\n");
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