#pragma once
#include"SingletonT.h"


class Camera :public SingletonT<Camera>
{
public:
	enum class State 
	{
		Earthquake, Following, Normal
	};

	_float2 pos;
	//_float2 pos0;
	_float2 pos_win;

private:
	State state;
	unsigned const speed;
	unsigned speed_per_frame;
	float earthquake_time;
	bool focus_w;
	bool focus_h;


private:
	void set_speed_per_frame(float const delta);
	bool up(int const scroll);
	bool down(int const scroll);
	bool left(int const scroll);
	bool right(int const scroll);

public:
	Camera();
	~Camera() {};
	State get_state() const;
	void focusing(Object const& obj);
	void focus_on();
	void move(Mouse::POS_STATE state);
	void earthquake_start();
	void earthquake();
	void update();
};

