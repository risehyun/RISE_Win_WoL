#pragma once
#include <GameEngineCore/GameEngineActor.h>

class EFFECT_RedCastingCircle : public GameEngineActor
{
public:
	EFFECT_RedCastingCircle();
	~EFFECT_RedCastingCircle();

	EFFECT_RedCastingCircle(const EFFECT_RedCastingCircle& _Other) = delete;
	EFFECT_RedCastingCircle(EFFECT_RedCastingCircle&& _Other) noexcept = delete;
	EFFECT_RedCastingCircle& operator=(const EFFECT_RedCastingCircle& _Other) = delete;
	EFFECT_RedCastingCircle& operator=(EFFECT_RedCastingCircle&& _Other) noexcept = delete;

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
