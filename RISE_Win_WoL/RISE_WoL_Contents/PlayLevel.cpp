#include "PlayLevel.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>

#include "Player.h"
#include "BackGround.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Start()
{
	BackGround* Back = CreateActor<BackGround>();
	Back->Init("BackGround.Bmp");

	CreateActor<Player>();
}

void PlayLevel::Update(float _Delta)
{
}

void PlayLevel::Render()
{
}

void PlayLevel::Release()
{
}