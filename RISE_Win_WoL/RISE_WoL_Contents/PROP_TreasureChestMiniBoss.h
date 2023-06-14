#pragma once
#include <GameEngineCore/GameEngineActor.h>

class PROP_TreasureChestMiniBoss : public GameEngineActor
{
public:
	PROP_TreasureChestMiniBoss();
	~PROP_TreasureChestMiniBoss();

	PROP_TreasureChestMiniBoss(const PROP_TreasureChestMiniBoss& _Other) = delete;
	PROP_TreasureChestMiniBoss(PROP_TreasureChestMiniBoss&& _Other) noexcept = delete;
	PROP_TreasureChestMiniBoss& operator=(const PROP_TreasureChestMiniBoss& _Other) = delete;
	PROP_TreasureChestMiniBoss& operator=(PROP_TreasureChestMiniBoss&& _Other) noexcept = delete;

private:
	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};
