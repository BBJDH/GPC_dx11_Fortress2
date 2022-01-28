#pragma once
class S_Start final : public Scene
{
private:
    Engine::Rendering::Image::UI fortress;
    Engine::Rendering::Image::UI text;

    float text_width;
    float text_height;
    float       time =0.0f;
	
    
    bool     Enter();
    void init_image();
    void render_text();
    void    render();

public:
    void     Start() final override;
    Scene * Update() final override;
    void       End() final override;

};