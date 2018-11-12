s_color colors[MAX_PALETTES][MAX_COLORS] = {
	// DB 16
	{
		{20, 12, 28, 255}, // black (0)
		{222, 238, 214, 255}, // white (1)
		{68, 36, 52, 255}, // dark red (2)
		{48, 52, 109, 255}, // dark blue (3)
		{78, 74, 78, 255}, // dark gray (4)
		{133, 76, 48, 255}, // brown (5)
		{52, 101, 36, 255}, // dark green (6)
		{208, 70, 72, 255}, // red (7)
		{117, 113, 97, 255}, // light gray (8)
		{89, 125, 206, 255}, // light blue (9)
		{210, 125, 44, 255}, // orange (10)
		{133, 149, 161, 255}, // blue gray (11)
		{109, 170, 44, 255}, // light green (12)
		{210, 170, 153, 255}, // peach (13)
		{109, 194, 202, 255}, // cyan (14)
		{218, 212, 94, 255} // yellow (15)
	},

	// PICO-8
	{
		{0, 0, 0, 255}, // black (0)
		{29, 43, 83, 255}, // dark blue (1)
		{126, 37, 83, 255}, // dark purple (2)
		{0, 135, 81, 255}, // dark green (3)
		{171, 82, 54, 255}, // brown (4)
		{95, 87, 79, 255}, // dark gray (5)
		{194, 195, 199, 255}, // light gray (6)
		{255, 241, 232, 255}, // white (7)
		{255, 0, 77, 255}, // red (8)
		{255, 163, 0, 255}, // orange (9)
		{255, 236, 39, 255}, // yellow (10)
		{0, 228, 54, 255}, // green (11)
		{41, 173, 255, 255}, // blue (12)
		{131, 118, 156, 255}, // indigo (13)
		{255, 119, 168, 255}, // pink (14)
		{255, 204, 170, 255} // peach (15)
	}
};

s_color s_get_color(int n)
{
	if (n > MAX_COLORS || n < 0) {
		return colors[sweeet.Palette][n];
	}

	return colors[sweeet.Palette][n];
}