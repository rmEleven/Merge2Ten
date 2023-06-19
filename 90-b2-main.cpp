/* 通信 2051475 王浩 */
#include "cmd_console_tools.h"
#include "90-b2.h"
#include "lib_mto10_net_tools.h"
//主函数与菜单函数

char menu()
{
	cct_cls();

	cout << "---------------------------------------" << endl;
	cout << "1.命令行找出可合成项并标识（非递归）" << endl;
	cout << "2.命令行找出可合成项并标识（递归）" << endl;
	cout << "3.命令行完成一次合成（分步骤显示）" << endl;
	cout << "4.命令行完整版（分步骤显示）" << endl;
	cout << "5.伪图形界面显示初始数组（无分隔线）" << endl;
	cout << "6.伪图形界面显示初始数组（有分隔线）" << endl;
	cout << "7.伪图形界面下用箭头键/鼠标选择当前色块" << endl;
	cout << "8.伪图形界面完成一次合成（分步骤）" << endl;
	cout << "9.伪图形界面完整版(支持鼠标)" << endl;
	cout << "---------------------------------------" << endl;
	cout << "A.命令行界面（网络自动解-基本版）" << endl;
	cout << "B.伪图形界面（网络自动解-基本版）" << endl;
	cout << "C.命令行界面（网络自动解-竞赛版）" << endl;
	cout << "---------------------------------------" << endl;
	cout << "0.退出" << endl;
	cout << "---------------------------------------" << endl;
	cout << "[请选择:] ";

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

		const char* my_no = "2051475";		//本人学号
		const char* my_pwd = "513673.wh";   //本人密码

		char menu_return = menu();

		switch (menu_return)
		{
			case '1':
				input_set(&row, &colum, &target, 0);
				ini_array(array, row, colum);
				cout << "当前数组：" << endl;
				draw_array(array, array_, row, colum, 0);
				while (1)
				{
					input_array_location(&row_selected, &colum_selected, row, colum);
					int same_num = bfs(row_selected, colum_selected, row, colum, array, array_);
					if (same_num == 0)
					{
						cout << "输入的矩阵坐标位置处无连续相同值，请重新输入" << endl;
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
				cout << "当前数组：" << endl;
				draw_array(array, array_, row, colum, 0);
				while (1)
				{
					input_array_location(&row_selected, &colum_selected, row, colum);
					int same_num = dfs(row_selected, colum_selected, row, colum, array, array_);
					if (same_num == 0)
					{
						cout << "输入的矩阵坐标位置处无连续相同值，请重新输入" << endl;
						reset_record(array_, row, colum);
					}
					else
						break;
				}
				draw_array_result(array_, row, colum);
				cout << "当前数组(不同色标识)：" << endl;
				draw_array(array, array_, row, colum, 1);
				input_end();
				break;
			case '3':
				input_set(&row, &colum, &target, 1);
				ini_array(array, row, colum);
				cout << "当前数组：" << endl;
				draw_array(array, array_, row, colum, 0);
				while (1)
				{
					input_array_location(&row_selected, &colum_selected, row, colum);
					int same_num = bfs(row_selected, colum_selected, row, colum, array, array_);
					if (same_num == 0)
					{
						cout << "输入的矩阵坐标位置处无连续相同值，请重新输入" << endl;
						reset_record(array_, row, colum);
					}
					else
						break;
				}
				draw_array_result(array_, row, colum);
				draw_array(array, array_, row, colum, 1);
				cout << "请确认是否把相邻的相同值合并到" << char(row_selected + 'A') << colum_selected << "中(Y/N/Q)：";
				if (input_ynq() == 1)
				{
					cout << endl << endl;
					score_this = score_record(array, array_, row, colum);
					score_all += score_this;
					combine(array, array_, row_selected, colum_selected, row, colum);
					cout << "相同值归并后的数组(不同色标识)：" << endl;
					draw_array(array, array_, row, colum, 1);
					cout << "本次得分：" << score_this << " 总得分：" << score_all << " 合成目标：" << target << endl << endl;
					cout << "按回车键进行数组下落除0操作...";
					input_huiche();
					cout << endl << "除0后的数组(不同色标识)：" << endl;
					array_fall(array, row, colum);
					draw_array_fallen(array, row, colum);
					reset_record(array_, row, colum);
					change_array_(array, array_, row, colum);
					cout << "按回车键进行新值填充...";
					input_huiche();
					cout << endl << "新值填充后的数组(不同色标识)：" << endl;
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
						cout << "当前数组：" << endl;
						draw_array(array, array_, row, colum, 0);
						while (1)
						{
							input_array_location(&row_selected, &colum_selected, row, colum);
							int same_num = bfs(row_selected, colum_selected, row, colum, array, array_);
							if (same_num == 0)
							{
								cout << "输入的矩阵坐标位置处无连续相同值，请重新输入" << endl;
								reset_record(array_, row, colum);
							}
							else
								break;
						}
						draw_array_result(array_, row, colum);
						draw_array(array, array_, row, colum, 1);
						cout << "请确认是否把相邻的相同值合并到" << char(row_selected + 'A') << colum_selected << "中(Y/N/Q)：";
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
						cout << "相同值归并后的数组(不同色标识)：" << endl;
						draw_array(array, array_, row, colum, 1);
						cout << "本次得分：" << score_this << " 总得分：" << score_all << " 合成目标：" << target << endl << endl;
						cout << "按回车键进行数组下落除0操作...";
						input_huiche();
						cout << endl << "除0后的数组(不同色标识)：" << endl;
						array_fall(array, row, colum);
						draw_array_fallen(array, row, colum);
						reset_record(array_, row, colum);
						change_array_(array, array_, row, colum);
						cout << "按回车键进行新值填充...";
						input_huiche();
						cout << endl << "新值填充后的数组(不同色标识)：" << endl;
						num_max = find_num_max(array, row, colum);
						array_append(array, row, colum, num_max);
						draw_array(array, array_, row, colum, 1);
						cout << "本次合成结束，按回车键继续新一次的合成..." << endl;
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
						cout << "没有可以合成的值，游戏结束，按回车键继续";
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
				cout << "屏幕当前设置为：" << 7 + 6 * colum << "行" << 8 + 3 * row << "列";
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
				cout << "屏幕当前设置为：" << 5 + 8 * colum << "行" << 7 + 4 * row << "列";
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
				cout << "屏幕当前设置为：" << 5 + 8 * colum << "行" << 7 + 4 * row << "列";
				cct_gotoxy(0, 3 + 4 * row);
				cout << "箭头键/鼠标移动，回车键/单击左键选择并结束";
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
						cout << "选中了" << char(row_selected + 'A') << "行" << colum_selected << "列";
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
				cout << "屏幕当前设置为：" << 5 + 8 * colum << "行" << 7 + 4 * row << "列";
				cct_gotoxy(0, 3 + 4 * row);
				cout << "箭头键/鼠标移动，回车键/单击左键选择，Q/单击右键结束";
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

					if (get_return == 4)//退出
						break;
					else if (get_return == 1 || get_return == 2)//移动
					{
						clear_select_diamond(row_selected_record, colum_selected_record, array);
						draw_select_diamond(row_selected, colum_selected, array, 1);

						cct_gotoxy(0, 3 + 4 * row);
						cout << "                                                                                ";
						cct_gotoxy(0, 3 + 4 * row);
						if (get_return == 1)
							cout << "[当前键盘] " << char(row_selected + 'A') << "行" << colum_selected << "列";
						else
						{
							cout << "[当前鼠标] ";
							if (if_feifa)
								cout << "位置非法";
							else
								cout << char(row_selected + 'A') << "行" << colum_selected << "列";
						}
					}
					else if (get_return == 3)//选择色块
					{
						//接收松开左键
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
								cout << "周围无相同值，";
								cct_setcolor(COLOR_BLACK, COLOR_WHITE);
								cout << "箭头键/鼠标移动，回车键/单击左键选择，Q/单击右键结束";
								break;
							}
							else//周围有相同值
							{
								cct_gotoxy(0, 3 + 4 * row);
								cout << "                                                                                ";
								cct_gotoxy(0, 3 + 4 * row);
								cout << "箭头键/鼠标移动，回车键/单击左键合成";
								//标记选中与相同值
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
											cout << "[当前键盘] " << char(row_selected + 'A') << "行" << colum_selected << "列";
										else
										{
											cout << "[当前鼠标] ";
											if (if_feifa)
												cout << "位置非法";
											else
												cout << char(row_selected + 'A') << "行" << colum_selected << "列";
										}
										break;
									}
									else if (get_return == 3)//确定合成
									{
										//记分
										score_this = score_record(array, array_, row, colum);
										score_all += score_this;
										cct_gotoxy(0, 0);
										cout << "本次得分：" << score_this << " 总得分：" << score_all << " 合成目标：" << target;
										//清空 合成
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
										//下落
										cct_gotoxy(0, 3 + 4 * row);
										cout << "                                                                                ";
										cct_gotoxy(0, 3 + 4 * row);
										cout << "合成完成，回车键/单击左键下落0";
										while (1)
										{
											int g_r1 = kb_m_action(&row_selected, &colum_selected, row, colum, &if_feifa, &if_left);
											if (g_r1 == 3)
											{
												//接收松开左键
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
										//填充
										cct_gotoxy(0, 3 + 4 * row);
										cout << "                                                                                ";
										cct_gotoxy(0, 3 + 4 * row);
										cout << "下落0完成，回车键/单击左键填充新值";
										while (1)
										{
											int g_r1 = kb_m_action(&row_selected, &colum_selected, row, colum, &if_feifa, &if_left);
											if (g_r1 == 3)
											{
												//接收松开左键
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
				cout << "本次合成结束，按C/单击左键继续新一次的合成";
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
				cout << "屏幕当前设置为：" << 7 + 4 * row << "行" << 5 + 8 * colum << "列";
				cct_gotoxy(0, 3 + 4 * row);
				cout << "箭头键/鼠标移动，回车键/单击左键选择，Q/单击右键结束";
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

					if (get_return == 4)//退出
						break;
					else if (get_return == 1 || get_return == 2)//移动
					{
						clear_select_diamond(row_selected_record, colum_selected_record, array);
						draw_select_diamond(row_selected, colum_selected, array, 1);

						cct_gotoxy(0, 3 + 4 * row);
						cout << "                                                                                ";
						cct_gotoxy(0, 3 + 4 * row);
						if (get_return == 1)
							cout << "[当前键盘] " << char(row_selected + 'A') << "行" << colum_selected << "列";
						else
						{
							cout << "[当前鼠标] ";
							if (if_feifa)
								cout << "位置非法";
							else
								cout << char(row_selected + 'A') << "行" << colum_selected << "列";
						}
					}
					else if (get_return == 3)//选择色块
					{
						//接收松开左键
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
								cout << "周围无相同值，";
								cct_setcolor(COLOR_BLACK, COLOR_WHITE);
								cout << "箭头键/鼠标移动，回车键/单击左键选择，Q/单击右键结束";
							}
						else//周围有相同值
							{
								cct_gotoxy(0, 3 + 4 * row);
								cout << "                                                                                ";
								cct_gotoxy(0, 3 + 4 * row);
								cout << "箭头键/鼠标移动取消当前选择，回车键/单击左键合成";
								//标记选中与相同值
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
											cout << "[当前键盘] " << char(row_selected + 'A') << "行" << colum_selected << "列";
										else
										{
											cout << "[当前鼠标] ";
											if (if_feifa)
												cout << "位置非法";
											else
												cout << char(row_selected + 'A') << "行" << colum_selected << "列";
										}
										break;
									}
									else if (get_return == 3)//确定合成
									{
										//记分
										score_this = score_record(array, array_, row, colum);
										score_all += score_this;
										cct_gotoxy(0, 0);
										cout << "                                                                                ";
										cct_gotoxy(0, 0);
										cout << "本次得分：" << score_this << " 总得分：" << score_all << " 合成目标：" << target;
										//清空 合成
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
										//下落 接收松开左键
										if (if_left == 1)
										{
											int a, b, c, d, e;
											cct_read_keyboard_and_mouse(a, b, c, d, e);
											if_left = 0;
										}
										draw_diamond_fall(row, colum, array, 10);
										//填充
										num_max = find_num_max(array, row, colum);
										draw_diamond_append(row, colum, array, num_max);
										if (num_max == target)
										{
											cct_gotoxy(0, 3 + 4 * row);
											cout << "                                                                                ";
											cct_gotoxy(0, 3 + 4 * row);
											cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
											cout << "已合成到" << target << "，";
											cct_setcolor(COLOR_BLACK, COLOR_WHITE);
											cout << "按回车键/单击左键继续向更高目标进发";
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
													cout << "本次得分：" << score_this << " 总得分：" << score_all << " 合成目标：" << target;
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
						cout << "没有可以合成的值，游戏结束，按回车键继续";
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

				#if 1 //条件编译，此处改为 #if 0 则表示启用下面 #else 中的语句
					//输入行数
					while (1)
					{
						cout << "请输入行数(" << ROW_MIN << '-' << ROW_MAX << ")：" << endl;
						cin >> wanted_row;
						if (cin.good() == 0)
						{
							cin.clear();
							cin.ignore(65536, '\n');
						}
						else if ((wanted_row >= ROW_MIN) && (wanted_row <= ROW_MAX))
							break;
					}
					//输入列数
					while (1)
					{
						cout << "请输入列数(" << COLUM_MIN << '-' << COLUM_MAX << ")：" << endl;
						cin >> wanted_col;
						if (cin.good() == 0)
						{
							cin.clear();
							cin.ignore(65536, '\n');
						}
						else if ((wanted_col >= COLUM_MIN) && (wanted_col <= COLUM_MAX))
							break;
					}
					//wanted_row = 5;			//此处按需修改为键盘输入等形式
					//wanted_col = 5;			//此处按需修改为键盘输入等形式
					wanted_id = 12345;		//id为本次请求的游戏序号，如果置-1，表示服务器随机产生，[0..2^31-1]则表示想固定序号（序号固定，则每次给出的初始矩阵及后续填充均相同，方便调试）
					wanted_delay = 60 * 1000;	//delay为请求的每步应答的最长时延，单位ms
				#else
					wanted_row = -1;
					wanted_col = -1;
					wanted_id = -1;
					wanted_delay = -1;
				#endif
					mto10_net_tools client;
					/* 打开client类对象中的debug开关（调试时可打开，到图形界面时需关闭） */
					client.set_debug_switch(false);

					/* 连接服务器 */
					if (client.connect() < 0) {
						/* 连接失败信息，有没有debug_switch都打印 */
						cout << "连接服务器失败!" << endl;
						return -1;
					}

					/* 向Server端发送认证信息及参数 */
					if (client.send_parameter(my_no, '*', my_pwd, wanted_row, wanted_col, wanted_id, wanted_delay) < 0) {
						cout << "发送认证及参数信息失败!" << endl;
						return -1;
					}

					/* 等待Server端下发参数（游戏开始）*/
					if (client.wait_for_game_start() < 0) {
						cout << "等待GameStart失败!" << endl;
						return -1;
					}

					/* 打印从服务器收到的参数，本次游戏以此参数为准（例：发送6行6列，返回8行10列，则本次游戏以8行10列为准）
					   下面打印的信息，图形化界面可以自行去除 */
				
					cout << "服务器返回信息 : " << endl;
					cout << "  行数 : " << client.get_row() << endl;
					cout << "  列数 : " << client.get_col() << endl;
					cout << "  ID号 : " << client.get_gameid() << endl;
					cout << "  超时 : " << client.get_delay() / 1000.0 << "(秒)" << endl;
					cout << "  地图 : " << client.get_map() << endl;
					/* 地图串中的值为1-9，A-F，分别表示1-15的值，
						   例如：
							 服务器返回行=3
							 服务器返回列=4
							 服务器返回地图=123A85CF2123
						   则表示当前地图为(本例仅仅是示例)
							 1 2 3  10
							 8 5 12 15
							 2 1 2  3
							游戏结束的条件为：合成到16或无任何可合成元素 */

							/* 进入游戏交互环节
							   1、收到Server的GameOver则返回0，游戏结束
							   2、其它错误均返回-1（报文信息不正确等错误），重连，再次重复	*/
					if (game_progress(client, array, array_, 0, 0) < 0) {
						client.close();
						return -1;
					}

					client.close();
					cout << "游戏结束" << endl;
				}
				input_end_error();
				break;
			case 'b':
			case 'B':
				{
					int wanted_row, wanted_col, wanted_id, wanted_delay;

				#if 1 //条件编译，此处改为 #if 0 则表示启用下面 #else 中的语句
					//输入行数
					while (1)
					{
						cout << "请输入行数(" << ROW_MIN << '-' << ROW_MAX << ")：" << endl;
						cin >> wanted_row;
						if (cin.good() == 0)
						{
							cin.clear();
							cin.ignore(65536, '\n');
						}
						else if ((wanted_row >= ROW_MIN) && (wanted_row <= ROW_MAX))
							break;
					}
					//输入列数
					while (1)
					{
						cout << "请输入列数(" << COLUM_MIN << '-' << COLUM_MAX << ")：" << endl;
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
					//wanted_row = 5;			//此处按需修改为键盘输入等形式
					//wanted_col = 5;			//此处按需修改为键盘输入等形式
					wanted_id = 12345;		//id为本次请求的游戏序号，如果置-1，表示服务器随机产生，[0..2^31-1]则表示想固定序号（序号固定，则每次给出的初始矩阵及后续填充均相同，方便调试）
					wanted_delay = 60 * 1000;	//delay为请求的每步应答的最长时延，单位ms
				#else
					wanted_row = -1;
					wanted_col = -1;
					wanted_id = -1;
					wanted_delay = -1;
				#endif
					mto10_net_tools client;
					/* 打开client类对象中的debug开关（调试时可打开，到图形界面时需关闭） */
					client.set_debug_switch(false);

					/* 连接服务器 */
					if (client.connect() < 0) {
						/* 连接失败信息，有没有debug_switch都打印 */
						cout << "连接服务器失败!" << endl;
						return -1;
					}

					/* 向Server端发送认证信息及参数 */
					if (client.send_parameter(my_no, '*', my_pwd, wanted_row, wanted_col, wanted_id, wanted_delay) < 0) {
						cout << "发送认证及参数信息失败!" << endl;
						return -1;
					}

					/* 等待Server端下发参数（游戏开始）*/
					if (client.wait_for_game_start() < 0) {
						cout << "等待GameStart失败!" << endl;
						return -1;
					}
							/* 进入游戏交互环节
							   1、收到Server的GameOver则返回0，游戏结束
							   2、其它错误均返回-1（报文信息不正确等错误），重连，再次重复	*/
					if (game_progress(client, array, array_, 1, 100) < 0) {
						client.close();
						return -1;
					}

					client.close();
					cct_gotoxy(0, 4 + 4 * client.get_row());
					cout << "游戏结束" << endl;
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

				#if 0 //条件编译，此处改为 #if 0 则表示启用下面 #else 中的语句
					wanted_row = 5;			//此处按需修改为键盘输入等形式
					wanted_col = 5;			//此处按需修改为键盘输入等形式
					wanted_id = 12345;		//id为本次请求的游戏序号，如果置-1，表示服务器随机产生，[0..2^31-1]则表示想固定序号（序号固定，则每次给出的初始矩阵及后续填充均相同，方便调试）
					wanted_delay = 60 * 1000;	//delay为请求的每步应答的最长时延，单位ms
				#else
					wanted_row = -1;
					wanted_col = -1;
					wanted_id = -1;
					wanted_delay = -1;
				#endif
					mto10_net_tools client;

					/* 打开client类对象中的debug开关（调试时可打开，到图形界面时需关闭） */
					client.set_debug_switch(false);

					/* 连接服务器 */
					if (client.connect() < 0) {
						/* 连接失败信息，有没有debug_switch都打印 */
						cout << "连接服务器失败!" << endl;
						return -1;
					}

					/* 向Server端发送认证信息及参数 */
					if (client.send_parameter(my_no, '-', my_pwd, wanted_row, wanted_col, wanted_id, wanted_delay) < 0) {
						cout << "发送认证及参数信息失败!" << endl;
						return -1;
					}

					/* 等待Server端下发参数（游戏开始）*/
					if (client.wait_for_game_start() < 0) {
						cout << "等待GameStart失败!" << endl;
						return -1;
					}

							/* 进入游戏交互环节
							   1、收到Server的GameOver则返回0，游戏结束
							   2、其它错误均返回-1（报文信息不正确等错误），重连，再次重复	*/
					if (game_progress_competition(client, array, array_) < 0) {
						client.close();
						return -1;
					}
					//输出信息
					cout << "|" << setw(4) << i + 1 << " |";

					sum += information(client, array);

					client.close();
					//cout << "游戏结束" << endl;
				}
				cout << "本组得分:" << sum << endl;
				input_end_error();
				break;
			case 0:
				break;
		}
	}

	return 0;
}