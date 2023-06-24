#pragma once
#include <GameEngineCore/GameEngineActor.h>

class EFFECT_GoldCastingCircle : public GameEngineActor
{
public:
	EFFECT_GoldCastingCircle();
	~EFFECT_GoldCastingCircle();

	EFFECT_GoldCastingCircle(const EFFECT_GoldCastingCircle& _Other) = delete;
	EFFECT_GoldCastingCircle(EFFECT_GoldCastingCircle&& _Other) noexcept = delete;
	EFFECT_GoldCastingCircle& operator=(const EFFECT_GoldCastingCircle& _Other) = delete;
	EFFECT_GoldCastingCircle& operator=(EFFECT_GoldCastingCircle&& _Other) noexcept = delete;

	GameEngineRenderer* GetMainRenderer() const
	{
		return MainRenderer;
	}

private:
	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineRenderer* HitRenderer = nullptr;

	void Start() override;
	void Update(float _Delta) override;

};

