#include "SKILL_EarthenAegis.h"

#pragma region Headers

#include <GameEngineCore/ResourcesManager.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"
#include "ContentsEnum.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#pragma endregion

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

#pragma region 렌더러 생성

	{
		// 위
		GameEngineRenderer* Renderer = CreateRenderer();
		Renderer->SetRenderScale({ 70, 70 });
		Renderer->SetRenderPos({ 0, -100 });
		Renderers.push_back(Renderer);
	}

	{
		// 오른쪽 위 대각선
		GameEngineRenderer* Renderer = CreateRenderer();
		Renderer->SetRenderScale({ 70, 70 });
		Renderer->SetRenderPos({ 70, -70 });
		Renderers.push_back(Renderer);
	}

	{
		// 오른쪽
		GameEngineRenderer* Renderer = CreateRenderer();
		Renderer->SetRenderScale({ 70, 70 });
		Renderer->SetRenderPos({ 100, 0 });
		Renderers.push_back(Renderer);
	}

	{
		// 오른쪽 아래 대각선
		GameEngineRenderer* Renderer = CreateRenderer();
		Renderer->SetRenderScale({ 70, 70 });
		Renderer->SetRenderPos({ 70, 70 });
		Renderers.push_back(Renderer);
	}

	{
		// 아래
		GameEngineRenderer* Renderer = CreateRenderer();
		Renderer->SetRenderScale({ 70, 70 });
		Renderer->SetRenderPos({ 0, 100 });
		Renderers.push_back(Renderer);
	}

	{
		// 왼쪽 아래 대각선
		GameEngineRenderer* Renderer = CreateRenderer();
		Renderer->SetRenderScale({ 70, 70 });
		Renderer->SetRenderPos({ -70, 70 });
		Renderers.push_back(Renderer);
	}

	{
		// 왼쪽
		GameEngineRenderer* Renderer = CreateRenderer();
		Renderer->SetRenderScale({ 70, 70 });
		Renderer->SetRenderPos({ -100, 0 });
		Renderers.push_back(Renderer);
	}

	{
		// 왼쪽 위 대각선
		GameEngineRenderer* Renderer = CreateRenderer();
		Renderer->SetRenderScale({ 70, 70 });
		Renderer->SetRenderPos({ -70, -70 });
		Renderers.push_back(Renderer);
	}
#pragma endregion


