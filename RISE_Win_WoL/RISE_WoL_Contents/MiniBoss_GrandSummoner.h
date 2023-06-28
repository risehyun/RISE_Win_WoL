#pragma once
#include "Monster.h"
#include "SKILL_MiniBoss_GrandSummoner_Fireball.h"
#include "SKILL_MiniBoss_GrandSummoner_Magicball.h"

#include <vector>

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

	std::vector<SKILL_MiniBoss_GrandSummoner_Fireball*> AllFireball;

	std::vector<SKILL_MiniBoss_GrandSummoner_Magicball*> AllMagicball;


	int AttackIndex = -1;

	float4 NextPos;

protected:
	void StateUpdate(float _Delta);

	void IdleStart();
	void RunStart();

	void Skill_Fireball_Start();
	void Skill_MagicOrbWallRush_Start();

	void DamageStart();
	void DeathStart();
	


	void IdleUpdate(float _Delta);
	void RunUpdate(float _Delta);

	void Skill_Fireball_Update(float _Delta);
	void Skill_MagicOrbWallRush_Update(float _Delta);

	void DamageUpdate(float _Delta);
	void DeathUpdate(float _Delta);


	void ChangeState(MiniBossState _State);

	MiniBossState State = MiniBossState::Max;

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


	/// ������ ��� �׽�Ʈ��
	void DropItem(float4 _DropPos);

	float Speed = 500.0f;


};