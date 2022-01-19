#include <Windows.h>

#include "Stage1.h"
#include "Stage2.h"

#include "Engine/Input.h"
#include "Player.h"

void Stage1::Start()
{
    {
        Free.Skin.Name     = "Image/Free";
        Free.Skin.Length   = Vector<2>(500, 500) / 2;
        Free.Skin.Location = Vector<2>(320, 180);

        Free.Body.Radius = Free.Skin.Length[0] / 2;
        Free.Body.Center = Point(Free.Skin.Location[0], Free.Skin.Location[1]);
    }
    {
        Background.Name = "Image/Celadon";

        Background.Length = Vector<2>(960, 703) * 4;
    }
    {
        Sonic = new Player;

        Sonic->Start();
    }
    {
        Sentence.Text = "¾È³çÇÏ¼¼¿ä.";

        Sentence.Font.Name = "³ª´®¼Õ±Û¾¾ º×";
        Sentence.Font.Size = 100;
        Sentence.Font.Bold = true;
        Sentence.Font.Italic = true;
        Sentence.Font.Underlined = true;
        Sentence.Font.StructOut = true;

        Sentence.Color.Red = 0;
        Sentence.Color.Blue = 0;
        Sentence.Color.Green = 0;

        Sentence.Length = { 350, 150 };
        Sentence.Location = { 1000, 360 };

    }
}

Scene * Stage1::Update()
{
    using namespace Engine;

    Background.Render();

    Physics::Component<Point> const cursor(Point((float)Input::Get::Cursor::X(), (float)Input::Get::Cursor::Y()));

    Free.Skin.Render();

    Sonic->Update();

    Sentence.Render();

    if(Input::Get::Key::Press(VK_RBUTTON)) return new Stage2;
    else                                   return nullptr;
}

void Stage1::End()
{
    Sonic->End();

    delete Sonic;
}