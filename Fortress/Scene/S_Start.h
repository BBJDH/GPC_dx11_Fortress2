#pragma once
class S_Start final : public Scene
{
private:

    float const speed_x = 0.03f;
    float const speed_y = 0.01f;
    float const speed_time = 3.0f;

    float text_width ;
    float text_height;
    float time;
	
    
    bool     Enter();
    void render_text();
    void    render();

public:
    void     Start() final override;
    Scene * Update() final override;
    void       End() final override;

};