#include "SKILL_ArcherBow.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"
#include "ContentsEnum.h"

void SKILL_ArcherBow::Start()
{
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");

	GameEnginePath FolderPath = FilePath;

	FilePath.MoveChild("ContentsResources\\Texture\\Monster\\");

	if (false == ResourcesManager::GetInst().IsLoadTexture("ARCHER_BOW_LEFT.bmp"))
	{
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("ARCHER_BOW_LEFT.bmp"), 5, 9);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("ARCHER_BOW_RIGHT.bmp"))
	{
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("ARCHER_BOW_RIGHT.bmp"), 5, 9);
	}

	// 렌더러 생성과 로딩된 텍스처 지정
	SkillRenderer = CreateRenderer();
	SkillRenderer->SetRenderScale({ 100, 100 });

	// 애니메이션 생성
	SkillRenderer->CreateAnimation("Arrow_INDEX0", "ARCHER_BOW_RIGHT.bmp", 0, 3, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX1", "ARCHER_BOW_RIGHT.bmp", 5, 9, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX2", "ARCHER_BOW_RIGHT.bmp", 10, 13, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX3", "ARCHER_BOW_RIGHT.bmp", 15, 18, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX4", "ARCHER_BOW_RIGHT.bmp", 20, 23, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX5", "ARCHER_BOW_RIGHT.bmp", 25, 28, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX6", "ARCHER_BOW_RIGHT.bmp", 30, 33, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX7", "ARCHER_BOW_RIGHT.bmp", 35, 38, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX8", "ARCHER_BOW_RIGHT.bmp", 40, 43, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX9", "ARCHER_BOW_LEFT.bmp", 35, 38, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX10", "ARCHER_BOW_LEFT.bmp", 30, 33, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX11", "ARCHER_BOW_LEFT.bmp", 25, 28, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX12", "ARCHER_BOW_LEFT.bmp", 20, 23, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX13", "ARCHER_BOW_LEFT.bmp", 15, 18, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX14", "ARCHER_BOW_LEFT.bmp", 10, 13, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX15", "ARCHER_BOW_LEFT.bmp", 5, 8, 0.1f, false);

	SkillRenderer->ChangeAnimation("Arrow_INDEX0");
}

void SKILL_ArcherBow::Update(float _Delta)
{

	if (GetLiveTime() > 1.0f)
	{
		Death();
	}
}
