#include "BossSpawner.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Effect_Spawn.h"

#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "Monster.h"


#include "Monster_Swordman.h"
#include "Monster_Archer.h"

#include <GameEnginePlatform/GameEngineWindow.h>

int BossSpawner::MonsterCount = 0;

BossSpawner::BossSpawner()
{
	// 첫번째 웨이브
	{
		std::map<float, std::vector<MonsterSpawnData>> Wave;
		{
			std::vector<MonsterSpawnData> Data;
			Data.push_back(MonsterSpawnData{ SpawnType::Swordman, { 2270, 1534 } });
			Data.push_back(MonsterSpawnData{ SpawnType::Swordman, { 2070, 1534 } });
			Data.push_back(MonsterSpawnData{ SpawnType::Swordman, { 2470, 1534 } });

			Wave.insert(std::make_pair(0.0f, Data));
		}

		{
			std::vector<MonsterSpawnData> Data;
			Data.push_back(MonsterSpawnData{ SpawnType::Swordman, { 2270, 1934 } });
			Data.push_back(MonsterSpawnData{ SpawnType::Swordman, { 2070, 1934 } });
			Data.push_back(MonsterSpawnData{ SpawnType::Swordman, { 2470, 1934 }, true });

			Wave.insert(std::make_pair(1.0f, Data));
		}

		AllSpawnDatas.push_back(Wave);
	}

	// 2번째 웨이브
	{
		std::map<float, std::vector<MonsterSpawnData>> Wave;

		{
			std::vector<MonsterSpawnData> Data;
			Data.push_back(MonsterSpawnData{ SpawnType::Archer, { 2270, 1334 } });
			Data.push_back(MonsterSpawnData{ SpawnType::Archer, { 2070, 1634 } });
			Data.push_back(MonsterSpawnData{ SpawnType::Archer, { 2470, 1634 } });
			Data.push_back(MonsterSpawnData{ SpawnType::Archer, { 2270, 1934 }, true });

			Wave.insert(std::make_pair(5.0f, Data));
		}

		AllSpawnDatas.push_back(Wave);
	}

	// 3번째 웨이브
	{
		std::map<float, std::vector<MonsterSpawnData>> Wave;

		{
			std::vector<MonsterSpawnData> Data;
			Data.push_back(MonsterSpawnData{ SpawnType::GrandSummoner, { 2280, 1634 }, true });

			Wave.insert(std::make_pair(5.0f, Data));
		}

		AllSpawnDatas.push_back(Wave);
	}


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
	Renderer_ActivationCircle->SetRenderPos({ 2270, 1800 });

	Collsion_ActivationCircle = CreateCollision(CollisionOrder::Map);
	Collsion_ActivationCircle->SetCollisionScale({ 200, 200 });
	Collsion_ActivationCircle->SetCollisionType(CollisionType::CirCle);
	Collsion_ActivationCircle->SetCollisionPos({ 2270, 1800 });

	Renderer_Altar = CreateRenderer();
	Renderer_Altar->SetRenderScale({ 120, 160 });
	Renderer_Altar->SetTexture("MiniBossAltar.bmp");
	Renderer_Altar->SetRenderPos({ 2270, 1550 });

	Collsion_Altar = CreateCollision(CollisionOrder::Map);
	Collsion_Altar->SetCollisionScale({ 120, 160 });
	Collsion_Altar->SetCollisionType(CollisionType::Rect);
	Collsion_Altar->SetCollisionPos({ 2270, 1550 });


	// 스포너가 아예 멤버로 가지고 있도록 한다
	m_InteractUI = GetLevel()->CreateActor<UI_KeyboardF>();
	m_InteractUI->SetPos({ 2270, 1660 });
	m_InteractUI->GetMainRenderer()->Off();


	// 벡터로 만들어서 한번에 렌더링하고 해제하도록 수정
	Renderer_FenceUp = CreateRenderer();
	Renderer_FenceUp->SetRenderScale({ 200, 165 });
	Renderer_FenceUp->SetTexture("PRISON_HOR.bmp");
	Renderer_FenceUp->SetRenderPos({ 2276, 1320 });
	Renderer_FenceUp->SetOrder(1);

	Renderer_FenceDown = CreateRenderer();
	Renderer_FenceDown->SetRenderScale({ 200, 165 });
	Renderer_FenceDown->SetTexture("PRISON_HOR.bmp");
	Renderer_FenceDown->SetRenderPos({ 2276, 2224 });

	Renderer_FenceRight = CreateRenderer();
	Renderer_FenceRight->SetRenderScale({ 48, 298 });
	Renderer_FenceRight->SetTexture("PRISON_VER.bmp");
	Renderer_FenceRight->SetRenderPos({ 2785, 1710 });

	Renderer_FenceLeft = CreateRenderer();
	Renderer_FenceLeft->SetRenderScale({ 48, 298 });
	Renderer_FenceLeft->SetTexture("PRISON_VER.bmp");
	Renderer_FenceLeft->SetRenderPos({ 1805, 1710 });
	Renderer_FenceLeft->SetOrder(15);

	Renderer_FenceUp->Off();
	Renderer_FenceDown->Off();
	Renderer_FenceRight->Off();
	Renderer_FenceLeft->Off();

	Collsion_FenceUp = CreateCollision(CollisionOrder::Map);
	Collsion_FenceUp->SetCollisionScale({ 200, 83 });
	Collsion_FenceUp->SetCollisionType(CollisionType::Rect);
	Collsion_FenceUp->SetCollisionPos({ 2276, 1320 });
	Collsion_FenceUp->Off();

	Collsion_FenceDown = CreateCollision(CollisionOrder::Map);
	Collsion_FenceDown->SetCollisionScale({ 200, 165 });
	Collsion_FenceDown->SetCollisionType(CollisionType::Rect);
	Collsion_FenceDown->SetCollisionPos({ 2276, 2224 });
	Collsion_FenceDown->Off();

	Collsion_FenceRight = CreateCollision(CollisionOrder::Map);
	Collsion_FenceRight->SetCollisionScale({ 24, 298 });
	Collsion_FenceRight->SetCollisionType(CollisionType::Rect);
	Collsion_FenceRight->SetCollisionPos({ 2785, 1710 });
	Collsion_FenceRight->Off();

	Collsion_FenceLeft = CreateCollision(CollisionOrder::Map);
	Collsion_FenceLeft->SetCollisionScale({ 24, 298 });
	Collsion_FenceLeft->SetCollisionType(CollisionType::Rect);
	Collsion_FenceLeft->SetCollisionPos({ 1805, 1710 });
	Collsion_FenceLeft->Off();
}

