/* ͨ�� 2051475 ���� */
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

	//��¼����λ�õ÷����
	int score_record[ROW_MAX][COLUM_MAX] = { -999 };
	for (int i = 0; i < client.get_row(); i++)
	{
		for (int j = 0; j < client.get_col(); j++)
		{
			score_record[i][j] = get_score(i, j, client.get_row(), client.get_col(), array, array_);
		}
	}
	//ѡ������ֵ
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
	char svrpack[RECVBUF_LEN];	//��Ŵ�Server���յ�������
	char row;
	int col;
	int if_draw_interface = 1;
	int draw_change[ROW_MAX][COLUM_MAX] = { 0 };

	while (1) {
		/* -------------------
			Client=>Server
		   ------------------- */
		   /* ���ݷ���˷����ĵ�ͼ������һ�������꣨ĿǰΪ�ֹ�������ʽ����Ҫ��Ϊ�Զ�����ѽ����꣩
			  ��ʾ�����Խ�client.get_map()�ķ���ֵ���Ƶ��ַ������У��ٻ�ԭΪ���Լ��Ķ�ά��������
		   */
		char tmp[100] = { 0 };
		strcpy(tmp, client.get_map());
		char* p = tmp;
		//���Ƶ�ͼ
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
		
		//�����ֵ
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
			cout << "��ǰ���飺" << endl;
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
				//���� ���ı�
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

		/* ��Ϸ�ѽ������ٶ���*/
		if (client.is_gameover())
			break;

		search_score_max_location(client, array, array_, &row, &col);

		if (if_console == 0)
		{
			cout << "��������(A-J)��(0-9)���� : " << row << col;
			//�����ͬ��ֵ
			bfs(int(row - 'A'), col, client.get_row(), client.get_col(), array, array_);
			//*��ʾ��ֵͬ
			cout << endl;
			draw_array_result(array_, client.get_row(), client.get_col());

			//��ɫ��ʾ��ֵͬ
			draw_array(array, array_, client.get_row(), client.get_col(), 1);

			combine(array, array_, int(row - 'A'), col, client.get_row(), client.get_col());
			//����
			array_fall(array, client.get_row(), client.get_col());
			draw_array_fallen(array, client.get_row(), client.get_col());
		}
		else if (if_console == 1)
		{
			//�����ͬ��ֵ
			bfs(int(row - 'A'), col, client.get_row(), client.get_col(), array, array_);
			//������ʾѡ��Ԫ��
			cct_gotoxy(0, 4 + 4 * client.get_row());
			cout << "                                                     ";
			cct_gotoxy(0, 4 + 4 * client.get_row());
			cout << "ѡ��" << row << col;
			//��ɫ��ʾѡ��Ԫ��
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
			//���
			for (int i = 0; i < client.get_row(); i++)
			{
				for (int j = 0; j < client.get_col(); j++)
				{
					if (array[i][j] == 0)
						draw_empty_diamond(i, j, array);
				}
			}
			//��˸
			draw_blingbling(int(row - 'A'), col, array);

			//����
			draw_diamond_fall(client.get_row(), client.get_col(), array, sleep_time / 10);

			//��Ǹ���λ��
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
		/* ��պ����Ļ����� */
		//cin.clear();
		//cin.ignore(INT_MAX, '\n');

		//if (row >= 'a' && row <= 'j')
		//	row -= 32; //�����Сд��תΪ��д

		client.send_coordinate(row, col);

		/* -------------------
			Server=>Client
		   ------------------- */
		   /* �ȴ�Server�˵�gameprogress */
		if (client.get_gameprogress_string(svrpack) < 0) {
			return -1;
		}

		/* ��ӡ�� svrpack �����ݣ����д�������Server�˼�������
		   ���� Content �����ݣ��������£�
			"InvalidCoordinate" : �Ƿ�����
				GameID		��������ϷID
				Step		��Ŀǰ����
				Score		��Ŀǰ����
				MaxValue	��Ŀǰ�ϳɵ����ֵ
			"MergeFailed" : ѡ���������Χ�޿ɺϳ���
				GameID		��������ϷID
				Step		��Ŀǰ����
				Score		��Ŀǰ����
				MaxValue	��Ŀǰ�ϳɵ����ֵ
			"MergeSucceeded" : ���κϳɳɹ�
				GameID		��������ϷID
				Step		��Ŀǰ����
				Score		��Ŀǰ����
				MaxValue	��Ŀǰ�ϳɵ����ֵ
				OldMap		������ѡ�������ĵ�ͼ
				NewMap		������ѡ��������ٴ����ĵ�ͼ
			"GameOver" : ��ͼ�����������Ϸ����
				GameID			��������ϷID
				FinalStep		�����ղ���
				FinalScore		�����շ���
				FinalMaxValue	�����պϳɵ����ֵ
			"GameFinished" : �Ѻϳɵ��������ޣ�16������Ϸ���
				GameID			��������ϷID
				FinalStep		�����ղ���
				FinalScore		�����շ���
				FinalMaxValue	�����պϳɵ����ֵ */

				/* ��ӡ�յ���ԭʼ�ַ��� */
		if (if_console == 0)
			cout << "ServerӦ�� : " << endl << svrpack << endl;
	}//end of while(1)

	return 0;
}

int game_progress_competition(mto10_net_tools& client, int array[][COLUM_MAX], int array_[][COLUM_MAX])
{
	char svrpack[RECVBUF_LEN];	//��Ŵ�Server���յ�������
	char row;
	int col;
	int draw_change[ROW_MAX][COLUM_MAX] = { 0 };

	while (1) {
		/* -------------------
			Client=>Server
		   ------------------- */
		   /* ���ݷ���˷����ĵ�ͼ������һ�������꣨ĿǰΪ�ֹ�������ʽ����Ҫ��Ϊ�Զ�����ѽ����꣩
			  ��ʾ�����Խ�client.get_map()�ķ���ֵ���Ƶ��ַ������У��ٻ�ԭΪ���Լ��Ķ�ά��������
		   */

		//���Ƶ�ͼ
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

		//�����ֵ
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

		/* ��Ϸ�ѽ������ٶ���*/
		if (client.is_gameover())
			break;

		search_score_max_location(client, array, array_, &row, &col);

		client.send_coordinate(row, col);

		/* -------------------
			Server=>Client
		   ------------------- */
		   /* �ȴ�Server�˵�gameprogress */
		if (client.get_gameprogress_string(svrpack) < 0) {
			return -1;
		}

	}//end of while(1)

	return 0;
}

float information(mto10_net_tools& client, int array[][COLUM_MAX])
{

	//int get_gameid() const;		//��ϷID ���ֵ ��Ȩ�÷�

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