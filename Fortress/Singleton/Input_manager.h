#pragma once
#include"SingletonT.h"
class Input_manager : public SingletonT<Input_manager>
{
private:
	float interval = 0;
	float const speed = 0.03f;
public:
	void input(std::vector<Tank>& tank, std::vector<Missile>& missile, float const deltha);
	void find_nextstep(HDC const& hmapdc,  Tank & tank,  bool const isright);
	void fire(Tank& tank, std::vector<Missile>& missile, bool const keyon);
};
