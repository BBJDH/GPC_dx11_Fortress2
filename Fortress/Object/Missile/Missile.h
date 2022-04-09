#pragma once

class Missile : public Object
{
	//enum class Type 
	//{
	//	Circle, Ellipse
	//};
public:
	enum class State 
	{
		In_Air, Collide, Delete
	};
	enum class Hit_Type
	{
		Single_Hit, Multiple_Hit
	};
	enum class Angle_Type
	{
		Non_Angle, Angle
	};
	
protected:
	Engine::Rendering::Animation::Component animation;
	State		state;
	Hit_Type		hit_type;
	Angle_Type		angle_type;
	Effect::Type	effect_type;
	std::string name;
	_float2	 bomb_range;
	float	 ani_playtime;
	int 	damage;
	int		hit_count;
	int const hit_limit;



protected:
	virtual void ani_set();
	//void ani_set_boom();

public:
	//Missile(_float2 const& pos, unsigned const width, unsigned const height,
	//	Effect::Type const effect_type, Type const type = Type::Single_Hit, int const hit_limit = 1 );
	Missile(_float2 const& pos, unsigned const width, unsigned const height,
		_float2 const& missile_range, int const damage, Effect::Type const effect_type, Hit_Type const hit_type = Hit_Type::Single_Hit, int const hit_limit = 1);
	Missile(std::string const & name, _float2 const& pos, unsigned const width, unsigned const height,
		_float2 const& missile_range, int const damage, Effect::Type const effect_type,
		Angle_Type const angle_type = Angle_Type::Non_Angle, Hit_Type const hit_type = Hit_Type::Single_Hit, int const hit_limit = 1);
	
	virtual ~Missile() = default;
	Missile & operator=(Missile const& other_miss);
	float const get_range_w()const;
	int const get_damage()const;
	State get_state()const;
	Hit_Type get_type()const;
	Effect::Type get_effect_type()const;
	virtual void check_state();					//미사일에 따라 다단히트 등 메커니즘 다름
	void ballistics_equation(float const delta, float const wind = 0)override;
	void boom(HDC const& hmapdc);
	virtual void ani_render(float const delta); //미사일에 따라 각수정필요
	void ani_start();
	void set_state(State const state);

};
