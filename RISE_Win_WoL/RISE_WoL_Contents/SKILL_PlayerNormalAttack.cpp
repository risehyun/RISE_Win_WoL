#include "SKILL_PlayerNormalAttack.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "Player.h"

void SKILL_PlayerNormalAttack::Start()
{
	// 스킬 텍스처 로딩
	if (false == ResourcesManager::GetInst().IsLoadTexture("PLAYER_NORMAL_ATTACK.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Skill\\PlayerSkills\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("PLAYER_NORMAL_ATTACK.bmp"), 8, 8);
	}

	// 렌더러 생성과 로딩된 텍스처 지정
	Renderer = CreateRenderer();
	Renderer->SetRenderScale({ 100, 100 });
	Renderer->SetTexture("PLAYER_NORMAL_ATTACK.bmp");


	// 애니메이션 생성
	Renderer->CreateAnimation("ATTACK_NORMAL_LEFT", "PLAYER_NORMAL_ATTACK.bmp", 32, 36, 0.2f, false);
	
	Renderer->CreateAnimation("ATTACK_NORMAL_RIGHT", "PLAYER_NORMAL_ATTACK.bmp", 0, 4, 0.2f, false);

	Renderer->CreateAnimation("ATTACK_NORMAL_UP", "PLAYER_NORMAL_ATTACK.bmp", 16, 20, 0.2f, false);

	Renderer->CreateAnimation("ATTACK_NORMAL_DOWN", "PLAYER_NORMAL_ATTACK.bmp", 49, 52, 0.2f, false);	

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


