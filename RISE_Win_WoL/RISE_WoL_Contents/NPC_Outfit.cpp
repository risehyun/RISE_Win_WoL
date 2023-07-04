#include "NPC_Outfit.h"
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineLevel.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "UI_Dialog.h"

#include "PlayUIManager.h"

#include "Player.h"

NPC_Outfit::NPC_Outfit()
{
}

NPC_Outfit::~NPC_Outfit()
{
}

void NPC_Outfit::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("NPC_Outfit.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\NPC\\OUTFIT");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("NPC_Outfit.bmp"));
	}

	MainRenderer = CreateRenderer("NPC_Outfit.bmp", RenderOrder::BackGround);

	MainRenderer->SetRenderScale({ 150, 150 });


	BodyCollision = CreateCollision(CollisionOrder::Map);
	BodyCollision->SetCollisionScale({ 100, 100 });
	BodyCollision->SetCollisionType(CollisionType::CirCle);


	// 상호작용 UI 설정
	m_InteractUI = GetLevel()->CreateActor<UI_KeyboardF>();

	m_InteractUI->SetPos({ 1860, 600 });
	m_InteractUI->GetMainRenderer()->SetOrder(2);
	m_InteractUI->GetMainRenderer()->Off();

}

void NPC_Outfit::Update(float _Delta)
{
	static int DialogIndex = 0;


	// 캐릭터와 충돌 상태인 경우 F 키를 눌러서 대화 가능
	std::vector<GameEngineCollision*> _Col;
	if (true == BodyCollision->Collision(CollisionOrder::PlayerBody, _Col
		, CollisionType::CirCle
		, CollisionType::CirCle
	))
	{
		m_InteractUI->GetMainRenderer()->On();

		if (true == GameEngineInput::IsDown('F') && true == isAvailable)
		{
			PlayUIManager::UI->NewDialog->GetMainRenderer()->SetTexture("NPC_OUTFIT_INDEX0.bmp");
			PlayUIManager::UI->NewDialog->GetMainRenderer()->On();
		}


		if (true == GameEngineInput::IsDown(VK_RETURN) && DialogIndex != -2)
		{
			DialogIndex++;
		}

		if (DialogIndex == -2)
		{
			PlayUIManager::UI->NewDialog->GetMainRenderer()->Off();
		}

		if (DialogIndex == 1)
		{
			PlayUIManager::UI->NewDialog->GetMainRenderer()->SetTexture("NPC_OUTFIT_INDEX1.bmp");
		}

		if (DialogIndex == 2)
		{
			PlayUIManager::UI->NewDialog->GetMainRenderer()->SetTexture("NPC_OUTFIT_INDEX2.bmp");
		}

		if (DialogIndex == 3)
		{

			if (Player::MainPlayer->GetTotalGold() < 500)
			{
				PlayUIManager::UI->NewDialog->GetMainRenderer()->Off();
				return;
			}

			else
			{
				Player::MainPlayer->SetTotalGold(-500);

				if (Player::MainPlayer->GetCurHp() == Player::MainPlayer->GetMaxHp())
				{
					Player::MainPlayer->SetCurHp(Player::MainPlayer->GetMaxHp() + (Player::MainPlayer->GetMaxHp() * 5 / 100));
				}

				Player::MainPlayer->SetMaxHp(Player::MainPlayer->GetMaxHp() + (Player::MainPlayer->GetMaxHp() * 5 / 100));

				PlayUIManager::UI->NewDialog->GetMainRenderer()->SetTexture("NPC_OUTFIT_INDEX3.bmp");


				DialogIndex = -3;
				isAvailable = false;
				Player::MainPlayer->SetOutfitReinforced();

			}
		}

		if (true == GameEngineInput::IsDown(VK_ESCAPE))
		{
			DialogIndex = 0;
		}

		

	}

	else
	{
		m_InteractUI->GetMainRenderer()->Off();
		PlayUIManager::UI->NewDialog->GetMainRenderer()->Off();
		PlayUIManager::UI->NewDialog->GetMainRenderer()->SetTexture("NPC_OUTFIT_INDEX0.bmp");

		DialogIndex = 0;
	}


}
