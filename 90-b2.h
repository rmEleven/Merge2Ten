/* Í¨ÐÅ 2051475 ÍõºÆ */
#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <time.h>
#include "lib_mto10_net_tools.h"
#include <Windows.h>

using namespace std;

#define ROW_MIN    5
#define ROW_MAX    8
#define COLUM_MIN  5
#define COLUM_MAX  10
#define TARGET_MIN 5
#define TARGET_MAX 20

struct note
{
	int row;
	int colum;
};

void input_set(int* row, int* colum, int* target, int if_target);

int rand_int(int range);

void ini_array(int array[][COLUM_MAX], int row, int colum);

void draw_array(int array[][COLUM_MAX], int array_[][COLUM_MAX], int row, int colum, int color);

void draw_array_result(int array_[][COLUM_MAX], int row, int colum);

void input_array_location(int* row_selected, int* colum_selected, int row, int colum);

int bfs(int row_selected, int colum_selected, int row_max, int colum_max, int array[][COLUM_MAX], int array_[][COLUM_MAX]);

int dfs(int row_selected, int colum_selected, int row_max, int colum_max, int array[][COLUM_MAX], int array_[][COLUM_MAX]);

void input_end();

void reset_record(int array_[][COLUM_MAX], int row, int colum);

int input_ynq();

void combine(int array[][COLUM_MAX], int array_[][COLUM_MAX], int row_selected, int colum_selected, int row_max, int colum_max);

void input_huiche();

void array_fall(int array[][COLUM_MAX], int row_max, int colum_max);

void draw_array_fallen(int array[][COLUM_MAX], int row, int colum);

void change_array_(int array[][COLUM_MAX], int array_[][COLUM_MAX], int row_max, int colum_max);

void array_append(int array[][COLUM_MAX], int row_max, int colum_max, int num_max);

int find_num_max(int array[][COLUM_MAX], int row_max, int colum_max);

int score_record(int array[][COLUM_MAX], int array_[][COLUM_MAX], int row_max, int colum_max);

void draw_interface(int row, int colum, int array[][COLUM_MAX], int sleep_time);

void draw_interface_col(int row, int colum, int array[][COLUM_MAX], int sleep_time);

void input_end_error();

int select_diamond(int* row_selected, int* colum_selected, int row, int colum);

int kb_m_action(int* row_selected, int* colum_selected, int row, int colum, int* if_feifa, int* if_left);

void draw_select_diamond(int row_selected, int colum_selected, int array[][COLUM_MAX], int if_hwhite);

void clear_select_diamond(int row_selected, int colum_selected, int array[][COLUM_MAX]);

void draw_empty_diamond(int row_selected, int colum_selected, int array[][COLUM_MAX]);

void draw_blingbling(int row_selected, int colum_selected, int array[][COLUM_MAX]);

void draw_diamond_fall(int row, int colum, int array[][COLUM_MAX], int sleep_time);

void draw_one_diamond(int row_selected, int colum_selected, int array[][COLUM_MAX]);

void draw_diamond_append(int row, int colum, int array[][COLUM_MAX], int num_max);

int game_progress(mto10_net_tools& client, int array[][COLUM_MAX], int array_[][COLUM_MAX], int if_console, int sleep_time);

void search_score_max_location(mto10_net_tools& client, int array[][COLUM_MAX], int array_[][COLUM_MAX], char* row, int* colum);

int get_score(int row_selected, int colum_selected, int row_max, int colum_max, int array[][COLUM_MAX], int array_[][COLUM_MAX]);

int game_progress_competition(mto10_net_tools& client, int array[][COLUM_MAX], int array_[][COLUM_MAX]);

float information(mto10_net_tools& client, int array[][COLUM_MAX]);