#pragma once
class R_Missile : public Missile
{
private:
	float const sin_mul;
	_float2 center_pos;
public:
	R_Missile(std::string const& name, _float2 const& pos, unsigned const width, unsigned const height,
		_float2 const& missile_range, int const damage, float const sin_mul, Effect::Type const effect_type);
	~R_Missile()override;
	void ballistics_equation(float const delta, float const wind = 0)override;

};

//sin 함수의 값을 y값에 합산한다
//미사일 매니저에서 미사일 갯수에 따라
//(ex 2개면 +1 -1 3개면 +1 0 -1 4개면 +1 +0.5,-0.5, -1) sin에 곱할 수치를 입력