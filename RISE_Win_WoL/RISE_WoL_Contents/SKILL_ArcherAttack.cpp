#include "SKILL_ArcherAttack.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"
#include "ContentsEnum.h"

void SKILL_ArcherAttack::Start()
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
	SkillRenderer->CreateAnimation("Arrow_INDEX0", "ARCHER_BOW_RIGHT.bmp", 0, 2, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX1", "ARCHER_BOW_RIGHT.bmp", 5, 7, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX2", "ARCHER_BOW_RIGHT.bmp", 10, 12, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX3", "ARCHER_BOW_RIGHT.bmp", 15, 17, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX4", "ARCHER_BOW_RIGHT.bmp", 20, 22, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX5", "ARCHER_BOW_RIGHT.bmp", 25, 27, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX6", "ARCHER_BOW_RIGHT.bmp", 30, 32, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX7", "ARCHER_BOW_RIGHT.bmp", 35, 37, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX8", "ARCHER_BOW_RIGHT.bmp", 40, 42, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX9", "ARCHER_BOW_LEFT.bmp", 35, 37, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX10", "ARCHER_BOW_LEFT.bmp", 30, 32, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX11", "ARCHER_BOW_LEFT.bmp", 25, 27, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX12", "ARCHER_BOW_LEFT.bmp", 20, 22, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX13", "ARCHER_BOW_LEFT.bmp", 15, 17, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX14", "ARCHER_BOW_LEFT.bmp", 10, 12, 0.1f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX15", "ARCHER_BOW_LEFT.bmp", 5, 7, 0.1f, false);


	SkillRenderer->CreateAnimation("ArrowShot_INDEX0", "ARCHER_BOW_RIGHT.bmp", 4, 4, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX1", "ARCHER_BOW_RIGHT.bmp", 9, 9, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX2", "ARCHER_BOW_RIGHT.bmp", 14, 14, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX3", "ARCHER_BOW_RIGHT.bmp", 19, 19, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX4", "ARCHER_BOW_RIGHT.bmp", 24, 24, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX5", "ARCHER_BOW_RIGHT.bmp", 29, 29, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX6", "ARCHER_BOW_RIGHT.bmp", 34, 34, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX7", "ARCHER_BOW_RIGHT.bmp", 39, 39, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX8", "ARCHER_BOW_RIGHT.bmp", 44, 44, 0.2f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX9", "ARCHER_BOW_LEFT.bmp", 39, 39, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX10", "ARCHER_BOW_LEFT.bmp", 34, 34, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX11", "ARCHER_BOW_LEFT.bmp", 29, 29, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX12", "ARCHER_BOW_LEFT.bmp", 24, 24, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX13", "ARCHER_BOW_LEFT.bmp", 19, 19, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX14", "ARCHER_BOW_LEFT.bmp", 14, 14, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX15", "ARCHER_BOW_LEFT.bmp", 9, 9, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX16", "ARCHER_BOW_LEFT.bmp", 4, 4, 0.5f, false);

		// 충돌체 생성
	SkillCollsion = CreateCollision(CollisionOrder::MonsterSkill);
	SkillCollsion->SetCollisionScale({ 50, 50 });
	SkillCollsion->SetCollisionType(CollisionType::CirCle);

	m_iAttackPower = 10;

	SkillRenderer->ChangeAnimation("Arrow_INDEX0");


}

void SKILL_ArcherAttack::Update(float _Delta)
{
	float4 NextPos = Dir * _Delta * Speed;

	AddPos(NextPos);

	if (GetLiveTime() > 0.3f)
	{
		Death();
	}
}
