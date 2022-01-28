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
	Engine::Rendering::Animation::Component loading;
	Engine::Rendering::Animation::Component arrow;


	void initialize();


public:
	Animation();
	void render_loading();
	void render_tanks(std::vector<Tank> & tank);
	void render_missile(std::vector<Missile> & missile);
	void render_arrow(Tank const & tank);
	void render(std::vector<Tank> & tank, std::vector<Missile> & missile);
};