#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class PlayerState
{
	Idle,
	Run,
	Attack,
	Max, // default
};

enum class PlayerDir
{
	Right,
	Left,
	Max,
};

class Player : public GameEngineActor
{
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
	void AttackStart();

	void IdleUpdate(float _Delta);
	void RunUpdate(float _Delta);

	void AttackUpdate(float _Delta);

	void ChanageState(PlayerState State);

	PlayerState State = PlayerState::Max;

	PlayerDir Dir = PlayerDir::Right;
	std::string CurState = "";
	void DirCheck();
	void ChangeAnimationState(const std::string& _StateName);

private:
	void Start() override;
	void Update(float _Delta) override;
};