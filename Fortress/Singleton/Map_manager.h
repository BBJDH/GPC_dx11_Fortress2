#pragma once
#include"SingletonT.h"

class Map_manager : public SingletonT<Map_manager>
{
public:
	HDC hmapdc;

public:
	void initialize();
	void render_map();
	void make_crater(POINT const& center, SIZE const & size);

};
