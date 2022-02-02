#pragma once
class Button
{
public:
	enum class State
	{
		Normal, Clicked, Clicked_Up,
	};
private:
	State state;
	Quadrangle const collide_box;
	Engine::Rendering::Image::UI image;
	Engine::Rendering::Image::UI clicked_image;


private:

public:
	Button(std::string const& name, std::string const& clicked_name,
		float const location_x, float const location_y,
		float const length_x, float const length_y);
	void check_state();
	void render();
	bool clicked()const;


};

