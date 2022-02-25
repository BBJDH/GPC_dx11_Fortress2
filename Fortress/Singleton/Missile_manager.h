#pragma once
#include"SingletonT.h"
class Missile_manager :public SingletonT<Missile_manager>
{
public:
    std::vector<Missile> missiles;


private:
public:
    Missile_manager();
    void clear();
};