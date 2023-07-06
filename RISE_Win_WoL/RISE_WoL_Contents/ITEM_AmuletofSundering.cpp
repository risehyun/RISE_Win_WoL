#include "ITEM_AmuletofSundering.h"
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "Player.h"


void ITEM_AmuletofSundering::Start()
{
	// ������ �ؽ�ó �ε�
	if (false == ResourcesManager::GetInst().IsLoadTexture("ITEM_AmuletofSundering.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\NPC\\ITEMSHOP");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ITEM_AmuletofSundering.bmp"));
		
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("ITEM_Descript_AmuletofSundering.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\NPC\\ITEMSHOP");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ITEM_Descript_AmuletofSundering.bmp"));

	}

	// ������ ������ �ε��� �ؽ�ó ����
	MainRenderer = CreateRenderer();
	MainRenderer->SetTexture("ITEM_AmuletofSundering.bmp");
	MainRenderer->SetRenderScale({ 74, 100 });

	// �浹ü ����
	{
		BodyCollsion = CreateCollision(CollisionOrder::Item);
		BodyCollsion->SetCollisionScale({ 50, 50 });
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
	}

	m_InteractUI = GetLevel()->CreateActor<UI_KeyboardF>();
	m_InteractUI->SetPos({ 1100, 1710 });
	m_InteractUI->GetMainRenderer()->SetOrder(2);
	m_InteractUI->GetMainRenderer()->Off();


	DescriptRenerer = CreateRenderer();
	DescriptRenerer->SetTexture("ITEM_Descript_AmuletofSundering.bmp");
	DescriptRenerer->SetRenderScale({ 220, 115 });
	DescriptRenerer->SetRenderPos({ 1100, 1650 });
	DescriptRenerer->SetOrder(1);
	DescriptRenerer->Off();

}

void ITEM_AmuletofSundering::Update(float _Delta)
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

		if (Player::MainPlayer->GetTotalGold() < 100)
		{
			return;
		}

		else 
		{
			if (true == GameEngineInput::IsDown('F'))
			{
				m_InteractUI->GetMainRenderer()->Off();
				DescriptRenerer->Off();

				Player::MainPlayer->SetHasAmuletofSundering();
				Player::MainPlayer->SetTotalGold(-150);

				Death();
			}
		}


		
	}

	else
	{
		m_InteractUI->GetMainRenderer()->Off();
		DescriptRenerer->Off();
	}
}