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
#include <GameEnginePlatform/GameEngineWindow.h>

BossSpawner::BossSpawner()
{
}

BossSpawner::~BossSpawner()
{
}

void BossSpawner::Start()
{
	// 스킬 텍스처 로딩
	if (false == ResourcesManager::GetInst().IsLoadTexture("MiniBossActivationCircle.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("MiniBossActivationCircle.bmp"), 8, 8);

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("F.bmp"));

	}

	// 렌더러 생성과 로딩된 텍스처 지정
	MainRenderer = CreateRenderer();
	MainRenderer->SetRenderScale({ 200, 200 });
	MainRenderer->SetTexture("MiniBossActivationCircle.bmp");
	MainRenderer->SetRenderPos({ 1850, 1800 });

	Collsion = CreateCollision(CollisionOrder::Map);
	Collsion->SetCollisionScale({ 240, 240 });
	Collsion->SetCollisionType(CollisionType::CirCle);
	Collsion->SetCollisionPos({ 1850, 1800 });


	InputRenderer = CreateRenderer();
	InputRenderer->SetRenderScale({ 32, 32 });
	InputRenderer->SetTexture("F.bmp");
	InputRenderer->SetRenderPos({ 1850, 1634 });

	InputRenderer->Off();

}

void BossSpawner::Update(float _Delta)
{

	std::vector<GameEngineCollision*> _Col;
	if (true == Collsion->Collision(CollisionOrder::PlayerBody, _Col
		, CollisionType::CirCle
		, CollisionType::CirCle
	))
	{
		InputRenderer->On();

		if (true == GameEngineInput::IsDown('F'))
		{
			// 1. MainRenderer를 비활성한다.
			// 2. 몬스터를 지정한 위치에 스폰해준다.

			Collsion->Death();
			MainRenderer->Death();
			InputRenderer->Off();

			Effect_Spawn* Spawn = GetLevel()->CreateActor<Effect_Spawn>();
			Spawn->SpawnObject(SpawnType::Swordman, { 100, 200 });
			Spawn->SetPos({ 1850, 1634 });
				


		}




	}

	else
	{
		InputRenderer->Off();

	}
}