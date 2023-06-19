/* 通信 2051475 王浩 */
#include "cmd_console_tools.h"
#include "90-b2.h"

//伪图形界面需要的函数

void draw_interface(int row, int colum, int array[][COLUM_MAX], int sleep_time)
{
	int i, j;

	//第一行标签
	cout << ' ';
	for (i = 0; i < colum; i++)
		cout << setw(6) << i;
	cout << endl;

	cout << setiosflags(ios::left);

	//白色上边界
	cout << "  ";
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cout << "┏";
	Sleep(sleep_time);
	for (i = 0; i < colum; i++)
	{
		cout << "━━━";
		Sleep(sleep_time);
	}
	cout << "┓";
	Sleep(sleep_time);
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cout << endl;

	//中间白底
	for (i = 0; i < row; i++)
	{
		cout << "  ";
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "┃";
		Sleep(sleep_time);
		for (j = 0; j < colum; j++)
		{
			cout << "      ";
			Sleep(sleep_time);
		}
		cout << "┃";
		Sleep(sleep_time);
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		cout << endl;

		cout << char('A' + i) << ' ';
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "┃";
		Sleep(sleep_time);
		for (j = 0; j < colum; j++)
		{
			cout << "      ";
			Sleep(sleep_time);
		}
		cout << "┃";
		Sleep(sleep_time);
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		cout << endl;

		cout << "  ";
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "┃";
		Sleep(sleep_time);
		for (j = 0; j < colum; j++)
		{
			cout << "      ";
			Sleep(sleep_time);
		}
		cout << "┃";
		Sleep(sleep_time);
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		cout << endl;
	}

	//白色下边界
	cout << "  ";
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cout << "┗";
	Sleep(sleep_time);
	for (i = 0; i < colum; i++)
	{
		cout << "━━━";
		Sleep(sleep_time);
	}
	cout << "┛";
	Sleep(sleep_time);
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cout << endl;

	//色块
	cct_gotoxy(4, 3);
	for (i = 0; i < row * 3; i = i + 3)
	{
		//一行色块
		for (j = 0; j < colum * 6; j = j + 6)
		{
			cct_setcolor(array[i / 3][j / 6], COLOR_BLACK);
			cct_gotoxy(4 + j, 3 + i);
			cout << "┏━┓";
			cct_gotoxy(4 + j, 3 + i + 1);
			cout << setiosflags(ios::left);
			cout << "┃" << setw(2) << array[i / 3][j / 6] << "┃";
			cout << setiosflags(ios::right);
			cct_gotoxy(4 + j, 3 + i + 2);
			cout << "┗━┛";
		}
		Sleep(sleep_time);
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cout << resetiosflags(ios::left);
	cout << setiosflags(ios::right);
}

void input_end_error()
{
	char input[1000] = { 0 };
	cout << "本小题结束，请输入End继续...";
	int x, y;
	cct_getxy(x, y);
	while (1)
	{
		cin.getline(input, 65536);
		for (int i = 0; input[i] != '\0'; i++)
		{
			if (input[i] >= 'a' && input[i] <= 'z')
				input[i] = char(input[i] - 'a' + 'A');
		}
		if (!strcmp(input, "END"))
			break;
		else
		{
			cout << "输入错误，请重新输入.";
			cct_gotoxy(x, y);
			cout << "                            ";
			cct_gotoxy(x, y);
		}
	}
}

void draw_interface_col(int row, int colum, int array[][COLUM_MAX], int sleep_time)
{
	int i, j;

	//第一行标签
	cout << setw(7) << '0';
	for (i = 1; i < colum; i++)
		cout << setw(8) << i;
	cout << endl;

	cout << setiosflags(ios::left);

	//白色上边界
	cout << "  ";
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cout << "┏";
	Sleep(sleep_time);
	for (i = 0; i < colum; i++)
	{
		cout << "━━━";
		if (i < colum - 1)
			cout << "┳";
		Sleep(sleep_time);
	}
	cout << "┓";
	Sleep(sleep_time);
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cout << endl;

	//中间白底
	for (i = 0; i < row; i++)
	{
		cout << "  ";
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "┃";
		Sleep(sleep_time);
		for (j = 0; j < colum; j++)
		{
			cout << "      " << "┃";
			Sleep(sleep_time);
		}
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		cout << endl;

		cout << char('A' + i) << ' ';
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "┃";
		Sleep(sleep_time);
		for (j = 0; j < colum; j++)
		{
			cout << "      " << "┃";
			Sleep(sleep_time);
		}
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		cout << endl;

		cout << "  ";
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "┃";
		Sleep(sleep_time);
		for (j = 0; j < colum; j++)
		{
			cout << "      " << "┃";
			Sleep(sleep_time);
		}
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		cout << endl;

		if (i < row - 1)
		{
			cout << "  ";
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cout << "┣";
			Sleep(sleep_time);
			for (j = 0; j < colum; j++)
			{
				cout << "━━━";
				if (j < colum - 1)
					cout << "╋";
				Sleep(sleep_time);
			}
			cout << "┫";
			Sleep(sleep_time);
			cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			cout << endl;
		}
	}

	//白色下边界
	cout << "  ";
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cout << "┗";
	Sleep(sleep_time);
	for (i = 0; i < colum; i++)
	{
		cout << "━━━";
		if (i < colum - 1)
			cout << "┻";
		Sleep(sleep_time);
	}
	cout << "┛";
	Sleep(sleep_time);
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cout << endl;

	//色块
	cct_gotoxy(4, 3);
	for (i = 0; i < row * 4; i = i + 4)
	{
		//一行色块
		for (j = 0; j < colum * 8; j = j + 8)
		{
			int color = (array[i / 4][j / 8] > 0 ? array[i / 4][j / 8] : COLOR_HWHITE);
			cct_setcolor(color, (color == 0 ? 0 : COLOR_BLACK));
			cct_gotoxy(4 + j, 3 + i);
			cout << "┏━┓";
			cct_gotoxy(4 + j, 3 + i + 1);
			cout << "┃" << setw(2) << array[i / 4][j / 8] << "┃";
			cct_gotoxy(4 + j, 3 + i + 2);
			cout << "┗━┛";
		}
		Sleep(sleep_time);
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cout << resetiosflags(ios::left);
}

int select_diamond(int* row_selected, int* colum_selected, int row, int colum)
{
	cct_setcursor(CURSOR_INVISIBLE);
	int if_end = 0;

	while (1)
	{
		int if_break = 0;
		int MX, MY, MAction, keycode1, keycode2, cct_return;
		cct_return = cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);

		if (cct_return == CCT_KEYBOARD_EVENT)
		{
			if (keycode1 == 224)
			{
				if (keycode2 == KB_ARROW_UP)
				{
					if (*row_selected == 0)
						*row_selected = row - 1;
					else
						*row_selected -= 1;
					if_break = 1;
				}
				else if (keycode2 == KB_ARROW_DOWN)
				{
					if (*row_selected == row - 1)
						*row_selected = 0;
					else
						*row_selected += 1;
					if_break = 1;
				}
				else if (keycode2 == KB_ARROW_LEFT)
				{
					if (*colum_selected == 0)
						*colum_selected = colum - 1;
					else
						*colum_selected -= 1;
					if_break = 1;
				}
				else if (keycode2 == KB_ARROW_RIGHT)
				{
					if (*colum_selected == colum - 1)
						*colum_selected = 0;
					else
						*colum_selected += 1;
					if_break = 1;
				}
			}
			else if (keycode1 == '\r')
			{
				if_end = 1;
				break;
			}
			else
				continue;
			cct_gotoxy(0, 3 + 4 * row);
			cout << "                                                    ";
			cct_gotoxy(0, 3 + 4 * row);
			cout << "[当前键盘] " << char(*row_selected + 'A') << "行" << *colum_selected << "列";
			if (if_break)
				break;
		}
		else if (cct_return == CCT_MOUSE_EVENT)
		{
			int if_feifa = 1;
			int row_now = MY - 3;
			int colum_now = MX - 4;
			if (MAction == MOUSE_ONLY_MOVED)
			{
				//根据鼠标坐标修改选中数组元素
				for (int i = 0; i < row; i++)
				{
					if (row_now >= i * 4 && row_now <= i * 4 + 2)
					{
						*row_selected = i;
						for (int j = 0; j < colum; j++)
						{
							if (colum_now >= j * 8 && colum_now <= j * 8 + 5)
							{
								*colum_selected = j;
								if_break = 1;
								if_feifa = 0;
							}
						}
					}
				}
			}
			else if (MAction == MOUSE_LEFT_BUTTON_CLICK)
			{
				if_end = 1;
				break;
			}
			else
				continue;
			cct_gotoxy(0, 3 + 4 * row);
			cout << "                                                    ";
			cct_gotoxy(0, 3 + 4 * row);
			cout << "[当前鼠标] ";
			if (if_feifa)
				cout << "位置非法";
			else
				cout << char(*row_selected + 'A') << "行" << *colum_selected << "列";
			if (if_break)
				break;
		}
	}

	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	//cct_disable_mouse();

	return if_end;
}

void draw_select_diamond(int row_selected, int colum_selected, int array[][COLUM_MAX], int if_hwhite)
{
	int x = 4 + 8 * colum_selected;
	int y = 3 + 4 * row_selected;
	int color = (array[row_selected][colum_selected] > 0 ? array[row_selected][colum_selected] : COLOR_HWHITE);

	if (if_hwhite == 0)
		cct_setcolor(color, (color == 0 ? 0 : COLOR_WHITE));
	else
		cct_setcolor(color, (color == 0 ? 0 : COLOR_HWHITE));
	cout << setiosflags(ios::left);

	cct_gotoxy(x, y);
	cout << "┏━┓";
	cct_gotoxy(x, y + 1);
	cout << "┃" << setw(2) << array[row_selected][colum_selected] << "┃";
	cct_gotoxy(x, y + 2);
	cout << "┗━┛";

	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cout << resetiosflags(ios::left);
}

void draw_one_diamond(int row_selected, int colum_selected, int array[][COLUM_MAX])
{
	int x = 4 + 8 * colum_selected;
	int y = 3 + 4 * row_selected;

	cct_setcolor(array[row_selected][colum_selected], COLOR_BLACK);
	cout << setiosflags(ios::left);

	cct_gotoxy(x, y);
	cout << "┏━┓";
	cct_gotoxy(x, y + 1);
	cout << "┃" << setw(2) << array[row_selected][colum_selected] << "┃";
	cct_gotoxy(x, y + 2);
	cout << "┗━┛";

	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cout << resetiosflags(ios::left);
}

void draw_empty_diamond(int row_selected, int colum_selected, int array[][COLUM_MAX])
{
	int x = 4 + 8 * colum_selected;
	int y = 3 + 4 * row_selected;

	cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);

	cct_gotoxy(x, y);
	cout << "      ";
	cct_gotoxy(x, y + 1);
	cout << "      ";
	cct_gotoxy(x, y + 2);
	cout << "      ";

	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cout << resetiosflags(ios::left);
}

