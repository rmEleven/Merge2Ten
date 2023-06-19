/* 通信 2051475 王浩 */
#include "cmd_console_tools.h"
#include "90-b2.h"

//公用函数

void input_set(int* row, int* colum, int* target, int if_target)
{
	//输入行数
	while (1)
	{
		cout << "请输入行数(" << ROW_MIN << '-' << ROW_MAX << ")：" << endl;
		cin >> *row;
		if (cin.good() == 0)
		{
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else if ((*row >= ROW_MIN) && (*row <= ROW_MAX))
			break;
	}
	//输入列数
	while (1)
	{
		cout << "请输入列数(" << COLUM_MIN << '-' << COLUM_MAX << ")：" << endl;
		cin >> *colum;
		if (cin.good() == 0)
		{
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else if ((*colum >= COLUM_MIN) && (*colum <= COLUM_MAX))
			break;
	}
	//输入目标
	if(if_target)
		while (1)
		{
			cout << "请输入合成目标(" << TARGET_MIN << '-' << TARGET_MAX << ")：" << endl;
			cin >> *target;
			if (cin.good() == 0)
			{
				cin.clear();
				cin.ignore(65536, '\n');
			}
			else if ((*target >= TARGET_MIN) && (*target <= TARGET_MAX))
				break;
		}
	cout << endl;
}

int rand_int(int range)
{
	int randint = 0;

	if (range == 3)
	{
		randint = (rand() % 3) + 1;
		return randint;
	}
	else if (range == 4)
	{
		randint = rand() % 10;
		if (randint == 0)
			return 4;
		else
		{
			randint = (randint % 3) + 1;
			return randint;
		}
	}
	else if (range == 5)
	{
		randint = rand() % 20;
		if (randint == 0 || randint == 1)
			return 5;
		else if (randint >= 2 && randint <= 4)
			return 4;
		else
		{
			randint = (randint % 3) + 1;
			return randint;
		}
	}
	else if (range == 6)
	{
		randint = rand() % 20;
		if (randint == 0)
			return 6;
		else if (randint >= 1 && randint <= 3)
			return 5;
		else
		{
			randint = (randint % 4) + 1;
			return randint;
		}
	}
	else
	{
		randint = rand() % 10000;
		if (randint >= 0 && randint <= 399)
			return range;
		else if (randint >= 400 && randint <= 799)
			return range - 1;
		else if (randint >= 800 && randint <= 1599)
			return range - 2;
		else
		{
			randint = (randint % (range - 3)) + 1;
			return randint;
		}
	}
}

void ini_array(int array[][COLUM_MAX], int row, int colum)
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < colum; j++)
		{
			array[i][j] = rand_int(3);
		}
	}
}

void reset_record(int array_[][COLUM_MAX], int row, int colum)
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < colum; j++)
		{
			array_[i][j] = 0;
		}
	}
}

void combine(int array[][COLUM_MAX], int array_[][COLUM_MAX], int row_selected, int colum_selected, int row_max, int colum_max)
{
	int i, j;
	for (i = 0; i < row_max; i++)
	{
		for (j = 0; j < colum_max; j++)
		{
			if (array_[i][j] == 1)
			{
				if (i == row_selected && j == colum_selected)
					array[i][j]++;
				else
					array[i][j] = 0;
			}
		}
	}
}

void array_fall(int array[][COLUM_MAX], int row_max, int colum_max)
{
	int i, j;
	while (1)
	{
		int counter = 0;
		for (i = 0; i < row_max - 1; i++)
		{
			for (j = 0; j < colum_max; j++)
			{
				if (array[i + 1][j] == 0 && array[i][j] != 0)
				{
					array[i + 1][j] = array[i][j];
					array[i][j] = 0;
					counter++;
				}
			}
		}
		if (counter == 0)
			break;
	}
}

