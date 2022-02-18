#pragma once


class Fortress final : public Engine::Game
{
public:
    void  Start() final override;
    void Update() final override;
    void    End() final override;

private:
    class Scene * Now = nullptr;
};

// TODO:  
// 플레이어셋 맵으로 변경? 선택한 플레이어의 이름 정렬 필요
// 캐릭터 수, 맵 선택창 만들기,바람구현,휘날리는 애니메이션만들기
// 미사일 여러개 쏘는것 구현하기,
