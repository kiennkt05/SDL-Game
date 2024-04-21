#ifndef RENDER_H
#define RENDER_H

#include "CommonHeaders.h"
#include "Render.h"
#include "Texture.h"
#include "Init.h"
#include "Music.h"
#include "DataProcessing.h"
#include "Logic.h"

void F1GP_Render_Leaderboard(){
	Texture_Draw( 50, 50, TEXTURE_GAME_LEADERBOARD );
	F1GP_Font = TTF_OpenFont( "Fonts/KodeMono-Bold.ttf", 28 );
	SDL_Color textColor = { 255, 255, 255 };
	SDL_Surface* textSurface = NULL;
	SDL_Texture* textTexture = NULL;
	SDL_Rect dst;
	int n = F1GP_leaderboard.size();
	for ( int i = 0; i < n; i++ ){
		std::string s = to_string(i+1) + ". " + F1GP_leaderboard[i].first;
		s.resize( 15 ,' ' );
		s += "  " + to_string(F1GP_leaderboard[i].second);
		int n = s.size();
		textSurface = TTF_RenderText_Solid( F1GP_Font, s.c_str(), textColor );
		textTexture = SDL_CreateTextureFromSurface( render, textSurface );
		dst = { 80, 150 + i * 50, n * 17, 36 };
		SDL_RenderCopy( render, textTexture, NULL, &dst );
	}

	SDL_FreeSurface( textSurface );
	SDL_DestroyTexture( textTexture );
	TTF_CloseFont( F1GP_Font );
}

