#include "TitleLevel.h"

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
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
}

void TitleLevel::Render()
{
}

void TitleLevel::Release()
{
}