void draw_blingbling(int row_selected, int colum_selected, int array[][COLUM_MAX])
{
	int x = 4 + 8 * colum_selected;
	int y = 3 + 4 * row_selected;

	cout << setiosflags(ios::left);

	for (int i = 0; i < 5; i++)
	{
		cct_setcolor(array[row_selected][colum_selected], COLOR_BLACK);

		cct_gotoxy(x, y);
		cout << "┏━┓";
		cct_gotoxy(x, y + 1);
		cout << "┃" << setw(2) << array[row_selected][colum_selected] << "┃";
		cct_gotoxy(x, y + 2);
		cout << "┗━┛";
		Sleep(100);

		cct_setcolor(array[row_selected][colum_selected], COLOR_WHITE);

		cct_gotoxy(x, y);
		cout << "┏━┓";
		cct_gotoxy(x, y + 1);
		cout << "┃" << setw(2) << array[row_selected][colum_selected] << "┃";
		cct_gotoxy(x, y + 2);
		cout << "┗━┛";
		Sleep(100);
	}
	cct_setcolor(array[row_selected][colum_selected], COLOR_BLACK);

	cct_gotoxy(x, y);
	cout << "┏━┓";
	cct_gotoxy(x, y + 1);
	cout << "┃" << setw(2) << array[row_selected][colum_selected] << "┃";
	cct_gotoxy(x, y + 2);
	cout << "┗━┛";

	cct_setcolor(COLOR_BLACK, COLOR_WHITE);

	cout << resetiosflags(ios::left);
}

