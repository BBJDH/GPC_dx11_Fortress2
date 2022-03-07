#pragma once
#include"SingletonT.h"
class Missile_manager :public SingletonT<Missile_manager>
{
public:



    std::string const missile_type[2] = { "normal","special" };
    std::vector<Missile*> missiles;

private:
    void create_missile(Tank const& tank);
public:
    Missile_manager();
    ~Missile_manager();
    void create_missiles(Tank & tank);
    void del_missile(Missile const * missile);
    void clear();
};