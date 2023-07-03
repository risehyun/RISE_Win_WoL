#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_PlayerHpBar : public GameEngineActor
{
public:
	UI_PlayerHpBar();
	~UI_PlayerHpBar();

	UI_PlayerHpBar(const UI_PlayerHpBar& _Other) = delete;
	UI_PlayerHpBar(UI_PlayerHpBar&& _Other) noexcept = delete;
	UI_PlayerHpBar& operator=(const UI_PlayerHpBar& _Other) = delete;
	UI_PlayerHpBar& operator=(UI_PlayerHpBar&& _Other) noexcept = delete;


	float fCurHpFillAmount = 0.0f;
	float fMaxHpFillAmount = 0.0f;

	GameEngineRenderer* MainRenderer = nullptr;

	GameEngineRenderer* GetMainRenderer() const
	{
		return MainRenderer;
	}


protected:

private:
	void Start() override;
	void Update(float _Delta) override;


};