#pragma once
class Satellite_Missile : public Missile
{
	enum class State
	{
		Satellite, Ion
	};
private:
	State satellite_state;
	void check_state()override;
public:
	Satellite_Missile(std::string const& name, _float2 const& pos, unsigned const width, unsigned const height,
		_float2 const& missile_range, int const damage, Effect::Type const effect_type);
	~Satellite_Missile()override;

};
//�浹���� y��ǥ ���� ������ȯ
//���� �ִϸ��̼