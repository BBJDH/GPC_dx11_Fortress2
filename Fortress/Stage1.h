#pragma once

#include "Engine/Rendering.h"
#include "Engine/Physics.h"
#include "Engine/Circle.h"

#include "Scene.h"

class Stage1 final : public Scene
{
public:
    void     Start() final override;
    Scene * Update() final override;
    void       End() final override;

private:
    Engine::Rendering::Image::Component Background;

    struct
    {
        Engine::Rendering::Image::UI             Skin;
        Engine::Physics::Component<class Circle> Body;
    }
    Free;

    Engine::Rendering::Text::Component Sentence;

    class Actor * Sonic = nullptr;
};