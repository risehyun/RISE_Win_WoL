#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "UI_KeyboardF.h"

class NPC_Outfit : public GameEngineActor
{
public:
	NPC_Outfit();
	~NPC_Outfit();

	NPC_Outfit(const NPC_Outfit& _Other) = delete;
	NPC_Outfit(NPC_Outfit&& _Other) noexcept = delete;
	NPC_Outfit& operator=(const NPC_Outfit& _Other) = delete;
	NPC_Outfit& operator=(NPC_Outfit&& _Other) noexcept = delete;


	static NPC_Outfit* Outfit_Npc;


	bool GetIsAvailable()
	{
		return isAvailable;
	}

	int DialogIndex = 0;


protected:

private:
	void Start() override;
	void Update(float _Delta) override;


	GameEngineCollision* BodyCollision = nullptr;

	GameEngineRenderer* MainRenderer = nullptr;
	UI_KeyboardF* m_InteractUI = nullptr;
	
	bool isAvailable = true;
	

};

