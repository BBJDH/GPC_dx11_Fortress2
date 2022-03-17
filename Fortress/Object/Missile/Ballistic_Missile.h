#pragma once
#pragma once
class Ballistic_Missile : public Missile
{

private:
	void ani_set()override;	//¹Ù²î´Â³»¿ë

public:
	Ballistic_Missile(_float2 const& pos, unsigned const width, unsigned const height);
	~Ballistic_Missile()override;
	void ballistics_equation(float const delta, float const wind = 0)override;

};