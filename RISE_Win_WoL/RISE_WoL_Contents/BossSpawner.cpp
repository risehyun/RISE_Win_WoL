#include "BossSpawner.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Effect_Spawn.h"

// CreateActor()
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "Monster.h"
#include "Monster_Swordman.h"

#include "UI_KeyboardF.h"

#include <GameEnginePlatform/GameEngineWindow.h>

BossSpawner::BossSpawner()
{
}

BossSpawner::~BossSpawner()
{
}

void BossSpawner::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("MiniBossActivationCircle.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("MiniBossActivationCircle.bmp"), 8, 8);

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("PRISON_HOR.bmp"));

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("PRISON_VER.bmp"));

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MiniBossAltar.bmp"));
	}

	Renderer_ActivationCircle = CreateRenderer();
	Renderer_ActivationCircle->SetRenderScale({ 200, 200 });
	Renderer_ActivationCircle->SetTexture("MiniBossActivationCircle.bmp");
	Renderer_ActivationCircle->SetRenderPos({ 1850, 1800 });

	Collsion_ActivationCircle = CreateCollision(CollisionOrder::Map);
	Collsion_ActivationCircle->SetCollisionScale({ 200, 200 });
	Collsion_ActivationCircle->SetCollisionType(CollisionType::CirCle);
	Collsion_ActivationCircle->SetCollisionPos({ 1850, 1800 });

	Renderer_Altar = CreateRenderer();
	Renderer_Altar->SetRenderScale({ 120, 160 });
	Renderer_Altar->SetTexture("MiniBossAltar.bmp");
	Renderer_Altar->SetRenderPos({ 1850, 1550 });

	Collsion_Altar = CreateCollision(CollisionOrder::Map);
	Collsion_Altar->SetCollisionScale({ 120, 160 });
	Collsion_Altar->SetCollisionType(CollisionType::Rect);
	Collsion_Altar->SetCollisionPos({ 1850, 1550 });


	// 스포너가 아예 멤버로 가지고 있도록 한다
	m_InteractUI = GetLevel()->CreateActor<UI_KeyboardF>();
	m_InteractUI->SetPos({ 1850, 1660 });
	m_InteractUI->GetMainRenderer()->Off();


	// 벡터로 만들어서 한번에 렌더링하고 해제하도록 수정
	Renderer_FenceUp = CreateRenderer();
	Renderer_FenceUp->SetRenderScale({ 200, 165 });
	Renderer_FenceUp->SetTexture("PRISON_HOR.bmp");
	Renderer_FenceUp->SetRenderPos({ 1850, 1320 });

	Renderer_FenceDown = CreateRenderer();
	Renderer_FenceDown->SetRenderScale({ 200, 165 });
	Renderer_FenceDown->SetTexture("PRISON_HOR.bmp");
	Renderer_FenceDown->SetRenderPos({ 1850, 2224 });

	Renderer_FenceRight = CreateRenderer();
	Renderer_FenceRight->SetRenderScale({ 48, 298 });
	Renderer_FenceRight->SetTexture("PRISON_VER.bmp");
	Renderer_FenceRight->SetRenderPos({ 2360, 1710 });

	Renderer_FenceLeft = CreateRenderer();
	Renderer_FenceLeft->SetRenderScale({ 48, 298 });
	Renderer_FenceLeft->SetTexture("PRISON_VER.bmp");
	Renderer_FenceLeft->SetRenderPos({ 1380, 1710 });

	Renderer_FenceUp->Off();
	Renderer_FenceDown->Off();
	Renderer_FenceRight->Off();
	Renderer_FenceLeft->Off();

	Collsion_FenceUp = CreateCollision(CollisionOrder::Map);
	Collsion_FenceUp->SetCollisionScale({ 200, 83 });
	Collsion_FenceUp->SetCollisionType(CollisionType::Rect);
	Collsion_FenceUp->SetCollisionPos({ 1850, 1320 });
	Collsion_FenceUp->Off();

	Collsion_FenceDown = CreateCollision(CollisionOrder::Map);
	Collsion_FenceDown->SetCollisionScale({ 200, 165 });
	Collsion_FenceDown->SetCollisionType(CollisionType::Rect);
	Collsion_FenceDown->SetCollisionPos({ 1850, 2224 });
	Collsion_FenceDown->Off();

	Collsion_FenceRight = CreateCollision(CollisionOrder::Map);
	Collsion_FenceRight->SetCollisionScale({ 24, 298 });
	Collsion_FenceRight->SetCollisionType(CollisionType::Rect);
	Collsion_FenceRight->SetCollisionPos({ 2360, 1710 });
	Collsion_FenceRight->Off();

	Collsion_FenceLeft = CreateCollision(CollisionOrder::Map);
	Collsion_FenceLeft->SetCollisionScale({ 24, 298 });
	Collsion_FenceLeft->SetCollisionType(CollisionType::Rect);
	Collsion_FenceLeft->SetCollisionPos({ 1360, 1710 });
	Collsion_FenceLeft->Off();
}

