#ifndef MAIN_H
#define MAIN_H

#include "CommonHeaders.h"
#include "Logic.h"
#include "Main.h"
#include "Init.h"
#include "Render.h"
#include "Music.h"
#include "KeysProcessing.h"

void main_loop(SDL_Texture *texture) {
	SDL_Event event;

	while ( SDL_PollEvent(&event) ) {
		
		switch (event.type) {
			case SDL_QUIT:
				exit_main_loop = true;
				quit = true;
				F1GP_Update_History();
				break;
			case SDL_KEYDOWN:
				if ( F1GP_crashing_count_down == 0 && F1GP_is_crashing && F1GP_score > F1GP_high_score ) {
					F1GP_Handle_Key_Press( event, s );
				}
				else {
			 		F1GP_Keyboard_Key_Handler(event.key.keysym.sym, true);
				}
				break;
			case SDL_KEYUP:
			 	F1GP_Keyboard_Key_Handler(event.key.keysym.sym, false);
				break;
			case SDL_MOUSEBUTTONDOWN:
				if ( !F1GP_is_crashing ) 
					F1GP_Render_Button( event );
				break;
		}
	}

	
	SDL_SetRenderTarget( render, texture );

	if ( !F1GP_is_game_paused ){
		if ( !F1GP_is_crashing ) {
			F1GP_Framemove();
			F1GP_Render();
			F1GP_Render_Button( event );
		} 
		else {
			//Crashing process
			if ( F1GP_crashing_count_down > 0 ) F1GP_crashing_count_down--;
			if (F1GP_crashing_count_down >= 40)
				F1GP_Render_Player_Car_Crash();
			else {
				if (F1GP_crashing_count_down == 39)
					Music_Play(MUSIC_GAMEOVER, 0);
					
				F1GP_Show_Game_Over_Screen();
			}
			if ( F1GP_crashing_count_down == 0 && F1GP_score > F1GP_high_score ){
				F1GP_Render_Highscore();
			}
			else if (F1GP_crashing_count_down <= 0) {
				F1GP_Update_History();
				F1GP_is_crashing = false;
				F1GP_is_new_game = true;
				exit_main_loop = true;
			}
		}
	}
	else {
		F1GP_Render_Button( event );
	}
	SDL_SetRenderTarget(render, NULL);
	
	if( !exit_main_loop ) {
		SDL_Rect rectangle;
		rectangle.x = 0;
		rectangle.y = 0;
		rectangle.w = WINDOW_WIDTH;
		rectangle.h = WINDOW_HEIGHT;
		SDL_RenderCopy(render, texture, &rectangle, NULL);
		SDL_RenderPresent(render);
	}
}

#ifdef __EMSCRIPTEN__
void main_loop_emscripten(void *arguments) {
	CONTEXT_EMSCRIPTEN *context = arguments;
	main_loop(context->texture);
}
#endif

#endif