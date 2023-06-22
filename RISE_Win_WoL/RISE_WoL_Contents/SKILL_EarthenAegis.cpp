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
	// ��ų �ؽ�ó �ε�
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

#pragma region ������ ����

	{
		// ��
		GameEngineRenderer* Renderer = CreateRenderer();
		Renderer->SetRenderScale({ 70, 70 });
		Renderer->SetRenderPos({ 0, -100 });
		Renderers.push_back(Renderer);
	}

	{
		// ������ �� �밢��
		GameEngineRenderer* Renderer = CreateRenderer();
		Renderer->SetRenderScale({ 70, 70 });
		Renderer->SetRenderPos({ 70, -70 });
		Renderers.push_back(Renderer);
	}

	{
		// ������
		GameEngineRenderer* Renderer = CreateRenderer();
		Renderer->SetRenderScale({ 70, 70 });
		Renderer->SetRenderPos({ 100, 0 });
		Renderers.push_back(Renderer);
	}

	{
		// ������ �Ʒ� �밢��
		GameEngineRenderer* Renderer = CreateRenderer();
		Renderer->SetRenderScale({ 70, 70 });
		Renderer->SetRenderPos({ 70, 70 });
		Renderers.push_back(Renderer);
	}

	{
		// �Ʒ�
		GameEngineRenderer* Renderer = CreateRenderer();
		Renderer->SetRenderScale({ 70, 70 });
		Renderer->SetRenderPos({ 0, 100 });
		Renderers.push_back(Renderer);
	}

	{
		// ���� �Ʒ� �밢��
		GameEngineRenderer* Renderer = CreateRenderer();
		Renderer->SetRenderScale({ 70, 70 });
		Renderer->SetRenderPos({ -70, 70 });
		Renderers.push_back(Renderer);
	}

	{
		// ����
		GameEngineRenderer* Renderer = CreateRenderer();
		Renderer->SetRenderScale({ 70, 70 });
		Renderer->SetRenderPos({ -100, 0 });
		Renderers.push_back(Renderer);
	}

	{
		// ���� �� �밢��
		GameEngineRenderer* Renderer = CreateRenderer();
		Renderer->SetRenderScale({ 70, 70 });
		Renderer->SetRenderPos({ -70, -70 });
		Renderers.push_back(Renderer);
	}
#pragma endregion


#pragma region �ִϸ��̼� ����

	for (size_t i = 0; i < Renderers.size(); i++)
	{
		Renderers[i]->CreateAnimation("RockPop", "RockPop.bmp", 0, 3, 0.05f, false);
		Renderers[i]->CreateAnimation("ATTACK_EarthenAegis_Index0", "ARCANA_EarthenAegis_ALL.bmp", 0, 0, 0.2f, true);
		Renderers[i]->CreateAnimation("ATTACK_EarthenAegis_Index1", "ARCANA_EarthenAegis_ALL.bmp", 1, 1, 0.2f, true);
		Renderers[i]->CreateAnimation("ATTACK_EarthenAegis_Index2", "ARCANA_EarthenAegis_ALL.bmp", 2, 2, 0.2f, true);
		Renderers[i]->CreateAnimation("ATTACK_EarthenAegis_Index3", "ARCANA_EarthenAegis_ALL.bmp", 3, 3, 0.2f, true);
		Renderers[i]->CreateAnimation("ATTACK_EarthenAegis_Index4", "ARCANA_EarthenAegis_ALL.bmp", 4, 4, 0.2f, true);
		Renderers[i]->CreateAnimation("ATTACK_EarthenAegis_Index5", "ARCANA_EarthenAegis_ALL.bmp", 5, 5, 0.2f, true);
		Renderers[i]->CreateAnimation("ATTACK_EarthenAegis_Index6", "ARCANA_EarthenAegis_ALL.bmp", 6, 6, 0.2f, true);
		Renderers[i]->CreateAnimation("ATTACK_EarthenAegis_Index7", "ARCANA_EarthenAegis_ALL.bmp", 7, 7, 0.2f, true);
		Renderers[i]->CreateAnimation("ATTACK_EarthenAegis_Index8", "ARCANA_EarthenAegis_ALL.bmp", 8, 8, 0.2f, true);
		Renderers[i]->CreateAnimation("ATTACK_EarthenAegis_Index9", "ARCANA_EarthenAegis_ALL.bmp", 9, 9, 0.2f, true);
		Renderers[i]->CreateAnimation("ATTACK_EarthenAegis_Index10", "ARCANA_EarthenAegis_ALL.bmp", 10, 10, 0.2f, true);
		Renderers[i]->CreateAnimation("ATTACK_EarthenAegis_Index11", "ARCANA_EarthenAegis_ALL.bmp", 11, 11, 0.2f, true);
	}


	Renderers[0]->ChangeAnimation("ATTACK_EarthenAegis_Index3");

	Renderers[1]->ChangeAnimation("ATTACK_EarthenAegis_Index9");

	Renderers[2]->ChangeAnimation("ATTACK_EarthenAegis_Index6");

	Renderers[3]->ChangeAnimation("ATTACK_EarthenAegis_Index0");

	Renderers[4]->ChangeAnimation("ATTACK_EarthenAegis_Index7");

	Renderers[5]->ChangeAnimation("ATTACK_EarthenAegis_Index1");

	Renderers[6]->ChangeAnimation("ATTACK_EarthenAegis_Index5");

	Renderers[7]->ChangeAnimation("ATTACK_EarthenAegis_Index11");

