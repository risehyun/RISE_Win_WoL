#pragma once
#include "PlayActor.h"

// #include <GameEngineCore/GameEngineActor.h>

enum class PlayerState
{
	Idle,
	Run,
	Attack,
	Skill_ICEBLAST,
	Dash,
	Max, // default
};

enum class PlayerDir
{
	Right,
	Left,
	Up,
	Down,
	Max,
};

class Player : public PlayActor
{

private:
	static Player* MainPlayer;
public:
	static Player* GetMainPlayer()
	{
		return MainPlayer;
	}

public:
	Player();
	~Player();

	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	GameEngineRenderer* MainRenderer = nullptr;

protected:
	void StateUpdate(float _Delta);

	void IdleStart();
	void RunStart();
	void DashStart();

	void AttackStart();
	void Skill_ICEBLAST_Start();



	void IdleUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void DashUpdate(float _Delta);

	void AttackUpdate(float _Delta);

	void Skill_ICEBLAST_Update();

	void ChanageState(PlayerState State);

	PlayerState State = PlayerState::Max;

	PlayerDir Dir = PlayerDir::Right;
	std::string CurState = "";
	void DirCheck();
	void ChangeAnimationState(const std::string& _StateName);

private:
	void LevelStart() override;

	void Start() override;
	void Update(float _Delta) override;
};