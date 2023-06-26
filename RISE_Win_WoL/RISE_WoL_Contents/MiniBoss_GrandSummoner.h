#pragma once
#include "Monster.h"

class MiniBoss_GrandSummoner : public Monster
{
public:
	MiniBoss_GrandSummoner();
	~MiniBoss_GrandSummoner();

	MiniBoss_GrandSummoner(const MiniBoss_GrandSummoner& _Other) = delete;
	MiniBoss_GrandSummoner(MiniBoss_GrandSummoner&& _Other) noexcept = delete;
	MiniBoss_GrandSummoner& operator=(const MiniBoss_GrandSummoner& _Other) = delete;
	MiniBoss_GrandSummoner& operator=(MiniBoss_GrandSummoner&& _Other) noexcept = delete;

	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineRenderer* DamageRenderer = nullptr;


protected:
	void StateUpdate(float _Delta);

	void IdleStart();
	void RunStart();
	void AttackStart();
	void DamageStart();
	void DeathStart();

	void IdleUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void AttackUpdate(float _Delta);
	void DamageUpdate(float _Delta);
	void DeathUpdate(float _Delta);


	void ChangeState(MonsterState _State);

	MonsterState State = MonsterState::Max;

	MonsterDir Dir = MonsterDir::Right;
	std::string CurState = "";

	GameEngineCollision* BodyCollsion = nullptr;

	void DirCheck();
	void ChangeAnimationState(const std::string& _StateName);


private:
	GameEngineSoundPlayer EffectPlayer;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void SetInitStat() override;
	void OnDamaged(int _iAttackPower) override;


	/// 아이템 드롭 테스트용
	void DropItem(float4 _DropPos);

	float Speed = 500.0f;


};