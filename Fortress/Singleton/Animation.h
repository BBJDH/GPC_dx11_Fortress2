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
	Engine::Rendering::Animation::Component ani_tank;
	Engine::Rendering::Animation::Component ani_missile;


	void initialize();
	void set_tank_normal();
	void set_tank_steady();
	void set_tank_fire();
	void set_tank_move();
	void set_tank_stop();
	void set_tank_fall();
	void set_tank_dead();
	void render_object(Object const& obj, Obj_Type const type);
	void render_tank(Tank const& tank);

public:
	Animation();
	void render_tanks(std::vector<Tank> const& tank);
	void render_missile(std::vector<Missile> const& missile);

};