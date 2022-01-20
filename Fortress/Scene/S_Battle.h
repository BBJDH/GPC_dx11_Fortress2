#pragma once

#include"stdafx.h"

class S_Battle final : public Scene
{
private:
    Engine::Rendering::Image::Component Background;
    Engine::Rendering::Image::Component Map;
    Engine::Rendering::Image::UI UI_Back;
    Engine::Rendering::Image::UI UI_Front;
    Engine::Rendering::Camera Camera;


private:
    void    rendering();

public:
    void     Start() final override;
    Scene * Update() final override;
    void       End() final override;



};