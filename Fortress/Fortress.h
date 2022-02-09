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

// TODO:  텍스트 매니져 만들기 (피격시 데미지 표시)
// 피격 스프라이트 만들고 애니메이션 재생시간동안 텍스트 렌더링 하도록 구현
// 캐릭터 수, 맵 선택창 만들기,바람구현,휘날리는 애니메이션만들기
// 미사일 여러개 쏘는것 구현하기,
