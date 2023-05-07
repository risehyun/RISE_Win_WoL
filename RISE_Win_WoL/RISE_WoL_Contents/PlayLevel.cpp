#include "PlayLevel.h"
#include "Player.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Start()
{
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