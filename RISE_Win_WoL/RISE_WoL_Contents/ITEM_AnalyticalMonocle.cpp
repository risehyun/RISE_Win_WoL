#include "ITEM_AnalyticalMonocle.h"
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "Player.h"

void ITEM_AnalyticalMonocle::Start()
{

	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");

	GameEnginePath FolderPath = FilePath;

	FilePath.MoveChild("ContentsResources\\Texture\\NPC\\ITEMSHOP");

	// 아이템 텍스처 로딩
	if (false == ResourcesManager::GetInst().IsLoadTexture("ITEM_AnalyticalMonocle.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ITEM_AnalyticalMonocle.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("ITEM_Descript_AnalyticalMonocle.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ITEM_Descript_AnalyticalMonocle.bmp"));
	}



	// 렌더러 생성과 로딩된 텍스처 지정
	MainRenderer = CreateRenderer();
	MainRenderer->SetTexture("ITEM_AnalyticalMonocle.bmp");
	MainRenderer->SetRenderScale({ 74, 100 });

	// 충돌체 생성
	{
		BodyCollsion = CreateCollision(CollisionOrder::Item);
		BodyCollsion->SetCollisionScale({ 50, 50 });
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
	}

	m_InteractUI = GetLevel()->CreateActor<UI_KeyboardF>();
	m_InteractUI->SetPos({ 1000, 1710 });
	m_InteractUI->GetMainRenderer()->SetOrder(2);
	m_InteractUI->GetMainRenderer()->Off();


	DescriptRenerer = CreateRenderer();
	DescriptRenerer->SetTexture("ITEM_Descript_AnalyticalMonocle.bmp");
	DescriptRenerer->SetRenderScale({ 220, 115 });
	DescriptRenerer->SetRenderPos({ 1000, 1650 });
	DescriptRenerer->SetOrder(1);
	DescriptRenerer->Off();

}

void ITEM_AnalyticalMonocle::Update(float _Delta)
{
	// 플레이어와 자신의 콜리전이 충돌할 때 상호작용 UI 출력, 이 상태에서 키 입력시 아이템이 추가됨
	std::vector<GameEngineCollision*> _Col;
	if (true == BodyCollsion->Collision(CollisionOrder::PlayerBody, _Col
		, CollisionType::CirCle
		, CollisionType::CirCle
	))
	{
		m_InteractUI->GetMainRenderer()->SetRenderPos({ 0, 0 });
		m_InteractUI->GetMainRenderer()->On();
		DescriptRenerer->On();

		if (true == GameEngineInput::IsDown('F'))
		{
			m_InteractUI->GetMainRenderer()->Off();
			DescriptRenerer->Off();

			Player::MainPlayer->SetHasAnalyticalMonocle();

			Death();
		}
	}

	else
	{
		m_InteractUI->GetMainRenderer()->Off();
		DescriptRenerer->Off();
	}
}