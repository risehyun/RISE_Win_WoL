#include "SKILL_PlayerWindBoomerang.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"
#include "ContentsEnum.h"

void SKILL_PlayerWindBoomerang::Start()
{
	// 스킬 텍스처 로딩
	if (false == ResourcesManager::GetInst().IsLoadTexture("PLAYER_WINDBOOMERANG_ATTACK.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Skill\\PlayerSkills\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("PLAYER_WINDBOOMERANG_ATTACK.bmp"), 4, 1);
	}

	// 렌더러 생성과 로딩된 텍스처 지정
	Renderer = CreateRenderer();
	Renderer->SetRenderScale({ 100, 100 });
	Renderer->SetTexture("PLAYER_WINDBOOMERANG_ATTACK.bmp");

	// 애니메이션 생성
	Renderer->CreateAnimation("ATTACK_WINDBOOMERANG", "PLAYER_WINDBOOMERANG_ATTACK.bmp", 0, 3, 0.1f, true);


	// 충돌체 생성
	{
		BodyCollsion = CreateCollision(CollisionOrder::PlayerSkill);
		BodyCollsion->SetCollisionScale({ 100, 100 });
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
	}
}

void SKILL_PlayerWindBoomerang::Update(float _Delta)
{
	// 이동 => 방향 전환 필요

	float4 NextPos = Dir * _Delta * Speed;

	// livetime으로 구분
	// 도착지점은 처음 생성되었을 때의 지점이 되어야하고
	// 플레이어 중심에 부딪히면 소멸하는 방식도 있음
	if (0.4f <= GetLiveTime())
	{
		AddPos(NextPos);
	}

	else
	{
		AddPos(-NextPos);
	}


	// 데미지 처리
	if (nullptr != BodyCollsion)
	{
		std::vector<GameEngineCollision*> _Col;
		if (true == BodyCollsion->Collision(CollisionOrder::MonsterBody, _Col
			, CollisionType::CirCle
			, CollisionType::CirCle
		))
		{
			for (size_t i = 0; i < _Col.size(); i++)
			{
				GameEngineCollision* Collison = _Col[i];

				GameEngineActor* Actor = Collison->GetActor();

				Actor->Death();
			}
		}
	}

	if (0.8f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			Renderer->Death();
			Renderer = nullptr;

			BodyCollsion->Death();
			BodyCollsion = nullptr;
		}
	}
}