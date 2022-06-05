#include"Main_Functions.h"
#include"functions.h"
#include"Book.h"

using namespace std;

int main() {
	Book Book_info;
	Book_info.Get_info();

	while (1) {
		system("cls");
		main_menu();

		printf("请输入您想要进行的操作序号: ");

		int choi = 0;
		cin >> choi;
		getchar();

		switch (choi) {
		case 1:
			Book_info.Show_info();
			Back_to_Mainmenu();
			break;

		case 2:
			Book_info.Insert_info();
			Back_to_Mainmenu();
			break;

		case 3:
			Book_info.Delete_info();
			Back_to_Mainmenu();
			break;

		case 4:
			Book_info.Search_info();
			Back_to_Mainmenu();
			break;

		case 5:
			Book_info.Change_info();
			Back_to_Mainmenu();
			break;

		case 6:
			Book_info.Bubble_Sort();
			Back_to_Mainmenu();
			break;

		case 7:
			if (Book_info.Exit_system() == 'y')
				return 0;
			Back_to_Mainmenu();
			break;

		default:
			cout << "输入无效！请重新选择\n";
			break;
		}
	}
}