#include "stdafx.h"
#include "Animation.h"

Animation::Animation()
{
    initialize();
}

void Animation::render_loading()
{
    this->loading.Length = Vector<2>(CAM_SIZE_W, CAM_SIZE_H);
    this->loading.Location = { 0,0 };
    this->loading.Render();

}

void Animation::initialize()
{
    arrow.Name = "Animation/UI/arrow";
    arrow.Duration = 1.0f;
    arrow.Repeatable = true;

    loading.Name = "Animation/Screen/loading";
    loading.Duration = 1.0f;
    loading.Repeatable = true;
}


void Animation::render_tanks(std::vector<Tank> & tank)
{
    if (!tank.empty())
    {
        for (size_t i = 0; i < tank.size(); i++)
        {
            tank[i].ani_render(Engine::Time::Get::Delta());
        }
    }
}

void Animation::render_missile(std::vector<Missile> & missile)
{
    if (!missile.empty())
    {
        for (size_t i = 0; i < missile.size(); i++)
        {
            missile[i].ani_render(Engine::Time::Get::Delta());
        }
    }
}

void Animation::render_arrow(Tank const & tank)
{
       this->arrow.Length = Vector<2>(UI_Arrow_SIZE, UI_Arrow_SIZE);
       this->arrow.Location = { tank.getpos().x - MAPSIZE_W / 2,MAPSIZE_H / 2 - tank.getpos().y+UI_Arrow_Location_H };
       this->arrow.Render();
}

void Animation::render(std::vector<Tank>& tank, std::vector<Missile>& missile)
{
    render_tanks(tank);
    render_missile(missile);
    if (_Turn->get_state() == Turnmanager::State::Tank_Turn)
    {
        render_arrow(tank[_Turn->whosturn()]);
    }

}
