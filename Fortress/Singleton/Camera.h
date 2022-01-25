#pragma once
#include"SingletonT.h"


class Camera :public SingletonT<Camera>
{

private:
	unsigned const speed;
	bool focus_w;
	bool focus_h;

public:

	Position pos;
	Position pos_win;
	bool focus;

private:
	bool up();
	bool down();
	bool left();
	bool right();

public:
	Camera();
	~Camera() {};

	void focusing(Object const& obj);
	void focus_on();
	void move(Mouse::POS_STATE state);
};