void F1GP_Render_Highscore(){
	F1GP_Font = TTF_OpenFont("Fonts/KodeMono-Bold.ttf", 34);
	SDL_Color textColor = { 0, 0, 0 };
	SDL_Surface* textSurface;
	textSurface = TTF_RenderText_Solid(F1GP_Font, s.c_str(), textColor );
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(render, textSurface);
	int n = s.size();
	SDL_Rect dst = { 100, 187, 15 * n, 44 };
	Texture_Draw(50, 100, TEXTURE_HIGH_SCORE_FIELD );
	SDL_RenderCopy(render, textTexture, NULL, &dst);

	TTF_CloseFont(F1GP_Font);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

void F1GP_Render_Explosive_Effect(){
	for ( int i = 0; i < F1GP_OPPOSITE_CAR_DEFAULT_APPEAR_RATE; i++ ){
		if( F1GP_explosive_effect[i][0] > -1 ){
			SDL_Rect src = { F1GP_explosive_effect[i][2] * F1GP_EXPLOSIVE_EFFECT_FRAME_WIDTH, 0,
							 F1GP_EXPLOSIVE_EFFECT_FRAME_WIDTH, F1GP_EXPLOSIVE_EFFECT_FRAME_HEIGHT };
			Texture_Draw( F1GP_explosive_effect[i][0] - F1GP_EXPLOSIVE_EFFECT_FRAME_WIDTH / 2,
						  F1GP_explosive_effect[i][1] - F1GP_EXPLOSIVE_EFFECT_FRAME_HEIGHT / 2, TEXTURE_EXPLOSIVE_EFFECT, 4, &src );
			
			F1GP_explosive_effect[i][2]++;
			F1GP_explosive_effect[i][1] += F1GP_EXPLOSIVE_EFFECT_INCREMENT;
			if ( F1GP_explosive_effect[i][2] == 1 ){
				Music_Play( MUSIC_BUMBLEBEE_EXPLOSION, 0 );
			} 
			if ( F1GP_explosive_effect[i][2] == F1GP_EXPLOSIVE_EFFECT_FRAME ){
				F1GP_explosive_effect[i] = { -1, 0, 0, 0 };				
			}
		}
	}
}

void F1GP_Render_Intro(){
	SDL_RenderClear( render );
	SDL_RenderCopy( render, textures[TEXTURE_GAME_INTRO], NULL, NULL);
	SDL_RenderPresent( render );
	SDL_Delay( 2000 );
}

void F1GP_Render_Button( SDL_Event evt ){
	// In game button
	if ( !exit_main_loop && !F1GP_is_game_paused ){
		int p_times = 4, s_times = 4;
		
		// Handle Pause Button's size
		if ( Mouse_In_Button( 458, 15, 30, 30 ) ){
			p_times = 5;
		}

		// Handle Sound Button's size
		else if ( Mouse_In_Button( 416, 15, 30, 30 ) ){
			s_times = 5;
		}

		// Render Button Texture
		Texture_Draw( 458, 15, TEXTURE_BUTTON_PAUSE, p_times );
		if ( is_sound_on ) Texture_Draw( 416, 15, TEXTURE_BUTTON_SOUND_ON, s_times );
		else Texture_Draw( 416, 15, TEXTURE_BUTTON_SOUND_OFF, s_times );

	}
	
	// In paused button
	else if ( !exit_main_loop && F1GP_is_game_paused ){
		Texture_Draw( 81, 50, TEXTURE_BUTTON_PAUSE_OPTIONS );

		int resu_times = 4, rest_times = 4, h_times = 4;
		if ( Mouse_In_Button( 110, 80, 30, 30 ) ){
			resu_times = 5;
		}
		else if ( Mouse_In_Button( 168, 80, 30, 30 ) ){
			rest_times = 5;
		}
		else if ( Mouse_In_Button( 226, 80, 30, 30 ) ){
			h_times = 5;
		}

		Texture_Draw( 110, 80, TEXTURE_BUTTON_RESUME, resu_times );
		Texture_Draw( 168, 80, TEXTURE_BUTTON_RESTART, rest_times );
		Texture_Draw( 226, 80, TEXTURE_BUTTON_HOME, h_times );

	}
	
	// Menu's button
	else if ( !show_infor && !show_leader_board ){
		int l_times = 4, p_times = 4, q_times = 4, i_times = 4, s_times = 4;

		// Handle Sound Button's size
		if ( Mouse_In_Button( 416, 15, 30, 30 ) ){
			s_times = 5;
		}

		// Handle Infor Button's size
		else if( Mouse_In_Button( 458, 15, 30, 30 ) ){
			i_times = 5;
		}
		
		// Handle Leaderboard Button's size
		else if( Mouse_In_Button( F1GP_BUTTON_LEADERBOARD_X, F1GP_BUTTON_LEADERBOARD_Y, F1GP_BUTTON_LEADERBOARD_WIDTH, F1GP_BUTTON_LEADERBOARD_HEIGHT ) ) {
			l_times = 5;
		}

		// Handle Play Button's size
		else if( Mouse_In_Button( F1GP_BUTTON_PLAY_X, F1GP_BUTTON_PLAY_Y, F1GP_BUTTON_PLAY_WIDTH, F1GP_BUTTON_PLAY_HEIGHT ) ) {
			p_times = 5;
		}

		// Handle Quit Button's size
		else if( Mouse_In_Button( F1GP_BUTTON_QUIT_X, F1GP_BUTTON_QUIT_Y, F1GP_BUTTON_QUIT_WIDTH, F1GP_BUTTON_QUIT_HEIGHT ) )
		{
			q_times = 5;
		}

		// Render Button Texture
		if ( is_sound_on ) 
			Texture_Draw( 416, 15, TEXTURE_BUTTON_SOUND_ON_1, s_times );
		else 
			Texture_Draw( 416, 15, TEXTURE_BUTTON_SOUND_OFF_1, s_times );		
		Texture_Draw( 458, 15, TEXTURE_BUTTON_INFOR, i_times );
		Texture_Draw( F1GP_BUTTON_LEADERBOARD_X, F1GP_BUTTON_LEADERBOARD_Y, TEXTURE_BUTTON_LEADERBOARD, l_times );
		Texture_Draw( F1GP_BUTTON_PLAY_X, F1GP_BUTTON_PLAY_Y, TEXTURE_BUTTON_PLAY, p_times );
		Texture_Draw( F1GP_BUTTON_QUIT_X, F1GP_BUTTON_QUIT_Y, TEXTURE_BUTTON_QUIT, q_times );
	}
}

void F1GP_Render_Menu(){
	SDL_RenderCopy( render, textures[TEXTURE_GAME_MENU], NULL, NULL);
}

void F1GP_Render_Score(int x_pos, int y_pos);

void F1GP_Show_Game_Over_Screen() {
	SDL_SetRenderDrawColor( render, 0, 0, 0, 0 );
	SDL_RenderClear( render );
	SDL_RenderCopy( render, textures[TEXTURE_GAMEOVER_BACKGROUND], NULL, NULL);
	F1GP_Render_Score(264, 203);
	SDL_RenderPresent( render );
}

void F1GP_Render_Separator() {
	int start_y, end_y;
	SDL_Rect rectangle;

	start_y = F1GP_separator_0_block_start_y - 2 * (F1GP_SEPARATOR_HEIGHT - F1GP_SEPARATOR_HEIGHT_SPACE);
	end_y = start_y + F1GP_SEPARATOR_HEIGHT;
	while (true) {
		SDL_SetRenderDrawColor(render, 150, 150, 150, 0);
		rectangle.x = F1GP_SEPARATOR_0_START_X;
		rectangle.y = start_y;
		rectangle.w = F1GP_SEPARATOR_0_END_X + 1 - rectangle.x;
		rectangle.h = F1GP_SEPARATOR_HEIGHT;
		SDL_RenderFillRect(render, &rectangle);

		SDL_SetRenderDrawColor(render, 150, 150, 150, 0);
		rectangle.x = F1GP_SEPARATOR_1_START_X;
		rectangle.y = start_y + F1GP_SEPARATOR_HEIGHT_SPACE;
		SDL_RenderFillRect(render, &rectangle);

		start_y = end_y + F1GP_SEPARATOR_HEIGHT_SPACE;
		end_y = start_y + F1GP_SEPARATOR_HEIGHT;
		if (start_y > F1GP_DISPLAY_END_Y)
			break;
		if (end_y > F1GP_DISPLAY_END_Y)
			end_y = F1GP_DISPLAY_END_Y;
	}
 	F1GP_separator_0_block_start_y += F1GP_SEPARATOR_HEIGHT_SPACE * 3;
	if ( F1GP_separator_0_block_start_y  >= ( F1GP_DISPLAY_START_Y + F1GP_SEPARATOR_HEIGHT_SPACE + F1GP_SEPARATOR_HEIGHT) )
	 	F1GP_separator_0_block_start_y = F1GP_DISPLAY_START_Y;
}

void F1GP_Render_Score(int x_pos, int y_pos) {
	int value;
	int remain;

	SDL_Rect rectangle;
	SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
	rectangle = { x_pos, y_pos, F1GP_STATUS_WIDTH, F1GP_STATUS_HEIGHT };
	SDL_RenderFillRect(render, &rectangle);

	value = F1GP_score % 10;
	remain = F1GP_score / 10;
	x_pos += rectangle.w;

	while (true) {
		x_pos -= F1GP_STATUS_NUMBER_WIDTH;
		Texture_Draw( x_pos, y_pos - 17, static_cast<TEXTURE>(value));

		if (remain > 0) {
			value = remain % 10;
			remain = remain / 10;
		}
		else
			break;
	}
}

void F1GP_Render_Status() {

	F1GP_Render_Score ( F1GP_STATUS_START_X, 218 );
	Texture_Draw( F1GP_STATUS_START_X + F1GP_STATUS_WIDTH - F1GP_STATUS_NUMBER_WIDTH, 307 - 17, static_cast<TEXTURE>( F1GP_level ) );
	
	SDL_Rect rectangle = { F1GP_STATUS_START_X, 390 + F1GP_STATUS_HEIGHT, (F1GP_STATUS_WIDTH - (F1GP_STATUS_NUMBER_WIDTH * 2)) / 10, F1GP_STATUS_HEIGHT / 5 };
	for (int index = 0; index < 5; index++) {
		if (index < F1GP_fly_charger_count)
			SDL_SetRenderDrawColor(render, 255, 0, 0, 0);
		else
			SDL_SetRenderDrawColor(render, 100, 100, 100, 0);
		rectangle.x += 2 * rectangle.w;
		rectangle.y -= F1GP_STATUS_HEIGHT / 5;
		rectangle.h += F1GP_STATUS_HEIGHT / 5;
		SDL_RenderFillRect(render, &rectangle);
	}

	Texture_Draw( F1GP_STATUS_START_X + F1GP_STATUS_WIDTH - F1GP_STATUS_NUMBER_WIDTH, 394 - 17, static_cast<TEXTURE>( F1GP_fly_count ) );
}

void F1GP_Render_Player_Car() {
	int dx;
	int dy;

	TEXTURE image;

	if ( F1GP_player_is_car_transform ){
		SDL_Rect src = { ( abs(F1GP_run_count - 2) / 10) * 50, 0, 50, 57 };
		Texture_Draw ( 430, 60, TEXTURE_STOP_WATCH, 4, &src );

		if( F1GP_run_count < 17 ){
			if ( F1GP_run_count == 0 ){
				Mix_Pause( BGM_channel );
				Music_Play( MUSIC_BUMBLEBEE, 0 );
				Music_Play( MUSIC_BUMBLEBEE_TRANSFORM, 0 );
			}
			src = { F1GP_run_count * 232, 0, 232, 117 };
			Texture_Draw ( F1GP_player_car.pos_x - 92, F1GP_player_car.pos_y - 18, TEXTURE_PLAYER_CAR_TRANSFORM, 4, &src );		
		}
		else if ( F1GP_run_count < 62 ){
			int Frame_Count = (61 - F1GP_run_count) % 12;
			if ( Frame_Count % 6 == 1 ) Music_Play( MUSIC_BUMBLEBEE_RUN, 0 );
			src = { Frame_Count * 175, 0, 175, 157 };
			Texture_Draw ( F1GP_player_car.pos_x - 64, F1GP_player_car.pos_y - 76, TEXTURE_PLAYER_CAR_RUN, 4, &src );			
		}
		else if ( F1GP_run_count < 80 ){
			if ( F1GP_run_count == 62 ){
				Music_Play( MUSIC_BUMBLEBEE_TRANSFORM, 0 );
			}
			src = { (79 - F1GP_run_count) * 232, 0, 232, 117 };
			Texture_Draw ( F1GP_player_car.pos_x - 92, F1GP_player_car.pos_y - 18, TEXTURE_PLAYER_CAR_TRANSFORM, 4, &src );		
		}
		else{ 
			F1GP_run_count = -1;
			F1GP_player_is_car_transform = false;
			Mix_Resume( BGM_channel );
		}
		F1GP_run_count++;
	} 
	else if ( !F1GP_player_is_car_fly ){
		Texture_Draw ( F1GP_player_car.pos_x, F1GP_player_car.pos_y, TEXTURE_PLAYER_CAR );
		if ( F1GP_transform_count > 0 ){
			SDL_Rect src = { (F1GP_transform_count - 1) * 34, 0, 34, 5 };
			Texture_Draw ( F1GP_player_car.pos_x + (F1GP_player_car.dx - 34) / 2, F1GP_player_car.pos_y - 10, TEXTURE_SCROLL_BAR, 4, &src );
		}
	}
	else {
		dx = F1GP_player_car.pos_x - ( F1GP_PLAYER_CAR_FLY_IMAGE_SIZE_X - F1GP_player_car.dx ) / 2;
		dy = F1GP_player_car.pos_y - ( F1GP_PLAYER_CAR_FLY_IMAGE_SIZE_Y - F1GP_player_car.dy ) / 2;
		
		switch ( F1GP_player_car_fly_duration ) {
			case 0:
			case 1:
				image = TEXTURE_PLAYER_CAR_FLY_UP;
				break;
			case ( F1GP_PLAYER_CAR_FLY_FRAME_COUNT - 1 ):
			case ( F1GP_PLAYER_CAR_FLY_FRAME_COUNT - 2 ):
				image = TEXTURE_PLAYER_CAR_FLY_DOWN;
				break;
			default:
				image = TEXTURE_PLAYER_CAR_FLY;
				break;
		}
		Texture_Draw(dx, dy, image);
	}
}

void F1GP_Render_Opposite_Car() {
	for (int index = 0; index < F1GP_OPPOSITE_CAR_COUNT + 1; index++) {
		if ( !F1GP_opposite_car[index].is_empty )
			Texture_Draw ( F1GP_opposite_car[index].pos_x, F1GP_opposite_car[index].pos_y, F1GP_opposite_car[index].image );
	}
}

void F1GP_Render_Player_Car_Crash() {
	Texture_Draw ( F1GP_player_car.pos_x - 5, F1GP_player_car.pos_y - 20, TEXTURE_PLAYER_CAR_CRASH );
}

void F1GP_Render() {
	SDL_RenderCopy( render, textures[TEXTURE_GAME_BACKGROUND], NULL, NULL );
	F1GP_Render_Separator();
	F1GP_Render_Status();
	F1GP_Render_Opposite_Car();
	F1GP_Render_Explosive_Effect();
	F1GP_Render_Player_Car();
}

#endif 