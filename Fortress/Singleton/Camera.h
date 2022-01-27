#pragma once
#include"SingletonT.h"


class Camera :public SingletonT<Camera>
{
	// TODO : sin(t * 10.0f) * pow(0.5f,t) 지진효과가 되는지 테스트
public:
	enum class State 
	{
		Earthquake, Following, Normal
	};

	Position pos;
	Position pos_win;


private:
	State state;
	unsigned const speed;
	float earthquake_time;
	bool focus_w;
	bool focus_h;


private:
	bool up(int const scroll);
	bool down(int const scroll);
	bool left(int const scroll);
	bool right(int const scroll);

public:
	Camera();
	~Camera() {};

	void focusing(Object const& obj);
	void focus_on();
	void move(Mouse::POS_STATE state);
	void earthquake_start();
	void earthquake();
	void cam();
};

