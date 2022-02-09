#include "stdafx.h"
#include "Map_manager.h"


Map_manager::Map_manager() :minimap_loc{CAM_SIZE_W-MINIMAP_SIZE_W,0}
{
    initialize();
}

void Map_manager::initialize()
{
    HBITMAP hmapbit = static_cast<HBITMAP>(LoadImage
    (
        NULL,
        TEXT("Asset/Image/Map/Sky_M30001800.bmp"),
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
    _Image_manager->render_background();
    Engine::Rendering::Pipeline::HmemDC::Render_map
    (
        hmapdc,
        Transparent_Color,
        {0,0},
        { static_cast<long>(_CAM->pos_win.x), static_cast<long>(_CAM->pos_win.y) },
        { static_cast<int>(CAM_SIZE_W), static_cast<int>(CAM_SIZE_H) }
        //�»���� ������ǥ�� ��������ǥ�� ī�޶� �»�������� ī�޶� �����ŭ ������
    );
    //Map.Render();
}



void Map_manager::render_minimap()
{
    _Image_manager->render_minimap_background();
    Engine::Rendering::Pipeline::HmemDC::Render_minimap
    (
        hmapdc,
        Transparent_Color,
        { minimap_loc.x, minimap_loc.y },
        { MINIMAP_SIZE_W, MINIMAP_SIZE_H},
        127
    );
}

void Map_manager::make_crater(POINT const& center, SIZE const& size)
{
    HBRUSH hNewBrush = CreateSolidBrush(RGB(255,0,255));
    HPEN hNewPen = CreatePen(PS_SOLID, 2, 0xff00ff);
    HBITMAP hOldBmp = static_cast<HBITMAP>(SelectObject(hmapdc, hNewBrush));
    SelectObject(hmapdc, hNewPen);

    Ellipse(hmapdc, center.x-size.cx, center.y-size.cy, center.x+size.cx, center.y+size.cy);

}