/*1键盘移动 2鼠标移动 3选择 4结束*/
int kb_m_action(int* row_selected, int* colum_selected, int row, int colum, int* if_feifa, int* if_left)
{
	cct_setcursor(CURSOR_INVISIBLE);
	int if_end = 0;

	while (1)
	{
		int MX, MY, MAction, keycode1, keycode2, cct_return;
		cct_return = cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);

		if (cct_return == CCT_KEYBOARD_EVENT)
		{
			if (keycode1 == 224)
			{
				if (keycode2 == KB_ARROW_UP)
				{
					if (*row_selected == 0)
						*row_selected = row - 1;
					else
						*row_selected -= 1;
					return 1;
				}
				else if (keycode2 == KB_ARROW_DOWN)
				{
					if (*row_selected == row - 1)
						*row_selected = 0;
					else
						*row_selected += 1;
					return 1;
				}
				else if (keycode2 == KB_ARROW_LEFT)
				{
					if (*colum_selected == 0)
						*colum_selected = colum - 1;
					else
						*colum_selected -= 1;
					return 1;
				}
				else if (keycode2 == KB_ARROW_RIGHT)
				{
					if (*colum_selected == colum - 1)
						*colum_selected = 0;
					else
						*colum_selected += 1;
					return 1;
				}
			}
			else if (keycode1 == '\r')
			{
				return 3;
			}
			else if (keycode1 == 'Q' || keycode1 == 'q')
				return 4;
			else
				continue;
		}
		else if (cct_return == CCT_MOUSE_EVENT)
		{
			int row_now = MY - 3;
			int colum_now = MX - 4;
			if (MAction == MOUSE_ONLY_MOVED)
			{
				//根据鼠标坐标修改选中数组元素
				for (int i = 0; i < row; i++)
				{
					if (row_now >= i * 4 && row_now <= i * 4 + 2)
					{
						*row_selected = i;
						for (int j = 0; j < colum; j++)
						{
							if (colum_now >= j * 8 && colum_now <= j * 8 + 5)
							{
								*colum_selected = j;
								*if_feifa = 0;
							}
						}
					}
				}
				return 2;
			}
			else if (MAction == MOUSE_LEFT_BUTTON_CLICK)
			{
				*if_left = 1;
				return 3;
			}
			else if (MAction == MOUSE_RIGHT_BUTTON_CLICK)
				return 4;
			else
				continue;
		}
	}

	//cct_disable_mouse();

}

