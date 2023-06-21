#include "SKILL_EarthenAegis.h"
#include <GameEngineCore/ResourcesManager.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"
#include "ContentsEnum.h"
#include <GameEnginePlatform/GameEngineWindow.h>

void SKILL_EarthenAegis::Start()
{
	// 스킬 텍스처 로딩
	if (false == ResourcesManager::GetInst().IsLoadTexture("ARCANA_EarthenAegis_ALL.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Skill\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("ARCANA_EarthenAegis_ALL.bmp"), 12, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("RockPop.bmp"), 4, 1);
	}

	// 렌더러 생성과 로딩된 텍스처 지정
	Renderer = CreateRenderer();
	Renderer2 = CreateRenderer();
	Renderer3 = CreateRenderer();
	Renderer4 = CreateRenderer();
	Renderer5 = CreateRenderer();
	Renderer6 = CreateRenderer();
	Renderer7 = CreateRenderer();
	Renderer8 = CreateRenderer();

	Renderer->SetRenderScale({ 70, 70 });
	Renderer2->SetRenderScale({ 70, 70 });
	Renderer3->SetRenderScale({ 70, 70 });
	Renderer4->SetRenderScale({ 70, 70 });
	Renderer5->SetRenderScale({ 70, 70 });
	Renderer6->SetRenderScale({ 70, 70 });
	Renderer7->SetRenderScale({ 70, 70 });
	Renderer8->SetRenderScale({ 70, 70 });

	float PlayerX = Player::GetMainPlayer()->GetPos().X;

	// 아래
	Renderer->SetRenderPos({ 0, 100 });

	// 위
	Renderer2->SetRenderPos({ 0, -100 });

	// 오른쪽
	Renderer3->SetRenderPos({ 100, 0 });

	// 왼쪽
	Renderer4->SetRenderPos({ -100, 0 });

	// 대각선 오-위
	Renderer5->SetRenderPos({ 70, -70 });

	// 대각선 왼-아
	Renderer6->SetRenderPos({ -70, 70 });

	// 대각선 오-아
	Renderer7->SetRenderPos({ 70, 70 });

	// 대각선 왼-위
	Renderer8->SetRenderPos({ -70, -70 });


	//// 애니메이션 생성
	// 렌더러는 계속 공전이동을 하고 각도 값이 바뀔 때 다음 각도에 해당하는 애니메이션으로 교체됨 => Switch문으로 애니메이션 이름을 추가해서 변경
	// 회전 함수 추가




#pragma region 애니메이션 생성

	Renderer->CreateAnimation("RockPop", "RockPop.bmp", 0, 3, 0.05f, false);
	Renderer2->CreateAnimation("RockPop", "RockPop.bmp", 0, 3, 0.05f, false);
	Renderer3->CreateAnimation("RockPop", "RockPop.bmp", 0, 3, 0.05f, false);
	Renderer4->CreateAnimation("RockPop", "RockPop.bmp", 0, 3, 0.05f, false);
	Renderer5->CreateAnimation("RockPop", "RockPop.bmp", 0, 3, 0.05f, false);
	Renderer6->CreateAnimation("RockPop", "RockPop.bmp", 0, 3, 0.05f, false);
	Renderer7->CreateAnimation("RockPop", "RockPop.bmp", 0, 3, 0.05f, false);
	Renderer8->CreateAnimation("RockPop", "RockPop.bmp", 0, 3, 0.05f, false);


	Renderer->CreateAnimation("ATTACK_EarthenAegis_Dgr360", "ARCANA_EarthenAegis_ALL.bmp", 0, 0, 0.2f, true);
	Renderer->CreateAnimation("ATTACK_EarthenAegis_Dgr30", "ARCANA_EarthenAegis_ALL.bmp", 1, 1, 0.2f, true);
	Renderer->CreateAnimation("ATTACK_EarthenAegis_Dgr60", "ARCANA_EarthenAegis_ALL.bmp", 2, 2, 0.2f, true);
	Renderer->CreateAnimation("ATTACK_EarthenAegis_Dgr90", "ARCANA_EarthenAegis_ALL.bmp", 3, 3, 0.2f, true);
	Renderer->CreateAnimation("ATTACK_EarthenAegis_Dgr120", "ARCANA_EarthenAegis_ALL.bmp", 4, 4, 0.2f, true);
	Renderer->CreateAnimation("ATTACK_EarthenAegis_Dgr150", "ARCANA_EarthenAegis_ALL.bmp", 5, 5, 0.2f, true);
	Renderer->CreateAnimation("ATTACK_EarthenAegis_Dgr180", "ARCANA_EarthenAegis_ALL.bmp", 6, 6, 0.2f, true);
	Renderer->CreateAnimation("ATTACK_EarthenAegis_Dgr210", "ARCANA_EarthenAegis_ALL.bmp", 7, 7, 0.2f, true);
	Renderer->CreateAnimation("ATTACK_EarthenAegis_Dgr240", "ARCANA_EarthenAegis_ALL.bmp", 8, 8, 0.2f, true);
	Renderer->CreateAnimation("ATTACK_EarthenAegis_Dgr270", "ARCANA_EarthenAegis_ALL.bmp", 9, 9, 0.2f, true);
	Renderer->CreateAnimation("ATTACK_EarthenAegis_Dgr300", "ARCANA_EarthenAegis_ALL.bmp", 10, 10, 0.2f, true);
	Renderer->CreateAnimation("ATTACK_EarthenAegis_Dgr330", "ARCANA_EarthenAegis_ALL.bmp", 11, 11, 0.2f, true);



	Renderer2->CreateAnimation("ATTACK_EarthenAegis_Dgr360", "ARCANA_EarthenAegis_ALL.bmp", 0, 0, 0.2f, true);
	Renderer2->CreateAnimation("ATTACK_EarthenAegis_Dgr30", "ARCANA_EarthenAegis_ALL.bmp", 1, 1, 0.2f, true);
	Renderer2->CreateAnimation("ATTACK_EarthenAegis_Dgr60", "ARCANA_EarthenAegis_ALL.bmp", 2, 2, 0.2f, true);
	Renderer2->CreateAnimation("ATTACK_EarthenAegis_Dgr90", "ARCANA_EarthenAegis_ALL.bmp", 3, 3, 0.2f, true);
	Renderer2->CreateAnimation("ATTACK_EarthenAegis_Dgr120", "ARCANA_EarthenAegis_ALL.bmp", 4, 4, 0.2f, true);
	Renderer2->CreateAnimation("ATTACK_EarthenAegis_Dgr150", "ARCANA_EarthenAegis_ALL.bmp", 5, 5, 0.2f, true);
	Renderer2->CreateAnimation("ATTACK_EarthenAegis_Dgr180", "ARCANA_EarthenAegis_ALL.bmp", 6, 6, 0.2f, true);
	Renderer2->CreateAnimation("ATTACK_EarthenAegis_Dgr210", "ARCANA_EarthenAegis_ALL.bmp", 7, 7, 0.2f, true);
	Renderer2->CreateAnimation("ATTACK_EarthenAegis_Dgr240", "ARCANA_EarthenAegis_ALL.bmp", 8, 8, 0.2f, true);
	Renderer2->CreateAnimation("ATTACK_EarthenAegis_Dgr270", "ARCANA_EarthenAegis_ALL.bmp", 9, 9, 0.2f, true);
	Renderer2->CreateAnimation("ATTACK_EarthenAegis_Dgr300", "ARCANA_EarthenAegis_ALL.bmp", 10, 10, 0.2f, true);
	Renderer2->CreateAnimation("ATTACK_EarthenAegis_Dgr330", "ARCANA_EarthenAegis_ALL.bmp", 11, 11, 0.2f, true);


	Renderer3->CreateAnimation("ATTACK_EarthenAegis_Dgr360", "ARCANA_EarthenAegis_ALL.bmp", 0, 0, 0.2f, true);
	Renderer3->CreateAnimation("ATTACK_EarthenAegis_Dgr30", "ARCANA_EarthenAegis_ALL.bmp", 1, 1, 0.2f, true);
	Renderer3->CreateAnimation("ATTACK_EarthenAegis_Dgr60", "ARCANA_EarthenAegis_ALL.bmp", 2, 2, 0.2f, true);
	Renderer3->CreateAnimation("ATTACK_EarthenAegis_Dgr90", "ARCANA_EarthenAegis_ALL.bmp", 3, 3, 0.2f, true);
	Renderer3->CreateAnimation("ATTACK_EarthenAegis_Dgr120", "ARCANA_EarthenAegis_ALL.bmp", 4, 4, 0.2f, true);
	Renderer3->CreateAnimation("ATTACK_EarthenAegis_Dgr150", "ARCANA_EarthenAegis_ALL.bmp", 5, 5, 0.2f, true);
	Renderer3->CreateAnimation("ATTACK_EarthenAegis_Dgr180", "ARCANA_EarthenAegis_ALL.bmp", 6, 6, 0.2f, true);
	Renderer3->CreateAnimation("ATTACK_EarthenAegis_Dgr210", "ARCANA_EarthenAegis_ALL.bmp", 7, 7, 0.2f, true);
	Renderer3->CreateAnimation("ATTACK_EarthenAegis_Dgr240", "ARCANA_EarthenAegis_ALL.bmp", 8, 8, 0.2f, true);
	Renderer3->CreateAnimation("ATTACK_EarthenAegis_Dgr270", "ARCANA_EarthenAegis_ALL.bmp", 9, 9, 0.2f, true);
	Renderer3->CreateAnimation("ATTACK_EarthenAegis_Dgr300", "ARCANA_EarthenAegis_ALL.bmp", 10, 10, 0.2f, true);
	Renderer3->CreateAnimation("ATTACK_EarthenAegis_Dgr330", "ARCANA_EarthenAegis_ALL.bmp", 11, 11, 0.2f, true);



	Renderer4->CreateAnimation("ATTACK_EarthenAegis_Dgr360", "ARCANA_EarthenAegis_ALL.bmp", 0, 0, 0.2f, true);
	Renderer4->CreateAnimation("ATTACK_EarthenAegis_Dgr30", "ARCANA_EarthenAegis_ALL.bmp", 1, 1, 0.2f, true);
	Renderer4->CreateAnimation("ATTACK_EarthenAegis_Dgr60", "ARCANA_EarthenAegis_ALL.bmp", 2, 2, 0.2f, true);
	Renderer4->CreateAnimation("ATTACK_EarthenAegis_Dgr90", "ARCANA_EarthenAegis_ALL.bmp", 3, 3, 0.2f, true);
	Renderer4->CreateAnimation("ATTACK_EarthenAegis_Dgr120", "ARCANA_EarthenAegis_ALL.bmp", 4, 4, 0.2f, true);
	Renderer4->CreateAnimation("ATTACK_EarthenAegis_Dgr150", "ARCANA_EarthenAegis_ALL.bmp", 5, 5, 0.2f, true);
	Renderer4->CreateAnimation("ATTACK_EarthenAegis_Dgr180", "ARCANA_EarthenAegis_ALL.bmp", 6, 6, 0.2f, true);
	Renderer4->CreateAnimation("ATTACK_EarthenAegis_Dgr210", "ARCANA_EarthenAegis_ALL.bmp", 7, 7, 0.2f, true);
	Renderer4->CreateAnimation("ATTACK_EarthenAegis_Dgr240", "ARCANA_EarthenAegis_ALL.bmp", 8, 8, 0.2f, true);
	Renderer4->CreateAnimation("ATTACK_EarthenAegis_Dgr270", "ARCANA_EarthenAegis_ALL.bmp", 9, 9, 0.2f, true);
	Renderer4->CreateAnimation("ATTACK_EarthenAegis_Dgr300", "ARCANA_EarthenAegis_ALL.bmp", 10, 10, 0.2f, true);
	Renderer4->CreateAnimation("ATTACK_EarthenAegis_Dgr330", "ARCANA_EarthenAegis_ALL.bmp", 11, 11, 0.2f, true);


	Renderer5->CreateAnimation("ATTACK_EarthenAegis_Dgr360", "ARCANA_EarthenAegis_ALL.bmp", 0, 0, 0.2f, true);
	Renderer5->CreateAnimation("ATTACK_EarthenAegis_Dgr30", "ARCANA_EarthenAegis_ALL.bmp", 1, 1, 0.2f, true);
	Renderer5->CreateAnimation("ATTACK_EarthenAegis_Dgr60", "ARCANA_EarthenAegis_ALL.bmp", 2, 2, 0.2f, true);
	Renderer5->CreateAnimation("ATTACK_EarthenAegis_Dgr90", "ARCANA_EarthenAegis_ALL.bmp", 3, 3, 0.2f, true);
	Renderer5->CreateAnimation("ATTACK_EarthenAegis_Dgr120", "ARCANA_EarthenAegis_ALL.bmp", 4, 4, 0.2f, true);
	Renderer5->CreateAnimation("ATTACK_EarthenAegis_Dgr150", "ARCANA_EarthenAegis_ALL.bmp", 5, 5, 0.2f, true);
	Renderer5->CreateAnimation("ATTACK_EarthenAegis_Dgr180", "ARCANA_EarthenAegis_ALL.bmp", 6, 6, 0.2f, true);
	Renderer5->CreateAnimation("ATTACK_EarthenAegis_Dgr210", "ARCANA_EarthenAegis_ALL.bmp", 7, 7, 0.2f, true);
	Renderer5->CreateAnimation("ATTACK_EarthenAegis_Dgr240", "ARCANA_EarthenAegis_ALL.bmp", 8, 8, 0.2f, true);
	Renderer5->CreateAnimation("ATTACK_EarthenAegis_Dgr270", "ARCANA_EarthenAegis_ALL.bmp", 9, 9, 0.2f, true);
	Renderer5->CreateAnimation("ATTACK_EarthenAegis_Dgr300", "ARCANA_EarthenAegis_ALL.bmp", 10, 10, 0.2f, true);
	Renderer5->CreateAnimation("ATTACK_EarthenAegis_Dgr330", "ARCANA_EarthenAegis_ALL.bmp", 11, 11, 0.2f, true);


	Renderer6->CreateAnimation("ATTACK_EarthenAegis_Dgr360", "ARCANA_EarthenAegis_ALL.bmp", 0, 0, 0.2f, true);
	Renderer6->CreateAnimation("ATTACK_EarthenAegis_Dgr30", "ARCANA_EarthenAegis_ALL.bmp", 1, 1, 0.2f, true);
	Renderer6->CreateAnimation("ATTACK_EarthenAegis_Dgr60", "ARCANA_EarthenAegis_ALL.bmp", 2, 2, 0.2f, true);
	Renderer6->CreateAnimation("ATTACK_EarthenAegis_Dgr90", "ARCANA_EarthenAegis_ALL.bmp", 3, 3, 0.2f, true);
	Renderer6->CreateAnimation("ATTACK_EarthenAegis_Dgr120", "ARCANA_EarthenAegis_ALL.bmp", 4, 4, 0.2f, true);
	Renderer6->CreateAnimation("ATTACK_EarthenAegis_Dgr150", "ARCANA_EarthenAegis_ALL.bmp", 5, 5, 0.2f, true);
	Renderer6->CreateAnimation("ATTACK_EarthenAegis_Dgr180", "ARCANA_EarthenAegis_ALL.bmp", 6, 6, 0.2f, true);
	Renderer6->CreateAnimation("ATTACK_EarthenAegis_Dgr210", "ARCANA_EarthenAegis_ALL.bmp", 7, 7, 0.2f, true);
	Renderer6->CreateAnimation("ATTACK_EarthenAegis_Dgr240", "ARCANA_EarthenAegis_ALL.bmp", 8, 8, 0.2f, true);
	Renderer6->CreateAnimation("ATTACK_EarthenAegis_Dgr270", "ARCANA_EarthenAegis_ALL.bmp", 9, 9, 0.2f, true);
	Renderer6->CreateAnimation("ATTACK_EarthenAegis_Dgr300", "ARCANA_EarthenAegis_ALL.bmp", 10, 10, 0.2f, true);
	Renderer6->CreateAnimation("ATTACK_EarthenAegis_Dgr330", "ARCANA_EarthenAegis_ALL.bmp", 11, 11, 0.2f, true);

	Renderer7->CreateAnimation("ATTACK_EarthenAegis_Dgr360", "ARCANA_EarthenAegis_ALL.bmp", 0, 0, 0.2f, true);
	Renderer7->CreateAnimation("ATTACK_EarthenAegis_Dgr30", "ARCANA_EarthenAegis_ALL.bmp", 1, 1, 0.2f, true);
	Renderer7->CreateAnimation("ATTACK_EarthenAegis_Dgr60", "ARCANA_EarthenAegis_ALL.bmp", 2, 2, 0.2f, true);
	Renderer7->CreateAnimation("ATTACK_EarthenAegis_Dgr90", "ARCANA_EarthenAegis_ALL.bmp", 3, 3, 0.2f, true);
	Renderer7->CreateAnimation("ATTACK_EarthenAegis_Dgr120", "ARCANA_EarthenAegis_ALL.bmp", 4, 4, 0.2f, true);
	Renderer7->CreateAnimation("ATTACK_EarthenAegis_Dgr150", "ARCANA_EarthenAegis_ALL.bmp", 5, 5, 0.2f, true);
	Renderer7->CreateAnimation("ATTACK_EarthenAegis_Dgr180", "ARCANA_EarthenAegis_ALL.bmp", 6, 6, 0.2f, true);
	Renderer7->CreateAnimation("ATTACK_EarthenAegis_Dgr210", "ARCANA_EarthenAegis_ALL.bmp", 7, 7, 0.2f, true);
	Renderer7->CreateAnimation("ATTACK_EarthenAegis_Dgr240", "ARCANA_EarthenAegis_ALL.bmp", 8, 8, 0.2f, true);
	Renderer7->CreateAnimation("ATTACK_EarthenAegis_Dgr270", "ARCANA_EarthenAegis_ALL.bmp", 9, 9, 0.2f, true);
	Renderer7->CreateAnimation("ATTACK_EarthenAegis_Dgr300", "ARCANA_EarthenAegis_ALL.bmp", 10, 10, 0.2f, true);
	Renderer7->CreateAnimation("ATTACK_EarthenAegis_Dgr330", "ARCANA_EarthenAegis_ALL.bmp", 11, 11, 0.2f, true);


	Renderer8->CreateAnimation("ATTACK_EarthenAegis_Dgr360", "ARCANA_EarthenAegis_ALL.bmp", 0, 0, 0.2f, true);
	Renderer8->CreateAnimation("ATTACK_EarthenAegis_Dgr30", "ARCANA_EarthenAegis_ALL.bmp", 1, 1, 0.2f, true);
	Renderer8->CreateAnimation("ATTACK_EarthenAegis_Dgr60", "ARCANA_EarthenAegis_ALL.bmp", 2, 2, 0.2f, true);
	Renderer8->CreateAnimation("ATTACK_EarthenAegis_Dgr90", "ARCANA_EarthenAegis_ALL.bmp", 3, 3, 0.2f, true);
	Renderer8->CreateAnimation("ATTACK_EarthenAegis_Dgr120", "ARCANA_EarthenAegis_ALL.bmp", 4, 4, 0.2f, true);
	Renderer8->CreateAnimation("ATTACK_EarthenAegis_Dgr150", "ARCANA_EarthenAegis_ALL.bmp", 5, 5, 0.2f, true);
	Renderer8->CreateAnimation("ATTACK_EarthenAegis_Dgr180", "ARCANA_EarthenAegis_ALL.bmp", 6, 6, 0.2f, true);
	Renderer8->CreateAnimation("ATTACK_EarthenAegis_Dgr210", "ARCANA_EarthenAegis_ALL.bmp", 7, 7, 0.2f, true);
	Renderer8->CreateAnimation("ATTACK_EarthenAegis_Dgr240", "ARCANA_EarthenAegis_ALL.bmp", 8, 8, 0.2f, true);
	Renderer8->CreateAnimation("ATTACK_EarthenAegis_Dgr270", "ARCANA_EarthenAegis_ALL.bmp", 9, 9, 0.2f, true);
	Renderer8->CreateAnimation("ATTACK_EarthenAegis_Dgr300", "ARCANA_EarthenAegis_ALL.bmp", 10, 10, 0.2f, true);
	Renderer8->CreateAnimation("ATTACK_EarthenAegis_Dgr330", "ARCANA_EarthenAegis_ALL.bmp", 11, 11, 0.2f, true);

#pragma endregion

	// <기본값>
	// 아래
	Renderer->ChangeAnimation("ATTACK_EarthenAegis_Dgr360");


	// 위
	Renderer2->ChangeAnimation("ATTACK_EarthenAegis_Dgr180");


	// 오 (3)
	Renderer3->ChangeAnimation("ATTACK_EarthenAegis_Dgr90");


	// 왼 (9)
	Renderer4->ChangeAnimation("ATTACK_EarthenAegis_Dgr270");


	// 오른쪽 위 대각선 (4)
	Renderer5->ChangeAnimation("ATTACK_EarthenAegis_Dgr120");


	// 왼쪽 아래 대각선 (2)
	Renderer6->ChangeAnimation("ATTACK_EarthenAegis_Dgr300");


	Renderer7->ChangeAnimation("ATTACK_EarthenAegis_Dgr60");


	Renderer8->ChangeAnimation("ATTACK_EarthenAegis_Dgr240");

	// 충돌체 생성

	BodyCollsion = CreateCollision(CollisionOrder::PlayerSkill);
	BodyCollsion->SetCollisionScale({ 100, 100 });
	BodyCollsion->SetCollisionType(CollisionType::CirCle);
	BodyCollsion->SetCollisionPos({ 0, 100 });

	BodyCollsion2 = CreateCollision(CollisionOrder::PlayerSkill);
	BodyCollsion2->SetCollisionScale({ 100, 100 });
	BodyCollsion2->SetCollisionType(CollisionType::CirCle);
	BodyCollsion2->SetCollisionPos({ 0, -100 });

	BodyCollsion3 = CreateCollision(CollisionOrder::PlayerSkill);
	BodyCollsion3->SetCollisionScale({ 100, 100 });
	BodyCollsion3->SetCollisionType(CollisionType::CirCle);
	BodyCollsion3->SetCollisionPos({ 100, 0 });

	BodyCollsion4 = CreateCollision(CollisionOrder::PlayerSkill);
	BodyCollsion4->SetCollisionScale({ 100, 100 });
	BodyCollsion4->SetCollisionType(CollisionType::CirCle);
	BodyCollsion4->SetCollisionPos({ -100, 0 });

	BodyCollsion5 = CreateCollision(CollisionOrder::PlayerSkill);
	BodyCollsion5->SetCollisionScale({ 100, 100 });
	BodyCollsion5->SetCollisionType(CollisionType::CirCle);
	BodyCollsion5->SetCollisionPos({ 70, -70 });

	BodyCollsion6 = CreateCollision(CollisionOrder::PlayerSkill);
	BodyCollsion6->SetCollisionScale({ 100, 100 });
	BodyCollsion6->SetCollisionType(CollisionType::CirCle);
	BodyCollsion6->SetCollisionPos({ -70, 70 });

	BodyCollsion7 = CreateCollision(CollisionOrder::PlayerSkill);
	BodyCollsion7->SetCollisionScale({ 100, 100 });
	BodyCollsion7->SetCollisionType(CollisionType::CirCle);
	BodyCollsion7->SetCollisionPos({ 70, 70 });

	BodyCollsion8 = CreateCollision(CollisionOrder::PlayerSkill);
	BodyCollsion8->SetCollisionScale({ 100, 100 });
	BodyCollsion8->SetCollisionType(CollisionType::CirCle);
	BodyCollsion8->SetCollisionPos({ -70, -70 });


	// 추후 define으로 이동
	m_iAttackPower = 10;
}

void SKILL_EarthenAegis::Update(float _Delta)
{

	// 중심축인 플레이어를 기준으로 이동시 스킬도 이동거리에 맞춰서 이동
	float4 Dir = Player::GetMainPlayer()->GetPos() - GetPos();

	AddPos(Dir * _Delta * 400.0f);




	// 시계 방향으로 회전
	//// 아래
	//Renderer->SetRenderPos({ 0, 100});

	//// 위
	//Renderer2->SetRenderPos({ 0, -100 });

	//// 오른쪽
	//Renderer3->SetRenderPos({ 100, 0 });

	//// 왼쪽
	//Renderer4->SetRenderPos({ -100, 0 });

	//// 대각선 오-위
	//Renderer5->SetRenderPos({ 70, -70 });

	//// 대각선 왼-아
	//Renderer6->SetRenderPos({ -70, 70 });

	//// 대각선 오-아
	//Renderer7->SetRenderPos({ 70, 70 });

	//// 대각선 왼-위
	//Renderer8->SetRenderPos({ -70, -70 });






	if (GetLiveTime() < 5.0f)
	{
		RollAngle += _Delta * 270.0f;

		float4 Range = float4::GetUnitVectorFromDeg(RollAngle + (360.0f / 8) * 1) * 100.0f;
		float4 Range2 = float4::GetUnitVectorFromDeg(RollAngle + (360.0f / 8) * 2) * 100.0f;
		float4 Range3 = float4::GetUnitVectorFromDeg(RollAngle + (360.0f / 8) * 3) * 100.0f;
		float4 Range4 = float4::GetUnitVectorFromDeg(RollAngle + (360.0f / 8) * 4) * 100.0f;
		float4 Range5 = float4::GetUnitVectorFromDeg(RollAngle + (360.0f / 8) * 5) * 100.0f;
		float4 Range6 = float4::GetUnitVectorFromDeg(RollAngle + (360.0f / 8) * 6) * 100.0f;
		float4 Range7 = float4::GetUnitVectorFromDeg(RollAngle + (360.0f / 8) * 7) * 100.0f;
		float4 Range8 = float4::GetUnitVectorFromDeg(RollAngle + (360.0f / 8) * 8) * 100.0f;


		if (RollAngle > 360.0f)
		{
			RollAngle -= 360;
		}

		Renderer->SetRenderPos(Range);
		Renderer6->SetRenderPos(Range2);
		Renderer4->SetRenderPos(Range3);
		Renderer8->SetRenderPos(Range4);
		Renderer2->SetRenderPos(Range5);
		Renderer5->SetRenderPos(Range6);
		Renderer3->SetRenderPos(Range7);
		Renderer7->SetRenderPos(Range8);

		BodyCollsion->SetCollisionPos(Range);
		BodyCollsion6->SetCollisionPos(Range2);
		BodyCollsion4->SetCollisionPos(Range3);
		BodyCollsion8->SetCollisionPos(Range4);
		BodyCollsion2->SetCollisionPos(Range5);
		BodyCollsion5->SetCollisionPos(Range6);
		BodyCollsion3->SetCollisionPos(Range7);
		BodyCollsion7->SetCollisionPos(Range8);


		// 특정 각도가 될 때마다 애니메이션 교체
		if (RollAngle > 0.0f && RollAngle < 45.0f)
		{
			Renderer->ChangeAnimation("ATTACK_EarthenAegis_Dgr360");
		}

		if (RollAngle > 45.0f && RollAngle < 90.0f)
		{
			Renderer->ChangeAnimation("ATTACK_EarthenAegis_Dgr300");
		}

		if (RollAngle > 90.0f && RollAngle < 135.0f)
		{
			Renderer->ChangeAnimation("ATTACK_EarthenAegis_Dgr270");
		}

		if (RollAngle > 135.0f && RollAngle < 175.0f)
		{
			Renderer->ChangeAnimation("ATTACK_EarthenAegis_Dgr240");
		}

		if (RollAngle > 210.0f && RollAngle < 245.0f)
		{
			Renderer->ChangeAnimation("ATTACK_EarthenAegis_Dgr180");
		}

		if (RollAngle > 245.0f && RollAngle < 275.0f)
		{
			Renderer->ChangeAnimation("ATTACK_EarthenAegis_Dgr120");
		}

		if (RollAngle > 275.0f && RollAngle < 305.0f)
		{
			Renderer->ChangeAnimation("ATTACK_EarthenAegis_Dgr90");
		}

		if (RollAngle > 305.0f && RollAngle < 335.0f)
		{
			Renderer->ChangeAnimation("ATTACK_EarthenAegis_Dgr60");
		}


		if (RollAngle > 335.0f && RollAngle < 365.0f)
		{
			Renderer->ChangeAnimation("ATTACK_EarthenAegis_Dgr30");
		}

	}

	else if (GetLiveTime() > 5.0f && GetLiveTime() < 7.0f)
	{
		// O
		Renderer->ChangeAnimation("ATTACK_EarthenAegis_Dgr90");


		// O
		Renderer2->ChangeAnimation("ATTACK_EarthenAegis_Dgr270");


		// O
		Renderer3->ChangeAnimation("ATTACK_EarthenAegis_Dgr180");


		// 왼 (9)
		Renderer4->ChangeAnimation("ATTACK_EarthenAegis_Dgr360");


		// O
		Renderer5->ChangeAnimation("ATTACK_EarthenAegis_Dgr210");


		// O
		Renderer6->ChangeAnimation("ATTACK_EarthenAegis_Dgr30");


		// O
		Renderer7->ChangeAnimation("ATTACK_EarthenAegis_Dgr150");

		// O
		Renderer8->ChangeAnimation("ATTACK_EarthenAegis_Dgr330");
	}


	if (GetLiveTime() > 7.0f)
	{
		Renderer->ChangeAnimation("RockPop");
		Renderer2->ChangeAnimation("RockPop");
		Renderer3->ChangeAnimation("RockPop");
		Renderer4->ChangeAnimation("RockPop");
		Renderer5->ChangeAnimation("RockPop");
		Renderer6->ChangeAnimation("RockPop");
		Renderer7->ChangeAnimation("RockPop");
		Renderer8->ChangeAnimation("RockPop");

		if (true == Renderer->IsAnimationEnd())
		{
			Death();
		}
	}





}

void SKILL_EarthenAegis::Render(float _Delta)
{

	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();
	std::string Text = "";
	Text += "스킬 앵글 테스트 값 : ";
	Text += std::to_string(RollAngle);
	TextOutA(dc, 2, 3, Text.c_str(), static_cast<int>(Text.size()));

}
