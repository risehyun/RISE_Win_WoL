#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_HPBar : public GameEngineActor
{
public:
	UI_HPBar();
	~UI_HPBar();

	UI_HPBar(const UI_HPBar& _Other) = delete;
	UI_HPBar(UI_HPBar&& _Other) noexcept = delete;
	UI_HPBar& operator=(const UI_HPBar& _Other) = delete;
	UI_HPBar& operator=(UI_HPBar&& _Other) noexcept = delete;


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

