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

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("ICE_BLAST.bmp"), 5, 1);
	}

	// ������ ������ �ε��� �ؽ�ó ����
	Renderer = CreateRenderer();
	Renderer->SetRenderScale({ 200, 200 });
	Renderer->SetRenderPos({ -100, 0 });

	Renderer2 = CreateRenderer();
	Renderer2->SetRenderPos({ -200, 0 });
	Renderer2->SetRenderScale({ 200, 200 });

	Renderer3 = CreateRenderer();
	Renderer3->SetRenderScale({ 200, 200 });
	Renderer3->SetRenderPos({ -300, 0 });

	Renderer4 = CreateRenderer();
	Renderer4->SetRenderScale({ 200, 200 });
	Renderer4->SetRenderPos({ -400, 0 });

	// �ִϸ��̼� ����
	Renderer->CreateAnimation("ATTACK_WINDBOOMERANG", "ICE_BLAST.bmp", 0, 2, 0.2f, true);
	Renderer->CreateAnimation("ATTACK_WINDBOOMERANG_END", "ICE_BLAST.bmp", 2, 0, 0.2f, false);


	Renderer2->CreateAnimation("ATTACK_WINDBOOMERANG2", "ICE_BLAST.bmp", 2, 2, 0.2f, true);
	Renderer3->CreateAnimation("ATTACK_WINDBOOMERANG2", "ICE_BLAST.bmp", 2, 2, 0.2f, true);
	Renderer4->CreateAnimation("ATTACK_WINDBOOMERANG3", "ICE_BLAST.bmp", 3, 4, 0.2f, true);

	Renderer2->ChangeAnimation("ATTACK_WINDBOOMERANG2");
	Renderer3->ChangeAnimation("ATTACK_WINDBOOMERANG2");
	Renderer4->ChangeAnimation("ATTACK_WINDBOOMERANG3");

	// �浹ü ����
	
	BodyCollsion = CreateCollision(CollisionOrder::PlayerSkill);
	BodyCollsion->SetCollisionScale({ 100, 100 });
	BodyCollsion->SetCollisionType(CollisionType::CirCle);
	BodyCollsion->SetCollisionPos({ -100, 0 });
	
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

					Actor->AddPos({ Dir * _Delta * Speed });

					if (2.0f < GetLiveTime())
					{
						Actor->AddPos(-NextPos);
					}

				}
			}
		}
	}

	else
	{


		if (Player::GetMainPlayer()->GetPos().X < GetPos().X
			|| Player::GetMainPlayer()->GetPos().X > GetPos().X
			|| Player::GetMainPlayer()->GetPos().Y < GetPos().Y
			|| Player::GetMainPlayer()->GetPos().Y > GetPos().Y)
		{
			AddPos(-NextPos);

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

						Actor->SetPos(-NextPos);
					}
				}
			}

			//if (BodyCollsion != nullptr)
			//{
			//	BodyCollsion->SetCollisionPos({ 400, 0 });
			//}

		}
			
	}


	

	if (4.0f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			Renderer->Death();
			Renderer = nullptr;

			Renderer2->Death();
			Renderer2 = nullptr;

			Renderer3->Death();
			Renderer3 = nullptr;

			Renderer4->Death();
			Renderer4 = nullptr;

			BodyCollsion->Death();
			BodyCollsion = nullptr;
		}
	}
}