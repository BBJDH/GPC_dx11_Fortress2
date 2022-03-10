#pragma once
class Super_Special : public Missile
{
public:
public:
	enum class State
	{
		Crusing, Ready, Guide,
	};

private:
	Engine::Rendering::Animation::Component lock_on;
	State state;
	_float2 guide_target;
	float const guide_range;
	float const guide_speed;

private:
	bool check_guide_range();
	void ani_set();

public:
	Super_Special(_float2 const& pos, unsigned const width, unsigned const height);
	~Super_Special()override;
	void ani_render(float const delta)override;
	void ballistics_equation(float const delta, float const wind = 0)override;
};