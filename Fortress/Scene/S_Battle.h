#pragma once


class S_Battle final : public Scene
{
private:
    Engine::Rendering::Image::Component Background;
    Engine::Rendering::Image::Component Map;
    Engine::Rendering::Image::UI UI_Back;
    Engine::Rendering::Image::UI UI_Front;
    Engine::Rendering::Camera Camera;
    Engine::Rendering::Text::Component debug_mouse_x;


private:
    void    rendering();

public:
    void     Start() final override;
    Scene * Update() final override;
    void       End() final override;



};