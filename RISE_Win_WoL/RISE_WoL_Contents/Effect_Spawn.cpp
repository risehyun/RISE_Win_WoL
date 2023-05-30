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
	// ��ų �ؽ�ó �ε�
	if (false == ResourcesManager::GetInst().IsLoadTexture("SPAWN_PLAYER.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SPAWN_PLAYER.bmp"), 8, 1);
	}

	// ������ ������ �ε��� �ؽ�ó ����
	Renderer = CreateRenderer();
	Renderer->SetRenderScale({ 100, 365 });
	Renderer->SetTexture("SPAWN_PLAYER.bmp");
	Renderer->SetOrder(1000);

	// �ִϸ��̼� ����
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