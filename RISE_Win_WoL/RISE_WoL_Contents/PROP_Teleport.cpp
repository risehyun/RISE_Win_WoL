#include "PROP_Teleport.h"
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCore.h>

PROP_Teleport::PROP_Teleport()
{
}

PROP_Teleport::~PROP_Teleport()
{
}

void PROP_Teleport::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("TELEPORT.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Level");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("TELEPORT.bmp"), 5, 1);
	}

	// 렌더러 생성과 로딩된 텍스처 지정
	MainRenderer = CreateRenderer();
	MainRenderer->SetRenderScale({ 200, 200 });

	BodyCollision = CreateCollision(CollisionOrder::Map);
	BodyCollision->SetCollisionScale({ 100, 100 });
	BodyCollision->SetCollisionType(CollisionType::CirCle);

	MainRenderer->SetTexture("TELEPORT.bmp");
	MainRenderer->SetOrder(0);


	// 상호작용 UI 설정
	m_InteractUI = GetLevel()->CreateActor<UI_KeyboardF>();
	m_InteractUI->SetPos({ 1850, 1850 });
	m_InteractUI->GetMainRenderer()->SetOrder(2);
	m_InteractUI->GetMainRenderer()->Off();
}

void PROP_Teleport::Update(float _Delta)
{
	// 캐릭터와 충돌 상태인 경우 F 키를 눌러서 다음 스테이지로 이동 가능
	std::vector<GameEngineCollision*> _Col;
	if (true == BodyCollision->Collision(CollisionOrder::PlayerBody, _Col
		, CollisionType::CirCle
		, CollisionType::CirCle
	))
	{
		m_InteractUI->GetMainRenderer()->On();

		if (true == GameEngineInput::IsDown('F'))
		{
			GameEngineCore::ChangeLevel("BossLevel");
		}
	}

	else
	{
		m_InteractUI->GetMainRenderer()->Off();
	}
}