#include "SKILL_SnowflakeChakrams.h"
#include <GameEngineCore/ResourcesManager.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnum.h"
#include "Player.h"

void SKILL_SnowflakeChakrams::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("ARCANA_Snowflake.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Skill\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("ARCANA_Snowflake.bmp"), 6, 1);

	}

	// 렌더러 생성 - 위
	{
		GameEngineRenderer* Renderer = CreateRenderer();
		Renderer->SetRenderPos({ 0, -140 });
		Renderers.push_back(Renderer);
	}

	// 오른쪽
	{
		GameEngineRenderer* Renderer = CreateRenderer();
		Renderer->SetRenderPos({ 120, 100 });
		Renderers.push_back(Renderer);
	}

	// 왼쪽
	{
		GameEngineRenderer* Renderer = CreateRenderer();
		Renderer->SetRenderPos({ -120, 100 });
		Renderers.push_back(Renderer);
	}

	for (size_t i = 0; i < Renderers.size(); i++)
	{
		Renderers[i]->SetRenderScale({ 140, 140 });
		Renderers[i]->CreateAnimation("ARCANA_Snowflake", "ARCANA_Snowflake.bmp", 0, 5, 0.05f, true);
		Renderers[i]->ChangeAnimation("ARCANA_Snowflake");
	}



	// 충돌체 생성
	{
		GameEngineCollision* BodyCollsion = CreateCollision(CollisionOrder::PlayerSkill);
		BodyCollsion->SetCollisionScale({ 100, 100 });
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
		BodyCollsion->SetCollisionPos({ 0, -140 });
		Collisions.push_back(BodyCollsion);
	}

	{
		GameEngineCollision* BodyCollsion = CreateCollision(CollisionOrder::PlayerSkill);
		BodyCollsion->SetCollisionScale({ 100, 100 });
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
		BodyCollsion->SetCollisionPos({ 120, 100 });
		Collisions.push_back(BodyCollsion);
	}

	{
		GameEngineCollision* BodyCollsion = CreateCollision(CollisionOrder::PlayerSkill);
		BodyCollsion->SetCollisionScale({ 100, 100 });
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
		BodyCollsion->SetCollisionPos({ -120, 100 });
		Collisions.push_back(BodyCollsion);
	}


	// 추후 define으로 이동
	m_iAttackPower = 50 + Player::MainPlayer->ItemBuff;
}

void SKILL_SnowflakeChakrams::Update(float _Delta)
{
	// 중심축인 플레이어를 기준으로 이동시 스킬도 이동거리에 맞춰서 이동
	float4 Dir = Player::GetMainPlayer()->GetPos() - GetPos();
	AddPos(Dir * _Delta * 400.0f);

	RollAngle += _Delta * 360.0f;

	if (RollAngle >= 360.0f)
	{
		RollAngle -= 360.0f;
	}

	for (int i = 0; i < 3; i++)
	{
		Range = float4::GetUnitVectorFromDeg(RollAngle + (360.0f / 3) * i) * Radius;

		if (GetLiveTime() < 2.0f)
		{
			Renderers[i]->SetRenderPos(Range);
			Collisions[i]->SetCollisionPos(Range);
			Radius += 0.1f;
		}

		if (GetLiveTime() > 2.0f && GetLiveTime() < 4.0f)
		{

			Renderers[i]->SetRenderPos(Range);
			Collisions[i]->SetCollisionPos(Range);
			Radius -= 0.1f;

		}

		if (GetLiveTime() > 4.0f)
		{
			Death();
		}

	}
}