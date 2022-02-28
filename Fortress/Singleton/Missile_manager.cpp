#include "stdafx.h"
#include "Missile_manager.h"

Missile_manager::Missile_manager()
{

}

void Missile_manager::create_missile(_float2 const& position, Tank const& tank)
{
    int const width = 31;
    int const height = 33;
    switch (tank.get_tank_type())
    {
    case Tank::Tank_Type::Canon:
    {
        switch (tank.get_missile_type())
        {
        case Tank::Missile_Type::Normal:
        {
            missiles.push_back(new Canon_Normal(position, width, height));
            break;
        }
        case Tank::Missile_Type::Special:
        {
            missiles.push_back(new Canon_Special(position, width, height));
            break;
        }
        }
        return;
    }
    case Tank::Tank_Type::Super:
    {
        switch (tank.get_missile_type())
        {
        case Tank::Missile_Type::Normal:
        {
            missiles.push_back(new Canon_Normal(position, width, height));
            break;
        }
        case Tank::Missile_Type::Special:
        {
            missiles.push_back(new Canon_Normal(position, width, height));
            break;
        }
        }
        return;
    }
    }

}

void Missile_manager::create_missiles(_float2 const & position, float const angle, Tank & tank)
{//위치, 각도, 파워, 사이즈

    int const power = tank.getpower();
    tank.set_power_record(power);
    create_missile(position, tank);
    missiles.back()->ballistics_initialize(
        angle,
        static_cast<float const>(tank.getpower() * FIRE_MUL));
    missiles.back()->setmyturn(true);
}

void Missile_manager::clear()
{
	missiles.clear();
	std::vector<Missile*>().swap(missiles);
}
