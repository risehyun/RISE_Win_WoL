#include "Spawner_BossTrigger.h"
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "Boss.h"

Spawner_BossTrigger::Spawner_BossTrigger()
{
}

Spawner_BossTrigger::~Spawner_BossTrigger()
{
}

void Spawner_BossTrigger::Start()
{
	HitCollision = CreateCollision(CollisionOrder::Map);
	HitCollision->SetCollisionScale({ 200, 100 });
	HitCollision->SetCollisionType(CollisionType::CirCle);
}

void Spawner_BossTrigger::Update(float _Delta)
{
	std::vector<GameEngineCollision*> _Col;
	if (true == HitCollision->Collision(CollisionOrder::PlayerBody, _Col
		, CollisionType::CirCle
		, CollisionType::CirCle
	))
	{
		Boss* NewBoss = GetLevel()->CreateActor<Boss>();
		NewBoss->SetPos({ 1750, 700 });
		Death();
	}
}