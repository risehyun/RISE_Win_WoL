#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Spawner_BossTrigger : public GameEngineActor
{
public:
	Spawner_BossTrigger();
	~Spawner_BossTrigger();

	Spawner_BossTrigger(const Spawner_BossTrigger& _Other) = delete;
	Spawner_BossTrigger(Spawner_BossTrigger&& _Other) noexcept = delete;
	Spawner_BossTrigger& operator=(const Spawner_BossTrigger& _Other) = delete;
	Spawner_BossTrigger& operator=(Spawner_BossTrigger&& _Other) noexcept = delete;

	GameEngineCollision* HitCollision = nullptr;

private:

	void Start() override;
	void Update(float _Delta) override;

};

