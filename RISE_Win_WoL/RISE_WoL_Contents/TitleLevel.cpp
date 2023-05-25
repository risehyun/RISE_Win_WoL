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

	Back->Init("Background0.Bmp", 0.75f, { 640, 400 });

	BackGround* Logo = CreateActor<BackGround>();

	Back->Init("TitleLogo_.Bmp", 0.75f, { 640, 400 });
}

void TitleLevel::Update(float _Delta)
{

	if (true == GameEngineInput::IsDown(VK_RIGHT))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
}

void TitleLevel::Render(float _Delta)
{
}

void TitleLevel::Release()
{
}