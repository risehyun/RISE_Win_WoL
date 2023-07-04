#include "ITEM_Potion.h"
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "Player.h"

void ITEM_Potion::Start()
{
	// ������ �ؽ�ó �ε�
	if (false == ResourcesManager::GetInst().IsLoadTexture("ITEM_POTION.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\NPC\\ITEMSHOP");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ITEM_POTION.bmp"));

	}

	// ������ ������ �ε��� �ؽ�ó ����
	MainRenderer = CreateRenderer();
	MainRenderer->SetTexture("ITEM_POTION.bmp");
	MainRenderer->SetRenderScale({ 80, 120 });

	// �浹ü ����
	{
		BodyCollsion = CreateCollision(CollisionOrder::Item);
		BodyCollsion->SetCollisionScale({ 50, 50 });
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
	}

	m_InteractUI = GetLevel()->CreateActor<UI_KeyboardF>();
	m_InteractUI->SetPos({ 445, 1470 });
	m_InteractUI->GetMainRenderer()->SetOrder(2);
	m_InteractUI->GetMainRenderer()->Off();

	DescriptRenerer = CreateRenderer();
	DescriptRenerer->SetText("ġ�� ����", 20);
	DescriptRenerer->SetRenderPos({ 400, 1500 });
	DescriptRenerer->SetOrder(1);
	DescriptRenerer->Off();

}

void ITEM_Potion::Update(float _Delta)
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
			m_InteractUI->GetMainRenderer()->Off();
			DescriptRenerer->Off();

			if (Player::MainPlayer->GetTotalGold() < 100)
			{
				return;
			}

			if ((Player::MainPlayer->GetCurHp() + 100) > 500)
			{
				Player::MainPlayer->SetCurHp(500);
			}

			else
			{
				Player::MainPlayer->AddCurHp(100);
			}


			Player::MainPlayer->SetTotalGold(Player::MainPlayer->GetTotalGold() - 100);

			Death();
		}
	}

	else
	{
		m_InteractUI->GetMainRenderer()->Off();
		DescriptRenerer->Off();
	}
}