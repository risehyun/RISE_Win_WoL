#include "SKILL_Boss_AncientEarthDrill.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"
#include "ContentsEnum.h"

void SKILL_Boss_AncientEarthDrill::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("BOSS_AncientEarthDrill.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Monster\\MonsterSkill\\Boss\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BOSS_AncientEarthDrill.bmp"), 3, 4);
	}

	// 렌더러 생성과 로딩된 텍스처 지정
	SkillRenderer = CreateRenderer();
	SkillRenderer->SetRenderScale({ 100, 100 });

	// 애니메이션 생성
	SkillRenderer->CreateAnimation("AncientEarthDrill_LEFT", "BOSS_AncientEarthDrill.bmp", 9, 11, 0.2f, false);

	SkillRenderer->CreateAnimation("AncientEarthDrill_RIGHT", "BOSS_AncientEarthDrill.bmp", 6, 8, 0.2f, false);

	SkillRenderer->CreateAnimation("AncientEarthDrill_UP", "BOSS_AncientEarthDrill.bmp", 3, 5, 0.2f, false);

	SkillRenderer->CreateAnimation("AncientEarthDrill_DOWN", "BOSS_AncientEarthDrill.bmp", 0, 2, 0.2f, false);

	// 충돌체 생성

	SkillCollsion = CreateCollision(CollisionOrder::MonsterSkill);
	SkillCollsion->SetCollisionScale({ 50, 50 });
	SkillCollsion->SetCollisionType(CollisionType::CirCle);


	SkillRenderer->SetOrder(2);

	m_iAttackPower = 10;

}

void SKILL_Boss_AncientEarthDrill::Update(float _Delta)
{

}
