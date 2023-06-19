/* 通信 2051475 王浩 */
#include "cmd_console_tools.h"
#include "90-b2.h"

int get_score(int row_selected, int colum_selected, int row_max, int colum_max, int array[][COLUM_MAX], int array_[][COLUM_MAX])
{
	int score = 0;

	int num = bfs(row_selected, colum_selected, row_max, colum_max, array, array_);

	if (num == 0)
		score = -999;
	else
		score = (num + 1) * (8000 - 500 * array[row_selected][colum_selected]);

	return score;
}

void search_score_max_location(mto10_net_tools& client, int array[][COLUM_MAX], int array_[][COLUM_MAX], char* row, int* colum)
{
	reset_record(array_, client.get_row(), client.get_col());

	//记录各个位置得分情况
	int score_record[ROW_MAX][COLUM_MAX] = { -999 };
	for (int i = 0; i < client.get_row(); i++)
	{
		for (int j = 0; j < client.get_col(); j++)
		{
			score_record[i][j] = get_score(i, j, client.get_row(), client.get_col(), array, array_);
		}
	}
	//选择最大分值
	int score_max = score_record[0][0];
	int score_max_row = 0;
	int score_max_col = 0;
	for (int i = 0; i < client.get_row(); i++)
	{
		for (int j = 0; j < client.get_col(); j++)
		{
			if (score_record[i][j] > score_max)
			{
				score_max = score_record[i][j];
				score_max_row = i;
				score_max_col = j;
			}
		}
	}

	*row = char(score_max_row + 'A');
	*colum = score_max_col;
	reset_record(array_, client.get_row(), client.get_col());
}

