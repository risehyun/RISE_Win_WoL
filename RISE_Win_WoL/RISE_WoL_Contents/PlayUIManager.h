#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include "UI_PlayerHpBar.h"

#include "UI_MiniBossNameBar.h"
#include "UI_BossNameBar.h"

#include "UI_Inventory.h"
#include "UI_Dialog.h"

class PlayUIManager : public GameEngineActor
{
public:
	static PlayUIManager* UI;

public:
	PlayUIManager();
	~PlayUIManager();

	PlayUIManager(const PlayUIManager& _Other) = delete;
	PlayUIManager(PlayUIManager&& _Other) noexcept = delete;
	PlayUIManager& operator=(const PlayUIManager& _Other) = delete;
	PlayUIManager& operator=(PlayUIManager&& _Other) noexcept = delete;

	GameEngineCollision* ButtonCollsion = nullptr;

	UI_PlayerHpBar* NewHpBar = nullptr;

	UI_MiniBossNameBar* MiniBossNameBar = nullptr;
	UI_BossNameBar* BossNameBar = nullptr;


	UI_Inventory* NewInven = nullptr;

	UI_Dialog* NewDialog = nullptr;

	GameEngineRenderer* MousePtr = nullptr;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:


};