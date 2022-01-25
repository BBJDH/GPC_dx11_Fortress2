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

public:
	Animation();
	void initialize();
	void render_object(Object const& obj, Obj_Type const type);
	void render_tank(std::vector<Tank> const& tank);
	void render_missile(std::vector<Missile> const& missile);

};