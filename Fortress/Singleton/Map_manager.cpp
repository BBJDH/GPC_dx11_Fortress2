#include "stdafx.h"
#include "Map_manager.h"


Map_manager::Map_manager() :minimap_loc{CAM_SIZE_W-MINIMAP_SIZE_W,0},
name{"sky"}
{
    //initialize();
}

void Map_manager::initialize()
{
    name = _Button->get_map_name();
    std::string const location = "Asset/Image/Map/"+ name +".bmp";
    HBITMAP hmapbit = static_cast<HBITMAP>(LoadImage
    (
        NULL,
        TEXT(location.c_str()),
        //TEXT("Asset/Image/Map/Friends_M30001800.bmp"),
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

    //x, y ��ǥ�� (��ü �������� ũ�� - ķ������)/2�� ���밪 ��ŭ �¿�� �̵�
    //���� ���� �̵��� �ۼ�Ʈ��
    //���� �̵� ��Į������ ���ؼ� (������ �� ���� ������ ķ�� ����ٴϸ� ������)
    //������ (���� ũ�� - ķũ��)/2 ��ŭ �¿�� �����δ�
    //���ٰ��� ����
    
    
    //���� �߻���
    //������ ī�޶� ����ٴϸ� ����, ������ ����� ������ ��鸮�°����� ���̰�
    //_float2  pos;
    //if (_CAM->get_state() == Camera::State::Earthquake)
    //    pos = _CAM->pos0;
    //else
    //    pos = _CAM->pos;
    //_float2 const move_max = { (BackgroundSIZE_W - CAM_SIZE_W) / 2 , (BackgroundSIZE_H - CAM_SIZE_H) / 2 };
    ////xy ��� �߾� 0,0 ���ϴ� -860,-670 ���ϴ� 860 -670 ���� 860 540
    //_float2 move_mul = { pos.x / ((MAPSIZE_W - CAM_SIZE_W) / 2) , pos.y / ((MAPSIZE_H - CAM_SIZE_H) / 2) };

    //if (_CAM->get_state() == Camera::State::Earthquake)
    //{
    //    _Anime->render_background({ pos.x + (_CAM->pos.x - _CAM->pos0.x), pos.y + (_CAM->pos.y - _CAM->pos0.y) }, { BackgroundSIZE_W,BackgroundSIZE_H }, Engine::Time::Get::Delta());

    //}
    //else
    //{
    //    if (move_mul.y < -1.0f)
    //        move_mul.y = -1.0f; //ui ���������� ������ ������� ����

    //    _Anime->render_background({ pos.x - move_max.x* move_mul.x,pos.y - move_max.y * move_mul.y }, { BackgroundSIZE_W,BackgroundSIZE_H }, Engine::Time::Get::Delta());
    //}


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



void Map_manager::render_minimap(std::vector<Tank> const& tank)
{
    _Image_manager->render_minimap_background();
    Engine::Rendering::Pipeline::HmemDC::Render_minimap
    (
        hmapdc,
        Transparent_Color,
        { minimap_loc.x, minimap_loc.y },
        { MINIMAP_SIZE_W, MINIMAP_SIZE_H+ MINI_UI_SIZE },
        127
    );
    _Image_manager->render_minimap_tank(tank);
    _Image_manager->render_minimap_cambox();

}

void Map_manager::make_crater(POINT const& center, SIZE const& size)
{
    HBRUSH hNewBrush = CreateSolidBrush(RGB(255,0,255));
    HPEN hNewPen = CreatePen(PS_SOLID, 2, 0xff00ff);
    HBITMAP hOldBmp = static_cast<HBITMAP>(SelectObject(hmapdc, hNewBrush));
    SelectObject(hmapdc, hNewPen);

    Ellipse(hmapdc, center.x-size.cx, center.y-size.cy, center.x+size.cx, center.y+size.cy);

}
