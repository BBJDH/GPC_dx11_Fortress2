#pragma once
#include"SingletonT.h"

class Map_manager : public SingletonT<Map_manager>
{
public:
	HDC hmapdc;
	POINT minimap_loc;
	LONG const MINI_UI_SIZE = 13;
public:
	Map_manager();
	void initialize();
	void render_map();
	void render_minimap();
	void make_crater(POINT const& center, SIZE const & size);
};
