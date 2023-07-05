#include "NPC_Collector.h"

#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineLevel.h>

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "ARCANA_EarthenAegis.h"
#include "ARCANA_SnowflakeChakrams.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "UI_Dialog.h"

#include "PlayUIManager.h"

#include "ITEM_Gold.h"

#include "Player.h"

NPC_Collector::NPC_Collector()
{
}

NPC_Collector::~NPC_Collector()
{
}

void NPC_Collector::Start()
{
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\Texture\\NPC\\COIIECTOR");

	if (false == ResourcesManager::GetInst().IsLoadTexture("NPC_Collector.Bmp"))
	{

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("NPC_Collector.bmp"));
	}

	MainRenderer = CreateRenderer("NPC_Collector.bmp", RenderOrder::BackGround);

	MainRenderer->SetRenderScale({ 150, 150 });

	BodyCollision = CreateCollision(CollisionOrder::Map);
	BodyCollision->SetCollisionScale({ 200, 200 });
	BodyCollision->SetCollisionType(CollisionType::CirCle);

	// 상호작용 UI 설정
	m_InteractUI = GetLevel()->CreateActor<UI_KeyboardF>();

	m_InteractUI->SetPos({ 1850, 2700 });
	m_InteractUI->GetMainRenderer()->SetOrder(2);
	m_InteractUI->GetMainRenderer()->Off();

}

void NPC_Collector::Update(float _Delta)
{

	BodyCollision->CollisionCallBack
	(
		CollisionOrder::PlayerBody
		, CollisionType::CirCle // _this의 충돌체 타입
		, CollisionType::CirCle // _Other의 충돌체 타입
		, [](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			GameEngineActor* thisActor = _this->GetActor();
			NPC_Collector* ActorPtr = dynamic_cast<NPC_Collector*>(thisActor);

			ActorPtr->m_InteractUI->GetMainRenderer()->On();


		}

		, [](GameEngineCollision* _this, GameEngineCollision* _Other)
		{

			GameEngineActor* thisActor = _this->GetActor();
			NPC_Collector* ActorPtr = dynamic_cast<NPC_Collector*>(thisActor);

			if (true == GameEngineInput::IsDown('F'))
			{
				PlayUIManager::UI->NewDialog->GetMainRenderer()->On();
				PlayUIManager::UI->NewDialog->GetMainRenderer()->SetTexture("NPC_COLLECTOR_INDEX.bmp");
			}

			if (true == GameEngineInput::IsDown(VK_RETURN))
			{
				PlayUIManager::UI->NewDialog->GetMainRenderer()->Off();
			}

			if (true == GameEngineInput::IsDown(VK_SHIFT) && true == Player::MainPlayer->HasAnalyticalMonocle())
			{
				// 아이템 생성 + 돈 생성

				for (size_t i = 0; i < 5; i++)
				{
					ITEM_Gold* NewGold = ActorPtr->GetLevel()->CreateActor<ITEM_Gold>();
					NewGold->SetPos({ ActorPtr->GetPos().X, ActorPtr->GetPos().Y - 100 });
				}

				Player::MainPlayer->UnSetAnalyticalMonocle();
			}

		}

		, [](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			GameEngineActor* thisActor = _this->GetActor();
			NPC_Collector* ActorPtr = dynamic_cast<NPC_Collector*>(thisActor);

			ActorPtr->m_InteractUI->GetMainRenderer()->Off();

			PlayUIManager::UI->NewDialog->GetMainRenderer()->Off();
		}


		);

	//// 캐릭터와 충돌 상태인 경우 F 키를 눌러서 대화 가능
	//std::vector<GameEngineCollision*> _Col;
	//if (true == BodyCollision->Collision(CollisionOrder::PlayerBody, _Col
	//	, CollisionType::CirCle
	//	, CollisionType::CirCle
	//))
	//{

	//}

	//else
	//{

	//}
}
