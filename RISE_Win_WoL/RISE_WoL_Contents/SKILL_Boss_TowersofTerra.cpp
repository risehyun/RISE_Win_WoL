#include "SKILL_Boss_TowersofTerra.h"


#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"

void SKILL_Boss_TowersofTerra::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("BOSS_TowersofTerra.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Monster\\MonsterSkill\\Boss\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BOSS_TowersofTerra.bmp"), 3, 1);
	}

	// 렌더러 생성과 로딩된 텍스처 지정
	SkillRenderer = CreateRenderer();
	SkillRenderer->SetRenderScale({ 60, 200 });

	// 애니메이션 생성
	SkillRenderer->CreateAnimation("BOSS_TowersofTerra_INDEX1", "BOSS_TowersofTerra.bmp", 0, 0, 0.5f, false);
	SkillRenderer->CreateAnimation("BOSS_TowersofTerra_INDEX2", "BOSS_TowersofTerra.bmp", 1, 2, 0.2f, false);
	SkillRenderer->CreateAnimation("BOSS_TowersofTerra_INDEX_ALL", "BOSS_TowersofTerra.bmp", 0, 2, 0.3f, false);


	// 충돌체 생성

	SkillCollsion = CreateCollision(CollisionOrder::MonsterSkill);
	SkillCollsion->SetCollisionScale({ 50, 50 });
	SkillCollsion->SetCollisionType(CollisionType::CirCle);

	SkillRenderer->SetOrder(0);

	m_iAttackPower = 50;

	SkillRenderer->ChangeAnimation("BOSS_TowersofTerra_INDEX_ALL");
}

void SKILL_Boss_TowersofTerra::Update(float _Delta)
{
	//if (true == SkillRenderer->IsAnimationEnd())
	//{
	//	SkillRenderer->ChangeAnimation("BOSS_TowersofTerra_INDEX2");
	//}

	if (GetLiveTime() > 1.0f)
	{
		Death();
	}


}