#pragma endregion


#pragma region �浹ü ����

	// �浹ü ����
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

	// ���� define���� �̵�
	m_iAttackPower = 10;
}

void SKILL_EarthenAegis::Update(float _Delta)
{
	// �߽����� �÷��̾ �������� �̵��� ��ų�� �̵��Ÿ��� ���缭 �̵�
	float4 Dir = Player::GetMainPlayer()->GetPos() - GetPos();

	AddPos(Dir * _Delta * 400.0f);

	// ȸ��
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


			// Ư�� ������ �� ������ �ִϸ��̼� ��ü
			if (RollAngle > 0.0f && RollAngle < 45.0f)
			{
				Renderers[i]->ChangeAnimation("ATTACK_EarthenAegis_Index0");
			}

			if (RollAngle > 45.0f && RollAngle < 90.0f)
			{
				Renderers[i]->ChangeAnimation("ATTACK_EarthenAegis_Index10");
			}

			if (RollAngle > 90.0f && RollAngle < 135.0f)
			{
				Renderers[i]->ChangeAnimation("ATTACK_EarthenAegis_Index9");
			}

			if (RollAngle > 135.0f && RollAngle < 175.0f)
			{
				Renderers[i]->ChangeAnimation("ATTACK_EarthenAegis_Index8");
			}

			if (RollAngle > 210.0f && RollAngle < 245.0f)
			{
				Renderers[i]->ChangeAnimation("ATTACK_EarthenAegis_Index6");
			}

			if (RollAngle > 245.0f && RollAngle < 275.0f)
			{
				Renderers[i]->ChangeAnimation("ATTACK_EarthenAegis_Index5");
			}

			if (RollAngle > 275.0f && RollAngle < 305.0f)
			{
				Renderers[i]->ChangeAnimation("ATTACK_EarthenAegis_Index3");
			}

			if (RollAngle > 305.0f && RollAngle < 335.0f)
			{
				Renderers[i]->ChangeAnimation("ATTACK_EarthenAegis_Index2");
			}

			if (RollAngle > 335.0f && RollAngle < 365.0f)
			{
				Renderers[i]->ChangeAnimation("ATTACK_EarthenAegis_Index1");
			}

		}

		else if (GetLiveTime() > 5.0f && GetLiveTime() < 7.0f)
		{
			Renderers[0]->ChangeAnimation("ATTACK_EarthenAegis_Index1");

			Renderers[1]->ChangeAnimation("ATTACK_EarthenAegis_Index0");

			Renderers[2]->ChangeAnimation("ATTACK_EarthenAegis_Index11");

			Renderers[3]->ChangeAnimation("ATTACK_EarthenAegis_Index9");

			Renderers[4]->ChangeAnimation("ATTACK_EarthenAegis_Index7");

			Renderers[5]->ChangeAnimation("ATTACK_EarthenAegis_Index6");

			Renderers[6]->ChangeAnimation("ATTACK_EarthenAegis_Index5");

			Renderers[7]->ChangeAnimation("ATTACK_EarthenAegis_Index3");
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
	Text += "��ų �ޱ� �׽�Ʈ �� : ";
	Text += std::to_string(RollAngle);
	TextOutA(dc, 2, 3, Text.c_str(), static_cast<int>(Text.size()));

}
