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
	//Engine::Rendering::Animation::Component loading[8];
	//Engine::Rendering::Animation::Component change_loding;
	Engine::Rendering::Animation::Component animation;
	Engine::Rendering::Animation::Component map_animation;

	float loading_time;
	float background_time;


public:
	Animation();
	float const get_loading_time();
	//void render_loading(float const delta);
	void render_loading_fade_out(float const delta);
	void render_background(_float2 const& position, _float2 const& length, float const delta);
	void render_tanks(std::vector<Tank*> & tank);
	void render_missile(std::vector<Missile*> & missiles);
	void render_effect(std::vector<Effect*> & effects);
	void render_patterns(std::vector<Patterns*> & patterns);
	void render_arrow(Tank const & tank);
	void render(std::vector<Tank*> & tank, std::vector<Missile*> & missile, std::vector<Effect*>& effects);
};