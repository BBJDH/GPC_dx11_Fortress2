#pragma once

#include"stdafx.h"

class S_Battle final : public Scene
{
public:
    void     Start() final override;
    Scene * Update() final override;
    void       End() final override;

private:
    Engine::Rendering::Image::Component Background;
    Engine::Rendering::Image::Component Map;
    Engine::Rendering::Camera Camera;
};