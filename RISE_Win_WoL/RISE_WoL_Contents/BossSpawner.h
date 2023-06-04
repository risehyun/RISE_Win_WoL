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

	GameEngineRenderer* Renderer_FenceUp;
	GameEngineRenderer* Renderer_FenceDown;
	GameEngineRenderer* Renderer_FenceRight;
	GameEngineRenderer* Renderer_FenceLeft;

	GameEngineCollision* Collsion;

	GameEngineCollision* Collsion_FenceUp;
	GameEngineCollision* Collsion_FenceDown;
	GameEngineCollision* Collsion_FenceRight;
	GameEngineCollision* Collsion_FenceLeft;




private:
	void Start() override;
	void Update(float _Delta) override;
};
