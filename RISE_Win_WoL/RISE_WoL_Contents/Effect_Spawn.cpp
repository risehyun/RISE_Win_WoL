#include "Effect_Spawn.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>

#include <GameEngineCore/GameEngineRenderer.h>

#include <GameEngineCore/GameEngineLevel.h>

#include "Monster.h"
#include "Monster_Swordman.h"
#include "Monster_Archer.h"
#include "MiniBoss_GrandSummoner.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineRandom.h>


Effect_Spawn::Effect_Spawn()
{

}

Effect_Spawn::~Effect_Spawn()
{

}

void Effect_Spawn::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("SPAWN_PLAYER.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Effect\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SPAWN_PLAYER.bmp"), 8, 1);

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SPAWN_SWORDMAN.bmp"), 32, 1);

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SPAWN_ARCHER.bmp"), 32, 1);

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SPAWN_SUMMONER.bmp"), 32, 1);
		
	}

}


// 객체마다 유효 시간이 다르기 때문에 변수로 따로 빼서 관리
void Effect_Spawn::Update(float _Delta)
{

	// 스포너의 애니메이션 재생이 끝나면
	if (Renderer->IsAnimationEnd())
	{
		if (index == 1)
		{
			SpawnMonster(SpawnType::Swordman);

		}

		else if (index == 2)
		{
			SpawnMonster(SpawnType::Archer);

		}

		else if (index == 3)
		{
			SpawnMonster(SpawnType::GrandSummoner);
			
		}

		index = 0;
		Death();
	}
}

void Effect_Spawn::Render(float _Delta)
{



}

void Effect_Spawn::SpawnObject(SpawnType spawnType, float4 _Scale)
{
	Renderer = CreateRenderer();
	Renderer->SetRenderScale({ _Scale });
	Renderer->SetOrder(1000);

	switch (spawnType)
	{
	case SpawnType::Player:
		Renderer->CreateAnimation("SPAWN_PLAYER", "SPAWN_PLAYER.bmp", 0, 7, 0.1f, false);
		Renderer->ChangeAnimation("SPAWN_PLAYER");
		break;

	case SpawnType::Swordman:
		Renderer->CreateAnimation("SPAWN_SWORDMAN", "SPAWN_SWORDMAN.bmp", 0, 31, 0.1f, false);
		Renderer->ChangeAnimation("SPAWN_SWORDMAN");
		index = 1;
		break;

	case SpawnType::Archer:
		Renderer->CreateAnimation("SPAWN_ARCHER", "SPAWN_ARCHER.bmp", 0, 31, 0.1f, false);
		Renderer->ChangeAnimation("SPAWN_ARCHER");
		index = 2;
		break;


	case SpawnType::GrandSummoner:
		Renderer->CreateAnimation("SPAWN_SUMMONER", "SPAWN_SUMMONER.bmp", 0, 31, 0.1f, false);
		Renderer->ChangeAnimation("SPAWN_SUMMONER");
		index = 3;
		break;

	default:
		break;

	}
}

void Effect_Spawn::SpawnMonster(SpawnType spawnType)
{

	if (spawnType == SpawnType::Swordman)
	{
		Monster* NewMonster = GetLevel()->CreateActor<Monster_Swordman>();
		NewMonster->SetPos(GetPos());
	}

	else if (spawnType == SpawnType::Archer)
	{
		Monster* NewMonster = GetLevel()->CreateActor<Monster_Archer>();
		NewMonster->SetPos(GetPos());

	}

	else if (spawnType == SpawnType::GrandSummoner)
	{
		Monster* NewMonster = GetLevel()->CreateActor<MiniBoss_GrandSummoner>();
		NewMonster->SetPos(GetPos());

	}

}
