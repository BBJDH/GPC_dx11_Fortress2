#pragma once
class Effect : public Object
{
public:
	enum class State
	{
		Playing, Delete
	};
	enum class Type
	{
		Normal_Big, Normal_Small, Explosion_Super, Explosion_Missile,
		Missile_Special, Explosion_Secwind, Explosion_Laser, Explosion_Special_Laser,
		Ion_Normal, Ion_Special, Ion, Satellite_Active,
	};

protected:
	//사운드 여기에 추가
	Engine::Rendering::Animation::Component animation;
	std::string const name;
	State state;
	float playtime;

protected:
public:
	Effect(std::string const & location, _float2 const & position,
		_float2 const& size, float const duration);
	virtual ~Effect()=default;
	void check_state();
	void render();
	State get_state();
};