#ifndef LOGIC_H
#define LOGIC_H

#include "CommonHeaders.h"
#include "Logic.h"
#include "Music.h"

bool cmp( std::pair<std::string, int> p1, std::pair<std::string, int> p2 ){
	return (p1.second > p2.second);
}

void F1GP_Crashing() {
	Mix_HaltChannel( BGM_channel );
	Music_Play(MUSIC_CRASH, 0);

	F1GP_is_crashing = true;
	F1GP_crashing_count_down = 50;
}

void F1GP_New_Opposite_Car() {
	int index;
	int validIndex = 0;
	int no_slot;
	int car_type = 0;
	int road;
	int car_pos_x = 0;
	int car_shift;
	int enough_space;
	int rand_num;
	int speed_add;

	
	no_slot = true;
	if ((rand() % F1GP_OPPOSITE_CAR_DEFAULT_APPEAR_RATE) == 0) {
		for (index = 0; index < F1GP_OPPOSITE_CAR_COUNT + 1; index++) {
			// Search for the opposite car not initialized in opposite car list
			if ( F1GP_opposite_car[index].is_empty == true ) { 			
				validIndex = index;
				no_slot = false;
				break;
			}
		}
	}

	// If there all the list was initialized, then return
	if ( no_slot )
		return;

	// Rand for random road
	road = rand() % 3;

	// Check for avoid overlapping car
	if ( road == F1GP_last_car_road ) {
		road++;
		road %= 3;
	}

	// Rand for opposite car
	if ( F1GP_level < 3) {
		rand_num = rand() % 120;
		// 20 : 30 : 10 : 20 : 10 : 10 : 10 : 10
		if( rand_num < 20 ) car_type = 0;
		else if( rand_num < 50 ) car_type = 1;
		else if( rand_num < 60 ) car_type = 2;
		else if( rand_num < 80 ) car_type = 3;
		else if( rand_num < 90 ) car_type = 4;
		else if( rand_num < 100 ) car_type = 5;
		else if( rand_num < 110 ) car_type = 6;
		else car_type = 7;
	}

	if ( F1GP_level >= 3 ) {
		rand_num = rand() % 120;
		// 10 : 20 : 20 : 20 : 10 : 20 : 10 : 10
		if( rand_num < 10 ) car_type = 0;
		else if( rand_num < 30 ) car_type = 1;
		else if( rand_num < 50 ) car_type = 2;
		else if( rand_num < 70 ) car_type = 3;
		else if( rand_num < 80 ) car_type = 4;
		else if( rand_num < 100 ) car_type = 5;
		else if( rand_num < 110 ) car_type = 6;
		else car_type = 7;
	}
	
	// Check for available space for player car
	enough_space = true;
	for ( index = 0; index < F1GP_OPPOSITE_CAR_COUNT + 1; index++ ) {
		if ( ( F1GP_opposite_car[index].is_empty == false) && ( F1GP_opposite_car[index].pos_y <  ( F1GP_player_car.dy * 2 / 2 ) ) )
			enough_space = false;
	}
	
	if ( !enough_space )
		return;

	// Initialize opposite car's data
	speed_add = F1GP_level - 1;

	if( car_type == 7 )
		F1GP_opposite_car[validIndex].is_special_box = true;
	else F1GP_opposite_car[validIndex].is_special_box = false;
	F1GP_opposite_car[validIndex].is_empty = false;
	F1GP_opposite_car[validIndex].is_add_score = false;
	F1GP_opposite_car[validIndex].dx = F1GP_opposite_car_type[car_type].dx;
	F1GP_opposite_car[validIndex].dy = F1GP_opposite_car_type[car_type].dy;
	F1GP_opposite_car[validIndex].speed = F1GP_opposite_car_type[car_type].speed + speed_add;
	F1GP_opposite_car[validIndex].dx_from_road = F1GP_opposite_car_type[car_type].dx_from_road;
	F1GP_opposite_car[validIndex].image = F1GP_opposite_car_type[car_type].image;

	// x position
	car_shift = F1GP_opposite_car[validIndex].dx_from_road;
	switch (road) {
		case 0:
			car_pos_x = F1GP_ROAD_0_START_X + car_shift;
			break;
		case 1:
			car_pos_x = F1GP_ROAD_1_START_X + car_shift;
			break;
		case 2:
			car_pos_x = F1GP_ROAD_2_START_X + car_shift;
			break;
	}

	F1GP_opposite_car[validIndex].pos_x = car_pos_x;
	F1GP_opposite_car[validIndex].pos_y = F1GP_DISPLAY_START_Y - F1GP_opposite_car[validIndex].dy;
	F1GP_opposite_car[validIndex].road_id = road;

	F1GP_last_car_road = road;
}

