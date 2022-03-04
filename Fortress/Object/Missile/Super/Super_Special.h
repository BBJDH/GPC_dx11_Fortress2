#pragma once
class Super_Special : public Missile
{

private:
private:
	//void check_state();
	void ani_set();
	//void ani_set_boom();

public:
	Super_Special(_float2 const& pos, unsigned const width, unsigned const height);
	~Super_Special()override;
	void ani_render(float const delta)override;
	void ballistics_equation(float const delta, float const wind = 0)override;

};