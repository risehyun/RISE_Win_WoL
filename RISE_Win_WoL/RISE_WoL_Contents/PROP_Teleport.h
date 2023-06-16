#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "UI_KeyboardF.h"

class PROP_Teleport : public GameEngineActor
{
public:
	PROP_Teleport();
	~PROP_Teleport();

	PROP_Teleport(const PROP_Teleport& _Other) = delete;
	PROP_Teleport(PROP_Teleport&& _Other) noexcept = delete;
	PROP_Teleport& operator=(const PROP_Teleport& _Other) = delete;
	PROP_Teleport& operator=(PROP_Teleport&& _Other) noexcept = delete;

private:
	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	UI_KeyboardF* m_InteractUI = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};

