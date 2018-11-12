#include "src/sweeet.h"

clock_t cube_t, dur_t, chibi_t;
char plytime[25] = "Playing for: ";

static struct player_s {
	union {
		s_entity ent;
		s_entity_dynamic dynamic_ent;
	} base;
	s_quad Dance[12];
	s_quad Sprite;
};
struct player_s player;

static struct chibi_s {
	int x;
	int y;
	int Tick;
	int Frame;
	int Step;
	char *State;
	s_image Image;
	s_quad Walk[4];
	s_quad Wink[3];
	s_quad Sprite;
};
struct chibi_s chibi;

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
	player.base.dynamic_ent.Tick = 0;
	player.base.dynamic_ent.Frame = 0;
	player.base.dynamic_ent.Step = 7;
	player.base.dynamic_ent.State = "Dance";
	player.base.dynamic_ent.Image = s_load_image("reimu.png");
	player.Dance[0] = s_new_quad(0, 0, 172, 208);
	player.Dance[1] = s_new_quad(172, 0, 172, 208);
	player.Dance[2] = s_new_quad(344, 0, 172, 208);
	player.Dance[3] = s_new_quad(516, 0, 172, 208);
	player.Dance[4] = s_new_quad(688, 0, 172, 208);
	player.Dance[5] = s_new_quad(860, 0, 172, 208);
	player.Dance[6] = s_new_quad(0, 208, 172, 208);
	player.Dance[7] = s_new_quad(172, 208, 172, 208);
	player.Dance[8] = s_new_quad(344, 208, 172, 208);
	player.Dance[9] = s_new_quad(516, 208, 172, 208);
	player.Dance[10] = s_new_quad(688, 208, 172, 208);
	
	chibi.x = 800;
	chibi.y = 450;
	chibi.Tick = 0;
	chibi.Frame = 0;
	chibi.Step = 11;
	chibi.State = "Walk";
	chibi.Image = s_load_image("chibi.png");
	chibi.Walk[0] = s_new_quad(1110, 0, 185, 189);
	chibi.Walk[1] = s_new_quad(1295, 0, 185, 189);
	chibi.Walk[2] = s_new_quad(1480, 0, 185, 189);
	chibi.Wink[0] = s_new_quad(185, 378, 185, 189);
	chibi.Wink[1] = s_new_quad(370, 378, 160, 189);

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

	// this block handles alternating the frames to 
	// make sprites look like they are moving
	if (strcmp(player.base.dynamic_ent.State, "Dance") == 0) {
		player.base.dynamic_ent.Tick = (player.base.dynamic_ent.Tick+1) % player.base.dynamic_ent.Step;
		if (player.base.dynamic_ent.Tick == 0) {
			player.base.dynamic_ent.Frame = player.base.dynamic_ent.Frame % 11 +1;
			player.Sprite = player.Dance[player.base.dynamic_ent.Frame-1];
		}
	}

	if (strcmp(chibi.State, "Walk") == 0) {
		chibi.Tick = (chibi.Tick+1) % chibi.Step;
		if (chibi.Tick == 0) {
			chibi.Frame = chibi.Frame % 3 +1;
			chibi.Sprite = chibi.Walk[chibi.Frame-1];
		}
	} else if (strcmp(chibi.State, "Wink") == 0) {
		chibi.Tick = (chibi.Tick+1) % chibi.Step;
		if (chibi.Tick == 0) {
			chibi.Frame = chibi.Frame % 2 +1;
			chibi.Sprite = chibi.Wink[chibi.Frame-1];
		}
	}

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

	if (chibi_move && (strcmp(chibi.State, "Wink") != 0)) {
		if (chibi.x > 25) {
			if (clock()+1 > chibi_t) {
				chibi.x--;
				chibi_t = clock();
			}
		} else {
			chibi.State = "Wink";
		}
	}

	if (timer > 33) {
		cube.Stage = 2;
	}

	if (timer > 5) {
		chibi_move = true;
	}
}

static void s_render()
{
	s_background_color(2);
	s_rect(404, 14, 300, 40, 0, 255);
	s_rect(400, 10, 300, 40, 8, 255);
	s_print(plytime, 412, 17, 0);
	s_print(plytime, 410, 15, 7);
	s_draw_quad(player.base.dynamic_ent.Image, 64, 64, false, player.Sprite);
	s_draw_quad(chibi.Image, chibi.x, chibi.y, false, chibi.Sprite);
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