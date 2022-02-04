#pragma once
class Button
{
public:
	enum class State
	{
		Normal, Collide, Clicked_Up,
	};
	Quadrangle collide_box;
	Engine::Rendering::Image::UI image;
	Engine::Rendering::Image::UI collide_image;
private:
	State state;
	std::function<void(void)> on_click;
	
public:
	Button();
	Button(std::string const& name, std::string const& clicked_name,
		float const location_x, float const location_y,
		float const length_x, float const length_y);
	void check_state();
	void render();
	bool collide()const;
	auto click() const;


};

