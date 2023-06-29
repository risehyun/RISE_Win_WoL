#pragma once
#include "Monster.h"
#include "SKILL_ArcherAttack.h"

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
	GameEngineRenderer* DamageRenderer = nullptr;

	SKILL_ArcherAttack* Arrow = nullptr;

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

	float4 DirDeg;

	void DropItem(float4 _DropPos);

	float Speed = 500.0f;


	////////////////////// DebugValue
	float4 LeftCheck = { -50.0f, 0.0f };
	float4 RightCheck = { 50.0f, 0.0f };
	float4 UpCheck = { 0.0f, -50.0f };
	float4 DownCheck = { 0.0f, 50.0f };

};