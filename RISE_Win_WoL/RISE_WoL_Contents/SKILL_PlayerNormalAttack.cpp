#include "SKILL_PlayerNormalAttack.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

void SKILL_PlayerNormalAttack::Start()
{

	if (false == ResourcesManager::GetInst().IsLoadTexture("PLAYER_NORMAL_ATTACK.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Skill\\PlayerSkills\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("PLAYER_NORMAL_ATTACK.bmp"), 8, 8);
	}

	Renderer = CreateRenderer();

	Renderer->SetRenderScale({ 100, 100 });

	Renderer->SetTexture("PLAYER_NORMAL_ATTACK.bmp");

	Renderer->CreateAnimation("Attack_NORMAL", "PLAYER_NORMAL_ATTACK.bmp", 0, 4, 0.2f, false);

	Renderer->ChangeAnimation("Attack_NORMAL");

}

void SKILL_PlayerNormalAttack::Update(float _Delta)
{

	if (0.4f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			Renderer->Death();
			Renderer = nullptr;
		}
	}
}