void clear_select_diamond(int row_selected, int colum_selected, int array[][COLUM_MAX])
{
	int x = 4 + 8 * colum_selected;
	int y = 3 + 4 * row_selected;

	int color = (array[row_selected][colum_selected] > 0 ? array[row_selected][colum_selected] : COLOR_HWHITE);
	cct_setcolor(color, (color == COLOR_HWHITE ? COLOR_HWHITE : COLOR_BLACK));
	cout << setiosflags(ios::left);

	cct_gotoxy(x, y);
	cout << "┏━┓";
	cct_gotoxy(x, y + 1);
	cout << "┃" << setw(2) << array[row_selected][colum_selected] << "┃";
	cct_gotoxy(x, y + 2);
	cout << "┗━┛";

	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cout << resetiosflags(ios::left);
}

void draw_diamond_fall(int row, int colum, int array[][COLUM_MAX], int sleep_time)
{
	int i, j, k;
	for (j = 0; j < colum; j++)
	{
		for (i = row - 1; i >= 0; i--)
		{
			//有0元素 下落
			if (array[i][j] == 0)
			{
				//遍历0元素上方的位置
				for (k = i - 1; k >= 0; k--)
				{
					//遇到非零则下落
					int tmp = k;
					if (array[k][j] != 0)
					{
						while (1)
						{
							array[k + 1][j] = array[k][j];
							array[k][j] = 0;

							int x = 4 + 8 * j;
							int y = 3 + 4 * k;

							cout << setiosflags(ios::left);
							cct_setcolor(array[k][j], COLOR_BLACK);

							//draw_empty_diamond(k, j, array);
							//draw_one_diamond(k + 1, j, array);

							for (int number = 0; number < 4; number++)
							{
								cct_gotoxy(x, y);
								cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
								cout << "      ";
								cct_gotoxy(x, y + 1);
								cct_setcolor(array[k + 1][j], COLOR_BLACK);
								cout << "┏━┓";
								cct_gotoxy(x, y + 2);
								cout << "┃" << setw(2) << array[k + 1][j] << "┃";
								cct_gotoxy(x, y + 3);
								cout << "┗━┛";
								if (number == 3)
								{
									cct_gotoxy(x, y);
									cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
									cout << "━━━";
								}
								else
								{
									Sleep(sleep_time);
								}
								y++;
							}

							cct_setcolor(COLOR_BLACK, COLOR_WHITE);
							cout << resetiosflags(ios::left);

							k++;
							Sleep(sleep_time);
							if (array[k + 1][j] != 0 || k == row - 1)
								break;
						}
					}
					k = tmp;
				}
			}
		}
	}
}

void draw_diamond_append(int row, int colum, int array[][COLUM_MAX], int num_max)
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < colum; j++)
		{
			if (array[i][j] == 0)
			{
				array[i][j] = rand_int(num_max);
				draw_one_diamond(i, j, array);
			}
		}
	}
}
