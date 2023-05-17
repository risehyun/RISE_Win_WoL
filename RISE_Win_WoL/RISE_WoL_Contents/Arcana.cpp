#include "Arcana.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

Arcana::Arcana()
{
}

Arcana::~Arcana()
{
}

void Arcana::Start()
{
	Renderer = CreateRenderer();

	if (false == ResourcesManager::GetInst().IsLoadTexture(".Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

	}


}

void Arcana::Update(float _Delta)
{
	AddPos(Dir * _Delta * Speed);

	if (1.0f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			Renderer->Death();
			Renderer = nullptr;
		}
	}
}