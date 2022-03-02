#pragma once
#include"SingletonT.h"
class Missile_manager :public SingletonT<Missile_manager>
{
public:
    std::string const missile_type[2] = { "normal","special" };
    std::vector<Missile*> missiles;
    //TODO: ������ Ÿ������ ���� �߻�ȭ�� ����

private:
    void create_missile(_float2 const& position, Tank const& tank);
public:
    Missile_manager();
    void create_missiles(_float2 const& position, float const angle, Tank & tank);
    void clear();
};