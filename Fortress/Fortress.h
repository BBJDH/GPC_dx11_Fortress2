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

// TODO: 게임종료 씬 띄우기, 텍스트 매니져 만들기
// 게임종료화면에서 버튼누르면 시작화면으로 돌아가기
// 캐릭터 수, 맵 선택창 만들기,바람구현,휘날리는 애니메이션만들기
// 미사일 여러개 쏘는것 구현하기,
