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

	GameEngineRenderer* GetMainRenderer()
	{
		return MainRenderer;
	}


	std::vector<SKILL_MiniBoss_GrandSummoner_Fireball*> AllFireball;
	std::vector<SKILL_MiniBoss_GrandSummoner_Magicball*> AllMagicball;
	std::vector<SKILL_MiniBoss_GrandSummoner_Magicball*> AllMagicorb;

	GameEngineCollision* AttackRangeCollision = nullptr;

	int AttackIndex = -1;

	float4 NextPos;

	float4 DirDeg;

protected:
	void StateUpdate(float _Delta);

	void IdleStart();
	void RunStart();

	void Skill_Fireball_Start();
	void Skill_MagicOrbWallRush_Start();
	void Skill_MagicOrbAssault_Start();

	void DamageStart();
	void DeathStart();
	


	void IdleUpdate(float _Delta);
	void RunUpdate(float _Delta);

	void Skill_Fireball_Update(float _Delta);
	void Skill_MagicOrbWallRush_Update(float _Delta);
	void Skill_MagicOrbAssault_Update(float _Delta);

	void DamageUpdate(float _Delta);
	void DeathUpdate(float _Delta);


	void ChangeState(MiniBossState _State);

	MiniBossState State = MiniBossState::Max;

	MonsterDir Dir = MonsterDir::Right;
	std::string CurState = "";

	GameEngineCollision* BodyCollision = nullptr;

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