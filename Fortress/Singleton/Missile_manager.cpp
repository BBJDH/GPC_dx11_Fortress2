#include "stdafx.h"
#include "Missile_manager.h"

Missile_manager::Missile_manager()
{

}

Missile_manager::~Missile_manager()
{
    clear();
}

void Missile_manager::create_missile( Tank const& tank)
{
    int const width = 15;
    int const height = 15;

    float angle;
    if (tank.get_side() == Tank::Side::Right)
    {
        angle = -tank.getimage_angle() / Radian
            + tank.getangle_min() + tank.getangle();
    }
    else
    {
        angle = (-tank.getimage_angle() / Radian + 180.0f)
            - (tank.getangle_min() + tank.getangle());
    }
    float const power = static_cast<float const>(tank.getpower());
    //60분법으로 받음
    double cosval = cos(angle * Radian);
    double sinval = sin(angle * Radian);
    int min_x = static_cast<int>(width * cosval);
    int min_y = static_cast<int>(height * sinval);

    _float2 const position = { tank.getpos().x + min_x,tank.getpos().y - min_y };


    switch (tank.get_tank_type())
    {
    case Tank::Tank_Type::Canon:
    {
        switch (tank.get_missile_type())
        {
        case Tank::Missile_Type::Normal:
        {
            missiles.push_back(new Canon_Normal(position, width, height));
            missiles.back()->ballistics_initialize(
                angle ,
                power * FIRE_MUL);
            missiles.back()->setmyturn(true);
            break;
        }
        case Tank::Missile_Type::Special:
        {
            missiles.push_back(new Canon_Special(position, width, height));
            missiles.back()->ballistics_initialize(
                angle ,
                power * FIRE_MUL);
            missiles.back()->setmyturn(true);
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
            for (int i=0; i<3; i++)
            {
                missiles.push_back(new Super_Normal(position, width, height));
                missiles.back()->ballistics_initialize(
                    angle-static_cast<float>(i),
                    (power + static_cast<float>(i*4)) * FIRE_MUL);
                missiles.back()->setmyturn(true);
            }
            break;
        }
        case Tank::Missile_Type::Special:
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    missiles.push_back(new Super_Special(position, width, height));
                    missiles.back()->ballistics_initialize(
                        angle - static_cast<float>(i*2 ),
                        (power + static_cast<float>(j*2 )) * FIRE_MUL);
                    missiles.back()->setmyturn(true);
                }
            }
            //missiles.push_back(new Super_Special(position, width, height));
            //missiles.back()->ballistics_initialize(
            //    angle ,
            //    power * FIRE_MUL);
            //missiles.back()->setmyturn(true);
            break;
        }
        }
        return;
    }
    }

}

void Missile_manager::create_missiles(Tank & tank)
{//위치, 각도, 파워, 사이즈

    int const power = tank.getpower();
    tank.set_power_record(power);
    create_missile(tank);

}

void Missile_manager::del_missile(Missile const * missile)
{
    delete missile;
    missile = nullptr;
}

void Missile_manager::clear()
{
    if (!missiles.empty())
    {   
        for (int i = 0; i < missiles.size(); i++)
        {
            if (missiles[i] != nullptr)
            {
                del_missile(missiles[i]);
            }
        }
	    missiles.clear();
	    std::vector<Missile*>().swap(missiles);
    }

}
