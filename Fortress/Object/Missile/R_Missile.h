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

//sin �Լ��� ���� y���� �ջ��Ѵ�
//�̻��� �Ŵ������� �̻��� ������ ����
//(ex 2���� +1 -1 3���� +1 0 -1 4���� +1 +0.5,-0.5, -1) sin�� ���� ��ġ�� �Է