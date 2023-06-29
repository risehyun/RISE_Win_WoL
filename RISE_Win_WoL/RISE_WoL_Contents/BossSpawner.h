#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "UI_KeyboardF.h"
#include <map>
#include <vector>
#include "Effect_Spawn.h"

class MonsterSpawnData
{
public:
	SpawnType Type = SpawnType::Swordman;
	float4 Pos;
	bool IsEnd = false;
};

class BossSpawner : public GameEngineActor
{
	friend GameEngineActor;

public:
	static int MonsterCount;

	BossSpawner();
	~BossSpawner();

	BossSpawner(const BossSpawner& _Other) = delete;
	BossSpawner(BossSpawner&& _Other) noexcept = delete;
	BossSpawner& operator=(const BossSpawner& _Other) = delete;
	BossSpawner& operator=(BossSpawner&& _Other) noexcept = delete;

	UI_KeyboardF* m_InteractUI;

	GameEngineRenderer* Renderer_Altar;
	GameEngineRenderer* Renderer_ActivationCircle;

	GameEngineRenderer* Renderer_FenceUp;
	GameEngineRenderer* Renderer_FenceDown;
	GameEngineRenderer* Renderer_FenceRight;
	GameEngineRenderer* Renderer_FenceLeft;

	GameEngineCollision* Collsion_Altar;
	GameEngineCollision* Collsion_ActivationCircle;

	GameEngineCollision* Collsion_FenceUp;
	GameEngineCollision* Collsion_FenceDown;
	GameEngineCollision* Collsion_FenceRight;
	GameEngineCollision* Collsion_FenceLeft;

	

private:
	void Start() override;
	void Update(float _Delta) override;

	void MonsterSpawnCheck();

	std::list<std::map<float, std::vector<MonsterSpawnData>>> AllSpawnDatas;

	std::list<std::map<float, std::vector<MonsterSpawnData>>>::iterator CurWave;


	bool IsSpawnStart = false;
	bool IsAllDeathWait = false;


};