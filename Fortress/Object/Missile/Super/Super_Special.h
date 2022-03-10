#pragma once
class Super_Special : public Missile
{
public:
public:
	enum class State
	{
		Crusing, Guide,
	};

private:
	State state;
	_float2 guide_target;
	float const guide_range;

private:
	void check_guide_range();

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