void BossSpawner::MonsterSpawnCheck()
{
	if (false == IsSpawnStart)
	{
		return;
	}

	if (true == IsAllDeathWait)
	{
		if (0 < MonsterCount)
		{
			return;
		}
		else 
		{
			IsAllDeathWait = false;
			ResetLiveTime();
		}
	}

	if (CurWave == AllSpawnDatas.end())
	{
		// 모든 웨이브가 끝났다.
		SetLevelState();

		Renderer_FenceUp->Off();
		Renderer_FenceDown->Off();
		Renderer_FenceRight->Off();
		Renderer_FenceLeft->Off();

		Collsion_FenceUp->Off();
		Collsion_FenceDown->Off();
		Collsion_FenceRight->Off();
		Collsion_FenceLeft->Off();

		return;
	}

	std::map<float, std::vector<MonsterSpawnData>>& CurWaveMap = *CurWave;

	std::map<float, std::vector<MonsterSpawnData>>::iterator StartIter = CurWaveMap.begin();
	std::map<float, std::vector<MonsterSpawnData>>::iterator EndIter = CurWaveMap.end();

	for (; StartIter != EndIter; )
	{
		if (StartIter->first > GetLiveTime())
		{
			++StartIter;
			continue;
		}

		std::vector<MonsterSpawnData>& Datas = StartIter->second;

		for (const MonsterSpawnData& Data : Datas)
		{
			Effect_Spawn* Spawn = GetLevel()->CreateActor<Effect_Spawn>();

			// 이펙트 생성
			Spawn->SpawnObject(Data.Type, { 100, 200 });

			// 이펙트 위치(== 스폰되는 몬스터의 초기 위치)
			Spawn->SetPos(Data.Pos);
			++MonsterCount;

			if (true == Data.IsEnd)
			{
				IsAllDeathWait = true;
				++CurWave;
			}
		}

		StartIter = CurWaveMap.erase(StartIter);
	}


}

void BossSpawner::Update(float _Delta)
{
	MonsterSpawnCheck();



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

			IsSpawnStart = true;

			CurWave = AllSpawnDatas.begin();

			ResetLiveTime();
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

	if (true == GameEngineInput::IsDown('P'))
	{
		Renderer_FenceUp->Off();
		Renderer_FenceDown->Off();
		Renderer_FenceRight->Off();
		Renderer_FenceLeft->Off();

		Collsion_FenceUp->Off();
		Collsion_FenceDown->Off();
		Collsion_FenceRight->Off();
		Collsion_FenceLeft->Off();
	}
}