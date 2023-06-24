#include "ITEM_HealthCrystal.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include <GameEngineCore/GameEngineLevel.h>

#include "ITEM_HPBall.h"

#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineRandom.h>

void ITEM_HealthCrystal::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("ITEM_HealthCrystal.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Item");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ITEM_HealthCrystal.bmp"));
	}

	MainRenderer = CreateRenderer();
	MainRenderer->SetTexture("ITEM_HealthCrystal.bmp");
	MainRenderer->SetRenderScale({ 50, 100 });
	MainRenderer->SetOrder(1);

	BodyCollsion = CreateCollision(CollisionOrder::Item);
	BodyCollsion->SetCollisionScale({ 50, 50 });
	BodyCollsion->SetCollisionType(CollisionType::CirCle);

}

void ITEM_HealthCrystal::Update(float _Delta)
{
	std::vector<GameEngineCollision*> _Col;
	if (true == BodyCollsion->Collision(CollisionOrder::PlayerSkill, _Col
		, CollisionType::CirCle
		, CollisionType::CirCle
	))
	{

		for (size_t i = 0; i < 2; i++)
		{
			int OffSet = GameEngineRandom::MainRandom.RandomInt(0, 50);
			ITEM_HPBall* NewHPBall = GetLevel()->CreateActor<ITEM_HPBall>();
			NewHPBall->SetPos({ 1700, 1600 });
			NewHPBall->SetOrder(2);
			
		}


		BodyCollsion->Off();



//		, 

	}
}