#include "SKILL_ArcherAttack.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"
#include "ContentsEnum.h"

void SKILL_ArcherAttack::Start()
{
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");

	GameEnginePath FolderPath = FilePath;

	FilePath.MoveChild("ContentsResources\\Texture\\Monster\\");

	if (false == ResourcesManager::GetInst().IsLoadTexture("ARCHER_BOW_LEFT.bmp"))
	{
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("ARCHER_BOW_LEFT.bmp"), 5, 9);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("ARCHER_BOW_RIGHT.bmp"))
	{
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("ARCHER_BOW_RIGHT.bmp"), 5, 9);
	}

	// ������ ������ �ε��� �ؽ�ó ����
	SkillRenderer = CreateRenderer();
	SkillRenderer->SetRenderScale({ 100, 100 });

	// �ִϸ��̼� ����
	SkillRenderer->CreateAnimation("Arrow_INDEX0", "ARCHER_BOW_RIGHT.bmp", 0, 2, 0.2f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX1", "ARCHER_BOW_RIGHT.bmp", 5, 7, 0.2f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX2", "ARCHER_BOW_RIGHT.bmp", 10, 12, 0.2f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX3", "ARCHER_BOW_RIGHT.bmp", 15, 17, 0.2f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX4", "ARCHER_BOW_RIGHT.bmp", 20, 22, 0.2f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX5", "ARCHER_BOW_RIGHT.bmp", 25, 27, 0.2f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX6", "ARCHER_BOW_RIGHT.bmp", 30, 32, 0.2f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX7", "ARCHER_BOW_RIGHT.bmp", 35, 37, 0.2f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX8", "ARCHER_BOW_RIGHT.bmp", 40, 42, 0.2f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX9", "ARCHER_BOW_LEFT.bmp", 35, 37, 0.2f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX10", "ARCHER_BOW_LEFT.bmp", 30, 32, 0.2f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX11", "ARCHER_BOW_LEFT.bmp", 25, 27, 0.2f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX12", "ARCHER_BOW_LEFT.bmp", 20, 22, 0.2f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX13", "ARCHER_BOW_LEFT.bmp", 15, 17, 0.2f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX14", "ARCHER_BOW_LEFT.bmp", 10, 12, 0.2f, false);
	SkillRenderer->CreateAnimation("Arrow_INDEX15", "ARCHER_BOW_LEFT.bmp", 5, 7, 0.2f, false);


	SkillRenderer->CreateAnimation("ArrowShot_INDEX0", "ARCHER_BOW_RIGHT.bmp", 4, 4, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX1", "ARCHER_BOW_RIGHT.bmp", 9, 9, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX2", "ARCHER_BOW_RIGHT.bmp", 14, 14, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX3", "ARCHER_BOW_RIGHT.bmp", 19, 19, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX4", "ARCHER_BOW_RIGHT.bmp", 24, 24, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX5", "ARCHER_BOW_RIGHT.bmp", 29, 29, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX6", "ARCHER_BOW_RIGHT.bmp", 34, 34, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX7", "ARCHER_BOW_RIGHT.bmp", 39, 39, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX8", "ARCHER_BOW_RIGHT.bmp", 44, 44, 0.2f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX9", "ARCHER_BOW_LEFT.bmp", 39, 39, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX10", "ARCHER_BOW_LEFT.bmp", 34, 34, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX11", "ARCHER_BOW_LEFT.bmp", 29, 29, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX12", "ARCHER_BOW_LEFT.bmp", 24, 24, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX13", "ARCHER_BOW_LEFT.bmp", 19, 19, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX14", "ARCHER_BOW_LEFT.bmp", 14, 14, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX15", "ARCHER_BOW_LEFT.bmp", 9, 9, 0.5f, false);
	SkillRenderer->CreateAnimation("ArrowShot_INDEX16", "ARCHER_BOW_LEFT.bmp", 4, 4, 0.5f, false);

		// �浹ü ����
	SkillCollsion = CreateCollision(CollisionOrder::MonsterSkill);
	SkillCollsion->SetCollisionScale({ 50, 50 });
	SkillCollsion->SetCollisionType(CollisionType::CirCle);

	m_iAttackPower = 10;

	SkillRenderer->ChangeAnimation("Arrow_INDEX0");
}

