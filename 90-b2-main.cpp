/* ͨ�� 2051475 ���� */
#include "cmd_console_tools.h"
#include "90-b2.h"
#include "lib_mto10_net_tools.h"
//��������˵�����

char menu()
{
	cct_cls();

	cout << "---------------------------------------" << endl;
	cout << "1.�������ҳ��ɺϳ����ʶ���ǵݹ飩" << endl;
	cout << "2.�������ҳ��ɺϳ����ʶ���ݹ飩" << endl;
	cout << "3.���������һ�κϳɣ��ֲ�����ʾ��" << endl;
	cout << "4.�����������棨�ֲ�����ʾ��" << endl;
	cout << "5.αͼ�ν�����ʾ��ʼ���飨�޷ָ��ߣ�" << endl;
	cout << "6.αͼ�ν�����ʾ��ʼ���飨�зָ��ߣ�" << endl;
	cout << "7.αͼ�ν������ü�ͷ��/���ѡ��ǰɫ��" << endl;
	cout << "8.αͼ�ν������һ�κϳɣ��ֲ��裩" << endl;
	cout << "9.αͼ�ν���������(֧�����)" << endl;
	cout << "---------------------------------------" << endl;
	cout << "A.�����н��棨�����Զ���-�����棩" << endl;
	cout << "B.αͼ�ν��棨�����Զ���-�����棩" << endl;
	cout << "C.�����н��棨�����Զ���-�����棩" << endl;
	cout << "---------------------------------------" << endl;
	cout << "0.�˳�" << endl;
	cout << "---------------------------------------" << endl;
	cout << "[��ѡ��:] ";

	char ch;
	while (1)
	{
		ch = _getch();
		if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'c') || (ch >= 'A' && ch <= 'C'))
			break;
	}
	cout << ch;

	Sleep(300);
	cct_cls();

	return ch;
}

