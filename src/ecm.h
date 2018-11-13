
typedef struct {
	uint32_t x;
	uint32_t y;
	// dynamic ents
	uint8_t Tick;
	uint8_t Frame;
	uint8_t Step;
	s_quad States[15][15];
	int8_t State;
	s_quad Sprite;
	s_image Image;
} s_entity;

typedef struct {
	s_entity *entities[250];
	void (*add)(s_entity *ent);
	void (*tick)();
	uint8_t num_ents;
} _s_ent_mgr;

_s_ent_mgr s_ent_mgr;

void s_ent_mgr_add(s_entity *ent)
{
	s_ent_mgr.entities[s_ent_mgr.num_ents] = ent;
	s_ent_mgr.num_ents++;
}

void s_ent_mgr_tick()
{
	uint8_t i;
	for (i = 0; i < s_ent_mgr.num_ents; i++) {
		// make sure we have a valid animated object
		if (s_ent_mgr.entities[i]->State != -1) {
			s_ent_mgr.entities[i]->Tick = (s_ent_mgr.entities[i]->Tick+1) % s_ent_mgr.entities[i]->Step;
			if (s_ent_mgr.entities[i]->Tick == 0) {
				s_ent_mgr.entities[i]->Frame = s_ent_mgr.entities[i]->Frame % 11 +1;
				s_ent_mgr.entities[i]->Sprite = s_ent_mgr.entities[i]->
					States[s_ent_mgr.entities[i]->State][s_ent_mgr.entities[i]->Frame-1];
			}
		}
	}
}

void s_ent_mgr_init()
{
	s_ent_mgr.num_ents = 0;
    s_ent_mgr.add = &s_ent_mgr_add;
    s_ent_mgr.tick = &s_ent_mgr_tick;
}
