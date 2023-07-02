#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_DamageText : public GameEngineActor
{
public:
	UI_DamageText();
	~UI_DamageText();

	UI_DamageText(const UI_DamageText& _Other) = delete;
	UI_DamageText(UI_DamageText&& _Other) noexcept = delete;
	UI_DamageText& operator=(const UI_DamageText& _Other) = delete;
	UI_DamageText& operator=(UI_DamageText&& _Other) noexcept = delete;

	void SetDir(const float4& _Dir)
	{
		Dir = _Dir;
	}

	GameEngineRenderer* MainRenderer = nullptr;

	GameEngineRenderer* GetMainRenderer() const
	{
		return MainRenderer;
	}


protected:

private:
	float fDamageRenderSpeed = 50.0f;
	float fDamageRendererDuration = 1.0f;

	float RandomPos = 0.0f;

	float4 Dir;

	void Start() override;
	void Update(float _Delta) override;

};