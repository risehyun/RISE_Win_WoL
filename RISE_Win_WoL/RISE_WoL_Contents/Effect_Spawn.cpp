#include "Effect_Spawn.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>

#include <GameEngineCore/GameEngineRenderer.h>


#include <GameEngineCore/GameEngineLevel.h>
#include "Monster.h"
#include "Monster_Swordman.h"

#include <GameEnginePlatform/GameEngineWindow.h>


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

	// 렌더러 생성과 로딩된 텍스처 지정
	//Renderer = CreateRenderer();
	//Renderer->SetRenderScale({ 100, 365 });
	//Renderer->SetOrder(1000);

	//// 애니메이션 생성
	//Renderer->CreateAnimation("SPAWN_PLAYER", "SPAWN_PLAYER.bmp", 0, 7, 0.1f, false);

	//Renderer->CreateAnimation("SPAWN_SWORDMAN", "SPAWN_SWORDMAN.bmp", 0, 31, 0.1f, false);

//	Renderer->ChangeAnimation("SPAWN_SWORDMAN");

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
				Monster* NewMonster = GetLevel()->CreateActor<Monster_Swordman>();
				NewMonster->SetPos({ 1800, 1600 });
		
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
//	Renderer->SetRenderScale({ 100, 365 });
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