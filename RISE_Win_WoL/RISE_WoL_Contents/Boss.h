#pragma once
#include "Monster.h"

class Boss : public Monster
{
public:
	Boss();
	~Boss();

	Boss(const Boss& _Other) = delete;
	Boss(Boss&& _Other) noexcept = delete;
	Boss& operator=(const Boss& _Other) = delete;
	Boss& operator=(Boss&& _Other) noexcept = delete;

	GameEngineRenderer* MainRenderer = nullptr;


	GameEngineRenderer* TestRenderer = nullptr;



	GameEngineRenderer* DamageRenderer = nullptr;

protected:
	//void StateUpdate(float _Delta);

	//void IdleStart();
	//void RunStart();
	//void AttackStart();
	//void DamageStart();
	//void DeathStart();

	//void IdleUpdate(float _Delta);
	//void RunUpdate(float _Delta);
	//void AttackUpdate(float _Delta);
	//void DamageUpdate(float _Delta);
	//void DeathUpdate(float _Delta);


	//void ChanageState(MonsterState State);

	MonsterState State = MonsterState::Max;

	MonsterDir Dir = MonsterDir::Right;
	std::string CurState = "";

	GameEngineCollision* BodyCollsion = nullptr;

	//void DirCheck();
	//void ChangeAnimationState(const std::string & _StateName);
	//void ChangeState(MonsterState _State);

private:
	GameEngineSoundPlayer EffectPlayer;

	//void LevelStart() override;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;



	//void SetInitStat() override;
	//void OnDamaged(int _iAttackPower) override;


	///// 아이템 드롭 테스트용
	//void DropItem(float4 _DropPos);


	//////////////////////// DebugValue
	//float4 LeftCheck = { -50.0f, 0.0f };
	//float4 RightCheck = { 50.0f, 0.0f };
	//float4 UpCheck = { 0.0f, -50.0f };
	//float4 DownCheck = { 0.0f, 50.0f };

	//float fDamageRendererDuration = 0;

};