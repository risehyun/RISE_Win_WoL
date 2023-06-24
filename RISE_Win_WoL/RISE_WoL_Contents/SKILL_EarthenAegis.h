#pragma once
#include "Skill.h"
#include <vector>

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


	std::vector<GameEngineRenderer*> Renderers;
	std::vector<GameEngineCollision*> Collisions;


	GameEngineRenderer* Renderer = nullptr;


	// 렌더링 테스트용 임시 객체
	GameEngineRenderer* Renderer2 = nullptr;
	GameEngineRenderer* Renderer3 = nullptr;
	GameEngineRenderer* Renderer4 = nullptr;
	GameEngineRenderer* Renderer5 = nullptr;
	GameEngineRenderer* Renderer6 = nullptr;
	GameEngineRenderer* Renderer7 = nullptr;
	GameEngineRenderer* Renderer8 = nullptr;



	GameEngineCollision* BodyCollsion = nullptr;
	GameEngineCollision* BodyCollsion2 = nullptr;
	GameEngineCollision* BodyCollsion3 = nullptr;
	GameEngineCollision* BodyCollsion4 = nullptr;
	GameEngineCollision* BodyCollsion5 = nullptr;
	GameEngineCollision* BodyCollsion6 = nullptr;
	GameEngineCollision* BodyCollsion7 = nullptr;
	GameEngineCollision* BodyCollsion8 = nullptr;

private:
	float4 Dir;
	float Speed = 500.0f;

	float RollAngle = 45.0f;
	float Degree = 0.0f;
	float4 Range;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

};

