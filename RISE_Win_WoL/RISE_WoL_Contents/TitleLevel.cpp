#include "TitleLevel.h"

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "BackGround.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	BackGround* Back = CreateActor<BackGround>();
	Back->Init("TitleBackGround.Bmp");

	BackGround* Logo = CreateActor<BackGround>();
	Back->Init("TitleLogo.Bmp");
}

void TitleLevel::Update(float _Delta)
{

	if (true == GameEngineInput::IsDown(VK_RIGHT))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
}

void TitleLevel::Render()
{
}

void TitleLevel::Release()
{
}