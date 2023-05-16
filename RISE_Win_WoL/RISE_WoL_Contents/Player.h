#pragma once
#include <GameEngineCore/GameEngineActor.h>

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

private:
	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;
};