/* 通信 2051475 王浩 */
#include "cmd_console_tools.h"
#include "90-b2.h"

//内部数组方式需要的函数

void draw_array(int array[][COLUM_MAX], int array_[][COLUM_MAX], int row, int colum, int color)
{
	int i, j;

	cout << "  |";
	for (j = 0; j < colum; j++)
		cout << setw(3) << j;
	cout << endl;

	cout << "--+";
	for (j = 0; j < colum; j++)
		cout << "---";
	cout << '-' << endl;

	for (i = 0; i < row; i++)
	{
		cout << char('A' + i) << " |";
		for (j = 0; j < colum; j++)
		{
			if (color == 1 && array_[i][j])
			{
				if (array[i][j] >= 10)
					cout << " ";
				else
					cout << "  ";
				cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
				cout << array[i][j];
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			}
			else
				cout << setw(3) << array[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void draw_array_fallen(int array[][COLUM_MAX], int row, int colum)
{
	int i, j;

	cout << "  |";
	for (j = 0; j < colum; j++)
		cout << setw(3) << j;
	cout << endl;

	cout << "--+";
	for (j = 0; j < colum; j++)
		cout << "---";
	cout << '-' << endl;

	for (i = 0; i < row; i++)
	{
		cout << char('A' + i) << " |";
		for (j = 0; j < colum; j++)
		{
			if (array[i][j] == 0)
			{
				if (array[i][j] >= 10)
					cout << " ";
				else
					cout << "  ";
				cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
				cout << array[i][j];
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			}
			else
				cout << setw(3) << array[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void draw_array_result(int array_[][COLUM_MAX], int row, int colum)
{
	cout << "查找结果数组：" << endl;

	int i, j;

	cout << "  |";
	for (j = 0; j < colum; j++)
		cout << setw(3) << j;
	cout << endl;

	cout << "--+";
	for (j = 0; j < colum; j++)
		cout << "---";
	cout << '-' << endl;

	for (i = 0; i < row; i++)
	{
		cout << char('A' + i) << " |";
		for (j = 0; j < colum; j++)
		{
			if (array_[i][j] == 0)
				cout << setw(3) << 0;
			else
				cout << setw(3) << '*';
		}
		cout << endl;
	}
	cout << endl;
}

void input_array_location(int* row_selected, int* colum_selected, int row, int colum)
{
	cout << "请以字母+数字形式[例：c2]输入矩阵坐标：";
	int x, y;
	cct_getxy(x, y);

	char letter;
	int number;
	while (1)
	{
		cin >> letter >> number;
		if (cin.good() == 0)
		{
			cin.clear();
			cin.ignore(65536, '\n');
			
		}
		else if (number < colum && number >= 0)
		{
			if (letter >= 'a' && letter <= 'z')
				letter = char(letter - 'a' + 'A');
			if (letter < ('A' + row) && letter >= 'A')
				break;
		}
		cout << "输入错误，请重新输入.";
		cct_gotoxy(x, y);
		cout << "                            ";
		cct_gotoxy(x, y);
	}

	cout << "输入为" << letter << "行" << number << "列" << "            " << endl;
	cout << endl;
	*row_selected = letter - 'A';
	*colum_selected = number;
}

int input_ynq()
{
	// 1：是   2：否   3：退出
	char ch;
	while (1)
	{
		ch = _getche();
		if (ch == 'y' || ch == 'Y')
			return 1;
		else if (ch == 'n' || ch == 'N')
			return 2;
		else if (ch == 'q' || ch == 'Q')
			return 3;
		else
		{
			cout << '\b';
		}
	}
}

void input_huiche()
{
	char ch;
	while (1)
	{
		ch = _getch();
		if (ch == '\r')
			break;
	}
}

