#include"Main_Functions.h"
#include"functions.h"

using namespace std;

int main() {
	tot = Get_info();

	while (1) {
		system("cls");
		main_menu();

		printf("����������Ҫ���еĲ������: ");

		int choi = 0;
		cin >> choi;
		getchar();

		switch (choi) {
		case 1:
			Show_info();
			Back_to_Mainmenu();
			break;

		case 2:
			Insert_info();
			Back_to_Mainmenu();
			break;

		case 3:
			Delete_info();
			Back_to_Mainmenu();
			break;

		case 4:
			Search_info();
			Back_to_Mainmenu();
			break;

		case 5:
			Change_info();
			Back_to_Mainmenu();
			break;

		case 6:
			Sort_info();
			Back_to_Mainmenu();
			break;

		case 7:
			if (Exit_system() == 'y')
				return 0;
			Back_to_Mainmenu();
			break;

		default:
			cout << "������Ч��������ѡ��\n";
			break;
		}
	}	
}