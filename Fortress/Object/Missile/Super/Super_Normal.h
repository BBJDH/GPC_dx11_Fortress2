#pragma once
class Super_Normal : public Missile
{
	//enum class Type 
	//{
	//	Circle, Ellipse
	//};
private:
	float const explosion_time = 0.7f;
private:
	void check_state();
	void ani_set_throw();
	void ani_set_boom();
public:
	Super_Normal(_float2 const& pos, unsigned const width, unsigned const height);

	~Super_Normal()override;
	void ani_render(float const delta)override;
	void ballistics_equation(float const delta, float const wind = 0)override;

};