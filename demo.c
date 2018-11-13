#include "src/sweeet.h"

clock_t cube_t, dur_t, chibi_t;
char plytime[25] = "Playing for: ";

static struct player_s {
	union {
		s_entity ent;
	} base;
};
struct player_s player;

static struct cube_s {
	int x;
	int y;
	int w;
	int h;
	int Stage;
	int Color;
};
struct cube_s cube;
bool move_cube = false;
bool chibi_move = false;

static void s_load()
{
	// use the PICO-8 palette
	// the default (0) is DB16
	s_set_palette(1);

	// set up the player
	player.base.ent.x = 64;
	player.base.ent.y = 64;
	player.base.ent.Tick = 0;
	player.base.ent.Frame = 0;
	player.base.ent.Step = 7;
	player.base.ent.State = 0;
	player.base.ent.Image = s_load_image("reimu.png");
	player.base.ent.States[0][0] = s_new_quad(0, 0, 172, 208);
	player.base.ent.States[0][1] = s_new_quad(172, 0, 172, 208);
	player.base.ent.States[0][2] = s_new_quad(344, 0, 172, 208);
	player.base.ent.States[0][3] = s_new_quad(516, 0, 172, 208);
	player.base.ent.States[0][4] = s_new_quad(688, 0, 172, 208);
	player.base.ent.States[0][5] = s_new_quad(860, 0, 172, 208);
	player.base.ent.States[0][6] = s_new_quad(0, 208, 172, 208);
	player.base.ent.States[0][7] = s_new_quad(172, 208, 172, 208);
	player.base.ent.States[0][8] = s_new_quad(344, 208, 172, 208);
	player.base.ent.States[0][9] = s_new_quad(516, 208, 172, 208);
	player.base.ent.States[0][10] = s_new_quad(688, 208, 172, 208);
	s_ent_mgr.add(&player.base.ent);

	// the cube, which is really a square. whatever.
	cube.x = 300;
	cube.y = 300;
	cube.w = 0;
	cube.h = 0;
	cube.Stage = 1;
	cube.Color = 13;

	// play some sick beats
	s_sound itvara_sng = s_load_sound("fractal_itvara.ogg", true);
	s_play(itvara_sng);
}


static void s_tick()
{
	if (clock()+1 > dur_t) {
		dur_t = clock();
		sprintf(plytime, "Playing for: %.2f", (double)dur_t / CLOCKS_PER_SEC);
	}

	s_ent_mgr.tick();

	// yeah, no spectacular easing here so fuck you
	if (move_cube) {
		if (cube.Stage == 1) {
			if (cube.x < 800) {
				if (clock()+0.5 > cube_t && cube.h < 100) {
					cube_t = clock();
					cube.h++;
					cube.w++;
				}

				if (cube.h == 100) {
					if (cube.Color == 13) cube.Color = 12;
					cube.x = cube.x + 10;
				}
			}
		} else if (cube.Stage == 2) {
			if (clock()+0.5 > cube_t) {
				if (cube.x % 2) cube.Color = 3;
				else cube.Color = 11;
				cube.w = 75;
				cube.h = 75;
				cube.x = cube.x - 20;
				cube_t = clock();
			}
		}
	}

	// move the cube when the timer hits a certain point
	clock_t timer = dur_t / CLOCKS_PER_SEC;
	if (timer > 29 && !move_cube) {
		move_cube = true;
	}

	if (timer > 33) {
		cube.Stage = 2;
	}
}

static void s_render()
{
	s_background_color(2);
	s_rect(404, 14, 300, 40, 0, 255);
	s_rect(400, 10, 300, 40, 8, 255);
	s_print(plytime, 412, 17, 0);
	s_print(plytime, 410, 15, 7);
	s_draw_quad(player.base.ent.Image, 64, 64, false, player.base.ent.Sprite);
	s_rect(cube.x, cube.y, cube.w, cube.h, cube.Color, 255);
}

int main(int argc, char *argv[])
{
	s_window Win = {
		.title = "My Sweeet App",
		.x = S_WINDOW_CENTERED,
		.y = S_WINDOW_CENTERED,
		.w = 800,
		.h = 640,
		.fullscreen = false
	};

	s_init(&Win);
	return 0;
}