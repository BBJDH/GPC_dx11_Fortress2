#pragma once
class Guide_Missile : public Missile
{
public:
public:
	enum class State
	{
		Crusing, Ready, Guide,
	};

protected:
	Engine::Rendering::Animation::Component lock_on;
	State state;
	_float2 guide_target;
	float const guide_range;
	float const guide_speed;

private:
	bool check_guide_range();
	virtual void ani_set();

public:
	Guide_Missile(std::string const & name, _float2 const& pos, unsigned const width, unsigned const height,
		_float2 const& missile_range, int const damage, float const guide_range, float const guide_speed, Effect::Type const effect_type);
	~Guide_Missile()override;
	void ani_render(float const delta)override;
	void ballistics_equation(float const delta, float const wind = 0)override;
};