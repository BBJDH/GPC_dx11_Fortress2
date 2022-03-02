#pragma once
class Super_Special : public Missile
{

private:
	float const explosion_time = 0.7f;
private:
	void check_state();
	void ani_set_throw();
	void ani_set_boom();

public:
	Super_Special(_float2 const& pos, unsigned const width, unsigned const height);
	~Super_Special()override;
	void ani_render(float const delta)override;
	void ballistics_equation(float const delta, float const wind = 0)override;

};