#pragma once

#include "Engine/Rendering.h"

#include "Scene.h"

class Stage2 : public Scene
{
public:
    void     Start() final override;
    Scene * Update() final override;
    void       End() final override;

private:
    Engine::Rendering::Image::Component Background;

    class Actor * Sonic = nullptr;
};