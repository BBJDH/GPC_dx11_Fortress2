#pragma once
class Canon_Special : public Missile
{

private:
	float const explosion_time = 1.25f;
private:
	void check_state();
	void ani_set_throw();
	void ani_set_boom();

public:
	Canon_Special(_float2 const& pos, unsigned const width, unsigned const height);
	~Canon_Special()override;
	void ani_render(float const delta)override;
};