#pragma region 애니메이션 생성

	for (size_t i = 0; i < Renderers.size(); i++)
	{
		Renderers[i]->CreateAnimation("RockPop", "RockPop.bmp", 0, 3, 0.05f, false);
		Renderers[i]->CreateAnimation("ATTACK_EarthenAegis_Dgr360", "ARCANA_EarthenAegis_ALL.bmp", 0, 0, 0.2f, true);
		Renderers[i]->CreateAnimation("ATTACK_EarthenAegis_Dgr30", "ARCANA_EarthenAegis_ALL.bmp", 1, 1, 0.2f, true);
		Renderers[i]->CreateAnimation("ATTACK_EarthenAegis_Dgr60", "ARCANA_EarthenAegis_ALL.bmp", 2, 2, 0.2f, true);
		Renderers[i]->CreateAnimation("ATTACK_EarthenAegis_Dgr90", "ARCANA_EarthenAegis_ALL.bmp", 3, 3, 0.2f, true);
		Renderers[i]->CreateAnimation("ATTACK_EarthenAegis_Dgr120", "ARCANA_EarthenAegis_ALL.bmp", 4, 4, 0.2f, true);
		Renderers[i]->CreateAnimation("ATTACK_EarthenAegis_Dgr150", "ARCANA_EarthenAegis_ALL.bmp", 5, 5, 0.2f, true);
		Renderers[i]->CreateAnimation("ATTACK_EarthenAegis_Dgr180", "ARCANA_EarthenAegis_ALL.bmp", 6, 6, 0.2f, true);
		Renderers[i]->CreateAnimation("ATTACK_EarthenAegis_Dgr210", "ARCANA_EarthenAegis_ALL.bmp", 7, 7, 0.2f, true);
		Renderers[i]->CreateAnimation("ATTACK_EarthenAegis_Dgr240", "ARCANA_EarthenAegis_ALL.bmp", 8, 8, 0.2f, true);
		Renderers[i]->CreateAnimation("ATTACK_EarthenAegis_Dgr270", "ARCANA_EarthenAegis_ALL.bmp", 9, 9, 0.2f, true);
		Renderers[i]->CreateAnimation("ATTACK_EarthenAegis_Dgr300", "ARCANA_EarthenAegis_ALL.bmp", 10, 10, 0.2f, true);
		Renderers[i]->CreateAnimation("ATTACK_EarthenAegis_Dgr330", "ARCANA_EarthenAegis_ALL.bmp", 11, 11, 0.2f, true);
	}


	Renderers[0]->ChangeAnimation("ATTACK_EarthenAegis_Dgr90");

	Renderers[1]->ChangeAnimation("ATTACK_EarthenAegis_Dgr270");

	Renderers[2]->ChangeAnimation("ATTACK_EarthenAegis_Dgr180");

	Renderers[3]->ChangeAnimation("ATTACK_EarthenAegis_Dgr360");

	Renderers[4]->ChangeAnimation("ATTACK_EarthenAegis_Dgr210");

	Renderers[5]->ChangeAnimation("ATTACK_EarthenAegis_Dgr30");

	Renderers[6]->ChangeAnimation("ATTACK_EarthenAegis_Dgr150");

	Renderers[7]->ChangeAnimation("ATTACK_EarthenAegis_Dgr330");

#pragma endregion


#pragma region 충돌체 생성

	// 충돌체 생성
	{
		BodyCollsion = CreateCollision(CollisionOrder::PlayerSkill);
		BodyCollsion->SetCollisionScale({ 100, 100 });
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
		BodyCollsion->SetCollisionPos({ 0, -100 });
		Collisions.push_back(BodyCollsion);
	}


	{
		BodyCollsion = CreateCollision(CollisionOrder::PlayerSkill);
		BodyCollsion->SetCollisionScale({ 100, 100 });
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
		BodyCollsion->SetCollisionPos({ 70, -70 });
		Collisions.push_back(BodyCollsion);
	}

	{
		BodyCollsion = CreateCollision(CollisionOrder::PlayerSkill);
		BodyCollsion->SetCollisionScale({ 100, 100 });
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
		BodyCollsion->SetCollisionPos({ 100, 0 });
		Collisions.push_back(BodyCollsion);
	}

	{
		BodyCollsion = CreateCollision(CollisionOrder::PlayerSkill);
		BodyCollsion->SetCollisionScale({ 100, 100 });
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
		BodyCollsion->SetCollisionPos({ 70, 70 });
		Collisions.push_back(BodyCollsion);
	}

	{
		BodyCollsion = CreateCollision(CollisionOrder::PlayerSkill);
		BodyCollsion->SetCollisionScale({ 100, 100 });
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
		BodyCollsion->SetCollisionPos({ 0, 100 });
		Collisions.push_back(BodyCollsion);
	}

	{
		BodyCollsion = CreateCollision(CollisionOrder::PlayerSkill);
		BodyCollsion->SetCollisionScale({ 100, 100 });
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
		BodyCollsion->SetCollisionPos({ -70, 70 });
		Collisions.push_back(BodyCollsion);
	}


	{
		BodyCollsion = CreateCollision(CollisionOrder::PlayerSkill);
		BodyCollsion->SetCollisionScale({ 100, 100 });
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
		BodyCollsion->SetCollisionPos({ -100, 0 });
		Collisions.push_back(BodyCollsion);
	}

	{
		BodyCollsion = CreateCollision(CollisionOrder::PlayerSkill);
		BodyCollsion->SetCollisionScale({ 100, 100 });
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
		BodyCollsion->SetCollisionPos({ -70, -70 });
		Collisions.push_back(BodyCollsion);
	}