void BossSpawner::Update(float _Delta)
{
	std::vector<GameEngineCollision*> _Col;
	if (true == Collsion_ActivationCircle->Collision(CollisionOrder::PlayerBody, _Col
		, CollisionType::CirCle
		, CollisionType::CirCle
	))
	{
		m_InteractUI->GetMainRenderer()->On();

		if (true == GameEngineInput::IsDown('F'))
		{
			// 1. MainRenderer를 비활성한다.
			// 2. 몬스터를 지정한 위치에 스폰해준다.

			Collsion_ActivationCircle->Death();
			Renderer_ActivationCircle->Death();

			Renderer_Altar->Death();
			Collsion_Altar->Death();

			m_InteractUI->Off();

			Renderer_FenceUp->On();
			Renderer_FenceDown->On();
			Renderer_FenceRight->On();
			Renderer_FenceLeft->On();

			Collsion_FenceUp->On();
			Collsion_FenceDown->On();
			Collsion_FenceRight->On();
			Collsion_FenceLeft->On();

			Effect_Spawn* Spawn = GetLevel()->CreateActor<Effect_Spawn>();
			Spawn->SpawnObject(SpawnType::Swordman, { 100, 200 });
			Spawn->SetPos({ 1850, 1634 });
			
		}
	}

	else
	{
		m_InteractUI->GetMainRenderer()->Off();
	}

	if (true == Collsion_FenceUp->Collision(CollisionOrder::PlayerBody, _Col
		, CollisionType::Rect
		, CollisionType::CirCle
	))
	{
		// 플레이어를 밀어낸다.
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			Actor->AddPos(float4::DOWN);
		}
	}

	if (true == Collsion_FenceDown->Collision(CollisionOrder::PlayerBody, _Col
		, CollisionType::Rect
		, CollisionType::CirCle
	))
	{
		// 플레이어를 밀어낸다.
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			Actor->AddPos(float4::UP);
		}
	}

	if (true == Collsion_FenceRight->Collision(CollisionOrder::PlayerBody, _Col
		, CollisionType::Rect
		, CollisionType::CirCle
	))
	{
		// 플레이어를 밀어낸다.
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			Actor->AddPos(float4::LEFT);
		}
	}

	if (true == Collsion_FenceLeft->Collision(CollisionOrder::PlayerBody, _Col
		, CollisionType::Rect
		, CollisionType::CirCle
	))
	{
		// 플레이어를 밀어낸다.
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			Actor->AddPos(float4::RIGHT);
		}
	}

	if (true == Collsion_Altar->Collision(CollisionOrder::PlayerBody, _Col
		, CollisionType::Rect
		, CollisionType::CirCle
	))
	{

		// 플레이어를 밀어낸다.
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			Actor->AddPos(float4::DOWN);

		}
	}
}