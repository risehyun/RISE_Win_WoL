#include "SKILL_PlayerNormalAttack.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"
#include "ContentsEnum.h"

void SKILL_PlayerNormalAttack::Start()
{
	// 스킬 텍스처 로딩
	if (false == ResourcesManager::GetInst().IsLoadTexture("PLAYER_NORMAL_ATTACK.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Skill\\PlayerSkills\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("PLAYER_NORMAL_ATTACK.bmp"), 8, 8);
	}

	// 렌더러 생성과 로딩된 텍스처 지정
	Renderer = CreateRenderer();
	Renderer->SetRenderScale({ 100, 100 });
	Renderer->SetTexture("PLAYER_NORMAL_ATTACK.bmp");


	// 애니메이션 생성
	Renderer->CreateAnimation("ATTACK_NORMAL_LEFT", "PLAYER_NORMAL_ATTACK.bmp", 32, 36, 0.2f, false);
	
	Renderer->CreateAnimation("ATTACK_NORMAL_RIGHT", "PLAYER_NORMAL_ATTACK.bmp", 0, 4, 0.2f, false);

	Renderer->CreateAnimation("ATTACK_NORMAL_UP", "PLAYER_NORMAL_ATTACK.bmp", 16, 20, 0.2f, false);

	Renderer->CreateAnimation("ATTACK_NORMAL_DOWN", "PLAYER_NORMAL_ATTACK.bmp", 49, 52, 0.2f, false);	


	// 충돌체 생성
	{
		BodyCollsion = CreateCollision(CollisionOrder::PlayerBody);
		BodyCollsion->SetCollisionScale({ 100, 100 });
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
	}
}

void SKILL_PlayerNormalAttack::Update(float _Delta)
{
	if (nullptr != BodyCollsion)
	{
		std::vector<GameEngineCollision*> _Col;
		if (true == BodyCollsion->Collision(CollisionOrder::MonsterBody, _Col
			, CollisionType::CirCle // 나를 사각형으로 봐줘
			, CollisionType::CirCle // 상대도 사각형으로 봐줘
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


	

	if (0.4f < GetLiveTime())
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


