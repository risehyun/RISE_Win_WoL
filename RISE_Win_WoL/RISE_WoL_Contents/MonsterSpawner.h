#pragma once
#include <GameEngineCore/GameEngineActor.h>

class MonsterSpawner : public GameEngineActor
{
	friend GameEngineActor;

public:
	MonsterSpawner();
	~MonsterSpawner();

	MonsterSpawner(const MonsterSpawner& _Other) = delete;
	MonsterSpawner(MonsterSpawner&& _Other) noexcept = delete;
	MonsterSpawner& operator=(const MonsterSpawner& _Other) = delete;
	MonsterSpawner& operator=(MonsterSpawner&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update(float _Delta) override;


};