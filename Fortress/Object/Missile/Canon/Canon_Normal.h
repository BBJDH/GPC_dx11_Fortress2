#pragma once
class Canon_Normal : public Missile
{
	//enum class Type 
	//{
	//	Circle, Ellipse
	//};
private:
	float const explosion_time = 1.25f;
private:
	void check_state();
	void ani_set_throw();
	void ani_set_boom();
public:
	Canon_Normal(_float2 const& pos, unsigned const width, unsigned const height);

	~Canon_Normal()override;
	void ani_render(float const delta)override;
};