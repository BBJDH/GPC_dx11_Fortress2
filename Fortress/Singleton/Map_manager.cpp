#include "stdafx.h"
#include "Map_manager.h"


void Map_manager::initialize()
{
    HBITMAP hmapbit = static_cast<HBITMAP>(LoadImage
    (
        NULL,
        TEXT("Asset/Image/Map/Sky_M_ 30001800.bmp"),
        IMAGE_BITMAP,
        0,
        0,
        LR_LOADFROMFILE | LR_DEFAULTSIZE
    ));
    Engine::Rendering::Pipeline::HmemDC::draw_map(hmapbit);
    hmapdc = Engine::Rendering::Pipeline::HmemDC::getdc();
    DeleteObject(hmapbit);

}

void Map_manager::render_map()
{

    Engine::Rendering::Pipeline::HmemDC::Transparents_Color(hmapdc, Transparent_Color,
        {
            static_cast<int>(CAM_SIZE_W), 
            static_cast<int>(CAM_SIZE_H)

        },
        //좌상단을 고정좌표로 윈도우좌표계 카메라 좌상단점부터 카메라 사이즈만큼 가져옴
        {
            static_cast<long>(_CAM->pos_win.x)/*static_cast<long>(-MAPSIZE_W/2)*/,
            static_cast<long>(_CAM->pos_win.y)/*static_cast<long>(-MAPSIZE_H/2)*/
        }
        );
    //Map.Render();
}

void Map_manager::make_crater(POINT const& center, SIZE const& size)
{
    HBRUSH hNewBrush = CreateSolidBrush(RGB(255,0,255));
    HPEN hNewPen = CreatePen(PS_SOLID, 2, 0xff00ff);
    HBITMAP hOldBmp = static_cast<HBITMAP>(SelectObject(hmapdc, hNewBrush));
    SelectObject(hmapdc, hNewPen);

    Ellipse(hmapdc, center.x-size.cx, center.y-size.cy, center.x+size.cx, center.y+size.cy);

}
