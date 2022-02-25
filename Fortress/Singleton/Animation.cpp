#include "stdafx.h"
#include "Animation.h"

Animation::Animation() :loading_time{ 0 }, background_time{0}
{

    //loading[0].Name = "Animation/Screen/loading_0";
    //loading[1].Name = "Animation/Screen/loading_1";
    //loading[2].Name = "Animation/Screen/loading_2";
    //loading[3].Name = "Animation/Screen/loading_3";
    //loading[4].Name = "Animation/Screen/loading_4";
    //loading[5].Name = "Animation/Screen/loading_5";
    //loading[6].Name = "Animation/Screen/loading_6";
    //loading[7].Name = "Animation/Screen/loading_7";
    //loading[8].Name = "Animation/Screen/loading_8";

    //for (size_t i = 0; i < 8; i++)
    //{
    //    loading[i].Duration = 0.5f;
    //    loading[i].Repeatable = false;
    //    loading[i].Length = Vector<2>(CAM_SIZE_W, CAM_SIZE_H);
    //    loading[i].Location = { 0,0 };
    //}
}
//
//void Animation::render_loading(float const delta)
//{
//    loading_time += delta;
//
//    if(loading_time>4.5f)
//        loading_time =0.0f;
//    else
//    {
//        int const index = static_cast<int>(loading_time/0.5f);
//        loading[index].Render();
//    }
//}

void Animation::render_loading_fade_out(float const delta)
{
    loading_time += delta;

    animation.Name = "Animation/Screen/loading";
    animation.Duration = 0.5f;
    animation.Repeatable = false;
    animation.Playback = loading_time;
    animation.Length = Vector<2>(CAM_SIZE_W, CAM_SIZE_H);
    animation.Location = { 0,0 };
    if (loading_time > 0.5f)
        loading_time = 0.0f;
    else
    {
        animation.Render();
    }
}

void Animation::render_background(_float2 const & position, _float2 const& length, float const delta)
{
    //background_time += delta;
    //int const index = fmod();
    std::string const location = "Animation/Map/" + _Map_manager->name;
    map_animation.Name = location.c_str();
    map_animation.Duration = 2.0f;
    map_animation.Repeatable = true;
    //map_animation.Playback = background_time;
    map_animation.Length = { length.x,length.y };
    map_animation.Location = { position.x,position.y };
    map_animation.Render();
}

float const Animation::get_loading_time()
{
    return loading_time;
}

void Animation::render_tanks(std::vector<Tank> & tank)
{
    if (!tank.empty())
    {
        for (size_t i = 0; i < tank.size(); i++)
        {
            if (i != _Turn->whosturn())
            tank[i].ani_render(Engine::Time::Get::Delta());
        }
        tank[_Turn->whosturn()].ani_render(Engine::Time::Get::Delta());
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

void Animation::render_patterns(std::vector<Patterns> &  patterns)
{
    for (auto iter = patterns.begin(); iter != patterns.end(); iter++)
    {
        iter->render();
    }
}

void Animation::render_arrow(Tank const & tank)
{
    animation.Name = "Animation/UI/arrow";
    animation.Duration = 1.0f;
    animation.Repeatable = true;
    animation.Length = Vector<2>(UI_Arrow_SIZE, UI_Arrow_SIZE);
    animation.Location = { tank.getpos().x - MAPSIZE_W / 2,MAPSIZE_H / 2 - tank.getpos().y+UI_Arrow_Location_H };
    animation.Render();
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
