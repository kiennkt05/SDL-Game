#ifndef INIT_H
#define INIT_H

#include "CommonHeaders.h"
#include "Init.h"

void F1GP_Init() {
	int index;
	
	F1GP_key_up_pressed = false;
	F1GP_key_down_pressed = false;
	F1GP_key_right_pressed = false;
	F1GP_key_left_pressed = false;

	F1GP_separator_0_block_start_y = F1GP_DISPLAY_START_Y;
	F1GP_separator_1_block_start_y = F1GP_DISPLAY_START_Y + F1GP_SEPARATOR_HEIGHT_SPACE * 3;

	F1GP_player_car.image = TEXTURE_PLAYER_CAR;
	F1GP_player_car.image_fly = TEXTURE_PLAYER_CAR_FLY;
	
	F1GP_player_car.pos_x = ( ( F1GP_ROAD_1_START_X + F1GP_ROAD_1_END_X - F1GP_PLAYER_CAR_IMAGE_SIZE_X) / 2);
	F1GP_player_car.dx = F1GP_PLAYER_CAR_IMAGE_SIZE_X;
	F1GP_player_car.pos_y = F1GP_DISPLAY_END_Y - F1GP_PLAYER_CAR_IMAGE_SIZE_Y - 1;
	F1GP_player_car.dy = F1GP_PLAYER_CAR_IMAGE_SIZE_Y;

	F1GP_opposite_car_type[0].dx = F1GP_OPPOSITE_CAR_0_IMAGE_SIZE_X;
	F1GP_opposite_car_type[0].dy = F1GP_OPPOSITE_CAR_0_IMAGE_SIZE_Y;
	F1GP_opposite_car_type[0].image = TEXTURE_OPPOSITE_CAR_0;
	F1GP_opposite_car_type[0].speed = 12;
	F1GP_opposite_car_type[0].dx_from_road =  ( F1GP_ROAD_WIDTH - F1GP_OPPOSITE_CAR_0_IMAGE_SIZE_X) / 2;

	F1GP_opposite_car_type[1].dx = F1GP_OPPOSITE_CAR_1_IMAGE_SIZE_X;
	F1GP_opposite_car_type[1].dy = F1GP_OPPOSITE_CAR_1_IMAGE_SIZE_Y;
	F1GP_opposite_car_type[1].image = TEXTURE_OPPOSITE_CAR_1;
	F1GP_opposite_car_type[1].speed = 16;
	F1GP_opposite_car_type[1].dx_from_road =  ( F1GP_ROAD_WIDTH - F1GP_OPPOSITE_CAR_1_IMAGE_SIZE_X) / 2;

	F1GP_opposite_car_type[2].dx = F1GP_OPPOSITE_CAR_2_IMAGE_SIZE_X;
	F1GP_opposite_car_type[2].dy = F1GP_OPPOSITE_CAR_2_IMAGE_SIZE_Y;
	F1GP_opposite_car_type[2].image = TEXTURE_OPPOSITE_CAR_2;
	F1GP_opposite_car_type[2].speed = 24;
	F1GP_opposite_car_type[2].dx_from_road =  ( F1GP_ROAD_WIDTH - F1GP_OPPOSITE_CAR_2_IMAGE_SIZE_X) / 2;

	F1GP_opposite_car_type[3].dx = F1GP_OPPOSITE_CAR_3_IMAGE_SIZE_X;
	F1GP_opposite_car_type[3].dy = F1GP_OPPOSITE_CAR_3_IMAGE_SIZE_Y;
	F1GP_opposite_car_type[3].image = TEXTURE_OPPOSITE_CAR_3;
	F1GP_opposite_car_type[3].speed = 12;
	F1GP_opposite_car_type[3].dx_from_road = ( F1GP_ROAD_WIDTH - F1GP_OPPOSITE_CAR_3_IMAGE_SIZE_X) / 2;

	F1GP_opposite_car_type[4].dx = F1GP_OPPOSITE_CAR_4_IMAGE_SIZE_X;
	F1GP_opposite_car_type[4].dy = F1GP_OPPOSITE_CAR_4_IMAGE_SIZE_Y;
	F1GP_opposite_car_type[4].image = TEXTURE_OPPOSITE_CAR_4;
	F1GP_opposite_car_type[4].speed = 12;
	F1GP_opposite_car_type[4].dx_from_road = ( F1GP_ROAD_WIDTH - F1GP_OPPOSITE_CAR_4_IMAGE_SIZE_X) / 2;

	F1GP_opposite_car_type[5].dx = F1GP_OPPOSITE_CAR_5_IMAGE_SIZE_X;
	F1GP_opposite_car_type[5].dy = F1GP_OPPOSITE_CAR_5_IMAGE_SIZE_Y;
	F1GP_opposite_car_type[5].image = TEXTURE_OPPOSITE_CAR_5;
	F1GP_opposite_car_type[5].speed = 20;
	F1GP_opposite_car_type[5].dx_from_road = ( F1GP_ROAD_WIDTH - F1GP_OPPOSITE_CAR_5_IMAGE_SIZE_X) / 2;

	F1GP_opposite_car_type[6].dx = F1GP_OPPOSITE_CAR_6_IMAGE_SIZE_X;
	F1GP_opposite_car_type[6].dy = F1GP_OPPOSITE_CAR_6_IMAGE_SIZE_Y;
	F1GP_opposite_car_type[6].image = TEXTURE_OPPOSITE_CAR_6;
	F1GP_opposite_car_type[6].speed = 12;
	F1GP_opposite_car_type[6].dx_from_road = ( F1GP_ROAD_WIDTH - F1GP_OPPOSITE_CAR_6_IMAGE_SIZE_X) / 2;

	F1GP_opposite_car_type[7].dx = F1GP_SPECIAL_BOX_SIZE;
	F1GP_opposite_car_type[7].dy = F1GP_SPECIAL_BOX_SIZE;
	F1GP_opposite_car_type[7].image = TEXTURE_SPECIAL_BOX;
	F1GP_opposite_car_type[7].speed = 15;
	F1GP_opposite_car_type[7].dx_from_road = ( F1GP_ROAD_WIDTH - F1GP_SPECIAL_BOX_SIZE ) / 2;

	for ( index = 0; index < F1GP_OPPOSITE_CAR_COUNT + 1; index++ ) {
		F1GP_opposite_car[index].is_empty = true;
		F1GP_opposite_car[index].is_add_score = false;
	}
	
	F1GP_is_crashing = false;
	F1GP_last_car_road = 0;
	F1GP_player_car_transform_time = 7;
	F1GP_player_is_car_fly = false;
	F1GP_player_is_car_transform = false;
	F1GP_score = 0;
	F1GP_level = 1;
	F1GP_pass = 0;
	F1GP_fly_count = 1;
	F1GP_fly_charger_count = 0;
	F1GP_transform_count = 2;
	F1GP_run_count = 0;

	F1GP_explosive_effect.clear();
	for ( int i = 0; i < F1GP_OPPOSITE_CAR_DEFAULT_APPEAR_RATE; i++ ){
		std::vector<int> v = { -1, 0, 0, 0 };
		F1GP_explosive_effect.push_back( v );
	}

}

#endif