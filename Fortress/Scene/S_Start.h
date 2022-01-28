#pragma once
class S_Start final : public Scene
{
private:
    Engine::Rendering::Image::UI fortress;
    Engine::Rendering::Image::UI text;

    float       time =0.0f;
    void init_image();
	bool     Enter();
    void render();

public:
    void     Start() final override;
    Scene * Update() final override;
    void       End() final override;

};