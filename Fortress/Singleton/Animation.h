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
	Engine::Rendering::Animation::Component ani_missile;


	void initialize();

	void render_object(Object const& obj, Obj_Type const type);

public:
	Animation();
	void render_tanks(std::vector<Tank> & tank);
	void render_missile(std::vector<Missile> const& missile);

};