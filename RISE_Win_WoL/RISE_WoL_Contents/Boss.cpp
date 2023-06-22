#include "Boss.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "ContentsEnum.h"

#include "Player.h"
#include "EFFECT_RedCastingCircle.h"

#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineLevel.h>


Boss::Boss()
{
}
Boss::~Boss()
{
}
void Boss::Start()
{

	if (false == ResourcesManager::GetInst().IsLoadTexture("BOSS_LEFT.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Monster\\Boss");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("BOSS_LEFT.bmp"));

		// 텍스처 로딩과 함께 애니메이션을 위한 시트 분할
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BOSS_LEFT.bmp"), 9, 6);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("RedCastingCircle.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Effect");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("RedCastingCircle.bmp"));
	}


	MainRenderer = CreateRenderer(RenderOrder::Play);
	MainRenderer->SetRenderScale({ 150, 200 });
	MainRenderer->CreateAnimation("Left_Idle", "BOSS_LEFT.bmp", 0, 0, 0.1f, true);
	MainRenderer->CreateAnimation("Left_Jump", "BOSS_LEFT.bmp", 27, 28, 0.2f, false);
	MainRenderer->CreateAnimation("Left_JumpAir", "BOSS_LEFT.bmp", 29, 30, 0.2f, false);
	MainRenderer->CreateAnimation("Left_JumpFall", "BOSS_LEFT.bmp", 31, 32, 0.5f, false);
	MainRenderer->CreateAnimation("Left_JumpGround", "BOSS_LEFT.bmp", 33, 34, 0.5f, false);
	MainRenderer->ChangeAnimation("Left_Idle");
	MainRenderer->SetRenderPos({ 0,0 });


	//TestRenderer = CreateRenderer();
	//TestRenderer->SetRenderScale({ 200, 200 });
	//TestRenderer->SetTexture("RedCastingCircle.bmp");
	//TestRenderer->SetRenderPos({ 0.0f, 0.0f });


}

void Boss::Update(float _Delta)
{
	float4 playerPos = Player::GetMainPlayer()->GetPos();
	float4 Dir = playerPos - GetPos();


	Dir.Normalize();



	float4 MovePos;

	if (true == GameEngineInput::IsPress('P'))
	{
		EFFECT_RedCastingCircle* NewCircle = GetLevel()->CreateActor<EFFECT_RedCastingCircle>();

		NewCircle->GetMainRenderer()->SetRenderPos({ playerPos });

		if (GetLiveTime() < 4.0f)
		{

			AddPos(float4::UP * 100.0f * _Delta);

			MainRenderer->ChangeAnimation("Left_Jump");
		}

		if (GetLiveTime() > 2.0f && GetLiveTime() < 4.0f)
		{
			MainRenderer->ChangeAnimation("Left_JumpAir");

			AddPos((float4::UP + float4::LEFT) * 50.0f * _Delta);
		}

		if (GetLiveTime() > 4.0f && GetLiveTime() < 5.0f)
		{
			MainRenderer->ChangeAnimation("Left_JumpFall");
			
			AddPos(Dir * _Delta * 100.0f);
		}

		if (GetLiveTime() > 5.0f)
		{
			MainRenderer->ChangeAnimation("Left_JumpGround");

			AddPos(Dir * _Delta * 100.0f);
		}


	}
	//Dir.Normalize();

	//AddPos(Dir * _Delta * 100.0f);
//	MainRenderer->SetRenderPos();

}

void Boss::Render(float _Delta)
{

}
