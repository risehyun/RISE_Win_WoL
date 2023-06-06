#pragma once
#include "Skill.h"

class SKILL_KnightAttack : public Skill
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

	GameEngineRenderer* SkillRenderer;
	GameEngineCollision* SkillCollsion = nullptr;

private:
	float4 Dir;
	float Speed = 500.0f;

	void Start() override;
	void Update(float _Delta) override;

};
