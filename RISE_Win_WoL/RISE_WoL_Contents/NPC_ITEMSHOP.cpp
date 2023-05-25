#include "NPC_ITEMSHOP.h"
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineCollision.h>

NPC_ITEMSHOP::NPC_ITEMSHOP()
{
}

NPC_ITEMSHOP::~NPC_ITEMSHOP()
{
}

void NPC_ITEMSHOP::Update(float _Delta)
{

}

void NPC_ITEMSHOP::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("SWORDMAN_TEST.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Monster\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("SWORDMAN_TEST.bmp"));
	}

	//{
	//	GameEngineRenderer* Ptr = CreateRenderer("SWORDMAN_TEST.bmp", RenderOrder::Play);
	//	Ptr->SetRenderScale({ 150, 150 });
	//	Ptr->SetTexture("SWORDMAN_TEST.bmp");
	//}

	GameEngineCollision* BodyCollsion = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollsion->SetCollisionScale({ 100, 100 });
	BodyCollsion->SetCollisionType(CollisionType::CirCle);

}