int game_progress(mto10_net_tools& client, int array[][COLUM_MAX], int array_[][COLUM_MAX], int if_console, int sleep_time)
{
	char svrpack[RECVBUF_LEN];	//存放从Server端收到的数据
	char row;
	int col;
	int if_draw_interface = 1;
	int draw_change[ROW_MAX][COLUM_MAX] = { 0 };

	while (1) {
		/* -------------------
			Client=>Server
		   ------------------- */
		   /* 根据服务端发来的地图，返回一个解坐标（目前为手工输入形式，需要改为自动求最佳解坐标）
			  提示：可以将client.get_map()的返回值复制到字符数组中，再还原为你自己的二维数组后求解
		   */
		char tmp[100] = { 0 };
		strcpy(tmp, client.get_map());
		char* p = tmp;
		//复制地图
		for (int i = 0; i < client.get_row(); i++)
		{
			for (int j = 0; j < client.get_col(); j++)
			{
				int n = 0;

				if (*p >= '0' && *p <= '9')
					n = int(*p - '0');
				else if (*p >= 'a' && *p <= 'f')
					n = int(*p - 'a' + 10);
				else if (*p >= 'A' && *p <= 'F')
					n = int(*p - 'A' + 10);

				array[i][j] = n;
				p++;
			}
		}
		
		//找最大值
		int max_value = array[0][0];
		for (int i = 0; i < client.get_row(); i++)
		{
			for (int j = 0; j < client.get_col(); j++)
			{
				if (array[i][j] > max_value)
					max_value = array[i][j];
			}
		}

		reset_record(array_, client.get_row(), client.get_col());

		if (if_console == 0)
		{
			cout << "当前数组：" << endl;
			cout << "GameID = " << client.get_gameid() << " Step = " << client.get_step() << " Score = " << client.get_score() << " MaxValue = " << max_value << endl;
			draw_array(array, array_, client.get_row(), client.get_col(), 0);
		}
		else
		{
			if (if_draw_interface == 1)
			{
				cct_cls(); 
				cct_gotoxy(0, 0);
				cout << "                                                                                                  ";
				cct_gotoxy(0, 0);
				cout << "GameID=" << client.get_gameid() << " Step=" << client.get_step() << " Score=" << client.get_score() << " MaxValue=" << max_value;
				cout << endl;
				draw_interface_col(client.get_row(), client.get_col(), array, 0);
				if_draw_interface = 0;
			}
			else
			{
				cct_gotoxy(0, 0);
				cout << "                                                                                ";
				cct_gotoxy(0, 0);
				cout << "GameID=" << client.get_gameid() << " Step=" << client.get_step() << " Score=" << client.get_score() << " MaxValue=" << max_value;
				cout << endl;
				//遍历 画改变
				for (int i = 0; i < client.get_row(); i++)
				{
					for (int j = 0; j < client.get_col(); j++)
					{
						if (draw_change[i][j] == 1)
							draw_one_diamond(i, j, array);
					}
				}
				reset_record(draw_change, client.get_row(), client.get_col());
			}
		}

		/* 游戏已结束则不再读键*/
		if (client.is_gameover())
			break;

		search_score_max_location(client, array, array_, &row, &col);

		if (if_console == 0)
		{
			cout << "请输入行(A-J)列(0-9)坐标 : " << row << col;
			//标记相同数值
			bfs(int(row - 'A'), col, client.get_row(), client.get_col(), array, array_);
			//*显示相同值
			cout << endl;
			draw_array_result(array_, client.get_row(), client.get_col());

			//亮色显示相同值
			draw_array(array, array_, client.get_row(), client.get_col(), 1);

			combine(array, array_, int(row - 'A'), col, client.get_row(), client.get_col());
			//下落
			array_fall(array, client.get_row(), client.get_col());
			draw_array_fallen(array, client.get_row(), client.get_col());
		}
		else if (if_console == 1)
		{
			//标记相同数值
			bfs(int(row - 'A'), col, client.get_row(), client.get_col(), array, array_);
			//文字显示选中元素
			cct_gotoxy(0, 4 + 4 * client.get_row());
			cout << "                                                     ";
			cct_gotoxy(0, 4 + 4 * client.get_row());
			cout << "选中" << row << col;
			//亮色显示选中元素
			for (int i = 0; i < client.get_row(); i++)
			{
				for (int j = 0; j < client.get_col(); j++)
				{
					if (array_[i][j] == 1)
						draw_select_diamond(i, j, array, 0);
				}
			}
			draw_select_diamond(int(row - 'A'), col, array, 1);
			Sleep(sleep_time);

			combine(array, array_, int(row - 'A'), col, client.get_row(), client.get_col());
			//清空
			for (int i = 0; i < client.get_row(); i++)
			{
				for (int j = 0; j < client.get_col(); j++)
				{
					if (array[i][j] == 0)
						draw_empty_diamond(i, j, array);
				}
			}
			//闪烁
			draw_blingbling(int(row - 'A'), col, array);

			//下落
			draw_diamond_fall(client.get_row(), client.get_col(), array, sleep_time / 10);

			//标记更新位置
			for (int i = 0; i < client.get_row(); i++)
			{
				for (int j = 0; j < client.get_col(); j++)
				{
					if (array[i][j] == 0)
						draw_change[i][j] = 1;
				}
			}
		}
		
		Sleep(sleep_time);
		/* 清空后续的缓冲区 */
		//cin.clear();
		//cin.ignore(INT_MAX, '\n');

		//if (row >= 'a' && row <= 'j')
		//	row -= 32; //如果是小写则转为大写

		client.send_coordinate(row, col);

		/* -------------------
			Server=>Client
		   ------------------- */
		   /* 等待Server端的gameprogress */
		if (client.get_gameprogress_string(svrpack) < 0) {
			return -1;
		}

		/* 打印出 svrpack 的内容，自行处理，并向Server端继续反馈
		   根据 Content 的内容，解释如下：
			"InvalidCoordinate" : 非法坐标
				GameID		：本次游戏ID
				Step		：目前步数
				Score		：目前分数
				MaxValue	：目前合成的最大值
			"MergeFailed" : 选择的坐标周围无可合成项
				GameID		：本次游戏ID
				Step		：目前步数
				Score		：目前分数
				MaxValue	：目前合成的最大值
			"MergeSucceeded" : 本次合成成功
				GameID		：本次游戏ID
				Step		：目前步数
				Score		：目前分数
				MaxValue	：目前合成的最大值
				OldMap		：消除选择坐标后的地图
				NewMap		：消除选择坐标后再次填充的地图
			"GameOver" : 地图上无消除项，游戏结束
				GameID			：本次游戏ID
				FinalStep		：最终步数
				FinalScore		：最终分数
				FinalMaxValue	：最终合成的最大值
			"GameFinished" : 已合成到设置上限（16），游戏完成
				GameID			：本次游戏ID
				FinalStep		：最终步数
				FinalScore		：最终分数
				FinalMaxValue	：最终合成的最大值 */

				/* 打印收到的原始字符串 */
		if (if_console == 0)
			cout << "Server应答 : " << endl << svrpack << endl;
	}//end of while(1)

	return 0;
}

