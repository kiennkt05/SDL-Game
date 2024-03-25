#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "CommonHeaders.h"
#include "DataProcessing.h"
#include "Main.h"
#include "Texture.h"
#include "Music.h"
#include "Render.h"

int main(int argc, char *argv[]) {
	srand(time(0));

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	if( !( IMG_Init( IMG_INIT_PNG ) && IMG_INIT_PNG ) ){
		std::cout << "IMG_Init Error: " << IMG_GetError() << std::endl;
		return EXIT_FAILURE;		
	}
	
#if defined(_WIN32)
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");
#endif

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

	SDL_Window *window = SDL_CreateWindow("F1 Grand Prix", 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI );

	if (window == NULL) {
		std::cout << "SDL_CreateWindow Error: .\n" << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	SDL_Surface *icon = IMG_Load("assets/F1GP_ICON.png");
	if (icon == NULL)
		std::cout << "IMG_Load Error: " << SDL_GetError() << std::endl;
	else {
		SDL_SetColorKey(icon, SDL_TRUE, SDL_MapRGB(icon->format, 36, 227, 113)); // Icon transparent mask.
		SDL_SetWindowIcon(window, icon);
		SDL_FreeSurface(icon);
	}

	if (TTF_Init() == -1 ){
		std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_FAILURE;
	}

	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	if (render == NULL) {
		std::cout << "SDL_CreateRenderer Error:" << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_FAILURE;
	}
	Texture_Load();

	int result = Mix_Init(MIX_INIT_OGG);
	if (result != MIX_INIT_OGG) {
		std::cout << "Mix_Init Error: " << Mix_GetError() << std::endl;
		return EXIT_FAILURE;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 4096) == -1) {
		std::cout << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
		return EXIT_FAILURE;
	}
	Music_Load();

	F1GP_Load_Leaderboard();

	F1GP_Render_Intro();
	SDL_Event menu_event;
	while( !quit ){
		
		if ( exit_main_loop ){
			SDL_SetRenderDrawColor( render, 255, 255, 255, 0 ); // Orange
			SDL_RenderClear( render );

			while ( SDL_PollEvent(&menu_event) ){
				switch ( menu_event.type )
				{
					case SDL_QUIT:
						quit = true;
						break;
					
					case SDL_MOUSEBUTTONDOWN:
						if ( show_infor || show_leader_board ){
							int x, y; 
							SDL_GetMouseState( &x, &y );
							if ( x < 50 || x > 450 || y < 50 || y > 450 ){
								Music_Play( MUSIC_BUTTON_CLICKED, 0 );
								if ( show_infor ) show_infor = false;
								if ( show_leader_board ) show_leader_board = false;
							}
						}
						else
							F1GP_Render_Button( menu_event );
						break;
					case SDL_KEYDOWN:
						if ( menu_event.key.keysym.sym == SDLK_m ){
							if (is_sound_on){
								Mix_MasterVolume(0);
							}
							else {
								Mix_MasterVolume(128);
							}
							is_sound_on = !is_sound_on;
						}
				}

			}
			
			F1GP_Render_Menu();
			F1GP_Render_Button( menu_event );

			if ( show_infor ) Texture_Draw( 50, 50, TEXTURE_GAME_INFOR );
			else if( show_leader_board ){
				F1GP_Render_Leaderboard();
			}
				
			SDL_RenderPresent( render );
			
		} 
		else {
			// Start game
			SDL_RenderClear( render );
			F1GP_Init();
			F1GP_Load_History();
		 	F1GP_Render();
			BGM_channel = Music_Play(MUSIC_BACKGROUND, -1);
	

		#ifndef __EMSCRIPTEN__
			while ( !exit_main_loop ) {
				main_loop(textures[TEXTURE_SCREEN]);
				SDL_Delay(F1GP_TIMER_ELAPSE); // 10 FPS.
			}
		#else
			CONTEXT_EMSCRIPTEN context;
			context.texture = textures[TEXTURE_SCREEN];
			emscripten_set_main_loop_arg(main_loop_emscripten, &context, 10, 1); // 10 FPS.
		#endif
		}
	}
	
	// Update leaderboard
	F1GP_Update_Leaderboard();
	Mix_CloseAudio();
	Music_Unload();
	Texture_Unload();

	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}
