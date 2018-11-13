void s_init(s_window *win)
{
    if (TTF_Init() == -1) {
        fprintf(stderr, "TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }

    sweeet.Font = TTF_OpenFont("font.ttf", 32);
    if (sweeet.Font == NULL) {
        fprintf(stderr, "There was a problem opening the font: %s\n", TTF_GetError());
        exit(3);
    }

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0) {
        if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
            fprintf(stderr, "Failed to initialise SDL_Image: %s\n", SDL_GetError());
            exit(4);
        }

        int flags = 0;
        if (win->fullscreen)
            flags = SDL_WINDOW_FULLSCREEN;

        printf("sweeet initialized\n");
        sweeet.Window = SDL_CreateWindow(
            win->title,
            win->x,
            win->y,
            win->w,
            win->h,
            flags
        );

        if (sweeet.Window != NULL) {
            sweeet.Renderer = SDL_CreateRenderer(sweeet.Window, -1, SDL_RENDERER_SOFTWARE);
            
            if (sweeet.Renderer != NULL) {
                SDL_SetRenderDrawColor(sweeet.Renderer, 0, 0, 0, 255);
                SDL_SetRenderDrawBlendMode(sweeet.Renderer, SDL_BLENDMODE_BLEND);
            } else {
                perror("Failed to create renderer");
                exit(1);
            }
        } else {
            perror("Failed to create window");
            exit(1);
        }

        // if we made it this far then we're good to go
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
            fprintf(stderr, "Failed to open audio channel\n");
            exit(1);
        }

        s_ent_mgr_init();
        sweeet.Running = true;

        // set the initial color
        s_color c = s_get_color(0);
        SDL_SetRenderDrawColor(sweeet.Renderer, c.r, c.g, c.b, c.a);

        // start main loop
        s_load();
        s_game_loop();
    }
}