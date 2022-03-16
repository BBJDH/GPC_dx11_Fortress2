#pragma once
#include"SingletonT.h"
class Input_manager : public SingletonT<Input_manager>
{
private:
	float interval;
	float const speed = 0.03f;

	void debug_left_button(std::vector<Tank*>& tank);
	void debug_left_button(std::vector<Patterns>& patterns);
	void debug_right_button();

	void key_left(Tank & tank);
	void key_right(Tank & tank);
	void key_up(Tank & tank);
	void key_down(Tank & tank);
	void key_space(Tank & tank,std::vector<Missile*>& missile);
public:
	Input_manager();
	void input(std::vector<Tank*>& tank, std::vector<Missile*>& missile,
		 float const deltha);
	void find_nextstep(HDC const& hmapdc,  Tank & tank,  bool const isright);
	void fire(Tank& tank, std::vector<Missile*>& missile, bool const keyon);
};
