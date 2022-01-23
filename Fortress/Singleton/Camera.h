#pragma once
#include"SingletonT.h"


class Camera :public SingletonT<Camera>
{
public:

	Position pos;
	Position pos_win;
	unsigned const speed;
	void up();
	void down();
	void left();
	void right();
public:

	Camera();
	~Camera() {};

	void move(Mouse::POS_STATE state);
};

