#pragma once
#include "Skill.h"

class SKILL_ArcherAttack : public Skill
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

	GameEngineRenderer* GetMainRenderer()
	{
		return SkillRenderer;
	}

	GameEngineRenderer* SkillRenderer = nullptr;
	GameEngineCollision* SkillCollsion = nullptr;
	float4 Dir;

private:

	float Speed = 5.0f;

	void Start() override;
	void Update(float _Delta) override;

};

