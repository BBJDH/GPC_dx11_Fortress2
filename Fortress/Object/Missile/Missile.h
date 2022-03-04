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
		In_Air, Collide, Delete
	};
	enum class Type
	{
		Single_Hit, Multiple_Hit
	};
protected:
	Engine::Rendering::Animation::Component animation;
	State		state;
	Type		type;
	Effect::Type	effect_type;
	_float2	 bomb_range;
	float	 ani_playtime;
	int 	damage;
	int		hit_count;
	int const hit_limit;



protected:
	virtual void ani_set();
	//void ani_set_boom();

public:
	Missile(_float2 const& pos, unsigned const width, unsigned const height,
		Effect::Type const effect_type, Type const type = Type::Single_Hit, int const hit_limit = 1 );
	Missile(_float2 const& pos, unsigned const width, unsigned const height,
		_float2 const& missile_range, int const dagame, Effect::Type const effect_type, Type const type = Type::Single_Hit, int const hit_limit = 1);
	virtual ~Missile() = default;
	Missile & operator=(Missile const& other_miss);
	float const get_range_w()const;
	int const get_damage()const;
	State get_state()const;
	Type get_type()const;
	Effect::Type get_effect_type()const;
	virtual void check_state();					//�̻��Ͽ� ���� �ٴ���Ʈ �� ��Ŀ���� �ٸ�
	void boom(HDC const& hmapdc);
	virtual void ani_render(float const delta); //�̻��Ͽ� ���� �������ʿ�
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