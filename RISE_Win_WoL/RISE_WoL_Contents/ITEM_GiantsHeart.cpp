#include "ITEM_GiantsHeart.h"
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineInput.h>

void ITEM_GiantsHeart::Start()
{
	// ������ �ؽ�ó �ε�
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");

	GameEnginePath FolderPath = FilePath;

	FilePath.MoveChild("ContentsResources\\Texture\\NPC\\ITEMSHOP");

	if (false == ResourcesManager::GetInst().IsLoadTexture("ITEM_GiantsHeart.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ITEM_GiantsHeart.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("ITEM_Descript_GiantsHeart.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ITEM_Descript_GiantsHeart.bmp"));
	}

	

	// ������ ������ �ε��� �ؽ�ó ����
	MainRenderer = CreateRenderer();
	MainRenderer->SetTexture("ITEM_GiantsHeart.bmp");
	MainRenderer->SetRenderScale({ 74, 100 });

	// �浹ü ����
	{
		BodyCollsion = CreateCollision(CollisionOrder::Item);
		BodyCollsion->SetCollisionScale({ 50, 50 });
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
	}

	m_InteractUI = GetLevel()->CreateActor<UI_KeyboardF>();
	m_InteractUI->SetPos({ 900, 1710 });
	m_InteractUI->GetMainRenderer()->SetOrder(2);
	m_InteractUI->GetMainRenderer()->Off();


	DescriptRenerer = CreateRenderer();
	DescriptRenerer->SetTexture("ITEM_Descript_GiantsHeart.bmp");
	DescriptRenerer->SetRenderScale({ 220, 115 });
	DescriptRenerer->SetRenderPos({ 900, 1650 });
	DescriptRenerer->SetOrder(1);
	DescriptRenerer->Off();

}

void ITEM_GiantsHeart::Update(float _Delta)
{
	// �÷��̾�� �ڽ��� �ݸ����� �浹�� �� ��ȣ�ۿ� UI ���, �� ���¿��� Ű �Է½� �������� �߰���
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
			//m_InteractUI->GetMainRenderer()->Off();
			//DescriptRenerer->Off();

			//Death();
		}
	}

	else
	{
		m_InteractUI->GetMainRenderer()->Off();
		DescriptRenerer->Off();
	}
}