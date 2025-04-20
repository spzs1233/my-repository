#include "need.h"
//主程序
int main() {
	whether_erect();
	srand(time(0));
	menu();
again:
	create_text_files();
	int input = 0;
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