s_sound s_load_sound(const char *path, bool stream)
{
	if (stream) {
		Mix_Music *mus = Mix_LoadMUS(path);
		music[NUM_MUSIC] = mus;
		s_sound s = { NUM_MUSIC, true };
		sounds[NUM_SOUNDS] = s;
		NUM_MUSIC++;
		NUM_SOUNDS++;
		return sounds[NUM_SOUNDS-1];
	} else {
		// chunk
		Mix_Chunk *chunk = Mix_LoadWAV(path);
		sfx[NUM_SFX] = chunk;
		s_sound s = { NUM_SFX, false };
		sounds[NUM_SOUNDS] = s;
		NUM_SFX++;
		NUM_SOUNDS++;
		return sounds[NUM_SOUNDS-1];
	}
}

void s_play(s_sound s)
{
	if (s.stream) {
		// play music
		Mix_Music *mus = music[s.Snd];
		Mix_PlayMusic(mus, 0);
	} else {
		// play chunk
		Mix_Chunk *chunk = sfx[s.Snd];
		Mix_PlayChannel(-1, chunk, 0);
	}
}