void F1GP_CollisionCheck() {
	int index; 
	bool collided = false;
	int minA_x, minA_y, maxA_x, maxA_y;
	int minB_x, minB_y, maxB_x, maxB_y;

	minA_x = F1GP_player_car.pos_x + 1;
	maxA_x = minA_x + F1GP_player_car.dx - 2;
	minA_y = F1GP_player_car.pos_y;
	maxA_y = minA_y + F1GP_player_car.dy;

	for (index = 0; index < F1GP_OPPOSITE_CAR_COUNT + 1; index++) {
		if ( F1GP_opposite_car[index].is_empty == false) {

			minB_x = F1GP_opposite_car[index].pos_x + 1;
			maxB_x = minB_x + F1GP_opposite_car[index].dx - 2;
			minB_y = F1GP_opposite_car[index].pos_y;
			maxB_y = minB_y + F1GP_opposite_car[index].dy;

			//Overlap
			if (((minA_x <= minB_x) && (minB_x <= maxA_x)) || ((minA_x <= maxB_x) && (maxB_x <= maxA_x))) {
				if (((minA_y <= minB_y) && (minB_y <= maxA_y)) || ((minA_y <= maxB_y) && (maxB_y <= maxA_y))) {
				 	collided = true;
					break;
				}
			}

			//Top left corner of A is in B
			if ((minA_x >= minB_x) && (minA_x <= maxB_x) && (minA_y >= minB_y) && (minA_y <= maxB_y)) {
				collided = true;
				break;
			}

			//Bottom left cornor of A is in B
			if ((minA_x >= minB_x) && (minA_x <= maxB_x) && (maxA_y >= minB_y) && (maxA_y <= maxB_y)) {
				collided = true;
				break;
			}

			//Top right corner of A is in B
			if ((maxA_x >= minB_x) && (maxA_x <= maxB_x) && (minA_y >= minB_y) && (minA_y <= maxB_y)) {
				collided = true;
				break;
			}

			//Bottom right corner of A is in B
			if ((maxA_x >= minB_x) && (maxA_x <= maxB_x) && (maxA_y >= minB_y) && (maxA_y <= maxB_y)) {
				collided = true;
				break;
			}

			//Increment the score when the car over another
			if ((maxA_y < minB_y) &&  ( F1GP_opposite_car[index].is_add_score == false) && !(F1GP_opposite_car[index].is_special_box)) {
				F1GP_score++;
				F1GP_pass++;
				F1GP_opposite_car[index].is_add_score = true;

				if ( F1GP_pass == 10) F1GP_level++; /* level 2 */
				else if (F1GP_pass == 20) F1GP_level++; /* level 3 */
				else if (F1GP_pass == 30) F1GP_level++; /* level 4 */
				else if (F1GP_pass == 40) F1GP_level++; /* level 5 */
				else if (F1GP_pass == 50) F1GP_level++; /* level 6 */
				else if (F1GP_pass == 60) F1GP_level++; /* level 7 */
				else if (F1GP_pass == 70) F1GP_level++; /* level 8 */
				else if (F1GP_pass == 100) F1GP_level++; /* level 9 */

				F1GP_fly_charger_count++;
				if (F1GP_fly_charger_count >= 6) {
					if (F1GP_fly_count < F1GP_MAX_FLY_COUNT) {
						F1GP_fly_charger_count = 0;
						F1GP_fly_count++;
					} else
						F1GP_fly_charger_count--;
				}
			}
		}
	}
 
	if ( collided && F1GP_player_is_car_transform ){
		if ( F1GP_opposite_car[index].is_special_box ){
			Music_Play(MUSIC_GET_BOX, 0);
			F1GP_transform_count++;			
		}
		else{
			F1GP_score++;
			F1GP_pass++;
			F1GP_opposite_car[index].is_add_score = true;

			if ( F1GP_pass == 10) F1GP_level++; /* level 2 */
			else if (F1GP_pass == 20) F1GP_level++; /* level 3 */
			else if (F1GP_pass == 30) F1GP_level++; /* level 4 */
			else if (F1GP_pass == 40) F1GP_level++; /* level 5 */
			else if (F1GP_pass == 50) F1GP_level++; /* level 6 */
			else if (F1GP_pass == 60) F1GP_level++; /* level 7 */
			else if (F1GP_pass == 70) F1GP_level++; /* level 8 */
			else if (F1GP_pass == 100) F1GP_level++; /* level 9 */

			// Initialize explosive effect - 14/03
			for ( int i = 0; i < F1GP_OPPOSITE_CAR_DEFAULT_APPEAR_RATE; i++ ){
				if ( F1GP_explosive_effect[i][0] == -1 ){
					F1GP_explosive_effect[i][0] = F1GP_opposite_car[index].pos_x + F1GP_opposite_car[index].dx / 2;
					F1GP_explosive_effect[i][1] = F1GP_opposite_car[index].pos_y + F1GP_opposite_car[index].dy / 2;
					F1GP_explosive_effect[i][3] = index;
					break;
				}
			}

		}
		F1GP_opposite_car[index].is_empty = true;
		
	}
	else if ( collided ){
		if ( F1GP_opposite_car[index].is_special_box ){
			Music_Play(MUSIC_GET_BOX, 0);
			F1GP_opposite_car[index].is_empty = true;
			F1GP_transform_count++;
		}
		else F1GP_Crashing(); 
	}
}

