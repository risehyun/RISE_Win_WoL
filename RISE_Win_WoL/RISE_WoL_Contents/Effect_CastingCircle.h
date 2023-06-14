#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Effect_CastingCircle : public GameEngineActor
{
public:
	Effect_CastingCircle();
	~Effect_CastingCircle();

	Effect_CastingCircle(const Effect_CastingCircle& _Other) = delete;
	Effect_CastingCircle(Effect_CastingCircle&& _Other) noexcept = delete;
	Effect_CastingCircle& operator=(const Effect_CastingCircle& _Other) = delete;
	Effect_CastingCircle& operator=(Effect_CastingCircle&& _Other) noexcept = delete;

private:
	GameEngineRenderer* MainRenderer = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};
