#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Skill : public GameEngineActor
{
public:
	Skill();
	~Skill();

	Skill(const Skill& _Other) = delete;
	Skill(Skill&& _Other) noexcept = delete;
	Skill& operator=(const Skill& _Other) = delete;
	Skill& operator=(Skill&& _Other) noexcept = delete;



protected:

private:


	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
};
