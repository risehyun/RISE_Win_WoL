#include "SKILL_Tornado.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"

void SKILL_Tornado::Start()
{
	// ��ų �ؽ�ó �ε�
	if (false == ResourcesManager::GetInst().IsLoadTexture("ARCANA_Tornado.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Skill\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("ARCANA_Tornado.bmp"), 3, 4);
	}

	// ������ ������ �ε��� �ؽ�ó ����
	Renderer = CreateRenderer();
	Renderer->SetRenderScale({ 600, 400 });
	Renderer->CreateAnimation("ARCANA_Tornado", "ARCANA_Tornado.bmp", 0, 11, 0.2f, false);
	Renderer->ChangeAnimation("ARCANA_Tornado");
	Renderer->SetOrder(2);


	BodyCollsion = CreateCollision(CollisionOrder::PlayerSkill);
	BodyCollsion->SetCollisionScale({ 300, 300 });
	BodyCollsion->SetCollisionType(CollisionType::CirCle);
	BodyCollsion->SetCollisionPos({ 0, 0 });


	// �Ϲ� 5 HIT, ��ȭ�� 7 HIT(������ ����)
	m_iAttackPower = 50;

}

void SKILL_Tornado::Update(float _Delta)
{

	// �ǰ� ���� ���� ���� ���͸� ������ ���ݾ� ����鿴�ٰ�(4 HIT), ������ Ÿ���� ������ ƨ�ܺ���(1 HIT)

	float4 NextPos = { _Delta * Speed };

	if (2.0f > GetLiveTime())
	{
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

					Actor->AddPos(NextPos);

					if (2.0f < GetLiveTime())
					{
						Actor->AddPos(-NextPos);
					}

				}
			}
		}
	}

	if (Renderer->IsAnimationEnd())
	{
		Death();
	}
}