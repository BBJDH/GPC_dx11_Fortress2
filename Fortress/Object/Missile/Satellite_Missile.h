#pragma once
class Satellite_Missile : public Missile
{
	enum class Satellite_State
	{
		Initialize, Move, Active, Launch
	};
private:
	Satellite_State satellite_state;
	void check_state()override;
	_float2 target_point;
	float animate_time;
	float const satellite_speed = 500;
public:
	Satellite_Missile(std::string const& name, _float2 const& pos, unsigned const width, unsigned const height,
		_float2 const& missile_range, int const damage, Effect::Type const effect_type);
	~Satellite_Missile()override;
	void ballistics_equation(float const delta, float const wind = 0)override;

};
//�浹���� y��ǥ ���� ������ȯ
//���� �ִϸ��̼�

// ������ȯ�� check_state���� ���� ������ �Լ����� ���̽��� ������ �̵������ ����
//  ���/���� �ؾ���
// �̵��ϴµ��� ���� ����_�̵� �ִϸ��̼� ���, ���� �� ����_�۵� �ִϸ��̼� ������ 
//�������� ����Ʈ�� ó��, ������ ������ ���� ����Ʈ ���� �� delete�� �Ѿ
// 
// �˰��� ����
// Initialize
// ��ǥ ��ǥ ����, ���� ��ġ ���� �� �ִϸ��̼� ����
// 
// �̻��� �浹��
// ������ġ�κ��� Ÿ�� ����Ʈ���� x��ǥ ���� y��ǥ �ȼ� �浹�˻�
// �浹 �� �ȼ��� ballistics���� �̻����� pos�� Ÿ�� ����Ʈ�� ����
// �̵� ����
// ���� �ִϸ��̼��� �̻��Ͽ��� ����_�̵� �ִϸ��̼����� ��ȯ
// y��ǥ�� �ֻ�ܿ��� ��Ÿ������ �Ʒ� 100��ŭ �Ϲ� �̵�
// �̵��Ϸ� �� Move���� Active�� ��ȯ
// 
// �۵� ����
// ���� �ִϸ��̼��� ����_�۵� �ִϸ��̼����� ��ȯ
// active �ִϸ��̼� ���, Ȱ��ȭ �ð� ��� �� ��� �߰��ð��� Effect ���� �� ����
// Launch�� ��ȯ
// 
// Launch
// effect ����� ��(Ȥ�� active �ִϸ��̼��� ���� �� ) ���� �ı� �� ������ �ο�
//