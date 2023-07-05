#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Background_Stage1 : public GameEngineActor
{
public:
	Background_Stage1();
	~Background_Stage1();

	Background_Stage1(const Background_Stage1& _Other) = delete;
	Background_Stage1(Background_Stage1&& _Other) noexcept = delete;
	Background_Stage1& operator=(const Background_Stage1& _Other) = delete;
	Background_Stage1& operator=(Background_Stage1&& _Other) noexcept = delete;

	GameEngineRenderer* MainRenderer = nullptr;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

};