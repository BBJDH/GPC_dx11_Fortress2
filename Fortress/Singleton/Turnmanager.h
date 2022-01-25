#pragma once
#include"SingletonT.h"
#include"Random.h"
class Turnmanager :public SingletonT<Turnmanager>
{
private:
	Random rand;
	unsigned index;
	bool is_obj_turn(Object const & obj);
	bool is_tank_turn(std::vector<Tank>& tank);
	bool check_tank_falling(std::vector<Tank>& tank);
	bool is_missile_turn(std::vector<Missile>& missile);
	void rerand();
public:
	//�� �÷��̾�� �̻����� ���� ���������� 
	//�����÷��̾��� ���� ���ش�
	//�̻����� ���� ��ũ �̻��� �߻�� ������ ���������
	void tankturn_start(std::vector<Tank>& tank);
	unsigned const whosturn();
	void checkturn(std::vector<Tank> & tank, std::vector<Missile> & missile);
	Turnmanager();
	~Turnmanager();

};
