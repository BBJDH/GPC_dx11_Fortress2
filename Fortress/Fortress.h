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

// TODO: �������� �� ����, �ؽ�Ʈ �Ŵ��� �����
// ��������ȭ�鿡�� ��ư������ ����ȭ������ ���ư���
// ĳ���� ��, �� ����â �����,�ٶ�����,�ֳ����� �ִϸ��̼Ǹ����
// �̻��� ������ ��°� �����ϱ�,
