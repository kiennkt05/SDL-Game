#ifndef F1GP_VARIABLES_H
#define F1GP_VARIABLES_H

#include "CommonHeaders.h"

Mix_Chunk *music_tracks[MUSIC_MAX] = { NULL };
int BGM_channel = -1;
SDL_Texture *textures[TEXTURE_MAX] = { NULL };

bool show_infor = false;
bool show_leader_board = false;
bool is_sound_on = true;
bool quit = false;
bool exit_main_loop = true;
SDL_Renderer *render = NULL;

bool F1GP_is_game_paused = false;
bool F1GP_is_game_restarted = false;
bool F1GP_is_new_game = true;
bool F1GP_is_crashing;
int F1GP_crashing_count_down;
int F1GP_separator_0_block_start_y;
int F1GP_separator_1_block_start_y;
int F1GP_last_car_road;
int F1GP_transform_count;
int F1GP_run_count;
bool F1GP_player_is_car_transform;
int F1GP_player_car_transform_time;
bool F1GP_player_is_car_fly;
int F1GP_player_car_fly_duration;
int F1GP_score;
int F1GP_level;
int F1GP_pass;
int F1GP_fly_count;
int F1GP_fly_charger_count;
int F1GP_transform_frame;
int F1GP_high_score = 0;
std::vector< std::vector<int> > F1GP_explosive_effect;
std::vector< std::pair<std::string, int> > F1GP_leaderboard;

bool F1GP_key_up_pressed;
bool F1GP_key_down_pressed;
bool F1GP_key_right_pressed;
bool F1GP_key_left_pressed;

std::string s = "Enter your name";

TTF_Font* F1GP_Number_Font = NULL;
TTF_Font* F1GP_Font = NULL;

F1GP_CAR F1GP_player_car;
F1GP_OPPOSITE_CAR_TYPE F1GP_opposite_car_type[F1GP_OPPOSITE_CAR_TYPE_COUNT + 1];
F1GP_OPPOSITE_CAR F1GP_opposite_car[F1GP_OPPOSITE_CAR_COUNT + 1];

#endif