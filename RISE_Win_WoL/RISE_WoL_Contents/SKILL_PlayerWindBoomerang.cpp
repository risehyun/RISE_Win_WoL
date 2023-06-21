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
	if (false == ResourcesManager::GetInst().IsLoadTexture("ICE_BLAST.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Skill");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("ICE_BLAST.bmp"), 6, 1);
	}

	// 렌더러 생성과 로딩된 텍스처 지정
	Renderer = CreateRenderer();
	Renderer->SetRenderScale({ 200, 200 });

	// 애니메이션 생성
	Renderer->CreateAnimation("ATTACK_WINDBOOMERANG", "ICE_BLAST.bmp", 2, 0, 0.2f, true);
	Renderer->CreateAnimation("ATTACK_WINDBOOMERANG_END", "ICE_BLAST.bmp", 2, 0, 0.2f, false);

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
	if (2.0f > GetLiveTime())
	{
		AddPos(NextPos);
	}

	else
	{
		if (Player::GetMainPlayer()->GetPos().X < GetPos().X
			|| Player::GetMainPlayer()->GetPos().X > GetPos().X
			|| Player::GetMainPlayer()->GetPos().Y < GetPos().Y
			|| Player::GetMainPlayer()->GetPos().Y > GetPos().Y)
		{
			AddPos(-NextPos);
		}
			
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

	if (4.0f < GetLiveTime())
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