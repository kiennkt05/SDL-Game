#include "CommonHeaders.h"
#include "DataProcessing.h"
#include "KeysProcessing.h"
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
	
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

	SDL_Window *window = SDL_CreateWindow("F1 Grand Prix", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI );
	if (window == NULL) {
		std::cout << "SDL_CreateWindow Error: .\n" << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	SDL_Surface *icon = IMG_Load("assets/F1GP_ICON.png");
	if (icon == NULL){
		std::cout << "IMG_Load Error: " << SDL_GetError() << std::endl;
	}
	else {
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

	if (Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG) {
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
	SDL_Event event;
	while( !quit ){	
		if ( exit_main_loop ){
			SDL_SetRenderDrawColor( render, 255, 255, 255, 0 ); // Orange
			SDL_RenderClear( render );

			while ( SDL_PollEvent(&event) ){
				switch ( event.type )
				{
					case SDL_QUIT:
						quit = true;
						break;
					
					case SDL_MOUSEBUTTONDOWN:
						int x, y;
						SDL_GetMouseState(&x, &y);
						if ( show_infor || show_leader_board ){
							if ( x < 50 || x > 450 || y < 50 || y > 450 ){
								Music_Play( MUSIC_BUTTON_CLICKED, 0 );
								if ( show_infor ) show_infor = false;
								if ( show_leader_board ) show_leader_board = false;
							}
						}
						else{
							// Sound button clicked
							if (x >= 416 && x <= 416 + 30 && y >= 15 && y <= 15 + 30){
								Music_Play( MUSIC_BUTTON_CLICKED, 0 );
								if ( is_sound_on ){
									Mix_MasterVolume( 0 );
								}
								else {
									Mix_MasterVolume( 128 );
								}
								is_sound_on = !is_sound_on;
							}

							// Infor button clicked
							else if (x >= 458 && x <= 458 + 30 && y >= 15 && y <= 15 + 30){
								Music_Play( MUSIC_BUTTON_CLICKED, 0 );
								show_infor = true;								
							}

							// Leaderboard button cliked
							else if (x >= F1GP_BUTTON_LEADERBOARD_X && x <= F1GP_BUTTON_LEADERBOARD_X + F1GP_BUTTON_LEADERBOARD_WIDTH && 
								y >= F1GP_BUTTON_LEADERBOARD_Y && y <= F1GP_BUTTON_LEADERBOARD_Y + F1GP_BUTTON_LEADERBOARD_HEIGHT){
								Music_Play( MUSIC_BUTTON_CLICKED, 0 );
								show_leader_board = true;
							}

							// Play button clicked
							else if (x >= F1GP_BUTTON_PLAY_X && x <= F1GP_BUTTON_PLAY_X + F1GP_BUTTON_PLAY_WIDTH && 
								y >= F1GP_BUTTON_PLAY_Y && y <= F1GP_BUTTON_PLAY_Y + F1GP_BUTTON_PLAY_HEIGHT){
								Music_Play( MUSIC_BUTTON_CLICKED, 0 );
								exit_main_loop = false;
							}				

							// Quit button clicked
							else if (x >= F1GP_BUTTON_QUIT_X && x <= F1GP_BUTTON_QUIT_X + F1GP_BUTTON_QUIT_WIDTH && 
								y >= F1GP_BUTTON_QUIT_Y && y <= F1GP_BUTTON_QUIT_Y + F1GP_BUTTON_QUIT_HEIGHT){
								Music_Play( MUSIC_BUTTON_CLICKED, 0 );
								quit = true;
							}			

						}
						break;
					case SDL_KEYDOWN:
						if ( event.key.keysym.sym == SDLK_m ){
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
			F1GP_Render_Button( event );

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
			remained = F1GP_Load_History();
		 	F1GP_Render();
			BGM_channel = Music_Play(MUSIC_BACKGROUND, -1);

			while ( !exit_main_loop ) {
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
							if (!F1GP_is_crashing){
								int x, y;
								SDL_GetMouseState(&x, &y);
								if (!F1GP_is_game_paused){
									// Pause button clicked
									if (x >= 458 && x <= 458 + 30 && y >= 15 && y <= 15 + 30){
										Mix_Pause(-1);
										Music_Play( MUSIC_BUTTON_CLICKED, 0 );
										F1GP_is_game_paused = true;
									}

									// Sound button clicked
									else if (x >= 416 && x <= 416 + 30 && y >= 15 && y <= 15 + 30){
										Music_Play( MUSIC_BUTTON_CLICKED, 0 );
										if ( is_sound_on ){
											Mix_MasterVolume( 0 );
										}
										else {
											Mix_MasterVolume( 128 );
										}
										is_sound_on = !is_sound_on;
									}
								}
								else {
									// Resume button cliked
									if (x >= 110 && x <= 110 + 30 && y >= 80 && y <= 80 + 30){
										Music_Play( MUSIC_BUTTON_CLICKED, 0 );
										Mix_Resume(-1);
										F1GP_is_game_paused = false;										
									}
									
									// Restart butotn cliked
									else if (x >= 168 && x <= 168 + 30 && y >= 80 && y <= 80 + 30){
										Music_Play( MUSIC_BUTTON_CLICKED, 0 );
										Mix_PlayChannel(BGM_channel, music_tracks[MUSIC_BACKGROUND], -1 );
										F1GP_is_game_paused = false;
										F1GP_Init();										
									}									
									
									// Home button clicked
									else if (x >= 226 && x <= 226 + 30 && y >= 80 && y <= 80 + 30){
										F1GP_is_game_paused = false;
										Mix_HaltChannel(-1);
										Music_Play( MUSIC_BUTTON_CLICKED, 0 );
										F1GP_Update_History();
										exit_main_loop = true;										
									}								}
							}
							break;
					}
				}

				SDL_SetRenderTarget( render, textures[TEXTURE_SCREEN] );

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
					if (remained){
						F1GP_is_game_paused = true;
						Mix_Pause(-1);
						remained = false;
					}
				}
				else {
					F1GP_Render_Button( event );
				}
				SDL_SetRenderTarget(render, NULL);
				
				if( !exit_main_loop ) {
						SDL_RenderClear(render);
						SDL_Rect rectangle;
						rectangle.x = 0;
						rectangle.y = 0;
						rectangle.w = WINDOW_WIDTH;
						rectangle.h = WINDOW_HEIGHT;
						SDL_RenderCopy(render, textures[TEXTURE_SCREEN], &rectangle, NULL);
						SDL_RenderPresent(render);
					}
				SDL_Delay(F1GP_TIMER_ELAPSE); // 10 FPS.
			}
		}
	}
	

	
	F1GP_Update_Leaderboard();
	Mix_CloseAudio();
	Music_Unload();
	Texture_Unload();
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}
