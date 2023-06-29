#pragma once
#include "Skill.h"

class SKILL_ArcherBow : public Skill
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

	float4 GetDir()
	{
		return Dir;
	}

	GameEngineRenderer* SkillRenderer = nullptr;
	GameEngineCollision* SkillCollsion = nullptr;
	float4 Dir;
	float4 DirDeg;

private:

	float Speed = 5.0f;

	void Start() override;
	void Update(float _Delta) override;

};