int game_progress_competition(mto10_net_tools& client, int array[][COLUM_MAX], int array_[][COLUM_MAX])
{
	char svrpack[RECVBUF_LEN];	//存放从Server端收到的数据
	char row;
	int col;
	int draw_change[ROW_MAX][COLUM_MAX] = { 0 };

	while (1) {
		/* -------------------
			Client=>Server
		   ------------------- */
		   /* 根据服务端发来的地图，返回一个解坐标（目前为手工输入形式，需要改为自动求最佳解坐标）
			  提示：可以将client.get_map()的返回值复制到字符数组中，再还原为你自己的二维数组后求解
		   */

		//复制地图
		char tmp[100] = { 0 };
		strcpy(tmp, client.get_map());
		char* p = tmp;
		for (int i = 0; i < client.get_row(); i++)
		{
			for (int j = 0; j < client.get_col(); j++)
			{
				int n = 0;

				if (*p >= '0' && *p <= '9')
					n = int(*p - '0');
				else if (*p >= 'a' && *p <= 'f')
					n = int(*p - 'a' + 10);
				else if (*p >= 'A' && *p <= 'F')
					n = int(*p - 'A' + 10);

				array[i][j] = n;
				p++;
			}
		}

		//找最大值
		int max_value = array[0][0];
		for (int i = 0; i < client.get_row(); i++)
		{
			for (int j = 0; j < client.get_col(); j++)
			{
				if (array[i][j] > max_value)
					max_value = array[i][j];
			}
		}

		reset_record(array_, client.get_row(), client.get_col());

		/* 游戏已结束则不再读键*/
		if (client.is_gameover())
			break;

		search_score_max_location(client, array, array_, &row, &col);

		client.send_coordinate(row, col);

		/* -------------------
			Server=>Client
		   ------------------- */
		   /* 等待Server端的gameprogress */
		if (client.get_gameprogress_string(svrpack) < 0) {
			return -1;
		}

	}//end of while(1)

	return 0;
}

float information(mto10_net_tools& client, int array[][COLUM_MAX])
{

	//int get_gameid() const;		//游戏ID 最大值 加权得分

	int max_value = array[0][0];
	for (int i = 0; i < client.get_row(); i++)
	{
		for (int j = 0; j < client.get_col(); j++)
		{
			if (array[i][j] > max_value)
				max_value = array[i][j];
		}
	}
	float weight = float(client.get_score()) / client.get_row() / client.get_col();
	
	cout << setw(12) << client.get_gameid() << " |";
	cout << setw(3) << client.get_row() << "  |";
	cout << setw(3) << client.get_col() << "  |";
	cout << setw(7) << client.get_score() << "  |";
	cout << setw(6) << client.get_step() << "  |";
	cout << setw(5) << max_value << "   |";
	cout << setw(8) << weight << "  |";
	cout << endl;
	cout << "------------------------------------------------------------------------" << endl;

	return weight;
}