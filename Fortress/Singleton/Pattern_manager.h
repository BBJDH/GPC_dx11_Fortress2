#pragma once
#include"SingletonT.h"
class Missile_manager :public SingletonT<Missile_manager>
{
public:

    std::vector<Patterns> patterns;


private:
    void create_missile(Tank const& tank);
public:
    Missile_manager();
    ~Missile_manager();
    void create_missiles(Tank& tank);
    void del_missile(Missile const* missile);
    void clear();
};