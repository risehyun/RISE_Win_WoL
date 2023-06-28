#pragma once
#include "Skill.h"

class SKILL_MiniBoss_GrandSummoner_Fireball : public Skill
{
public:
	void SetDir(const float4& _Dir)
	{
		Dir = _Dir;
	}

	void SetSpeed(const float _Speed)
	{
		Speed = _Speed;
	}

	float4 GetDir()
	{
		return Dir;
	}

	GameEngineRenderer* SkillRenderer = nullptr;
	GameEngineCollision* SkillCollsion = nullptr;

	GameEngineRenderer* GetMainRenderer()
	{
		return SkillRenderer;
	}

private:
	float4 Dir;
	float Speed = 500.0f;

	void Start() override;
	void Update(float _Delta) override;
};