#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include "CommonHeaders.h"
#include "Texture.h"

void Set_Texture_Alpha_Mode(TEXTURE texture_id, int a){
	SDL_SetTextureAlphaMod(textures[texture_id], a);
}

void Texture_Create(const char *filepath, TEXTURE texture_id) {
	SDL_Surface *image = IMG_Load(filepath);
	textures[texture_id] = SDL_CreateTextureFromSurface(render, image);
	SDL_FreeSurface(image);
}

void Texture_Load() {

	F1GP_Number_Font = TTF_OpenFont("Fonts/MonomaniacOne-Regular.ttf", 34);
	SDL_Color num_color =  { 255, 255, 255 };
	for ( int i = 0; i < 10; i++ ){
		char s[] = { char(i + 48), '\0' };
		SDL_Surface* num_suface = TTF_RenderText_Solid( F1GP_Number_Font, s, num_color );
		textures[static_cast<TEXTURE>(i)] = SDL_CreateTextureFromSurface( render, num_suface );
		SDL_FreeSurface( num_suface );
	}
	TTF_CloseFont( F1GP_Number_Font );
	
	textures[TEXTURE_SCREEN] =
		SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
		
	Texture_Create("assets/F1GP_PLAYER_CAR.png", TEXTURE_PLAYER_CAR);
	Texture_Create("assets/F1GP_PLAYER_CAR_FLY.png", TEXTURE_PLAYER_CAR_FLY);
	Texture_Create("assets/F1GP_PLAYER_CAR_FLY_UP.png", TEXTURE_PLAYER_CAR_FLY_UP);
	Texture_Create("assets/F1GP_PLAYER_CAR_FLY_DOWN.png", TEXTURE_PLAYER_CAR_FLY_DOWN);
	Texture_Create("assets/F1GP_PLAYER_CAR_CRASH.png", TEXTURE_PLAYER_CAR_CRASH);
	Texture_Create("assets/F1GP_PLAYER_CAR_RUN.png", TEXTURE_PLAYER_CAR_RUN);
	Texture_Create("assets/F1GP_PLAYER_CAR_TRANSFORM.png", TEXTURE_PLAYER_CAR_TRANSFORM);
	Texture_Create("assets/F1GP_LOGO.png", TEXTURE_LOGO);
	Texture_Create("assets/F1GP_STATUS_SCORE.png", TEXTURE_STATUS_SCORE);
	Texture_Create("assets/F1GP_STATUS_LEVEL.png", TEXTURE_STATUS_LEVEL);
	Texture_Create("assets/F1GP_STATUS_FLY.png", TEXTURE_STATUS_FLY);
	Texture_Create("assets/F1GP_OPPOSITE_CAR_0.png", TEXTURE_OPPOSITE_CAR_0);
	Texture_Create("assets/F1GP_OPPOSITE_CAR_1.png", TEXTURE_OPPOSITE_CAR_1);
	Texture_Create("assets/F1GP_OPPOSITE_CAR_2.png", TEXTURE_OPPOSITE_CAR_2);
	Texture_Create("assets/F1GP_OPPOSITE_CAR_3.png", TEXTURE_OPPOSITE_CAR_3);
	Texture_Create("assets/F1GP_OPPOSITE_CAR_4.png", TEXTURE_OPPOSITE_CAR_4);
	Texture_Create("assets/F1GP_OPPOSITE_CAR_5.png", TEXTURE_OPPOSITE_CAR_5);
	Texture_Create("assets/F1GP_OPPOSITE_CAR_6.png", TEXTURE_OPPOSITE_CAR_6);
	Texture_Create("assets/F1GP_GAME_BACKGROUND.png", TEXTURE_GAME_BACKGROUND);
	Texture_Create("assets/F1GP_GAMEOVER_BACKGROUND.png", TEXTURE_GAMEOVER_BACKGROUND);
	Texture_Create("assets/F1GP_GAMEOVER_CRASH.png", TEXTURE_GAMEOVER_CRASH);
	Texture_Create("assets/Intro.png", TEXTURE_GAME_INTRO);
	Texture_Create("assets/Menu.png", TEXTURE_GAME_MENU);
	Texture_Create("assets/F1GP_INFOR.png", TEXTURE_GAME_INFOR );
	Texture_Create("assets/F1GP_LEADERBOARD.png", TEXTURE_GAME_LEADERBOARD );
	Texture_Create("assets/F1GP_LEADERBOARD_BUTTON.png", TEXTURE_BUTTON_LEADERBOARD);
	Texture_Create("assets/F1GP_INFOR_BUTTON.png", TEXTURE_BUTTON_INFOR );					SDL_SetTextureAlphaMod( textures[TEXTURE_BUTTON_INFOR], 160 );
	Texture_Create("assets/Play_Button.png", TEXTURE_BUTTON_PLAY);
	Texture_Create("assets/Quit_Button.png", TEXTURE_BUTTON_QUIT);
	Texture_Create("assets/Back_Button.png", TEXTURE_BUTTON_BACK);
	Texture_Create("assets/F1GP_HOME_Button.png", TEXTURE_BUTTON_HOME);
	Texture_Create("assets/F1GP_Pause_Button.png", TEXTURE_BUTTON_PAUSE);
	Texture_Create("assets/F1GP_Pause_OPTIONS.png", TEXTURE_BUTTON_PAUSE_OPTIONS);			
	Texture_Create("assets/F1GP_SOUND_OFF.png", TEXTURE_BUTTON_SOUND_OFF);
	Texture_Create("assets/F1GP_SOUND_ON.png", TEXTURE_BUTTON_SOUND_ON);
	Texture_Create("assets/F1GP_SOUND_OFF_1.png", TEXTURE_BUTTON_SOUND_OFF_1);				SDL_SetTextureAlphaMod( textures[TEXTURE_BUTTON_SOUND_OFF_1], 160 );
	Texture_Create("assets/F1GP_SOUND_ON_1.png", TEXTURE_BUTTON_SOUND_ON_1);				SDL_SetTextureAlphaMod( textures[TEXTURE_BUTTON_SOUND_ON_1], 160 );
	Texture_Create("assets/F1GP_Resume_Button.png", TEXTURE_BUTTON_RESUME);
	Texture_Create("assets/F1GP_Restart_Button.png", TEXTURE_BUTTON_RESTART);
	Texture_Create("assets/F1GP_SPECIAL_BOX.png", TEXTURE_SPECIAL_BOX);
	Texture_Create("assets/F1GP_SCROLL_BAR.png", TEXTURE_SCROLL_BAR);
	Texture_Create("assets/F1GP_STOP_WATCH.png", TEXTURE_STOP_WATCH);
	Texture_Create("assets/F1GP_EXPLOSIVE_EFFECT.png", TEXTURE_EXPLOSIVE_EFFECT);
	Texture_Create("assets/F1GP_HIGHSCORE_FIELD.png", TEXTURE_HIGH_SCORE_FIELD);

}

void Texture_Draw(int x, int y, TEXTURE texture_id, int times = 4, SDL_Rect* src = NULL ) {
	SDL_Rect rectangle;
	rectangle.x = x;
	rectangle.y = y;
	if( src != NULL ){
		rectangle.w = src->w;
		rectangle.h = src->h;
		SDL_RenderCopy(render, textures[texture_id], src, &rectangle);
	}
	else{	
		SDL_QueryTexture(textures[texture_id], NULL, NULL, &rectangle.w, &rectangle.h);
		rectangle.x -= rectangle.w * ( times - 4 ) / 8;
		rectangle.y -= rectangle.h * ( times - 4 ) / 8;
		rectangle.w = rectangle.w * times / 4;
		rectangle.h = rectangle.h * times / 4;
		SDL_RenderCopy(render, textures[texture_id], NULL, &rectangle);
	}

}

void Texture_Unload() {
	int i = 0;
	for (; i < TEXTURE_MAX; ++i)
		if (textures[i])
			SDL_DestroyTexture(textures[i]);
}

#endif