#pragma endregion

	// 추후 define으로 이동
	m_iAttackPower = 10;
}

void SKILL_EarthenAegis::Update(float _Delta)
{

	// 중심축인 플레이어를 기준으로 이동시 스킬도 이동거리에 맞춰서 이동
	float4 Dir = Player::GetMainPlayer()->GetPos() - GetPos();

	AddPos(Dir * _Delta * 400.0f);


	// 회전
	RollAngle += _Delta * 360.0f;

	if (RollAngle >= 360.0f)
	{
		RollAngle -= 360.0f;
	}

	for (int i = 0; i < 8; i++)
	{
		Range = float4::GetUnitVectorFromDeg(RollAngle + (360.0f / 8) * i) * 100.0f;



		if (GetLiveTime() < 5.0f)
		{
			Renderers[i]->SetRenderPos(Range);
			Collisions[i]->SetCollisionPos(Range);


			// 특정 각도가 될 때마다 애니메이션 교체
			if (RollAngle > 0.0f && RollAngle < 45.0f)
			{
				Renderers[i]->ChangeAnimation("ATTACK_EarthenAegis_Dgr360");
			}

			if (RollAngle > 45.0f && RollAngle < 90.0f)
			{
				Renderers[i]->ChangeAnimation("ATTACK_EarthenAegis_Dgr300");
			}

			if (RollAngle > 90.0f && RollAngle < 135.0f)
			{
				Renderers[i]->ChangeAnimation("ATTACK_EarthenAegis_Dgr270");
			}

			if (RollAngle > 135.0f && RollAngle < 175.0f)
			{
				Renderers[i]->ChangeAnimation("ATTACK_EarthenAegis_Dgr240");
			}

			if (RollAngle > 210.0f && RollAngle < 245.0f)
			{
				Renderers[i]->ChangeAnimation("ATTACK_EarthenAegis_Dgr180");
			}

			if (RollAngle > 245.0f && RollAngle < 275.0f)
			{
				Renderers[i]->ChangeAnimation("ATTACK_EarthenAegis_Dgr150");
			}

			if (RollAngle > 275.0f && RollAngle < 305.0f)
			{
				Renderers[i]->ChangeAnimation("ATTACK_EarthenAegis_Dgr90");
			}

			if (RollAngle > 305.0f && RollAngle < 335.0f)
			{
				Renderers[i]->ChangeAnimation("ATTACK_EarthenAegis_Dgr60");
			}

			if (RollAngle > 335.0f && RollAngle < 365.0f)
			{
				Renderers[i]->ChangeAnimation("ATTACK_EarthenAegis_Dgr30");
			}

		}

		else if (GetLiveTime() > 5.0f && GetLiveTime() < 7.0f)
		{
			// 오른쪽 아래
			Renderers[0]->ChangeAnimation("ATTACK_EarthenAegis_Dgr30");


			// 아래
			Renderers[1]->ChangeAnimation("ATTACK_EarthenAegis_Dgr360");


			// O
			Renderers[2]->ChangeAnimation("ATTACK_EarthenAegis_Dgr330");


			// 왼 (9)
			Renderers[3]->ChangeAnimation("ATTACK_EarthenAegis_Dgr270");


			// O
			Renderers[4]->ChangeAnimation("ATTACK_EarthenAegis_Dgr210");


			// O
			Renderers[5]->ChangeAnimation("ATTACK_EarthenAegis_Dgr180");


			// O
			Renderers[6]->ChangeAnimation("ATTACK_EarthenAegis_Dgr150");

			// O
			Renderers[7]->ChangeAnimation("ATTACK_EarthenAegis_Dgr90");

		}


		if (GetLiveTime() > 7.0f)
		{
			Renderers[i]->ChangeAnimation("RockPop");

			if (true == Renderers[i]->IsAnimationEnd())
			{
				Death();
			}
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
