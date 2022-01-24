#pragma once
#include"SingletonT.h"


class Camera :public SingletonT<Camera>
{
public:

	Position pos;
	Position pos_win;
	unsigned const speed;
	bool focus_w;
	bool focus_h;
	bool up();
	bool down();
	bool left();
	bool right();
	void focusing(Position const & obj_pos);
	void focus_on();
public:

	Camera();
	~Camera() {};

	void move(Mouse::POS_STATE state);
};

