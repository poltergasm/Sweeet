typedef SDL_Rect s_quad;

typedef struct {
	const char *title;
	int x;
	int y;
	int w;
	int h;
	bool fullscreen;
} s_window;

typedef struct {
	int r;
	int g;
	int b;
	int a;
} s_color;

typedef struct {
	SDL_Texture *Texture;
	SDL_Rect Rect;
} s_image;

typedef struct {
	int Snd;
	bool stream;
} s_sound;

// counters
static int NUM_IMAGES = 0;
static int NUM_MUSIC = 0;
static int NUM_SFX = 0;
static int NUM_SOUNDS = 0;
static Mix_Music *music[MAX_MUSIC];
static Mix_Chunk *sfx[MAX_SFX];
s_sound sounds[MAX_SOUNDS];
s_image images[MAX_TEXTURES];

void s_core_render()
{
	SDL_RenderClear(sweeet.Renderer);
	s_render();
	SDL_RenderPresent(sweeet.Renderer);
}

void s_cleanup()
{
	SDL_DestroyWindow(sweeet.Window);
	SDL_DestroyRenderer(sweeet.Renderer);
	int i;
    for (i = 0; i < MAX_TEXTURES; i++) {
    	if (images[i].Texture != NULL) {
    		SDL_DestroyTexture(images[i].Texture);
    	}
    }
    for (i = 0; i < MAX_MUSIC; i++) {
    	if (music[i] != NULL)
    		Mix_FreeMusic(music[i]);
    }
    for (i = 0; i < MAX_SFX; i++) {
    	if (sfx[i] != NULL)
    		Mix_FreeChunk(sfx[i]);
    }
	TTF_CloseFont(sweeet.Font);
	Mix_CloseAudio();
	IMG_Quit();
	SDL_Quit();
	printf("Cleaned up.\n");
}

void s_set_palette(int n) { sweeet.Palette = n; }

void s_game_loop()
{
	const int FPS = 60;
	const int frame_delay = 1000 / FPS;
	uint32_t frame_start;
	int frame_time;

	while (sweeet.Running) {
		frame_start = SDL_GetTicks();
		key_pressed = -1;

		s_handle_events();
		s_tick();
		s_core_render();

		frame_time = SDL_GetTicks() - frame_start;
		if (frame_delay > frame_time) {
			SDL_Delay(frame_delay - frame_time);
		}
	}

	s_cleanup();
}