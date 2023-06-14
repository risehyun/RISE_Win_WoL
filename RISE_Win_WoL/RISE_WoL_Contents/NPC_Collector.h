#pragma once
#include <GameEngineCore/GameEngineActor.h>

class NPC_Collector : public GameEngineActor
{
public:
	NPC_Collector();
	~NPC_Collector();

	NPC_Collector(const NPC_Collector& _Other) = delete;
	NPC_Collector(NPC_Collector&& _Other) noexcept = delete;
	NPC_Collector& operator=(const NPC_Collector& _Other) = delete;
	NPC_Collector& operator=(NPC_Collector&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	GameEngineRenderer* MainRenderer = nullptr;
};