#include "Effect_Spawn.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>

#include <GameEngineCore/GameEngineRenderer.h>


#include <GameEngineCore/GameEngineLevel.h>
#include "Monster.h"
#include "Monster_Swordman.h"
#include "Monster_Archer.h"

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
	}

}


// 객체마다 유효 시간이 다르기 때문에 변수로 따로 빼서 관리
void Effect_Spawn::Update(float _Delta)
{
	if (effectLiveTime < GetLiveTime())
	{

		if (nullptr != Renderer)
		{

			Renderer->Death();
			Renderer = nullptr;

			if (effectLiveTime == 3.0f)
			{
		//		Monster* NewMonster = GetLevel()->CreateActor<Monster_Swordman>();
				
				Monster* NewMonster = GetLevel()->CreateActor<Monster_Archer>();


				int Test2 = GameEngineRandom::MainRandom.RandomInt(0, 500);
				NewMonster->SetPos({ 1800+static_cast<float>(Test2), 1600 + static_cast<float>(Test2) });
		
			}

			this->Death();

		}

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
		effectLiveTime = 0.8f;



		break;

	case SpawnType::Swordman:
		Renderer->CreateAnimation("SPAWN_SWORDMAN", "SPAWN_SWORDMAN.bmp", 0, 31, 0.1f, false);
		Renderer->ChangeAnimation("SPAWN_SWORDMAN");
		effectLiveTime = 3.0f;
		break;

	default:
		break;

	}
}