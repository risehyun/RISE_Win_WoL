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
	if (false == ResourcesManager::GetInst().IsLoadTexture("PLAYER_WINDBOOMERANG_ATTACK.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Skill\\PlayerSkills\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("PLAYER_WINDBOOMERANG_ATTACK.bmp"), 4, 1);
	}

	// ������ ������ �ε��� �ؽ�ó ����
	Renderer = CreateRenderer();
	Renderer->SetRenderScale({ 100, 100 });
	Renderer->SetTexture("PLAYER_WINDBOOMERANG_ATTACK.bmp");

	// �ִϸ��̼� ����
	Renderer->CreateAnimation("ATTACK_WINDBOOMERANG", "PLAYER_WINDBOOMERANG_ATTACK.bmp", 0, 3, 0.1f, true);


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
	if (0.4f <= GetLiveTime())
	{
		AddPos(NextPos);
	}

	else
	{
		AddPos(-NextPos);
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

	if (0.8f < GetLiveTime())
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