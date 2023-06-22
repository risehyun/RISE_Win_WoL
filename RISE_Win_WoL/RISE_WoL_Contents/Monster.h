#pragma once
//#include <GameEngineCore/GameEngineActor.h>
#include "PlayActor.h"
#include <GameEnginePlatform/GameEngineSound.h>

enum class MonsterState
{
	Idle,
	Run,
	Attack,
	Damage,
	Death,
	Max,
};

enum class BossState
{
	Idle,
	Run,
	NormalAttack,
	Damage,
	Death,
	Max,
};

enum class MonsterDir
{
	Right,
	Left,
	Up,
	Down,
	Max,
};

class Monster : public PlayActor
{
private:
	static std::list<Monster*> AllMonster;

public:
	static void AllMonsterDeath();

public:
	Monster();
	~Monster();

	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

protected:


private:
	void Start() override;
	void Update(float _Delta) override;

	void SetInitStat() override;
	void OnDamaged(int _iAttackPower) override;


};