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
	enum class Type
	{
		Single_Hit, Multiple_Hit
	};
protected:
	Engine::Rendering::Animation::Component animation;
	State		state;
	Type		type;
	Effect::Type	effect_type;
	_float2	 bomb_range;
	float	 ani_playtime;
	int 	damage;
	int		hit_count;
	int const hit_limit;



protected:
	virtual void ani_set();
	//void ani_set_boom();

public:
	Missile(_float2 const& pos, unsigned const width, unsigned const height,
		Effect::Type const effect_type, Type const type = Type::Single_Hit, int const hit_limit = 1 );
	Missile(_float2 const& pos, unsigned const width, unsigned const height,
		_float2 const& missile_range, int const dagame, Effect::Type const effect_type, Type const type = Type::Single_Hit, int const hit_limit = 1);
	virtual ~Missile() = default;
	Missile & operator=(Missile const& other_miss);
	float const get_range_w()const;
	int const get_damage()const;
	State get_state()const;
	Type get_type()const;
	Effect::Type get_effect_type()const;
	virtual void check_state();					//미사일에 따라 다단히트 등 메커니즘 다름
	void boom(HDC const& hmapdc);
	virtual void ani_render(float const delta); //미사일에 따라 각수정필요
	void ani_start();
	void set_state(State const state);

};
//
//미사일 클래스
//{
//	private:
//	좌표
//	폭발타입(원 타원 다단히트 프로토타입은 원으로구현)
//	폭발 반경 너비높이
//	데미지
//	이동각도
//	발사속도(발사 파워(힘)에따라, 중력가속도에 따라 변동)
//
//	public:
//	이동함수(이동할 좌표)
//	이동계산함수()
//	- 다음 이동할 좌표를 계산, 충돌폭발이라면 폭발위치가 이동할 좌표이며 이동함수 호출 후 폭발함수를 호출
//	폭발함수(캐릭터클래스 배열, 캐릭터수)
//	- 충돌한 캐릭터들의 데미지함수 호출, 낙하판정함수호출
//
//}