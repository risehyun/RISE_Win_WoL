#pragma once
#include "Monster.h"

class Monster_Swordman : public Monster
{
public:
	Monster_Swordman();
	~Monster_Swordman();

	Monster_Swordman(const Monster_Swordman& _Other) = delete;
	Monster_Swordman(Monster_Swordman&& _Other) noexcept = delete;
	Monster_Swordman& operator=(const Monster_Swordman& _Other) = delete;
	Monster_Swordman& operator=(Monster_Swordman&& _Other) noexcept = delete;

	GameEngineRenderer* MainRenderer = nullptr;

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

	GameEngineCollision* BodyCollision = nullptr;
	GameEngineCollision* AttackRangeCollision = nullptr;

	void DirCheck();
	void ChangeAnimationState(const std::string& _StateName);

private:
	GameEngineSoundPlayer EffectPlayer;

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

	void LevelStart() override;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;



	void SetInitStat() override;
	void OnDamaged(int _iAttackPower) override;


	/// 아이템 드롭 테스트용
	void DropItem(float4 _DropPos);



	////////////////////// DebugValue
	float4 LeftCheck = { -50.0f, 0.0f };
	float4 RightCheck = { 50.0f, 0.0f };
	float4 UpCheck = { 0.0f, -50.0f };
	float4 DownCheck = { 0.0f, 50.0f };


	


};

