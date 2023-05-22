#include "LabLevel.h"

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineInput.h>


#include <math.h>

#include "BackGround.h"

LabLevel::LabLevel()
{
}

LabLevel::~LabLevel()
{
}

void LabLevel::Start()
{
	static BackGround* Back = CreateActor<BackGround>();
	//Back->Init("UI_MONEY.Bmp", 0.75f, { 640, 400 });


}

void LabLevel::Update(float _Delta)
{
	


	if (true == GameEngineInput::IsDown(VK_UP))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
}

void LabLevel::Render()
{
}

void LabLevel::Release()
{
}