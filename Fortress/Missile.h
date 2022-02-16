#pragma once

class Missile : public Object
{
	//enum class Type 
	//{
	//	Circle, Ellipse
	//};
public:
	enum class State 
	{
		Throw, Boom, Delete
	};
private:
	Engine::Rendering::Animation::Component animation;
	float ani_playtime;

	int const damage;
	State state;
	int const bomb_range_w;
	int const bomb_range_h;
	//Type     explosion_type;

	void check_state();
	void ani_set_throw();
	void ani_set_boom();

public:
	Missile(_float2 const& pos, unsigned const width, unsigned const height);
	Missile & operator=(Missile const& other_miss);
	int const get_range_w()const;
	int const get_damage()const;
	State get_state()const;
	void boom(HDC const& hmapdc);
	void ani_render(float const delta);
	void ani_start();
	void set_state(State const state);

};
//
//�̻��� Ŭ����
//{
//	private:
//	��ǥ
//	����Ÿ��(�� Ÿ�� �ٴ���Ʈ ������Ÿ���� �����α���)
//	���� �ݰ� �ʺ����
//	������
//	�̵�����
//	�߻�ӵ�(�߻� �Ŀ�(��)������, �߷°��ӵ��� ���� ����)
//
//	public:
//	�̵��Լ�(�̵��� ��ǥ)
//	�̵�����Լ�()
//	- ���� �̵��� ��ǥ�� ���, �浹�����̶�� ������ġ�� �̵��� ��ǥ�̸� �̵��Լ� ȣ�� �� �����Լ��� ȣ��
//	�����Լ�(ĳ����Ŭ���� �迭, ĳ���ͼ�)
//	- �浹�� ĳ���͵��� �������Լ� ȣ��, ���������Լ�ȣ��
//
//}