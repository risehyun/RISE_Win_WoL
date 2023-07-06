#pragma once
#include "Monster.h"
#include "SKILL_ArcherAttack.h"
#include "SKILL_ArcherBow.h"

class Monster_Archer : public Monster
{
public:
	Monster_Archer();
	~Monster_Archer();

	Monster_Archer(const Monster_Archer& _Other) = delete;
	Monster_Archer(Monster_Archer&& _Other) noexcept = delete;
	Monster_Archer& operator=(const Monster_Archer& _Other) = delete;
	Monster_Archer& operator=(Monster_Archer&& _Other) noexcept = delete;

	GameEngineRenderer* MainRenderer = nullptr;



	void ChangeState(MonsterState _State);

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



	MonsterState State = MonsterState::Max;

	MonsterDir Dir = MonsterDir::Right;
	std::string CurState = "";

	GameEngineCollision* BodyCollision = nullptr;
	GameEngineCollision* AttackRangeCollision = nullptr;

	SKILL_ArcherBow* NewBow = nullptr;

	void DirCheck();
	void ChangeAnimationState(const std::string& _StateName);


private:

	float cooldown = 2.0f;
	float currentCooldown = 0.0f;

	void UpdateCooldown(float deltaTime)
	{
		if (currentCooldown > 0)
		{
			currentCooldown -= deltaTime;
		}
	}

	bool IsReady()
	{
		return currentCooldown <= 0;
	}



	GameEngineSoundPlayer EffectPlayer;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void SetInitStat() override;
	void OnDamaged(int _iAttackPower) override;

	float4 DirDeg;

	void DropItem(float4 _DropPos);

	float Speed = 500.0f;


	////////////////////// DebugValue
	float4 LeftCheck = { -50.0f, 0.0f };
	float4 RightCheck = { 50.0f, 0.0f };
	float4 UpCheck = { 0.0f, -50.0f };
	float4 DownCheck = { 0.0f, 50.0f };

};