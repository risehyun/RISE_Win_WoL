#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Boss.h"

#include "UI_HPBar.h"

class UI_BossNameBar : public GameEngineActor
{
public:
	UI_BossNameBar();
	~UI_BossNameBar();

	UI_BossNameBar(const UI_BossNameBar& _Other) = delete;
	UI_BossNameBar(UI_BossNameBar&& _Other) noexcept = delete;
	UI_BossNameBar& operator=(const UI_BossNameBar& _Other) = delete;
	UI_BossNameBar& operator=(UI_BossNameBar&& _Other) noexcept = delete;

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