void change_array_(int array[][COLUM_MAX], int array_[][COLUM_MAX], int row_max, int colum_max)
{
	int i, j;
	for (i = 0; i < row_max; i++)
	{
		for (j = 0; j < colum_max; j++)
		{
			if (array[i][j] == 0)
			{
				array_[i][j] = 1;
			}
		}
	}
}

void array_append(int array[][COLUM_MAX], int row_max, int colum_max, int num_max)
{
	int i, j;
	for (i = 0; i < row_max; i++)
	{
		for (j = 0; j < colum_max; j++)
		{
			if (array[i][j] == 0)
			{
				array[i][j] = rand_int(num_max);
			}
		}
	}
}

int find_num_max(int array[][COLUM_MAX], int row_max, int colum_max)
{
	int num_max = 0;
	int i, j;
	for (i = 0; i < row_max; i++)
	{
		for (j = 0; j < colum_max; j++)
		{
			if (array[i][j] > num_max)
				num_max = array[i][j];
		}
	}
	return num_max;
}

int score_record(int array[][COLUM_MAX], int array_[][COLUM_MAX], int row_max, int colum_max)
{
	int score = 0;

	int i, j;
	for (i = 0; i < row_max; i++)
	{
		for (j = 0; j < colum_max; j++)
		{
			if (array_[i][j] == 1)
			{
				score += 3 * array[i][j];
			}
		}
	}

	return score;
}

void input_end()
{
	char input[1000] = { 0 };
	cin.ignore(65536, '\n');
	while (1)
	{
		cout << "本小题结束，请输入End继续...";
		cin.getline(input, 65536);
		for (int i = 0; input[i] != '\0'; i++)
		{
			if (input[i] >= 'a' && input[i] <= 'z')
				input[i] = char(input[i] - 'a' + 'A');
		}
		if (!strcmp(input, "END"))
			break;
		cout << endl << endl;
	}
}

int bfs(int row_selected, int colum_selected, int row_max, int colum_max, int array[][COLUM_MAX], int array_[][COLUM_MAX])
{
	//创建队列
	struct note que[ROW_MAX * COLUM_MAX];
	//移动方向
	int next[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };
	//初始化队列
	int head = 0, tail = 0;
	//相同数字个数
	int counter = 0;
	//插入起始坐标
	que[tail].row = row_selected;
	que[tail].colum = colum_selected;
	tail++;
	array_[row_selected][colum_selected] = 1;
	//队列非空时循环
	while (head < tail)
	{
		//遍历四个方向
		for (int k = 0; k < 4; k++)
		{
			//下一个位置的坐标
			int row = que[head].row + next[k][0];
			int colum = que[head].colum + next[k][1];
			//是否越界
			if (row < 0 || row >= row_max || colum < 0 || colum >= colum_max)
				continue;
			//判断该位置
			if (array[row][colum] == array[row_selected][colum_selected] && array_[row][colum] == 0)
			{
				//数字相同且没被标记
				//计数
				counter++;
				//标记
				array_[row][colum] = 1;
				//插入队列
				que[tail].row = row;
				que[tail].colum = colum;
				tail++;
			}
		}
		head++;
	}
	return counter;
}

int dfs(int row_selected, int colum_selected, int row_max, int colum_max, int array[][COLUM_MAX], int array_[][COLUM_MAX])
{
	//移动方向
	int next[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };
	//计数
	static int counter = 0;

	array_[row_selected][colum_selected] = 1;


	//遍历四个方向
	for (int k = 0; k < 4; k++)
	{
		//下一个位置的坐标
		int row = row_selected + next[k][0];
		int colum = colum_selected + next[k][1];
		//是否越界
		if (row < 0 || row >= row_max || colum < 0 || colum >= colum_max)
			continue;
		//判断该位置
		if (array[row][colum] == array[row_selected][colum_selected] && array_[row][colum] == 0)
		{
			//数字相同且没被标记
			//计数
			counter++;
			//标记
			array_[row][colum] = 1;
			//尝试下一个位置 递归
			dfs(row, colum, row_max, colum_max, array, array_);
			//array_[row][colum] = 0;
		}
	}

	return counter;
}