void SKILL_ArcherAttack::Update(float _Delta)
{

	if (1.0f < GetLiveTime())
	{
		float4 DirDeg = Player::GetMainPlayer()->GetPos() - GetPos();

		// ��
		if (DirDeg.AngleDeg() >= 258.75f && DirDeg.AngleDeg() < 281.25f)
		{

			SkillRenderer->ChangeAnimation("Arrow_INDEX0");

			if (SkillRenderer->IsAnimationEnd())
			{
				SkillRenderer->ChangeAnimation("ArrowShot_INDEX0");
				SetDir(DirDeg);

			}


		}

		else if (DirDeg.AngleDeg() >= 281.25f && DirDeg.AngleDeg() < 303.75f)
		{
			SkillRenderer->ChangeAnimation("Arrow_INDEX1");

			if (SkillRenderer->IsAnimationEnd())
			{
				SkillRenderer->ChangeAnimation("ArrowShot_INDEX1");
				SetDir(DirDeg);

			}

		}

		else if (DirDeg.AngleDeg() >= 303.75f && DirDeg.AngleDeg() < 326.25f)
		{
			SkillRenderer->ChangeAnimation("Arrow_INDEX2");

			if (SkillRenderer->IsAnimationEnd())
			{
				SkillRenderer->ChangeAnimation("ArrowShot_INDEX2");
				SetDir(DirDeg);

			}
		}

		else if (DirDeg.AngleDeg() >= 326.25f && DirDeg.AngleDeg() < 348.75f)
		{
			SkillRenderer->ChangeAnimation("Arrow_INDEX3");

			if (SkillRenderer->IsAnimationEnd())
			{
				SkillRenderer->ChangeAnimation("ArrowShot_INDEX3");
				SetDir(DirDeg);

			}
		}

		else if (DirDeg.AngleDeg() >= 11.25f && DirDeg.AngleDeg() < 33.75f)
		{
			SkillRenderer->ChangeAnimation("Arrow_INDEX4");

			if (SkillRenderer->IsAnimationEnd())
			{
				SkillRenderer->ChangeAnimation("ArrowShot_INDEX4");
				SetDir(DirDeg);

			}

		}

		else if (DirDeg.AngleDeg() >= 33.75f && DirDeg.AngleDeg() < 56.25f)
		{
			SkillRenderer->ChangeAnimation("Arrow_INDEX5");

			if (SkillRenderer->IsAnimationEnd())
			{
				SkillRenderer->ChangeAnimation("ArrowShot_INDEX5");
				SetDir(DirDeg);

			}

		}

		else if (DirDeg.AngleDeg() >= 56.25f && DirDeg.AngleDeg() < 78.75f)
		{
			SkillRenderer->ChangeAnimation("Arrow_INDEX6");

			if (SkillRenderer->IsAnimationEnd())
			{
				SkillRenderer->ChangeAnimation("ArrowShot_INDEX6");
				SetDir(DirDeg);

			}

		}

		else if (DirDeg.AngleDeg() >= 78.75f && DirDeg.AngleDeg() < 101.25f)
		{
			SkillRenderer->ChangeAnimation("Arrow_INDEX7");

			if (SkillRenderer->IsAnimationEnd())
			{
				SkillRenderer->ChangeAnimation("ArrowShot_INDEX7");
				SetDir(DirDeg);

			}

		}

		else if (DirDeg.AngleDeg() >= 101.25f && DirDeg.AngleDeg() < 123.75f)
		{
			SkillRenderer->ChangeAnimation("Arrow_INDEX8");

			if (SkillRenderer->IsAnimationEnd())
			{
				SkillRenderer->ChangeAnimation("ArrowShot_INDEX8");
				SetDir(DirDeg);

			}

		}

		else if (DirDeg.AngleDeg() >= 123.75f && DirDeg.AngleDeg() < 146.25f)
		{
			SkillRenderer->ChangeAnimation("Arrow_INDEX9");

			if (SkillRenderer->IsAnimationEnd())
			{
				SkillRenderer->ChangeAnimation("ArrowShot_INDEX9");
				SetDir(DirDeg);

			}
		}

		else if (DirDeg.AngleDeg() >= 146.25f && DirDeg.AngleDeg() < 168.75f)
		{
			SkillRenderer->ChangeAnimation("Arrow_INDEX10");

			if (SkillRenderer->IsAnimationEnd())
			{
				SkillRenderer->ChangeAnimation("ArrowShot_INDEX10");
				SetDir(DirDeg);

			}
		}

		else if (DirDeg.AngleDeg() >= 168.75f && DirDeg.AngleDeg() < 191.25f)
		{
			SkillRenderer->ChangeAnimation("Arrow_INDEX11");

			if (SkillRenderer->IsAnimationEnd())
			{
				SkillRenderer->ChangeAnimation("ArrowShot_INDEX11");
				SetDir(DirDeg);

			}

		}

		else if (DirDeg.AngleDeg() >= 191.25f && DirDeg.AngleDeg() < 213.75f)
		{
			SkillRenderer->ChangeAnimation("Arrow_INDEX12");

			if (SkillRenderer->IsAnimationEnd())
			{
				SkillRenderer->ChangeAnimation("ArrowShot_INDEX12");
				SetDir(DirDeg);

			}
		}


		else if (DirDeg.AngleDeg() >= 213.75f && DirDeg.AngleDeg() < 236.25f)
		{
			SkillRenderer->ChangeAnimation("Arrow_INDEX13");

			if (SkillRenderer->IsAnimationEnd())
			{
				SkillRenderer->ChangeAnimation("ArrowShot_INDEX13");
				SetDir(DirDeg);

			}
		}

		else if (DirDeg.AngleDeg() >= 236.25f && DirDeg.AngleDeg() < 258.75f)
		{
			SkillRenderer->ChangeAnimation("Arrow_INDEX14");

			if (SkillRenderer->IsAnimationEnd())
			{
				SkillRenderer->ChangeAnimation("ArrowShot_INDEX14");
				SetDir(DirDeg);

			}
		}

		else
		{
			SkillRenderer->ChangeAnimation("Arrow_INDEX15");

			if (SkillRenderer->IsAnimationEnd())
			{
				SkillRenderer->ChangeAnimation("ArrowShot_INDEX15");
				SetDir(DirDeg);

			}

		}

		ResetLiveTime();

	}

	if (GetLiveTime() > 1.0f)
	{
		Death();
	}

	float4 NextPos = Dir * _Delta * Speed;
	AddPos(NextPos);
}
