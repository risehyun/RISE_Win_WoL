#pragma once
#include "Skill.h"

class SKILL_Tornado : public Skill
{
	GameEngineRenderer* Renderer = nullptr;
	GameEngineCollision* BodyCollsion = nullptr;

private:
	float4 Dir;
	float Speed = 500.0f;
	
	void Start() override;
	void Update(float _Delta) override;
};

