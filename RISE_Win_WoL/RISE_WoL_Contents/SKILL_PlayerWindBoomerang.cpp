#include "SKILL_PlayerWindBoomerang.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"
#include "ContentsEnum.h"

void SKILL_PlayerWindBoomerang::Start()
{
	// ��ų �ؽ�ó �ε�
	if (false == ResourcesManager::GetInst().IsLoadTexture("ICE_BLAST.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Skill");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("ICE_BLAST.bmp"), 6, 1);
	}

	// ������ ������ �ε��� �ؽ�ó ����
	Renderer = CreateRenderer();
	Renderer->SetRenderScale({ 200, 200 });

	// �ִϸ��̼� ����
	Renderer->CreateAnimation("ATTACK_WINDBOOMERANG", "ICE_BLAST.bmp", 2, 0, 0.2f, true);
	Renderer->CreateAnimation("ATTACK_WINDBOOMERANG_END", "ICE_BLAST.bmp", 2, 0, 0.2f, false);

	// �浹ü ����
	{
		BodyCollsion = CreateCollision(CollisionOrder::PlayerSkill);
		BodyCollsion->SetCollisionScale({ 100, 100 });
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
	}
}

void SKILL_PlayerWindBoomerang::Update(float _Delta)
{
	// �̵� => ���� ��ȯ �ʿ�

	float4 NextPos = Dir * _Delta * Speed;

	// livetime���� ����
	// ���������� ó�� �����Ǿ��� ���� ������ �Ǿ���ϰ�
	// �÷��̾� �߽ɿ� �ε����� �Ҹ��ϴ� ��ĵ� ����
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


	// ������ ó��
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