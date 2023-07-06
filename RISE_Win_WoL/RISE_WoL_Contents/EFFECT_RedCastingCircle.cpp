#include "EFFECT_RedCastingCircle.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineCollision.h>

EFFECT_RedCastingCircle::EFFECT_RedCastingCircle()
{
}

EFFECT_RedCastingCircle::~EFFECT_RedCastingCircle()
{
}

void EFFECT_RedCastingCircle::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("RedCastingCircle.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Effect");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("RedCastingCircle.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("FloorCreater_All.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Effect");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("FloorCreater_All.bmp"), 3, 1);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("IceBlast.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Effect");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("IceBlast.bmp"), 3, 1);
	}


	MainRenderer = CreateRenderer();
	MainRenderer->SetOrder(0);
	MainRenderer->SetRenderScale({ 200, 200 });
	MainRenderer->SetTexture("RedCastingCircle.bmp");
	MainRenderer->SetRenderPos({ 0.0f, 0.0f });

	MainRenderer->CreateAnimation("FloorCreater", "FloorCreater_All.bmp", 0, 2, 0.5f, false);

	HitCollision = CreateCollision(CollisionOrder::MonsterSkill);
	HitCollision->SetCollisionScale({ 100, 100 });
	HitCollision->SetCollisionType(CollisionType::CirCle);
	HitCollision->Off();

	m_iAttackPower = 100;

}

void EFFECT_RedCastingCircle::Update(float _Delta)
{

	if (GetLiveTime() > 2.0f)
	{
		HitCollision->On();
	}



}
