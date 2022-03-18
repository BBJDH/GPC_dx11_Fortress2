#pragma once
class Satellite_Missile : public Missile
{
	enum class Satellite_State
	{
		Initialize, Move, Active, Launch
	};
private:
	Satellite_State satellite_state;
	void check_state()override;
	_float2 target_point;
	float animate_time;
	float const satellite_speed = 500;
public:
	Satellite_Missile(std::string const& name, _float2 const& pos, unsigned const width, unsigned const height,
		_float2 const& missile_range, int const damage, Effect::Type const effect_type);
	~Satellite_Missile()override;
	void ballistics_equation(float const delta, float const wind = 0)override;

};
//충돌지점 y좌표 조정 위성소환
//위성 애니메이션

// 위성소환을 check_state에서 할지 방정식 함수에서 케이스로 나누어 이동계산을 할지
//  고민/결정 해야함
// 이동하는동안 별도 위성_이동 애니메이션 재생, 정지 후 위성_작동 애니메이션 내보냄 
//레이저는 이펙트로 처리, 레이저 종료후 폭발 이펙트 생성 및 delete로 넘어감
// 
// 알고리즘 정리
// Initialize
// 목표 좌표 저장, 위성 위치 설정 및 애니메이션 설정
// 
// 미사일 충돌시
// 위성위치로부터 타겟 포인트까지 x좌표 고정 y좌표 픽셀 충돌검사
// 충돌 한 픽셀을 ballistics에서 미사일의 pos를 타겟 포인트로 저장
// 이동 상태
// 렌더 애니메이션은 미사일에서 위성_이동 애니메이션으로 변환
// y좌표를 최상단에서 델타식으로 아래 100만큼 하방 이동
// 이동완료 후 Move에서 Active로 전환
// 
// 작동 상태
// 렌더 애니메이션은 위성_작동 애니메이션으로 변환
// active 애니메이션 재생, 활성화 시간 경과 후 재생 중간시간에 Effect 위성 빔 생성
// Launch로 전환
// 
// Launch
// effect 사라진 후(혹은 active 애니메이션이 끝난 후 ) 지형 파괴 및 데미지 부여
//