#include "SKILL_MiniBoss_GrandSummoner_Magicball.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"
#include "ContentsEnum.h"

void SKILL_MiniBoss_GrandSummoner_Magicball::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("MiniBoss_GrandSummoner_MagicBall.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Monster\\MonsterSkill\\MiniBoss\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("MiniBoss_GrandSummoner_MagicBall.bmp"), 4, 16);
	}

	SkillRenderer = CreateRenderer();
	SkillRenderer->SetRenderScale({ 70, 70 });

	SkillRenderer->CreateAnimation("MagicBall_Idle", "MiniBoss_GrandSummoner_MagicBall.bmp", 0, 0, 0.2f, false);

	SkillRenderer->CreateAnimation("MagicBall_Damage", "MiniBoss_GrandSummoner_MagicBall.bmp", 1, 2, 0.2f, false);

	SkillRenderer->CreateAnimation("MagicBall_ATTACK_Index0", "MiniBoss_GrandSummoner_MagicBall.bmp", 4, 7, 0.2f, false);

	SkillRenderer->CreateAnimation("MagicBall_ATTACK_Index1", "MiniBoss_GrandSummoner_MagicBall.bmp", 8, 11, 0.2f, false);

	SkillRenderer->CreateAnimation("MagicBall_ATTACK_Index2", "MiniBoss_GrandSummoner_MagicBall.bmp", 12, 15, 0.2f, false);

	SkillRenderer->CreateAnimation("MagicBall_ATTACK_Index3", "MiniBoss_GrandSummoner_MagicBall.bmp", 16, 19, 0.2f, false);

	SkillRenderer->CreateAnimation("MagicBall_ATTACK_Index4", "MiniBoss_GrandSummoner_MagicBall.bmp", 20, 23, 0.2f, false);

	SkillRenderer->CreateAnimation("MagicBall_ATTACK_Index5", "MiniBoss_GrandSummoner_MagicBall.bmp", 24, 27, 0.2f, false);

	SkillRenderer->CreateAnimation("MagicBall_ATTACK_Index6", "MiniBoss_GrandSummoner_MagicBall.bmp", 28, 31, 0.2f, false);

	SkillRenderer->CreateAnimation("MagicBall_ATTACK_Index7", "MiniBoss_GrandSummoner_MagicBall.bmp", 32, 35, 0.2f, false);

	SkillRenderer->CreateAnimation("MagicBall_ATTACK_Index8", "MiniBoss_GrandSummoner_MagicBall.bmp", 36, 39, 0.2f, false);

	SkillRenderer->CreateAnimation("MagicBall_ATTACK_Index9", "MiniBoss_GrandSummoner_MagicBall.bmp", 40, 43, 0.2f, false);

	SkillRenderer->CreateAnimation("MagicBall_ATTACK_Index10", "MiniBoss_GrandSummoner_MagicBall.bmp", 44, 47, 0.2f, false);

	SkillRenderer->CreateAnimation("MagicBall_ATTACK_Index11", "MiniBoss_GrandSummoner_MagicBall.bmp", 48, 51, 0.2f, false);

	SkillRenderer->CreateAnimation("MagicBall_ATTACK_Index12", "MiniBoss_GrandSummoner_MagicBall.bmp", 52, 55, 0.2f, false);

	SkillRenderer->CreateAnimation("MagicBall_ATTACK_Index13", "MiniBoss_GrandSummoner_MagicBall.bmp", 56, 59, 0.2f, false);

	SkillRenderer->CreateAnimation("MagicBall_ATTACK_Index14", "MiniBoss_GrandSummoner_MagicBall.bmp", 60, 63, 0.2f, false);

	// 中宜端 持失
	//SkillCollsion = CreateCollision(CollisionOrder::MonsterSkill);
	//SkillCollsion->SetCollisionScale({ 50, 50 });
	//SkillCollsion->SetCollisionType(CollisionType::CirCle);

	m_iAttackPower = 10;

	SkillRenderer->ChangeAnimation("MagicBall_Idle");
}

void SKILL_MiniBoss_GrandSummoner_Magicball::Update(float _Delta)
{
	//if (SkillRenderer->IsAnimationEnd())
	//{
	//	Death();
	//}
}
