#include "Effect_Spawn.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>

#include <GameEngineCore/GameEngineRenderer.h>

Effect_Spawn::Effect_Spawn()
{

}

Effect_Spawn::~Effect_Spawn()
{

}

void Effect_Spawn::Start()
{
	// 스킬 텍스처 로딩
	if (false == ResourcesManager::GetInst().IsLoadTexture("SPAWN_PLAYER.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SPAWN_PLAYER.bmp"), 8, 1);
	}

	// 렌더러 생성과 로딩된 텍스처 지정
	Renderer = CreateRenderer();
	Renderer->SetRenderScale({ 100, 365 });
	Renderer->SetTexture("SPAWN_PLAYER.bmp");
	Renderer->SetOrder(1000);

	// 애니메이션 생성
	Renderer->CreateAnimation("SPAWN_PLAYER", "SPAWN_PLAYER.bmp", 0, 7, 0.1f, false);

	Renderer->ChangeAnimation("SPAWN_PLAYER");

}

void Effect_Spawn::Update(float _Delta)
{



	if (0.8f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			Renderer->Death();
			Renderer = nullptr;
		}
	}

}