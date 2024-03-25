#ifndef MUSIC_H
#define MUSIC_H

#include "CommonHeaders.h"
#include "music.h"

void Music_Load() {
	music_tracks[MUSIC_BACKGROUND] = Mix_LoadWAV("assets/F1GP_BGM.ogg");
	music_tracks[MUSIC_BACKGROUND_LOWCOST] = Mix_LoadWAV("assets/F1GP_BGM_LOWCOST.ogg");
	music_tracks[MUSIC_BUMBLEBEE] = Mix_LoadWAV("assets/F1GP_BUMBLEBEE_SOUND.mp3");
	music_tracks[MUSIC_BUMBLEBEE_RUN] = Mix_LoadWAV("assets/F1GP_BUMBLEBEE_RUN_STEPS_SOUND.mp3");
	music_tracks[MUSIC_BUMBLEBEE_EXPLOSION] = Mix_LoadWAV("assets/F1GP_BUMBLEBEE_EXPLOSION_SOUND.mp3");
	music_tracks[MUSIC_BUMBLEBEE_TRANSFORM] = Mix_LoadWAV("assets/F1GP_BUMBLEBEE_TRANSFORM_SOUND.mp3");
	music_tracks[MUSIC_BUTTON_CLICKED] = Mix_LoadWAV("assets/F1GP_BUTTON_SOUND.mp3");
	music_tracks[MUSIC_CRASH] = Mix_LoadWAV("assets/F1GP_CRASH.ogg");
	music_tracks[MUSIC_GAMEOVER] = Mix_LoadWAV("assets/F1GP_GAMEOVER.ogg");
	music_tracks[MUSIC_GET_BOX] = Mix_LoadWAV("assets/F1GP_GET_BOX.mp3");
}

int Music_Play(MUSIC_TRACK track, int loop) {
	return Mix_PlayChannel( -1, music_tracks[track], loop );
}

void Music_Unload() {
	int i = 0;
	for (; i < MUSIC_MAX; ++i)
		if (music_tracks[i])
			Mix_FreeChunk(music_tracks[i]);
}

#endif