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

	// ������ ���� - ��
	{
		GameEngineRenderer* Renderer = CreateRenderer();
		Renderer->SetRenderPos({ 0, -140 });
		Renderers.push_back(Renderer);
	}

	// ������
	{
		GameEngineRenderer* Renderer = CreateRenderer();
		Renderer->SetRenderPos({ 120, 100 });
		Renderers.push_back(Renderer);
	}

	// ����
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



	// �浹ü ����
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


	// ���� define���� �̵�
	m_iAttackPower = 50 + Player::MainPlayer->ItemBuff;
}

void SKILL_SnowflakeChakrams::Update(float _Delta)
{
	// �߽����� �÷��̾ �������� �̵��� ��ų�� �̵��Ÿ��� ���缭 �̵�
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