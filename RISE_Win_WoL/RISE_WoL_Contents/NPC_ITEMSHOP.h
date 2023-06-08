#pragma once
#include <GameEngineCore/GameEngineActor.h>

class NPC_ITEMSHOP : public GameEngineActor
{
public:
	NPC_ITEMSHOP();
	~NPC_ITEMSHOP();

	NPC_ITEMSHOP(const NPC_ITEMSHOP& _Other) = delete;
	NPC_ITEMSHOP(NPC_ITEMSHOP&& _Other) noexcept = delete;
	NPC_ITEMSHOP& operator=(const NPC_ITEMSHOP& _Other) = delete;
	NPC_ITEMSHOP& operator=(NPC_ITEMSHOP&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	GameEngineRenderer* MainRenderer = nullptr;

	GameEngineRenderer* PotionRenderer = nullptr;
};

