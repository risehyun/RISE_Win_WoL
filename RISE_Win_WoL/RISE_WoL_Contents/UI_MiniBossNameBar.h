#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "MiniBoss_GrandSummoner.h"

#include "UI_HPBar.h"

class UI_MiniBossNameBar : public GameEngineActor
{
public:
	UI_MiniBossNameBar();
	~UI_MiniBossNameBar();

	UI_MiniBossNameBar(const UI_MiniBossNameBar& _Other) = delete;
	UI_MiniBossNameBar(UI_MiniBossNameBar&& _Other) noexcept = delete;
	UI_MiniBossNameBar& operator=(const UI_MiniBossNameBar& _Other) = delete;
	UI_MiniBossNameBar& operator=(UI_MiniBossNameBar&& _Other) noexcept = delete;

	GameEngineRenderer* MainRenderer = nullptr;

	GameEngineRenderer* GetMainRenderer() const
	{
		return MainRenderer;
	}

	UI_HPBar* NewHpBar = nullptr;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
};