int main()
{
	while (1)
	{
		srand((unsigned int)(time(0)));

		int row = 0, colum = 0, target = 0;
		int array[ROW_MAX][COLUM_MAX] = { 0 };
		int array_[ROW_MAX][COLUM_MAX] = { 0 };
		int row_selected = 0, colum_selected = 0;
		int num_max = 0, score_all = 0, score_this = 0;
		float sum = 0.0F;

		const char* my_no = "2051475";		//����ѧ��
		const char* my_pwd = "513673.wh";   //��������

		char menu_return = menu();

		switch (menu_return)
		{
			case '1':
				input_set(&row, &colum, &target, 0);
				ini_array(array, row, colum);
				cout << "��ǰ���飺" << endl;
				draw_array(array, array_, row, colum, 0);
				while (1)
				{
					input_array_location(&row_selected, &colum_selected, row, colum);
					int same_num = bfs(row_selected, colum_selected, row, colum, array, array_);
					if (same_num == 0)
					{
						cout << "����ľ�������λ�ô���������ֵͬ������������" << endl;
						reset_record(array_, row, colum);
					}
					else
						break;
				}
				draw_array_result(array_, row, colum);
				draw_array(array, array_, row, colum, 1);
				input_end();
				break;
			case '2':
				input_set(&row, &colum, &target, 0);
				ini_array(array, row, colum);
				cout << "��ǰ���飺" << endl;
				draw_array(array, array_, row, colum, 0);
				while (1)
				{
					input_array_location(&row_selected, &colum_selected, row, colum);
					int same_num = dfs(row_selected, colum_selected, row, colum, array, array_);
					if (same_num == 0)
					{
						cout << "����ľ�������λ�ô���������ֵͬ������������" << endl;
						reset_record(array_, row, colum);
					}
					else
						break;
				}
				draw_array_result(array_, row, colum);
				cout << "��ǰ����(��ͬɫ��ʶ)��" << endl;
				draw_array(array, array_, row, colum, 1);
				input_end();
				break;
			case '3':
				input_set(&row, &colum, &target, 1);
				ini_array(array, row, colum);
				cout << "��ǰ���飺" << endl;
				draw_array(array, array_, row, colum, 0);
				while (1)
				{
					input_array_location(&row_selected, &colum_selected, row, colum);
					int same_num = bfs(row_selected, colum_selected, row, colum, array, array_);
					if (same_num == 0)
					{
						cout << "����ľ�������λ�ô���������ֵͬ������������" << endl;
						reset_record(array_, row, colum);
					}
					else
						break;
				}
				draw_array_result(array_, row, colum);
				draw_array(array, array_, row, colum, 1);
				cout << "��ȷ���Ƿ�����ڵ���ֵͬ�ϲ���" << char(row_selected + 'A') << colum_selected << "��(Y/N/Q)��";
				if (input_ynq() == 1)
				{
					cout << endl << endl;
					score_this = score_record(array, array_, row, colum);
					score_all += score_this;
					combine(array, array_, row_selected, colum_selected, row, colum);
					cout << "��ֵͬ�鲢�������(��ͬɫ��ʶ)��" << endl;
					draw_array(array, array_, row, colum, 1);
					cout << "���ε÷֣�" << score_this << " �ܵ÷֣�" << score_all << " �ϳ�Ŀ�꣺" << target << endl << endl;
					cout << "���س����������������0����...";
					input_huiche();
					cout << endl << "��0�������(��ͬɫ��ʶ)��" << endl;
					array_fall(array, row, colum);
					draw_array_fallen(array, row, colum);
					reset_record(array_, row, colum);
					change_array_(array, array_, row, colum);
					cout << "���س���������ֵ���...";
					input_huiche();
					cout << endl << "��ֵ���������(��ͬɫ��ʶ)��" << endl;
					num_max = find_num_max(array, row, colum);
					array_append(array, row, colum, num_max);
					draw_array(array, array_, row, colum, 1);
					input_end();
					
				}
				cout << endl << endl;
				input_end();
				break;
			case '4':
				input_set(&row, &colum, &target, 1);
				ini_array(array, row, colum);
				while (1)
				{
					int if_fail = 1;
					int input = 0;
					while (1)
					{
						reset_record(array_, row, colum);
						cout << "��ǰ���飺" << endl;
						draw_array(array, array_, row, colum, 0);
						while (1)
						{
							input_array_location(&row_selected, &colum_selected, row, colum);
							int same_num = bfs(row_selected, colum_selected, row, colum, array, array_);
							if (same_num == 0)
							{
								cout << "����ľ�������λ�ô���������ֵͬ������������" << endl;
								reset_record(array_, row, colum);
							}
							else
								break;
						}
						draw_array_result(array_, row, colum);
						draw_array(array, array_, row, colum, 1);
						cout << "��ȷ���Ƿ�����ڵ���ֵͬ�ϲ���" << char(row_selected + 'A') << colum_selected << "��(Y/N/Q)��";
						input = input_ynq();
						if (input != 2)
							break;
						cout << endl << endl;
					}
					if (input == 1)
					{
						cout << endl << endl;
						score_this = score_record(array, array_, row, colum);
						score_all += score_this;
						combine(array, array_, row_selected, colum_selected, row, colum);
						cout << "��ֵͬ�鲢�������(��ͬɫ��ʶ)��" << endl;
						draw_array(array, array_, row, colum, 1);
						cout << "���ε÷֣�" << score_this << " �ܵ÷֣�" << score_all << " �ϳ�Ŀ�꣺" << target << endl << endl;
						cout << "���س����������������0����...";
						input_huiche();
						cout << endl << "��0�������(��ͬɫ��ʶ)��" << endl;
						array_fall(array, row, colum);
						draw_array_fallen(array, row, colum);
						reset_record(array_, row, colum);
						change_array_(array, array_, row, colum);
						cout << "���س���������ֵ���...";
						input_huiche();
						cout << endl << "��ֵ���������(��ͬɫ��ʶ)��" << endl;
						num_max = find_num_max(array, row, colum);
						array_append(array, row, colum, num_max);
						draw_array(array, array_, row, colum, 1);
						cout << "���κϳɽ��������س���������һ�εĺϳ�..." << endl;
						input_huiche();
						cout << endl;
					}
					else
					{
						cout << endl << endl;
						input_end();
						break;
					}

					for (int i = 0; i < row; i++)
					{
						for (int j = 0; j < colum; j++)
						{
							if (bfs(i, j, row, colum, array, array_) != 0)
								if_fail = 0;
						}
					}

					if (if_fail == 1)
					{
						cct_gotoxy(0, 3 + 4 * row);
						cout << "                                                                                ";
						cct_gotoxy(0, 3 + 4 * row);
						cout << "û�п��Ժϳɵ�ֵ����Ϸ���������س�������";
						input_huiche();
						break;
					}
				}
				break;
			case '5':
				input_set(&row, &colum, &target, 0);
				ini_array(array, row, colum);
				cct_setconsoleborder(7 + 6 * colum, 8 + 3 * row, 7 + 6 * colum, 8 + 3 * row);
				cct_cls();
				cout << endl;
				draw_interface(row, colum, array, 1);
				cct_gotoxy(0, 0);
				cout << "��Ļ��ǰ����Ϊ��" << 7 + 6 * colum << "��" << 8 + 3 * row << "��";
				cct_gotoxy(0, 5 + 3 * row);
				input_end_error();
				break;
			case '6':
				input_set(&row, &colum, &target, 0);
				ini_array(array, row, colum);
				cct_setconsoleborder(5 + 8 * colum, 7 + 4 * row, 5 + 8 * colum, 7 + 4 * row);
				cct_cls();
				cout << endl;
				draw_interface_col(row, colum, array, 1);
				cct_gotoxy(0, 0);
				cout << "��Ļ��ǰ����Ϊ��" << 5 + 8 * colum << "��" << 7 + 4 * row << "��";
				cct_gotoxy(0, 4 + 4 * row);
				input_end_error();
				break;
			case '7':
				input_set(&row, &colum, &target, 0);
				ini_array(array, row, colum);
				cct_setconsoleborder(5 + 8 * colum, 7 + 4 * row, 5 + 8 * colum, 7 + 4 * row);
				cct_cls();
				cout << endl;
				draw_interface_col(row, colum, array, 1);
				cct_gotoxy(0, 0);
				cout << "��Ļ��ǰ����Ϊ��" << 5 + 8 * colum << "��" << 7 + 4 * row << "��";
				cct_gotoxy(0, 3 + 4 * row);
				cout << "��ͷ��/����ƶ����س���/�������ѡ�񲢽���";
				draw_select_diamond(row_selected, colum_selected, array, 0);
				cct_enable_mouse();
				int row_selected_record, colum_selected_record;
				while (1)
				{
					row_selected_record = row_selected;
					colum_selected_record = colum_selected;
					if (select_diamond(&row_selected, &colum_selected, row, colum) == 1)
					{
						cct_gotoxy(0, 3 + 4 * row);
						cout << "                                                    ";
						cct_gotoxy(0, 3 + 4 * row);
						cout << "ѡ����" << char(row_selected + 'A') << "��" << colum_selected << "��";
						break;
					}
					clear_select_diamond(row_selected_record, colum_selected_record, array);
					draw_select_diamond(row_selected, colum_selected, array, 0);
				}
				cct_gotoxy(0, 4 + 4 * row);
				input_end_error();
				break;
			case '8':
				input_set(&row, &colum, &target, 1);
				ini_array(array, row, colum);
				cct_setconsoleborder(5 + 8 * colum, 7 + 4 * row, 5 + 8 * colum, 7 + 4 * row);
				cct_cls();
				cout << endl;
				draw_interface_col(row, colum, array, 1);
				cct_gotoxy(0, 0);
				cout << "��Ļ��ǰ����Ϊ��" << 5 + 8 * colum << "��" << 7 + 4 * row << "��";
				cct_gotoxy(0, 3 + 4 * row);
				cout << "��ͷ��/����ƶ����س���/�������ѡ��Q/�����Ҽ�����";
				draw_select_diamond(row_selected, colum_selected, array, 0);
				cct_enable_mouse();
				while (1)
				{
					reset_record(array_, row, colum);
					int if_feifa = 1;
					int if_left;
					int row_selected_record = row_selected;
					int colum_selected_record = colum_selected;
					int get_return = kb_m_action(&row_selected, &colum_selected, row, colum, &if_feifa, &if_left);

					if (get_return == 4)//�˳�
						break;
					else if (get_return == 1 || get_return == 2)//�ƶ�
					{
						clear_select_diamond(row_selected_record, colum_selected_record, array);
						draw_select_diamond(row_selected, colum_selected, array, 1);

						cct_gotoxy(0, 3 + 4 * row);
						cout << "                                                                                ";
						cct_gotoxy(0, 3 + 4 * row);
						if (get_return == 1)
							cout << "[��ǰ����] " << char(row_selected + 'A') << "��" << colum_selected << "��";
						else
						{
							cout << "[��ǰ���] ";
							if (if_feifa)
								cout << "λ�÷Ƿ�";
							else
								cout << char(row_selected + 'A') << "��" << colum_selected << "��";
						}
					}
					else if (get_return == 3)//ѡ��ɫ��
					{
						//�����ɿ����
						if (if_left == 1)
						{
							int a, b, c, d, e;
							cct_read_keyboard_and_mouse(a, b, c, d, e);
							if_left = 0;
						}

						int num = 0;
						while (1)
						{
							num = bfs(row_selected, colum_selected, row, colum, array, array_);
							if (num == 0)
							{
								cct_gotoxy(0, 3 + 4 * row);
								cout << "                                                                                ";
								cct_gotoxy(0, 3 + 4 * row);
								cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
								cout << "��Χ����ֵͬ��";
								cct_setcolor(COLOR_BLACK, COLOR_WHITE);
								cout << "��ͷ��/����ƶ����س���/�������ѡ��Q/�����Ҽ�����";
								break;
							}
							else//��Χ����ֵͬ
							{
								cct_gotoxy(0, 3 + 4 * row);
								cout << "                                                                                ";
								cct_gotoxy(0, 3 + 4 * row);
								cout << "��ͷ��/����ƶ����س���/��������ϳ�";
								//���ѡ������ֵͬ
								for (int i = 0; i < row; i++)
								{
									for (int j = 0; j < colum; j++)
									{
										if (array_[i][j] == 1)
											draw_select_diamond(i, j, array, 0);
									}
								}
								draw_select_diamond(row_selected, colum_selected, array, 1);

								while (1)
								{
									int g_r = kb_m_action(&row_selected, &colum_selected, row, colum, &if_feifa, &if_left);
									if (g_r == 1 || g_r == 2)
									{
										num = 0;
										for (int i = 0; i < row; i++)
										{
											for (int j = 0; j < colum; j++)
											{
												if (array_[i][j] == 1)
													clear_select_diamond(i, j, array);
											}
										}
										draw_select_diamond(row_selected, colum_selected, array, 1);

										cct_gotoxy(0, 3 + 4 * row);
										cout << "                                                                                ";
										cct_gotoxy(0, 3 + 4 * row);
										if (get_return == 1)
											cout << "[��ǰ����] " << char(row_selected + 'A') << "��" << colum_selected << "��";
										else
										{
											cout << "[��ǰ���] ";
											if (if_feifa)
												cout << "λ�÷Ƿ�";
											else
												cout << char(row_selected + 'A') << "��" << colum_selected << "��";
										}
										break;
									}
									else if (get_return == 3)//ȷ���ϳ�
									{
										//�Ƿ�
										score_this = score_record(array, array_, row, colum);
										score_all += score_this;
										cct_gotoxy(0, 0);
										cout << "���ε÷֣�" << score_this << " �ܵ÷֣�" << score_all << " �ϳ�Ŀ�꣺" << target;
										//��� �ϳ�
										combine(array, array_, row_selected, colum_selected, row, colum);
										for (int i = 0; i < row; i++)
										{
											for (int j = 0; j < colum; j++)
											{
												if (array[i][j] == 0)
													draw_empty_diamond(i, j, array);
											}
										}
										draw_blingbling(row_selected, colum_selected, array);
										//����
										cct_gotoxy(0, 3 + 4 * row);
										cout << "                                                                                ";
										cct_gotoxy(0, 3 + 4 * row);
										cout << "�ϳ���ɣ��س���/�����������0";
										while (1)
										{
											int g_r1 = kb_m_action(&row_selected, &colum_selected, row, colum, &if_feifa, &if_left);
											if (g_r1 == 3)
											{
												//�����ɿ����
												if (if_left == 1)
												{
													int a, b, c, d, e;
													cct_read_keyboard_and_mouse(a, b, c, d, e);
													if_left = 0;
												}
												draw_diamond_fall(row, colum, array, 10);
												break;
											}
										}
										//���
										cct_gotoxy(0, 3 + 4 * row);
										cout << "                                                                                ";
										cct_gotoxy(0, 3 + 4 * row);
										cout << "����0��ɣ��س���/������������ֵ";
										while (1)
										{
											int g_r1 = kb_m_action(&row_selected, &colum_selected, row, colum, &if_feifa, &if_left);
											if (g_r1 == 3)
											{
												//�����ɿ����
												if (if_left == 1)
												{
													int a, b, c, d, e;
													cct_read_keyboard_and_mouse(a, b, c, d, e);
													if_left = 0;
												}
												num_max = find_num_max(array, row, colum);
												draw_diamond_append(row, colum, array, num_max);
												break;
											}
										}
									}
									break;
								}
							}
							break;
						}
						if (num == 0)
							continue;
						else
							break;
					}
				}
				cct_gotoxy(0, 3 + 4 * row);
				cout << "                                                                                ";
				cct_gotoxy(0, 3 + 4 * row);
				cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
				cout << "���κϳɽ�������C/�������������һ�εĺϳ�";
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
				while (1)
				{
					int mx, my, ma, k1, k2, kb_m;
					kb_m = cct_read_keyboard_and_mouse(mx, my, ma, k1, k2);
					if ((kb_m = CCT_KEYBOARD_EVENT && (k1 == 'c' || k1 == 'C')) || (kb_m == CCT_MOUSE_EVENT && ma == MOUSE_LEFT_BUTTON_CLICK))
						break;
				}
				cct_gotoxy(0, 4 + 4 * row);
				input_end_error();
				break;
			case '9':
				input_set(&row, &colum, &target, 1);
				ini_array(array, row, colum);
				cct_setconsoleborder(5 + 8 * colum, 7 + 4 * row, 5 + 8 * colum, 7 + 4 * row);
				cct_cls();
				cout << endl;
				draw_interface_col(row, colum, array, 1);
				cct_gotoxy(0, 0);
				cout << "��Ļ��ǰ����Ϊ��" << 7 + 4 * row << "��" << 5 + 8 * colum << "��";
				cct_gotoxy(0, 3 + 4 * row);
				cout << "��ͷ��/����ƶ����س���/�������ѡ��Q/�����Ҽ�����";
				draw_select_diamond(row_selected, colum_selected, array, 0);
				cct_enable_mouse();
				while (1)
				{
					reset_record(array_, row, colum);
					int if_fail = 1;
					int if_feifa = 1;
					int if_left;
					int row_selected_record = row_selected;
					int colum_selected_record = colum_selected;

					int get_return = kb_m_action(&row_selected, &colum_selected, row, colum, &if_feifa, &if_left);

					if (get_return == 4)//�˳�
						break;
					else if (get_return == 1 || get_return == 2)//�ƶ�
					{
						clear_select_diamond(row_selected_record, colum_selected_record, array);
						draw_select_diamond(row_selected, colum_selected, array, 1);

						cct_gotoxy(0, 3 + 4 * row);
						cout << "                                                                                ";
						cct_gotoxy(0, 3 + 4 * row);
						if (get_return == 1)
							cout << "[��ǰ����] " << char(row_selected + 'A') << "��" << colum_selected << "��";
						else
						{
							cout << "[��ǰ���] ";
							if (if_feifa)
								cout << "λ�÷Ƿ�";
							else
								cout << char(row_selected + 'A') << "��" << colum_selected << "��";
						}
					}
					else if (get_return == 3)//ѡ��ɫ��
					{
						//�����ɿ����
						if (if_left == 1)
						{
							int a, b, c, d, e;
							cct_read_keyboard_and_mouse(a, b, c, d, e);
							if_left = 0;
						}

						int num = 0;
						num = bfs(row_selected, colum_selected, row, colum, array, array_);

						if (num == 0)
							{
								cct_gotoxy(0, 3 + 4 * row);
								cout << "                                                                                ";
								cct_gotoxy(0, 3 + 4 * row);
								cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
								cout << "��Χ����ֵͬ��";
								cct_setcolor(COLOR_BLACK, COLOR_WHITE);
								cout << "��ͷ��/����ƶ����س���/�������ѡ��Q/�����Ҽ�����";
							}
						else//��Χ����ֵͬ
							{
								cct_gotoxy(0, 3 + 4 * row);
								cout << "                                                                                ";
								cct_gotoxy(0, 3 + 4 * row);
								cout << "��ͷ��/����ƶ�ȡ����ǰѡ�񣬻س���/��������ϳ�";
								//���ѡ������ֵͬ
								for (int i = 0; i < row; i++)
								{
									for (int j = 0; j < colum; j++)
									{
										if (array_[i][j] == 1)
											draw_select_diamond(i, j, array, 0);
									}
								}
								draw_select_diamond(row_selected, colum_selected, array, 1);
								while (1)
								{
									int g_r = kb_m_action(&row_selected, &colum_selected, row, colum, &if_feifa, &if_left);
									if (g_r == 1 || g_r == 2)
									{
										num = 0;

										for (int i = 0; i < row; i++)
										{
											for (int j = 0; j < colum; j++)
											{
												if (array_[i][j] == 1)
													clear_select_diamond(i, j, array);
											}
										}
										draw_select_diamond(row_selected, colum_selected, array, 1);

										cct_gotoxy(0, 3 + 4 * row);
										cout << "                                                                                ";
										cct_gotoxy(0, 3 + 4 * row);
										if (get_return == 1)
											cout << "[��ǰ����] " << char(row_selected + 'A') << "��" << colum_selected << "��";
										else
										{
											cout << "[��ǰ���] ";
											if (if_feifa)
												cout << "λ�÷Ƿ�";
											else
												cout << char(row_selected + 'A') << "��" << colum_selected << "��";
										}
										break;
									}
									else if (get_return == 3)//ȷ���ϳ�
									{
										//�Ƿ�
										score_this = score_record(array, array_, row, colum);
										score_all += score_this;
										cct_gotoxy(0, 0);
										cout << "                                                                                ";
										cct_gotoxy(0, 0);
										cout << "���ε÷֣�" << score_this << " �ܵ÷֣�" << score_all << " �ϳ�Ŀ�꣺" << target;
										//��� �ϳ�
										combine(array, array_, row_selected, colum_selected, row, colum);
										for (int i = 0; i < row; i++)
										{
											for (int j = 0; j < colum; j++)
											{
												if (array[i][j] == 0)
													draw_empty_diamond(i, j, array);
											}
										}
										draw_blingbling(row_selected, colum_selected, array);
										//���� �����ɿ����
										if (if_left == 1)
										{
											int a, b, c, d, e;
											cct_read_keyboard_and_mouse(a, b, c, d, e);
											if_left = 0;
										}
										draw_diamond_fall(row, colum, array, 10);
										//���
										num_max = find_num_max(array, row, colum);
										draw_diamond_append(row, colum, array, num_max);
										if (num_max == target)
										{
											cct_gotoxy(0, 3 + 4 * row);
											cout << "                                                                                ";
											cct_gotoxy(0, 3 + 4 * row);
											cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
											cout << "�Ѻϳɵ�" << target << "��";
											cct_setcolor(COLOR_BLACK, COLOR_WHITE);
											cout << "���س���/����������������Ŀ�����";
											while (1)
											{
												int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, t = 0;
												t = kb_m_action(&a, &b, c, d, &e, &f);
												if (t == 3)
												{
													target++;
													row_selected = 0;
													colum_selected = 0;
													cct_gotoxy(0, 0);
													cout << "                                                                                ";
													cct_gotoxy(0, 0);
													cout << "���ε÷֣�" << score_this << " �ܵ÷֣�" << score_all << " �ϳ�Ŀ�꣺" << target;
													break;
												}
											}
										}
										break;
									}
								}
							}
					}

					for (int i = 0; i < row; i++)
					{
						for (int j = 0; j < colum; j++)
						{
							if (bfs(i, j, row, colum, array, array_) != 0)
								if_fail = 0;
						}
					}

					if (if_fail == 1)
					{
						cct_gotoxy(0, 3 + 4 * row);
						cout << "                                                                                ";
						cct_gotoxy(0, 3 + 4 * row);
						cout << "û�п��Ժϳɵ�ֵ����Ϸ���������س�������";
						input_huiche();
						break;
					}

				}
				cct_gotoxy(0, 3 + 4 * row);
				cout << "                                                                                ";
				cct_gotoxy(0, 4 + 4 * row);
				input_end_error();
				break;
			case 'a':
			case 'A':
				{
					int wanted_row, wanted_col, wanted_id, wanted_delay;

				#if 1 //�������룬�˴���Ϊ #if 0 ���ʾ�������� #else �е����
					//��������
					while (1)
					{
						cout << "����������(" << ROW_MIN << '-' << ROW_MAX << ")��" << endl;
						cin >> wanted_row;
						if (cin.good() == 0)
						{
							cin.clear();
							cin.ignore(65536, '\n');
						}
						else if ((wanted_row >= ROW_MIN) && (wanted_row <= ROW_MAX))
							break;
					}
					//��������
					while (1)
					{
						cout << "����������(" << COLUM_MIN << '-' << COLUM_MAX << ")��" << endl;
						cin >> wanted_col;
						if (cin.good() == 0)
						{
							cin.clear();
							cin.ignore(65536, '\n');
						}
						else if ((wanted_col >= COLUM_MIN) && (wanted_col <= COLUM_MAX))
							break;
					}
					//wanted_row = 5;			//�˴������޸�Ϊ�����������ʽ
					//wanted_col = 5;			//�˴������޸�Ϊ�����������ʽ
					wanted_id = 12345;		//idΪ�����������Ϸ��ţ������-1����ʾ���������������[0..2^31-1]���ʾ��̶���ţ���Ź̶�����ÿ�θ����ĳ�ʼ���󼰺���������ͬ��������ԣ�
					wanted_delay = 60 * 1000;	//delayΪ�����ÿ��Ӧ����ʱ�ӣ���λms
				#else
					wanted_row = -1;
					wanted_col = -1;
					wanted_id = -1;
					wanted_delay = -1;
				#endif
					mto10_net_tools client;
					/* ��client������е�debug���أ�����ʱ�ɴ򿪣���ͼ�ν���ʱ��رգ� */
					client.set_debug_switch(false);

					/* ���ӷ����� */
					if (client.connect() < 0) {
						/* ����ʧ����Ϣ����û��debug_switch����ӡ */
						cout << "���ӷ�����ʧ��!" << endl;
						return -1;
					}

					/* ��Server�˷�����֤��Ϣ������ */
					if (client.send_parameter(my_no, '*', my_pwd, wanted_row, wanted_col, wanted_id, wanted_delay) < 0) {
						cout << "������֤��������Ϣʧ��!" << endl;
						return -1;
					}

					/* �ȴ�Server���·���������Ϸ��ʼ��*/
					if (client.wait_for_game_start() < 0) {
						cout << "�ȴ�GameStartʧ��!" << endl;
						return -1;
					}

					/* ��ӡ�ӷ������յ��Ĳ�����������Ϸ�Դ˲���Ϊ׼����������6��6�У�����8��10�У��򱾴���Ϸ��8��10��Ϊ׼��
					   �����ӡ����Ϣ��ͼ�λ������������ȥ�� */
				
					cout << "������������Ϣ : " << endl;
					cout << "  ���� : " << client.get_row() << endl;
					cout << "  ���� : " << client.get_col() << endl;
					cout << "  ID�� : " << client.get_gameid() << endl;
					cout << "  ��ʱ : " << client.get_delay() / 1000.0 << "(��)" << endl;
					cout << "  ��ͼ : " << client.get_map() << endl;
					/* ��ͼ���е�ֵΪ1-9��A-F���ֱ��ʾ1-15��ֵ��
						   ���磺
							 ������������=3
							 ������������=4
							 ���������ص�ͼ=123A85CF2123
						   ���ʾ��ǰ��ͼΪ(����������ʾ��)
							 1 2 3  10
							 8 5 12 15
							 2 1 2  3
							��Ϸ����������Ϊ���ϳɵ�16�����κοɺϳ�Ԫ�� */

							/* ������Ϸ��������
							   1���յ�Server��GameOver�򷵻�0����Ϸ����
							   2���������������-1��������Ϣ����ȷ�ȴ��󣩣��������ٴ��ظ�	*/
					if (game_progress(client, array, array_, 0, 0) < 0) {
						client.close();
						return -1;
					}

					client.close();
					cout << "��Ϸ����" << endl;
				}
				input_end_error();
				break;
			case 'b':
			case 'B':
				{
					int wanted_row, wanted_col, wanted_id, wanted_delay;

				#if 1 //�������룬�˴���Ϊ #if 0 ���ʾ�������� #else �е����
					//��������
					while (1)
					{
						cout << "����������(" << ROW_MIN << '-' << ROW_MAX << ")��" << endl;
						cin >> wanted_row;
						if (cin.good() == 0)
						{
							cin.clear();
							cin.ignore(65536, '\n');
						}
						else if ((wanted_row >= ROW_MIN) && (wanted_row <= ROW_MAX))
							break;
					}
					//��������
					while (1)
					{
						cout << "����������(" << COLUM_MIN << '-' << COLUM_MAX << ")��" << endl;
						cin >> wanted_col;
						if (cin.good() == 0)
						{
							cin.clear();
							cin.ignore(65536, '\n');
						}
						else if ((wanted_col >= COLUM_MIN) && (wanted_col <= COLUM_MAX))
							break;
					}
					cct_setconsoleborder(5 + 8 * wanted_col, 7 + 4 * wanted_row, 5 + 8 * wanted_col, 7 + 4 * wanted_row);
					//wanted_row = 5;			//�˴������޸�Ϊ�����������ʽ
					//wanted_col = 5;			//�˴������޸�Ϊ�����������ʽ
					wanted_id = 12345;		//idΪ�����������Ϸ��ţ������-1����ʾ���������������[0..2^31-1]���ʾ��̶���ţ���Ź̶�����ÿ�θ����ĳ�ʼ���󼰺���������ͬ��������ԣ�
					wanted_delay = 60 * 1000;	//delayΪ�����ÿ��Ӧ����ʱ�ӣ���λms
				#else
					wanted_row = -1;
					wanted_col = -1;
					wanted_id = -1;
					wanted_delay = -1;
				#endif
					mto10_net_tools client;
					/* ��client������е�debug���أ�����ʱ�ɴ򿪣���ͼ�ν���ʱ��رգ� */
					client.set_debug_switch(false);

					/* ���ӷ����� */
					if (client.connect() < 0) {
						/* ����ʧ����Ϣ����û��debug_switch����ӡ */
						cout << "���ӷ�����ʧ��!" << endl;
						return -1;
					}

					/* ��Server�˷�����֤��Ϣ������ */
					if (client.send_parameter(my_no, '*', my_pwd, wanted_row, wanted_col, wanted_id, wanted_delay) < 0) {
						cout << "������֤��������Ϣʧ��!" << endl;
						return -1;
					}

					/* �ȴ�Server���·���������Ϸ��ʼ��*/
					if (client.wait_for_game_start() < 0) {
						cout << "�ȴ�GameStartʧ��!" << endl;
						return -1;
					}
							/* ������Ϸ��������
							   1���յ�Server��GameOver�򷵻�0����Ϸ����
							   2���������������-1��������Ϣ����ȷ�ȴ��󣩣��������ٴ��ظ�	*/
					if (game_progress(client, array, array_, 1, 100) < 0) {
						client.close();
						return -1;
					}

					client.close();
					cct_gotoxy(0, 4 + 4 * client.get_row());
					cout << "��Ϸ����" << endl;
				}
				input_end_error();
				break;
			case 'c':
			case 'C':
				cout << "------------------------------------------------------------------------" << endl;
				cout << "| num |    mapid    | row | col |  score  |  step  | mvalue |  weight  |" << endl;
				cout << "------------------------------------------------------------------------" << endl;
				for (int i = 0; i < 64; i++)
				{
					int wanted_row, wanted_col, wanted_id, wanted_delay;

				#if 0 //�������룬�˴���Ϊ #if 0 ���ʾ�������� #else �е����
					wanted_row = 5;			//�˴������޸�Ϊ�����������ʽ
					wanted_col = 5;			//�˴������޸�Ϊ�����������ʽ
					wanted_id = 12345;		//idΪ�����������Ϸ��ţ������-1����ʾ���������������[0..2^31-1]���ʾ��̶���ţ���Ź̶�����ÿ�θ����ĳ�ʼ���󼰺���������ͬ��������ԣ�
					wanted_delay = 60 * 1000;	//delayΪ�����ÿ��Ӧ����ʱ�ӣ���λms
				#else
					wanted_row = -1;
					wanted_col = -1;
					wanted_id = -1;
					wanted_delay = -1;
				#endif
					mto10_net_tools client;

					/* ��client������е�debug���أ�����ʱ�ɴ򿪣���ͼ�ν���ʱ��رգ� */
					client.set_debug_switch(false);

					/* ���ӷ����� */
					if (client.connect() < 0) {
						/* ����ʧ����Ϣ����û��debug_switch����ӡ */
						cout << "���ӷ�����ʧ��!" << endl;
						return -1;
					}

					/* ��Server�˷�����֤��Ϣ������ */
					if (client.send_parameter(my_no, '-', my_pwd, wanted_row, wanted_col, wanted_id, wanted_delay) < 0) {
						cout << "������֤��������Ϣʧ��!" << endl;
						return -1;
					}

					/* �ȴ�Server���·���������Ϸ��ʼ��*/
					if (client.wait_for_game_start() < 0) {
						cout << "�ȴ�GameStartʧ��!" << endl;
						return -1;
					}

							/* ������Ϸ��������
							   1���յ�Server��GameOver�򷵻�0����Ϸ����
							   2���������������-1��������Ϣ����ȷ�ȴ��󣩣��������ٴ��ظ�	*/
					if (game_progress_competition(client, array, array_) < 0) {
						client.close();
						return -1;
					}
					//�����Ϣ
					cout << "|" << setw(4) << i + 1 << " |";

					sum += information(client, array);

					client.close();
					//cout << "��Ϸ����" << endl;
				}
				cout << "����÷�:" << sum << endl;
				input_end_error();
				break;
			case 0:
				break;
		}
	}

	return 0;
}