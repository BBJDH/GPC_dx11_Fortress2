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

// TODO:  버튼기능 초기화 함수 재작성, 앞으로 생길버튼을 모아둘 stl 설계
// 버튼 이미지파일들 만들기
// 캐릭터 수, 맵 선택창 만들기,바람구현,휘날리는 애니메이션만들기
// 미사일 여러개 쏘는것 구현하기,
