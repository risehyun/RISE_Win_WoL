#include "ITEM_Gold.h"

#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "Player.h"

void ITEM_Gold::Start()
{
	// 아이템 텍스처 로딩
	if (false == ResourcesManager::GetInst().IsLoadTexture("ITEM_GOLD.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Item");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("ITEM_GOLD.bmp"), 2, 1);
	}

	// 렌더러 생성과 로딩된 텍스처 지정
	MainRenderer = CreateRenderer();
	MainRenderer->SetTexture("ITEM_GOLD.bmp");
	MainRenderer->SetRenderScale({ 31, 31 });
	MainRenderer->CreateAnimation("GOLD_DROP", "ITEM_GOLD.bmp", 0, 1, 0.1f, true);

	MainRenderer->ChangeAnimation("GOLD_DROP");

	// 충돌체 생성
	{
		BodyCollsion = CreateCollision(CollisionOrder::Item);
		BodyCollsion->SetCollisionScale({ 50, 50 });
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
	}

}

void ITEM_Gold::Update(float _Delta)
{
	if (GetLiveTime() > 2.0f)
	{
		float4 Dir = Player::GetMainPlayer()->GetPos() - GetPos();

		Dir.Normalize();

		AddPos(Dir * _Delta * 200.0f);
	}

	std::vector<GameEngineCollision*> _Col;
	if (true == BodyCollsion->Collision(CollisionOrder::PlayerBody, _Col
		, CollisionType::CirCle
		, CollisionType::CirCle
	))
	{
		// 추후 수정 : 매개변수로 넘기는 값은 상수가 아니라 Define된 Value값이 되어야 한다.
		Player::GetMainPlayer()->SetTotalGold(100);

		Death();	
	}
}