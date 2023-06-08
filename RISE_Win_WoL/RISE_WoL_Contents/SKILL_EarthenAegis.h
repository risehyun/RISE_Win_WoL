#pragma once
#include "Skill.h"

class SKILL_EarthenAegis : public Skill
{
	void SetDir(const float4& _Dir)
	{
		Dir = _Dir;
	}

	void SetSpeed(const float _Speed)
	{
		Speed = _Speed;
	}

	GameEngineRenderer* Renderer = nullptr;
	GameEngineCollision* BodyCollsion = nullptr;

private:
	float4 Dir;
	float Speed = 500.0f;

	void Start() override;
	void Update(float _Delta) override;

};

