#pragma once
#include"SingletonT.h"



class Animation : public SingletonT<Animation>
{
public:
	enum class Obj_Type
	{
		Tank, Missile, Item
	};
private:
	Engine::Rendering::Animation::Component loading[9];
	Engine::Rendering::Animation::Component arrow;

	float loading_time;


	void initialize();


public:
	Animation();
	float const get_loading_time();
	void render_loading(float const delta);
	void render_tanks(std::vector<Tank> & tank);
	void render_missile(std::vector<Missile> & missile);
	void render_arrow(Tank const & tank);
	void render(std::vector<Tank> & tank, std::vector<Missile> & missile);
};