#pragma once
#include "Skill.h"
#include <vector>

class SKILL_SnowflakeChakrams : public Skill
{
	std::vector<GameEngineRenderer*> Renderers;
	std::vector<GameEngineCollision*> Collisions;

private:
	float4 Dir;
	float4 Range;

	float RollAngle = 45.0f;
	float Radius = 100.0f;

	void Start() override;
	void Update(float _Delta) override;
};

