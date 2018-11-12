typedef struct {
	uint32_t x;
	uint32_t y;
} s_entity;

typedef struct {
	uint8_t Tick;
	uint8_t Frame;
	uint8_t Step;
	char *State;
	s_image Image;
	union {
		s_entity entity;
	} base;
} s_entity_dynamic;