void F1GP_Framemove() {
	int shift;
	int max;
	int index;

	shift = F1GP_PLAYER_CAR_SHIFT;
	if (F1GP_key_up_pressed) {
		//If the player car reach the upper bound
		if (F1GP_player_car.pos_y - shift < F1GP_DISPLAY_START_Y)
			shift = F1GP_player_car.pos_y - F1GP_DISPLAY_START_Y - 1;
		if ( !F1GP_player_is_car_fly )
		 	F1GP_player_car.pos_y -= shift;
	}

	if (F1GP_key_down_pressed) {
		//If the player car reach the lower bound
		max = F1GP_player_car.pos_y + F1GP_player_car.dy;
		if (max + shift > F1GP_DISPLAY_END_Y)
			shift = F1GP_DISPLAY_END_Y - max;
		if ( !F1GP_player_is_car_fly )
		 	F1GP_player_car.pos_y += shift;
	}

	if (F1GP_key_right_pressed) {
		//If the player car reach the right bound
		max = F1GP_player_car.pos_x + F1GP_player_car.dx;
		if (max + shift > F1GP_ROAD_2_END_X) 
			shift = F1GP_ROAD_2_END_X - max;
	 	F1GP_player_car.pos_x += shift;
	}

	if (F1GP_key_left_pressed) {
		//If the player car reach the left bound
		if (F1GP_player_car.pos_x - shift < F1GP_ROAD_0_START_X)
			shift = F1GP_player_car.pos_x - F1GP_ROAD_0_START_X - 1;
	 	F1GP_player_car.pos_x -= shift;
	}

	for (index = 0; index < F1GP_OPPOSITE_CAR_COUNT + 1; index++) {
		if (F1GP_opposite_car[index].is_empty == false) {
		  	F1GP_opposite_car[index].pos_y += F1GP_opposite_car[index].speed;
			//Delete the opposite car when it out of bound
			if (F1GP_opposite_car[index].pos_y > (F1GP_DISPLAY_END_Y + F1GP_opposite_car[index].dy))
			  	F1GP_opposite_car[index].is_empty = true;
		}
	}

	if ( F1GP_transform_count == 3 ){
		F1GP_player_is_car_transform = true;
		F1GP_transform_count = 0;
	}

	if ( F1GP_player_is_car_transform ) F1GP_player_car_transform_time--;

	//If the player car is flying
	if ( F1GP_player_is_car_fly ) {
		F1GP_player_car_fly_duration++;
		if (F1GP_player_car_fly_duration == F1GP_PLAYER_CAR_FLY_FRAME_COUNT) F1GP_player_is_car_fly = false;
		shift = F1GP_PLAYER_CAR_FLY_SHIFT;
		if ( (F1GP_player_car.pos_y - shift) < F1GP_DISPLAY_START_Y)
			shift = F1GP_player_car.pos_y - F1GP_DISPLAY_START_Y - 1;
	 	F1GP_player_car.pos_y -= shift;
	} else
	 	F1GP_CollisionCheck();

 	F1GP_New_Opposite_Car();
}


#endif