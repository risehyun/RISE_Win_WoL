#include "GameEngineInput.h"

GameEngineInput::GameEngineInput()
{
}

GameEngineInput::~GameEngineInput()
{
}

void GameEngineInput::InputInit()
{
	
	
}

void GameEngineInput::GameEngineKey::Update(float _DeltaTime)
{
	if (true == KeyCheck())
	{
		// 키가 눌렸다면
		PressTime += _DeltaTime;

		// 이전에 키가 눌렸던적이 없다면
		if (true == Free)
		{
			Down = true;
			Press = true;
			Up = false;
			Free = false;
		}

		else if (true == Down)
		{
			Down = false;
			Press = true;
			Up = false;
			Free = false;
		}

	}

	else
	{
		PressTime = 0.0f;

		// 키가 눌리지 않은 경우
		if (true == Press)
		{
			Down = false;
			Press = false;
			Up = true;
			Free = true;
		}
		else if (true == Up)
		{
			Down = false;
			Press = false;
			Up = false;
			Free = true;
		}
	}
}