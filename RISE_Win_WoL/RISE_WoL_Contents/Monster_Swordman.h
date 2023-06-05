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

	void IdleUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void AttackUpdate(float _Delta);

	void ChanageState(MonsterState State);

	MonsterState State = MonsterState::Max;

	MonsterDir Dir = MonsterDir::Right;
	std::string CurState = "";

	GameEngineCollision* BodyCollsion = nullptr;

	void DirCheck();
	void ChangeAnimationState(const std::string& _StateName);

private:
	void LevelStart() override;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	////////////////////// DebugValue
	float4 LeftCheck = { -50.0f, 0.0f };
	float4 RightCheck = { 50.0f, 0.0f };
	float4 UpCheck = { 0.0f, -50.0f };
	float4 DownCheck = { 0.0f, 50.0f };

};

