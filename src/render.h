SDL_Color s_make_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    SDL_Color c = {r, g, b, a};

    return c;
}

void s_background_color(int n)
{
	s_color c = s_get_color(n);
	SDL_SetRenderDrawColor(sweeet.Renderer, c.r, c.g, c.b, c.a);
	SDL_RenderClear(sweeet.Renderer);
}

void s_print(const char *text, int x, int y, int cn)
{
	s_color c = s_get_color(cn);
	SDL_Color col = s_make_color(c.r, c.g, c.b, c.a);
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(
		sweeet.Font,
		text,
		col
	);

	SDL_Texture* message = SDL_CreateTextureFromSurface(
		sweeet.Renderer,
		surfaceMessage
	);
	
	int tw,th;
	TTF_SizeText(sweeet.Font, text, &tw, &th);

	SDL_Rect message_rect;
	message_rect.x = x;
	message_rect.y = y;
	message_rect.w = tw;
	message_rect.h = th;
	SDL_RenderCopy(sweeet.Renderer, message, NULL, &message_rect);
	SDL_DestroyTexture(message);
	SDL_FreeSurface(surfaceMessage);
}

void s_rect(int x, int y, int w, int h, int cn, int alpha)
{
	SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;

    s_color c = s_get_color(cn);
    SDL_SetRenderDrawColor(sweeet.Renderer,
    	c.r, c.g, c.b, alpha);

    SDL_RenderFillRect(sweeet.Renderer, &r);
}

void s_circ(int _x, int _y, int radius)
{ 
   int x = radius - 1;
   int y = 0;
   int tx = 1;
   int ty = 1;
   int err = tx - (radius << 1); // shifting bits left by 1 effectively
                                 // doubles the value. == tx - diameter
   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(sweeet.Renderer, _x + x, _y - y);
      SDL_RenderDrawPoint(sweeet.Renderer, _x + x, _y + y);
      SDL_RenderDrawPoint(sweeet.Renderer, _x - x, _y - y);
      SDL_RenderDrawPoint(sweeet.Renderer, _x - x, _y + y);
      SDL_RenderDrawPoint(sweeet.Renderer, _x + y, _y - x);
      SDL_RenderDrawPoint(sweeet.Renderer, _x + y, _y + x);
      SDL_RenderDrawPoint(sweeet.Renderer, _x - y, _y - x);
      SDL_RenderDrawPoint(sweeet.Renderer, _x - y, _y + x);

      if (err <= 0)
      {
         y++;
         err += ty;
         ty += 2;
      }
      if (err > 0)
      {
         x--;
         tx += 2;
         err += tx - (radius << 1);
      }
   }
}

int s_get_win_width()
{
	int w, h;
	SDL_GetWindowSize(sweeet.Window, &w, &h);
	return w;
}

int s_get_win_height()
{
	int w, h;
	SDL_GetWindowSize(sweeet.Window, &w, &h);
	return h;
}

s_image s_load_image(const char *path)
{
	//char *fpath = s_get_path(path);
	SDL_Texture *img = NULL;
	img = IMG_LoadTexture(sweeet.Renderer, path);
	if (img == NULL) {
		fprintf(stderr, "Failed to load image: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_Rect rect;
	SDL_QueryTexture(img, NULL, NULL, &rect.w, &rect.h);
	rect.x = 0;
	rect.y = 0;
	s_image im = {img, rect};
	images[NUM_IMAGES] = im;
	NUM_IMAGES++;
	//free(fpath);
	
	return images[NUM_IMAGES-1];
}

s_quad s_new_quad(int xoff, int yoff, int w, int h)
{
	s_quad rect;
	rect.x = xoff;
	rect.y = yoff;
	rect.w = w;
	rect.h = h;
	return rect;
}

void s_draw(s_image img, int x, int y, bool flipped)
{
	img.Rect.x = x;
	img.Rect.y = y;
	if (flipped) {
		SDL_RenderCopyEx(sweeet.Renderer, img.Texture, NULL, &img.Rect, 0, NULL, SDL_FLIP_HORIZONTAL);
	} else {
		if (SDL_RenderCopy(sweeet.Renderer, img.Texture, NULL, &img.Rect) != 0) {
			fprintf(stderr, "Unable to render texture: %s\n", SDL_GetError());
			exit(1);
		}
	}
}

void s_draw_quad(s_image img, int x, int y, bool flipped, s_quad quad)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	SDL_Rect q;
	q.x = quad.x;
	q.y = quad.y;
	q.w = quad.w;
	q.h = quad.h;
	rect.h = quad.h;
	rect.w = quad.w;

	if (flipped) {
		SDL_RenderCopyEx(sweeet.Renderer, img.Texture, &q, &rect, 0, NULL, SDL_FLIP_HORIZONTAL);
	} else {
		if (SDL_RenderCopy(sweeet.Renderer, img.Texture, &q, &rect) != 0) {
			fprintf(stderr, "Unable to render texture: %s\n", SDL_GetError());
			exit(1);
		}
	}
}

int s_text_width(const char *str)
{
	int tw,th;
	TTF_SizeText(sweeet.Font, str, &tw, &th);
	return tw;
}

int s_text_height(const char *str)
{
	int tw,th;
	TTF_SizeText(sweeet.Font, str, &tw, &th);
	return th;
}

void s_scale(int sx, int sy)
{
	if (sx < 1) sx = 1;
	if (sy < 1) sy = 1;
	SDL_RenderSetScale(sweeet.Renderer, sx, sy);
}