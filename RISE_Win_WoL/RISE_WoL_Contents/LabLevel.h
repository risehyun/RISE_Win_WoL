#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class LabLevel : public GameEngineLevel
{
public:
	LabLevel();
	~LabLevel();

	LabLevel(const LabLevel& _Other) = delete;
	LabLevel(LabLevel&& _Other) noexcept = delete;
	LabLevel& operator=(const LabLevel& _Other) = delete;
	LabLevel& operator=(LabLevel&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;
};