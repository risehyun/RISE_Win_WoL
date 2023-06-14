#pragma once
#include <GameEngineCore/GameEngineActor.h>

class NPC_Outfit : public GameEngineActor
{
public:
	NPC_Outfit();
	~NPC_Outfit();

	NPC_Outfit(const NPC_Outfit& _Other) = delete;
	NPC_Outfit(NPC_Outfit&& _Other) noexcept = delete;
	NPC_Outfit& operator=(const NPC_Outfit& _Other) = delete;
	NPC_Outfit& operator=(NPC_Outfit&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	GameEngineRenderer* MainRenderer = nullptr;
};

