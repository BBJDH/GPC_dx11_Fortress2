#pragma once
#include"SingletonT.h"
class Missile_manager :public SingletonT<Missile_manager>
{
public:



    std::string const missile_type[2] = { "normal","special" };
    std::vector<Missile*> missiles;
private:
    float const RANGE_MUL = 1.5f;
    int const DAMAGE_MUL = 2;


private:
    void create_missile(Tank const& tank);
public:
    Missile_manager();
    ~Missile_manager();
    void create_missiles(Tank & tank);
    void del_missile(Missile const * missile);
    void clear();
};