#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BossSpawner : public GameEngineActor
{
	friend GameEngineActor;

public:
	BossSpawner();
	~BossSpawner();

	BossSpawner(const BossSpawner& _Other) = delete;
	BossSpawner(BossSpawner&& _Other) noexcept = delete;
	BossSpawner& operator=(const BossSpawner& _Other) = delete;
	BossSpawner& operator=(BossSpawner&& _Other) noexcept = delete;

	GameEngineRenderer* MainRenderer;
	GameEngineRenderer* InputRenderer;

	GameEngineCollision* Collsion;



private:
	void Start() override;
	void Update(float _Delta) override;
};

