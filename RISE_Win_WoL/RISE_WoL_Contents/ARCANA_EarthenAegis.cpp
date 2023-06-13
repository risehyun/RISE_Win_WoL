#include "ARCANA_EarthenAegis.h"
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineInput.h>

void ARCANA_EarthenAegis::Start()
{
	// 아이템 텍스처 로딩
	if (false == ResourcesManager::GetInst().IsLoadTexture("ARCANA_EarthenAegis.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\SKILL");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ARCANA_EarthenAegis.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("ITEM_Descript_VampiresEyeglasses.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Skill");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ARCANA_Descript_EarthenAegis.bmp"));

	}

	// 렌더러 생성과 로딩된 텍스처 지정
	MainRenderer = CreateRenderer();
	MainRenderer->SetTexture("ARCANA_EarthenAegis.bmp");
	MainRenderer->SetRenderScale({ 74, 100 });

	// 충돌체 생성
	{
		BodyCollsion = CreateCollision(CollisionOrder::Item);
		BodyCollsion->SetCollisionScale({ 50, 50 });
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
	}

	m_InteractUI = GetLevel()->CreateActor<UI_KeyboardF>();
	m_InteractUI->SetPos({ 2900, 1710 });
	m_InteractUI->GetMainRenderer()->SetOrder(2);
	m_InteractUI->GetMainRenderer()->Off();


	DescriptRenerer = CreateRenderer();
	DescriptRenerer->SetTexture("ARCANA_Descript_EarthenAegis.bmp");
	DescriptRenerer->SetRenderScale({ 220, 115 });
	DescriptRenerer->SetRenderPos({ 2900, 1650 });
	DescriptRenerer->SetOrder(1);
	DescriptRenerer->Off();

}

void ARCANA_EarthenAegis::Update(float _Delta)
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

			Death();
		}
	}

	else
	{
		m_InteractUI->GetMainRenderer()->Off();
		DescriptRenerer->Off();
	}
}