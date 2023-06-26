#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class SpawnType
{
	Player,
	Swordman,
	Archer,
};

class Effect_Spawn : public GameEngineActor
{
public:
	Effect_Spawn();
	~Effect_Spawn();

	Effect_Spawn(const Effect_Spawn& _Other) = delete;
	Effect_Spawn(Effect_Spawn&& _Other) noexcept = delete;
	Effect_Spawn& operator=(const Effect_Spawn& _Other) = delete;
	Effect_Spawn& operator=(Effect_Spawn&& _Other) noexcept = delete;

	SpawnType spawnType;
	float effectLiveTime = 0.0f;


	void SpawnObject(SpawnType spawnType, float4 _Scale);

	bool IsSpawnable()
	{
		return spawnable;
	}

	void SetSpawnable()
	{
		spawnable = !spawnable;
	}

	float GetEffectLiveTime()
	{
		return effectLiveTime;
	}

protected:
	GameEngineRenderer* Renderer;

private:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	bool spawnable = false;
};

