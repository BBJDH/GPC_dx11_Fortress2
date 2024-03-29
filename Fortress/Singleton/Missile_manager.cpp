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
    int const width = 20;
    int const height = 20;

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

    //각도, 파워, 애니메이션, 
    switch (tank.get_tank_type())
    {
    case Tank::Tank_Type::Canon:
    {
        switch (tank.get_missile_type())
        {
        case Tank::Missile_Type::Normal:
        {
            missiles.push_back(new Missile("Canon/normal", position, width, height, { 78* RANGE_MUL,65* RANGE_MUL }, 280* DAMAGE_MUL, Effect::Type::Normal_Big));

            missiles.back()->ballistics_initialize(
                angle,
                power * FIRE_MUL);
            missiles.back()->setmyturn(true);
            break;
        }
        case Tank::Missile_Type::Special:
        {
            missiles.push_back(new Missile("Canon/special", position, width, height, { 35 * RANGE_MUL,30 * RANGE_MUL }, 500* DAMAGE_MUL, Effect::Type::Normal_Small));

            missiles.back()->ballistics_initialize(
                angle,
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
            for (int i = 0; i < 3; i++)
            {
                missiles.push_back(new Multi_Hit_Missile("Super/normal", position, width, height, { 45 * RANGE_MUL,40 * RANGE_MUL }, 200*DAMAGE_MUL, 3, Effect::Type::Explosion_Super));
                missiles.back()->ballistics_initialize(
                    angle - static_cast<float>(i),
                    (power + static_cast<float>(i * 3)) * FIRE_MUL);
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
                    missiles.push_back(new Guide_Missile("Super/special", position, width, height, {28 * RANGE_MUL,28 * RANGE_MUL },60 * DAMAGE_MUL, 200, 1000, Effect::Type::Explosion_Missile));
                    missiles.back()->ballistics_initialize(
                        angle - static_cast<float>(i * 2),
                        (power + static_cast<float>(j * 2)) * FIRE_MUL);
                    missiles.back()->setmyturn(true);
                }
            }

            break;
        }
        }
        return;
    }
    case Tank::Tank_Type::Ion_Attacker:
    {
        switch (tank.get_missile_type())
        {
        case Tank::Missile_Type::Normal:
        {
            missiles.push_back(new Missile("Ion_Attacker/normal", position, width, height, { 48 * RANGE_MUL,40 * RANGE_MUL }, 250 * DAMAGE_MUL, Effect::Type::Ion_Normal, Missile::Angle_Type::Angle));
            missiles.back()->ballistics_initialize(
                angle,
                power * FIRE_MUL);
            missiles.back()->setmyturn(true);
            break;
        }
        case Tank::Missile_Type::Special:
        {
            missiles.push_back(new Satellite_Missile("Ion_Attacker/special", position, width, height, { 66 * RANGE_MUL,50 * RANGE_MUL }, 350 * DAMAGE_MUL, Effect::Type::Ion_Normal));
            missiles.back()->ballistics_initialize(
                angle,
                power * FIRE_MUL);
            missiles.back()->setmyturn(true);
            break;
        }
        }
        return;
    }
    case Tank::Tank_Type::Multi_Missile:
    {
        switch (tank.get_missile_type())
        {
        case Tank::Missile_Type::Normal:
        {
            for (int i = 0; i < 3; i++)
            {
                missiles.push_back(new Missile("Multi_Missile/normal", position, width, height, { 45 * RANGE_MUL,35 * RANGE_MUL }, 225 * DAMAGE_MUL, Effect::Type::Explosion_Missile, Missile::Angle_Type::Angle));

                missiles.back()->ballistics_initialize(
                    angle - static_cast<float>(i),
                    (power + static_cast<float>(i * 3)) * FIRE_MUL);
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
                    missiles.push_back(new Missile("Multi_Missile/special", position, width, height, { 28 * RANGE_MUL,20 * RANGE_MUL }, 90 * DAMAGE_MUL, Effect::Type::Missile_Special, Missile::Angle_Type::Angle));
                    missiles.back()->ballistics_initialize(
                        angle - static_cast<float>(i * 2),
                        (power + static_cast<float>(j * 2)) * FIRE_MUL);
                    missiles.back()->setmyturn(true);
                }
            }

            break;
        }
        }
        return;
    }
    case Tank::Tank_Type::Carrot:
    {
        switch (tank.get_missile_type())
        {
        case Tank::Missile_Type::Normal:
        {

                missiles.push_back(new Missile("Carrot/normal", position, width, height, { 60 * RANGE_MUL,50 * RANGE_MUL }, 300 * DAMAGE_MUL, Effect::Type::Missile_Special, Missile::Angle_Type::Angle));
                missiles.back()->ballistics_initialize(angle, power* FIRE_MUL);
                missiles.back()->setmyturn(true);

            break;
        }
        case Tank::Missile_Type::Special:
        {
            for (int i = 0; i < 3; i++)
            {
    
                missiles.push_back(new Missile("Carrot/special", position, width, height, { 40 * RANGE_MUL,32 * RANGE_MUL }, 200 * DAMAGE_MUL, Effect::Type::Missile_Special, Missile::Angle_Type::Angle));
                missiles.back()->ballistics_initialize(
                    angle,
                    (power + static_cast<float>(i * 4)) * FIRE_MUL);
                missiles.back()->setmyturn(true);
    
            }

            break;
        }
        }
        return;
    }
    case Tank::Tank_Type::Missile_Tank:
    {
        switch (tank.get_missile_type())
        {
        case Tank::Missile_Type::Normal:
        {
            missiles.push_back(new Multi_Hit_Missile("Missile_Tank/normal", position, width, height, { 45 * RANGE_MUL,38 * RANGE_MUL }, 350 * DAMAGE_MUL, 4, Effect::Type::Explosion_Missile));

            //missiles.push_back(new Missile("Missile_Tank/normal", position, width, height, { 60,50 }, 300, Effect::Type::Missile_Special, Missile::Angle_Type::Angle));
            missiles.back()->ballistics_initialize(angle, power * FIRE_MUL);
            missiles.back()->setmyturn(true);

            break;
        }
        case Tank::Missile_Type::Special:
        {

            missiles.push_back(new Guide_Missile("Missile_Tank/special", position, width, height, { 32 * RANGE_MUL,32 * RANGE_MUL }, 120 * DAMAGE_MUL, 220, 1000, Effect::Type::Explosion_Missile));

            //missiles.push_back(new Missile("Missile_Tank/special", position, width, height, { 40,32 }, 200, Effect::Type::Missile_Special, Missile::Angle_Type::Angle));
            missiles.back()->ballistics_initialize(angle, power* FIRE_MUL);

            missiles.back()->setmyturn(true);


            break;
        }
        }
        return;
    }
    case Tank::Tank_Type::Secwind:
    {
        switch (tank.get_missile_type())
        {
        case Tank::Missile_Type::Normal:
        {

            missiles.push_back(new Missile("Secwind/normal", position, width, height, { 70 * RANGE_MUL,60 * RANGE_MUL }, 270 * DAMAGE_MUL, Effect::Type::Explosion_Secwind ));
            missiles.back()->ballistics_initialize(angle, power * FIRE_MUL);
            missiles.back()->setmyturn(true);

            break;
        }
        case Tank::Missile_Type::Special:
        {
            missiles.push_back(new R_Missile("Secwind/special", position, width, height, { 45 * RANGE_MUL,40 * RANGE_MUL }, 200 * DAMAGE_MUL, 10, Effect::Type::Explosion_Secwind));
            missiles.back()->ballistics_initialize( angle, power * FIRE_MUL);
            missiles.push_back(new R_Missile("Secwind/special", position, width, height, { 45 * RANGE_MUL,40 * RANGE_MUL }, 200 * DAMAGE_MUL, -10, Effect::Type::Explosion_Secwind));
            missiles.back()->ballistics_initialize(angle, power* FIRE_MUL);

            missiles.back()->setmyturn(true);

            break;
        }
        }
        return;
    }
    case Tank::Tank_Type::Laser:
    {
        switch (tank.get_missile_type())
        {
        case Tank::Missile_Type::Normal:
        {
            missiles.push_back(new Missile("Laser/normal", position, width, height, { 70 * RANGE_MUL,60 * RANGE_MUL }, 270 * DAMAGE_MUL, Effect::Type::Explosion_Laser, Missile::Angle_Type::Angle));
            missiles.back()->ballistics_initialize(angle, power * FIRE_MUL);
            missiles.back()->setmyturn(true);

            break;
        }
        case Tank::Missile_Type::Special:
        {
            missiles.push_back(new R_Missile("Laser/special", position, width, height, { 45 * RANGE_MUL,35 * RANGE_MUL }, 130 * DAMAGE_MUL, 15, Effect::Type::Explosion_Special_Laser));
            missiles.back()->ballistics_initialize(angle, power* FIRE_MUL);
            missiles.push_back(new R_Missile("Laser/special", position, width, height, { 45 * RANGE_MUL,35 * RANGE_MUL }, 130 * DAMAGE_MUL, -15, Effect::Type::Explosion_Special_Laser));
            missiles.back()->ballistics_initialize(angle, power* FIRE_MUL);
            missiles.push_back(new R_Missile("Laser/special", position, width, height, { 45 * RANGE_MUL,35 * RANGE_MUL }, 130 * DAMAGE_MUL, 0, Effect::Type::Explosion_Special_Laser));
            missiles.back()->ballistics_initialize(angle, power* FIRE_MUL);


            missiles.back()->setmyturn(true);
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
