#include "ITEM_HPBall.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"

#include "Player.h"

void ITEM_HPBall::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("ITEM_HPBall.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Item");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ITEM_HPBall.bmp"));
	}


	MainRenderer = CreateRenderer();
	MainRenderer->SetOrder(1);
	MainRenderer->SetRenderScale({ 64, 64 });
	MainRenderer->SetTexture("ITEM_HPBall.bmp");


	BodyCollsion = CreateCollision(CollisionOrder::Item);
	BodyCollsion->SetCollisionScale({ 64, 64 });
	BodyCollsion->SetCollisionType(CollisionType::CirCle);

}

void ITEM_HPBall::Update(float _Delta)
{
	std::vector<GameEngineCollision*> _Col;
	if (true == BodyCollsion->Collision(CollisionOrder::PlayerBody, _Col
		, CollisionType::CirCle
		, CollisionType::CirCle
	))
	{
		if ((Player::MainPlayer->GetCurHp() + 100) > Player::MainPlayer->GetMaxHp())
		{
			Player::MainPlayer->SetCurHp(Player::MainPlayer->GetMaxHp());
		}

		else
		{
			Player::MainPlayer->AddCurHp(100);
		}

		Death();
	}
}
