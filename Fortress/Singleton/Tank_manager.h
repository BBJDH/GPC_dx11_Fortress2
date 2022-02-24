#pragma once
#include"SingletonT.h"
class Tank_manager :public SingletonT<Tank_manager>
{
public:
    std::vector<Tank> tanks;

private:
public:
    Tank_manager();
    void create_tanks();
    void clear();
};