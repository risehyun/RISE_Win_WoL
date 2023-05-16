#include "Player.h"
#include "ContentsEnum.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Bullet.h"

Player::Player()
{
}

Player::~Player()
{
}


void Player::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Test.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.GetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");




		// sprite 로딩


		// 캐릭터 이동
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("FRONT_COMPLETE.bmp"), 11, 7);

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BACK_COMPLETE.bmp"), 11, 7);

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("LEFT_COMPLETE.bmp"), 11, 7);

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("RIGHT_COMPLETE.bmp"), 11, 7);
		






		

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("idle.bmp"));

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Fireball_0.bmp"));



		// UI 임시

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HPBar.bmp"));

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_PLAYERBAR.bmp"));

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_MONEY.bmp"));

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_SKILLBAR.bmp"));

		
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);
		MainRenderer->SetRenderScale({ 100, 100 });
		// MainRenderer->SetSprite("Left_Player.bmp");

		MainRenderer->CreateAnimation("Idle_FRONT", "FRONT_COMPLETE.bmp", 0, 0, 0.1f, true);







		// RUN
		MainRenderer->CreateAnimation("Run_FRONT", "FRONT_COMPLETE.bmp", 12, 14, 0.1f, true);

		MainRenderer->CreateAnimation("Run_BACK", "BACK_COMPLETE.bmp", 12, 14, 0.1f, true);

		MainRenderer->CreateAnimation("Run_LEFT", "LEFT_COMPLETE.bmp", 12, 16, 0.1f, true);

		MainRenderer->CreateAnimation("Run_RIGHT", "RIGHT_COMPLETE.bmp", 12, 16, 0.1f, true);







		MainRenderer->ChangeAnimation("Idle");
	}

	//{

	//	GameEngineRenderer* Ptr = CreateRenderer("idle.Bmp", RenderOrder::Play);
	//	Ptr->SetRenderScale({ 100, 100 });
	//	Ptr->SetTexture("idle.Bmp");
	//}

	//{
	//	GameEngineRenderer* Ptr = CreateRenderer("HPBar.bmp", RenderOrder::Play);
	//	Ptr->SetRenderPos({ 0, -70 });
	//	Ptr->SetRenderScale({ 100, 20 });
	//	Ptr->SetTexture("HPBar.bmp");
	//}
	{
		GameEngineRenderer* Ptr = CreateRenderer("UI_PLAYERBAR.bmp", RenderOrder::Play);
		Ptr->SetRenderPos({ -425, -320 });
		Ptr->SetRenderScale({ 328, 80 });
		Ptr->SetTexture("UI_PLAYERBAR.bmp");
	}

	{
		GameEngineRenderer* Ptr = CreateRenderer("UI_MONEY.bmp", RenderOrder::Play);
		Ptr->SetRenderPos({ 0, 340 });
		Ptr->SetRenderScale({ 16, 16 });
		Ptr->SetTexture("UI_MONEY.bmp");
	}

	{
		GameEngineRenderer* Ptr = CreateRenderer("UI_SKILLBAR.bmp", RenderOrder::Play);
		Ptr->SetRenderPos({ -425, 340 });
		Ptr->SetRenderScale({ 400, 100 });
		Ptr->SetTexture("UI_SKILLBAR.bmp");
	}

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	SetPos(WinScale.Half());

}

void Player::Update(float _Delta)
{
	float Speed = 200.0f;

	float4 MovePos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A'))
	{
		MovePos = { -Speed * _Delta, 0.0f };
		MainRenderer->ChangeAnimation("Run_LEFT");
	}

	if (true == GameEngineInput::IsPress('D'))
	{
		MovePos = { Speed * _Delta, 0.0f };

		MainRenderer->ChangeAnimation("Run_RIGHT");	
	}

	if (true == GameEngineInput::IsPress('W'))
	{
		MovePos = { 0.0f, -Speed * _Delta };

		MainRenderer->ChangeAnimation("Run_BACK");
	}

	if (true == GameEngineInput::IsPress('S'))
	{
		MovePos = { 0.0f, Speed * _Delta };
		MainRenderer->ChangeAnimation("Run_FRONT");
	}






	if (MovePos.X != 0.0f || MovePos.Y != 0.0f)
	{
		//MainRenderer->ChangeAnimation("Run");
	}
	else
	{
		MainRenderer->ChangeAnimation("Idle_FRONT");
	}




	if (true == GameEngineInput::IsUp(VK_LBUTTON))
	{
		float4 Pos = GameEngineWindow::MainWindow.GetMousePos();

		Bullet* NewBullet = GetLevel()->CreateActor<Bullet>();
		NewBullet->Renderer->SetTexture("Fireball_0.bmp");

		NewBullet->SetDir(float4::RIGHT);
		NewBullet->SetPos(GetPos());
//		NewBullet->SetPos(Pos);
	}

	AddPos(MovePos);
	GetLevel()->GetMainCamera()->AddPos(MovePos);
}

void Player::Render()
{


}

void Player::Release()
{

}