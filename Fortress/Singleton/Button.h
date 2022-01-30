#pragma once
class Button
{
private:
	Engine::Rendering::Image::UI button_image;


private:

public:
	Button();
	~Button();
	void render();
	bool clicked();


};

