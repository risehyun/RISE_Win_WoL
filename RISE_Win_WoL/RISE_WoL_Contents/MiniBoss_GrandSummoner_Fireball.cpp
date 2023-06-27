#include "MiniBoss_GrandSummoner_Fireball.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"
#include "ContentsEnum.h"

void MiniBoss_GrandSummoner_Fireball::Start()
{

	if (false == ResourcesManager::GetInst().IsLoadTexture("MiniBoss_GrandSummoner_Fire.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Monster\\MonsterSkill\\MiniBoss\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("MiniBoss_GrandSummoner_Fire.bmp"), 6, 16);
	}

	SkillRenderer = CreateRenderer();
	SkillRenderer->SetRenderScale({ 100, 100 });

	// 局聪皋捞记 积己
	SkillRenderer->CreateAnimation("ATTACK_Index0", "MiniBoss_GrandSummoner_Fire.bmp", 0, 5, 0.2f, false);

	SkillRenderer->CreateAnimation("ATTACK_Index1", "MiniBoss_GrandSummoner_Fire.bmp", 6, 11, 0.2f, false);

	SkillRenderer->CreateAnimation("ATTACK_Index2", "MiniBoss_GrandSummoner_Fire.bmp", 12, 17, 0.2f, false);

	SkillRenderer->CreateAnimation("ATTACK_Index3", "MiniBoss_GrandSummoner_Fire.bmp", 18, 23, 0.2f, false);

	SkillRenderer->CreateAnimation("ATTACK_Index4", "MiniBoss_GrandSummoner_Fire.bmp", 24, 29, 0.2f, false);

	SkillRenderer->CreateAnimation("ATTACK_Index5", "MiniBoss_GrandSummoner_Fire.bmp", 30, 35, 0.2f, false);

	SkillRenderer->CreateAnimation("ATTACK_Index6", "MiniBoss_GrandSummoner_Fire.bmp", 36, 41, 0.2f, false);

	SkillRenderer->CreateAnimation("ATTACK_Index7", "MiniBoss_GrandSummoner_Fire.bmp", 42, 47, 0.2f, false);

	SkillRenderer->CreateAnimation("ATTACK_Index8", "MiniBoss_GrandSummoner_Fire.bmp", 48, 53, 0.2f, false);

	SkillRenderer->CreateAnimation("ATTACK_Index9", "MiniBoss_GrandSummoner_Fire.bmp", 54, 59, 0.2f, false);

	SkillRenderer->CreateAnimation("ATTACK_Index10", "MiniBoss_GrandSummoner_Fire.bmp", 60, 65, 0.2f, false);

	SkillRenderer->CreateAnimation("ATTACK_Index11", "MiniBoss_GrandSummoner_Fire.bmp", 66, 71, 0.2f, false);

	SkillRenderer->CreateAnimation("ATTACK_Index12", "MiniBoss_GrandSummoner_Fire.bmp", 72, 77, 0.2f, false);

	SkillRenderer->CreateAnimation("ATTACK_Index13", "MiniBoss_GrandSummoner_Fire.bmp", 78, 83, 0.2f, false);

	SkillRenderer->CreateAnimation("ATTACK_Index14", "MiniBoss_GrandSummoner_Fire.bmp", 84, 89, 0.2f, false);

	SkillRenderer->CreateAnimation("ATTACK_Index15", "MiniBoss_GrandSummoner_Fire.bmp", 90, 95, 0.2f, false);

	// 面倒眉 积己
	SkillCollsion = CreateCollision(CollisionOrder::MonsterSkill);
	SkillCollsion->SetCollisionScale({ 50, 50 });
	SkillCollsion->SetCollisionType(CollisionType::CirCle);

	m_iAttackPower = 10;

	SkillRenderer->ChangeAnimation("ATTACK_Index0");

}

void MiniBoss_GrandSummoner_Fireball::Update(float _Delta)
{
	if (SkillRenderer->IsAnimationEnd())
	{
		Death();
	}

}