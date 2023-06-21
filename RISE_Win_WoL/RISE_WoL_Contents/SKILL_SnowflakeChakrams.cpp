#include "SKILL_SnowflakeChakrams.h"
#include <GameEngineCore/ResourcesManager.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"
#include "ContentsEnum.h"

void SKILL_SnowflakeChakrams::Start()
{
	// 스킬 텍스처 로딩
	if (false == ResourcesManager::GetInst().IsLoadTexture("ARCANA_Snowflake_1.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Skill\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ARCANA_Snowflake_1.bmp"));
	}

	// 렌더러 생성과 로딩된 텍스처 지정
	Renderer = CreateRenderer();
	Renderer2 = CreateRenderer();
	Renderer3 = CreateRenderer();


	Renderer->SetRenderScale({ 140, 140 });
	Renderer2->SetRenderScale({ 140, 140 });
	Renderer3->SetRenderScale({ 140, 140 });


	// 위
	Renderer->SetRenderPos({ 0, -140 });


	// 오른쪽
	Renderer2->SetRenderPos({ 120, 100 });


	// 아래
	Renderer3->SetRenderPos({ -120, 100 });


	Renderer->SetTexture("ARCANA_Snowflake_1.bmp");
	Renderer2->SetTexture("ARCANA_Snowflake_1.bmp");
	Renderer3->SetTexture("ARCANA_Snowflake_1.bmp");



	// 충돌체 생성

	BodyCollsion = CreateCollision(CollisionOrder::PlayerSkill);
	BodyCollsion->SetCollisionScale({ 100, 100 });
	BodyCollsion->SetCollisionType(CollisionType::CirCle);
	BodyCollsion->SetCollisionPos({ 0, -140 });


	BodyCollsion2 = CreateCollision(CollisionOrder::PlayerSkill);
	BodyCollsion2->SetCollisionScale({ 100, 100 });
	BodyCollsion2->SetCollisionType(CollisionType::CirCle);
	BodyCollsion2->SetCollisionPos({ 120, 100 });

	BodyCollsion3 = CreateCollision(CollisionOrder::PlayerSkill);
	BodyCollsion3->SetCollisionScale({ 100, 100 });
	BodyCollsion3->SetCollisionType(CollisionType::CirCle);
	BodyCollsion3->SetCollisionPos({ -120, 100 });



	// 추후 define으로 이동
	m_iAttackPower = 50;
}

void SKILL_SnowflakeChakrams::Update(float _Delta)
{

	// 중심축인 플레이어를 기준으로 이동시 스킬도 이동거리에 맞춰서 이동
	float4 Dir = Player::GetMainPlayer()->GetPos() - GetPos();

	AddPos(Dir * _Delta * 400.0f);


	float4 Range;
	float4 Range2;
	float4 Range3;

	static float temp = 100.0f;

	RollAngle += _Delta * 270.0f;


	if (GetLiveTime() < 2.0f)
	{

		Range = float4::GetUnitVectorFromDeg(RollAngle + (360.0f / 3) * 1) * temp;
		Range2 = float4::GetUnitVectorFromDeg(RollAngle + (360.0f / 3) * 2) * temp;
		Range3 = float4::GetUnitVectorFromDeg(RollAngle + (360.0f / 3) * 3) * temp;


		Renderer->SetRenderPos(Range);
		BodyCollsion->SetCollisionPos(Range);

		Renderer2->SetRenderPos(Range2);
		BodyCollsion2->SetCollisionPos(Range2);

		Renderer3->SetRenderPos(Range3);
		BodyCollsion3->SetCollisionPos(Range3);

		temp += 0.3f;
	}

	if (GetLiveTime() > 2.0f && GetLiveTime() < 4.0f)
	{

		Range = float4::GetUnitVectorFromDeg(RollAngle + (360.0f / 3) * 1) * temp;
		Range2 = float4::GetUnitVectorFromDeg(RollAngle + (360.0f / 3) * 2) * temp;
		Range3 = float4::GetUnitVectorFromDeg(RollAngle + (360.0f / 3) * 3) * temp;


		Renderer->SetRenderPos(Range);
		BodyCollsion->SetCollisionPos(Range);

		Renderer2->SetRenderPos(Range2);
		BodyCollsion2->SetCollisionPos(Range2);

		Renderer3->SetRenderPos(Range3);
		BodyCollsion3->SetCollisionPos(Range3);


		temp -= 0.3f;
	}


	if (GetLiveTime() > 4.0f)
	{
		Death();
	}


	if (RollAngle > 360.0f)
	{
		RollAngle -= 360;
	}

}

void SKILL_SnowflakeChakrams::Render(float _Delta)
{

}
