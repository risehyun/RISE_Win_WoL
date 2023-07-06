#pragma once
#include <GameEngineCore/GameEngineActor.h>

class NPC_ArcanaShop : public GameEngineActor
{
public:
	NPC_ArcanaShop();
	~NPC_ArcanaShop();

	NPC_ArcanaShop(const NPC_ArcanaShop& _Other) = delete;
	NPC_ArcanaShop(NPC_ArcanaShop&& _Other) noexcept = delete;
	NPC_ArcanaShop& operator=(const NPC_ArcanaShop& _Other) = delete;
	NPC_ArcanaShop& operator=(NPC_ArcanaShop&& _Other) noexcept = delete;

	GameEngineRenderer* ShadowRenderer = nullptr;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	GameEngineRenderer* MainRenderer = nullptr;
};