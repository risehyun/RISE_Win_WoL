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
#include "Monster.h"

Player* Player::MainPlayer = nullptr;

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
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");


		if (false == ResourcesManager::GetInst().IsLoadTexture("FRONT_COMPLETE.bmp"))
		{
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("FRONT_COMPLETE.bmp"), 11, 7);

			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BACK_COMPLETE.bmp"), 11, 7);

			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("LEFT_COMPLETE.bmp"), 11, 7);

			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("RIGHT_COMPLETE.bmp"), 11, 7);



			// 스킬 테스트
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("PLAYER_NORMAL_ATTACK.bmp"), 8, 8);
		}

		if(false == ResourcesManager::GetInst().IsLoadTexture("idle.Bmp"))
		{
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("idle.bmp"));
		}

		if (false == ResourcesManager::GetInst().IsLoadTexture("Fireball_0.Bmp"))
		{		
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Fireball_0.bmp"));
		}

		if (false == ResourcesManager::GetInst().IsLoadTexture("DashAirBurst.Bmp"))
		{
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("DashAirBurst.bmp"));
		}

		// UI 임시
		if (false == ResourcesManager::GetInst().IsLoadTexture("HPBar.Bmp"))
		{
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HPBar.bmp"));

			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_PLAYERBAR.bmp"));

			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_MONEY.bmp"));

			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_SKILLBAR.bmp"));
		}

#pragma region 애니메이션 생성
		{
			// 렌더러 설정
//			MainRenderer = CreateRenderer(RenderOrder::Play);
			MainRenderer = CreateRenderer(1000);
			MainRenderer->SetRenderScale({ 100, 100 });

			// IDLE
			MainRenderer->CreateAnimation("Left_Idle", "LEFT_COMPLETE.bmp", 0, 0, 0.1f, true);

			MainRenderer->CreateAnimation("Right_Idle", "RIGHT_COMPLETE.bmp", 0, 0, 0.1f, true);

			MainRenderer->CreateAnimation("Down_Idle", "FRONT_COMPLETE.bmp", 0, 0, 0.1f, true);

			MainRenderer->CreateAnimation("Up_Idle", "BACK_COMPLETE.bmp", 0, 0, 0.1f, true);

			// RUN
			MainRenderer->CreateAnimation("Down_Run", "FRONT_COMPLETE.bmp", 12, 14, 0.1f, true);

			MainRenderer->CreateAnimation("Up_Run", "BACK_COMPLETE.bmp", 12, 14, 0.1f, true);

			MainRenderer->CreateAnimation("Left_Run", "LEFT_COMPLETE.bmp", 12, 16, 0.1f, true);
			
			MainRenderer->CreateAnimation("Right_Run", "RIGHT_COMPLETE.bmp", 12, 16, 0.1f, true);

			
			// Dash
			MainRenderer->CreateAnimation("Down_Dash", "FRONT_COMPLETE.bmp", 23, 25, 0.1f, false);

			MainRenderer->CreateAnimation("Up_Dash", "BACK_COMPLETE.bmp", 23, 25, 0.1f, false);

			MainRenderer->CreateAnimation("Left_Dash", "LEFT_COMPLETE.bmp", 23, 25, 0.1f, false);

			MainRenderer->CreateAnimation("Right_Dash", "RIGHT_COMPLETE.bmp", 23, 25, 0.1f, false);



			// NORMAL ATTACK
			MainRenderer->CreateAnimation("Down_Attack", "FRONT_COMPLETE.bmp", 33, 36, 0.05f, false);

			MainRenderer->CreateAnimation("Up_Attack", "BACK_COMPLETE.bmp", 55, 58, 0.05f, false);
			 
			MainRenderer->CreateAnimation("Left_Attack", "LEFT_COMPLETE.bmp", 33, 36, 0.05f, false);

			MainRenderer->CreateAnimation("Right_Attack", "RIGHT_COMPLETE.bmp", 33, 36, 0.05f, false);



//			MainRenderer->CreateAnimation("Attack_NORMAL", "PLAYER_NORMAL_ATTACK.bmp", 0, 8, 0.1f, true);
		}

#pragma endregion

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
	}

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

//	SetPos(WinScale.Half());

	// 레벨별로 캐릭터 시작 위치가 다름
	// playLevel의 경우 { 1850, 1700 }
	// bossLevel의 경우 { 1710, 2610 }
	SetPos({ 1710, 2610 });
	ChanageState(PlayerState::Idle);

}

void Player::Update(float _Delta)
{
	// 디버깅용 모든 몬스터를 없애는 함수 발동
	if (true == GameEngineInput::IsDown('L'))
	{
		Monster::AllMonsterDeath();
	}

	// 중력 제거
	if (true == GameEngineInput::IsDown('Y'))
	{
		MainRenderer->SetOrder(-200);
//		GravityOff();
	}

	if (true == GameEngineInput::IsDown('U'))
	{
		MainRenderer->SetOrder(1000);
		//		GravityOff();
	}

	StateUpdate(_Delta);

	CameraFocus();
}

void Player::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PlayerState::Idle:
		return IdleUpdate(_Delta);

	case PlayerState::Run:
		return RunUpdate(_Delta);

	case PlayerState::Dash:
		return DashUpdate(_Delta);
	
	case PlayerState::Attack:
		return AttackUpdate(_Delta);

	case PlayerState::Skill_ICEBLAST:
		return AttackUpdate(_Delta);

	default:
		break;
	}
}

void Player::ChanageState(PlayerState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;

		case PlayerState::Run:
			RunStart();
			break;

		case PlayerState::Attack:
			AttackStart();
			break;

		case PlayerState::Skill_ICEBLAST:
			Skill_ICEBLAST_Start();
			break;

		case PlayerState::Dash:
			DashStart();
			break;
	
		default:
			break;
		}
	}

	State = _State;
}

void Player::DirCheck()
{

	if (true == GameEngineInput::IsDown('A'))
	{
		Dir = PlayerDir::Left;
		ChangeAnimationState(CurState);
		return;
	}

	if (true == GameEngineInput::IsDown('D'))
	{
		Dir = PlayerDir::Right;
		ChangeAnimationState(CurState);
		return;
	}

	if (true == GameEngineInput::IsDown('W'))
	{
		Dir = PlayerDir::Up;
		ChangeAnimationState(CurState);
		return;
	}

	if (true == GameEngineInput::IsDown('S'))
	{
		Dir = PlayerDir::Down;
		ChangeAnimationState(CurState);
		return;
	}

}

void Player::ChangeAnimationState(const std::string& _StateName)
{
	// "Idle"
	// _StateName
	std::string AnimationName;
	switch (Dir)
	{
	case PlayerDir::Right:
		AnimationName = "Right_";
		break;

	case PlayerDir::Left:
		AnimationName = "Left_";
		break;

	case PlayerDir::Up:
		AnimationName = "Up_";
		break;

	case PlayerDir::Down:
		AnimationName = "Down_";
		break;

	default:
		break;
	}

	AnimationName += _StateName;
	CurState = _StateName;
	MainRenderer->ChangeAnimation(AnimationName);
}

void Player::LevelStart()
{
	MainPlayer = this;
}