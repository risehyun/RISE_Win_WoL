#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "UI_KeyboardF.h"
#include "UI_Dialog.h"
#include "PlayUIManager.h"

class NPC_Collector : public GameEngineActor
{
public:
	NPC_Collector();
	~NPC_Collector();

	NPC_Collector(const NPC_Collector& _Other) = delete;
	NPC_Collector(NPC_Collector&& _Other) noexcept = delete;
	NPC_Collector& operator=(const NPC_Collector& _Other) = delete;
	NPC_Collector& operator=(NPC_Collector&& _Other) noexcept = delete;

	GameEngineRenderer* ShadowRenderer = nullptr;

	static NPC_Collector* Collector_Npc;
	UI_Dialog* m_DialogUI = PlayUIManager::UI->NewDialog;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	GameEngineRenderer* MainRenderer = nullptr;


	GameEngineCollision* BodyCollision = nullptr;
	UI_KeyboardF* m_InteractUI = nullptr;



};