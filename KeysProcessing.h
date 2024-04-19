#ifndef KEYSPROCESSING_H
#define KEYSPROCESSING_H

#include "CommonHeaders.h"
#include "KeysProcessing.h"
#include "Music.h"
#include "Logic.h"
#include <algorithm>

void F1GP_Key_Left_Pressed() {
	F1GP_RELEASE_ALL_KEY;
	F1GP_key_left_pressed = true;
}

void F1GP_Key_Left_Released() {
	F1GP_key_left_pressed = false;	
}

void F1GP_Key_Right_Pressed() {
 	F1GP_RELEASE_ALL_KEY;
 	F1GP_key_right_pressed = true;
}

void F1GP_Key_Right_Released() {
 	F1GP_key_right_pressed = false;
}

void F1GP_Key_Up_Pressed() {
	F1GP_RELEASE_ALL_KEY;
	F1GP_key_up_pressed = true;
}

void F1GP_Key_Up_Released() {
 	F1GP_key_up_pressed = false;
}

void F1GP_Key_Down_Pressed() {
	F1GP_RELEASE_ALL_KEY;
	F1GP_key_down_pressed = true;
}

void F1GP_Key_Down_Released() {
 	F1GP_key_down_pressed = false;
}

void F1GP_Key_Fly_Pressed() {
	if ( F1GP_player_is_car_fly != false)
		return;

	if ( F1GP_fly_count > 0) {
		F1GP_player_is_car_fly = true;
		F1GP_player_car_fly_duration = 0;
		F1GP_fly_count--;
	}
}

void F1GP_Keyboard_Key_Handler(int vkey_code, int key_state) {
	switch (vkey_code) {
		case SDLK_LEFT:
		case SDLK_a:
			(key_state) ? F1GP_Key_Left_Pressed() : F1GP_Key_Left_Released();
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			(key_state) ? F1GP_Key_Right_Pressed() : F1GP_Key_Right_Released();
			break;
		case SDLK_UP:
		case SDLK_w:
			(key_state) ? F1GP_Key_Up_Pressed() : F1GP_Key_Up_Released();
			break;
		case SDLK_DOWN:
		case SDLK_s:
			(key_state) ? F1GP_Key_Down_Pressed() : F1GP_Key_Down_Released();
			break;
		case SDLK_SPACE:
			if (key_state)
			 F1GP_Key_Fly_Pressed();
			break;
		case SDLK_m:
			if (key_state) {
				if (is_sound_on){
					Mix_MasterVolume(0);
				}
				else {
					Mix_MasterVolume(128);
				}
				is_sound_on = !is_sound_on;
			}
			break;
		case SDLK_ESCAPE:
		case SDLK_p:
			if (key_state) {
				if (!F1GP_is_game_paused) {
					Mix_Pause(-1);
				}
				else { 
					Mix_Resume(-1);
				}
				F1GP_is_game_paused = !F1GP_is_game_paused;
			}
			break;
	}
}

void F1GP_Handle_Key_Press(SDL_Event& event, std::string &s) {
	if ( s == "Enter your name" ) s = "";
	switch(event.key.keysym.sym) {
		case SDLK_RETURN:
			if (F1GP_leaderboard.size() == 5) 
				F1GP_leaderboard.pop_back();
			F1GP_leaderboard.push_back(make_pair(s,F1GP_score));
			sort(F1GP_leaderboard.begin(), F1GP_leaderboard.end(), cmp);
			F1GP_high_score = F1GP_leaderboard.back().second;
			s = "Enter your name";
			F1GP_crashing_count_down = -1;
			Music_Play( MUSIC_BUTTON_CLICKED, 0 );
			break;
        case SDLK_BACKSPACE:
            if (!s.empty())
                s.pop_back();
            break;
		case SDLK_SPACE:
			s += " ";
			break;
        default:
            if ((event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z) || 
                (event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9)) {
                // Append the key to the string
                s += static_cast<char>(event.key.keysym.sym);
            }
            break;
    }
	if ( s.size() > 12 && s != "Enter your name" ) s.resize(12);
	if ( s == "" ) s = "Enter your name";
}

#endif