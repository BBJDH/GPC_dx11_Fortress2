#pragma once
#include"SingletonT.h"
class Tank_manager :public SingletonT<Tank_manager>
{
public:
    std::string const tank_name[12] = { "Canon","Super", };
    std::vector<Tank*> tanks;
    
private:
    void create_tank(_float2 const& position, std::string const& player_name, Tank::Tank_Type const tank_name, Color const color);

public:
    Tank_manager();
    ~Tank_manager();
    void create_tanks();
    void clear();
};