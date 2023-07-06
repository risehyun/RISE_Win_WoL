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
	MainRenderer->SetOrder(2);

	ShadowRenderer = CreateRenderer();
	ShadowRenderer->SetRenderPos({ GetPos().X + 5.0f, GetPos().Y + 70.0f });
	ShadowRenderer->SetRenderScale({ 70, 35 });
	ShadowRenderer->SetTexture("PLAYER_SHADOW.bmp");
	ShadowRenderer->SetOrder(1);

	BodyCollision = CreateCollision(CollisionOrder::Map);
	BodyCollision->SetCollisionScale({ 100, 100 });
	BodyCollision->SetCollisionType(CollisionType::CirCle);


	// 상호작용 UI 설정
	m_InteractUI = GetLevel()->CreateActor<UI_KeyboardF>();

	m_InteractUI->SetPos({ 2270, 600 });
	m_InteractUI->GetMainRenderer()->SetOrder(2);
	m_InteractUI->GetMainRenderer()->Off();

}

void NPC_Outfit::Update(float _Delta)
{


	BodyCollision->CollisionCallBack
	(
		CollisionOrder::PlayerBody
		, CollisionType::CirCle // _this의 충돌체 타입
		, CollisionType::CirCle // _Other의 충돌체 타입
		, [](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			GameEngineActor* thisActor = _this->GetActor();
			NPC_Outfit* ActorPtr = dynamic_cast<NPC_Outfit*>(thisActor);

			ActorPtr->m_InteractUI->GetMainRenderer()->On();




		}

		, [](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			GameEngineActor* thisActor = _this->GetActor();
			NPC_Outfit* ActorPtr = dynamic_cast<NPC_Outfit*>(thisActor);


			if (true == GameEngineInput::IsDown('F') && true == ActorPtr->isAvailable)
			{
				PlayUIManager::UI->NewDialog->GetMainRenderer()->SetTexture("NPC_OUTFIT_INDEX0.bmp");
				PlayUIManager::UI->NewDialog->GetMainRenderer()->On();
			}

			if (true == GameEngineInput::IsDown(VK_RETURN) && ActorPtr->DialogIndex != -2)
			{
				ActorPtr->DialogIndex++;
			}

			if (ActorPtr->DialogIndex == -2)
			{
				PlayUIManager::UI->NewDialog->GetMainRenderer()->Off();
			}

			if (ActorPtr->DialogIndex == 1)
			{
				PlayUIManager::UI->NewDialog->GetMainRenderer()->SetTexture("NPC_OUTFIT_INDEX1.bmp");
			}

			if (ActorPtr->DialogIndex == 2)
			{
				PlayUIManager::UI->NewDialog->GetMainRenderer()->SetTexture("NPC_OUTFIT_INDEX2.bmp");

				if (true == GameEngineInput::IsDown(VK_ESCAPE))
				{
					PlayUIManager::UI->NewDialog->GetMainRenderer()->Off();
					ActorPtr->DialogIndex = 0;

				}
			}

			if (ActorPtr->DialogIndex == 3)
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


					ActorPtr->DialogIndex = -3;
					ActorPtr->isAvailable = false;
					Player::MainPlayer->SetOutfitReinforced();

				}
			}

		}

		, [](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			GameEngineActor* thisActor = _this->GetActor();
			NPC_Outfit* ActorPtr = dynamic_cast<NPC_Outfit*>(thisActor);

			ActorPtr->m_InteractUI->GetMainRenderer()->Off();
			PlayUIManager::UI->NewDialog->GetMainRenderer()->Off();

			ActorPtr->DialogIndex = 0;
		}
		);
}
