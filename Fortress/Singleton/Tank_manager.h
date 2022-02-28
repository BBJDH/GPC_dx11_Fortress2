#pragma once
#include"SingletonT.h"
class Tank_manager :public SingletonT<Tank_manager>
{
public:
    enum class Tank_Name
    {
        Canon,Super
    };
    std::string const tank_name[12] = { "canon","super", };

    std::vector<Tank> tanks;
    
private:
    void create_tank(std::string const & tank_name);
public:
    Tank_manager();
    void create_tanks();
    void clear();
};