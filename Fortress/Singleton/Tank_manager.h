#pragma once
#include"SingletonT.h"
class Tank_manager :public SingletonT<Tank_manager>
{
public:
    std::string const tank_name[12] = { "Canon","Super","Ion_Attacker","Multi_Missile","Carrot","Missile_Tank","Secwind","Laser"};
    std::vector<Tank*> tanks;
    
private:
    void create_tank(_float2 const& position, std::string const& player_name, Tank::Tank_Type const tank_name, Color const color);
    void del_tank(Tank const * tank);

public:
    Tank_manager();
    ~Tank_manager();
    void create_tanks();
    void clear();
};

//
// ��ũ �߰� ����
// ���ο� ��ũ Ŭ���� �ۼ�(��������Ʈ ������ ù�� �빮�� ���� ���� ����, Ŭ���� ���� enumŬ���� ��ũŸ�� ���)
// �̸� �����ϵ� ����� �߰�
// ��ũŬ���� enum Ŭ���� ��� �߰�
// ��ũ �Ŵ��� ���� case �߰�, tank_name �迭�� ���(������) �߰�
// �̻��� ��������Ʈ ������ ù�� �빮�� ���� ���� ���� �ۼ�(����� �߰��Ȱ�� Ŭ���� �ۼ�)
// ���� �̹��� �����ܿ��� �̴� ������ �̹��� �߰�
// �̻��� �Ŵ��� ���� case �߰�
// ===����Ʈ �߰��Ǵ� ���=====
//  ����Ʈ enum Ŭ���� ��� �߰�, ��������Ʈ �۾�
// ����Ʈ �Ŵ��� ���� case �߰�
// 
//