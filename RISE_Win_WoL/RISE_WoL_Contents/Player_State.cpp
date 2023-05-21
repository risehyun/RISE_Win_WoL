#include "Player.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "Bullet.h"
#include <GameEnginePlatform/GameEngineWindow.h>

void Player::IdleStart()
{
	ChangeAnimationState("Idle");
}

void Player::RunStart()
{
	ChangeAnimationState("Run");
}

void Player::DashStart()
{
	ChangeAnimationState("Dash");
}

void Player::AttackStart()
{
	ChangeAnimationState("Attack");
	//	ChangeAnimation("Attack_NORMAL");
}

void Player::Skill_ICEBLAST_Start()
{
	ChangeAnimationState("Attack");
}












void Player::IdleUpdate(float _Delta)
{
	//	Gravity(_Delta);

	if (true == GameEngineInput::IsDown('A')
		|| true == GameEngineInput::IsDown('W')
		|| true == GameEngineInput::IsDown('S')
		|| true == GameEngineInput::IsDown('D'))
	{
		DirCheck();
		ChanageState(PlayerState::Run);
		return;
	}

	if (true == GameEngineInput::IsUp(VK_LBUTTON))
	{
		ChanageState(PlayerState::Attack);

		float4 Pos = GameEngineWindow::MainWindow.GetMousePos();


		Bullet* NewBullet = GetLevel()->CreateActor<Bullet>();
		NewBullet->Renderer->SetTexture("Fireball_0.bmp");

		NewBullet->SetDir(float4::RIGHT);
		NewBullet->SetPos(GetPos());

		return;
	}

	if (true == GameEngineInput::IsDown(VK_RBUTTON))
	{
		ChanageState(PlayerState::Attack);
		return;
	}

	if (true == GameEngineInput::IsDown('Q'))
	{
		ChanageState(PlayerState::Attack);
		return;
	}

	if (true == GameEngineInput::IsUp(VK_SPACE))
	{
		ChanageState(PlayerState::Dash);
		return;
	}

}


void Player::RunUpdate(float _Delta)
{
	//	Gravity(_Delta);

	DirCheck();

	float Speed = 200.0f;

	float4 MovePos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A') && Dir == PlayerDir::Left)
	{
		MovePos = { -Speed * _Delta, 0.0f };
	}

	else if (true == GameEngineInput::IsPress('D') && Dir == PlayerDir::Right)
	{
		MovePos = { Speed * _Delta, 0.0f };
	}

	else if (true == GameEngineInput::IsPress('W') && Dir == PlayerDir::Up)
	{
		MovePos = { 0.0f, -Speed * _Delta };
	}

	else if (true == GameEngineInput::IsPress('S') && Dir == PlayerDir::Down)
	{
		MovePos = { 0.0f, Speed * _Delta };
	}

	if (MovePos == float4::ZERO)
	{
		DirCheck();
		ChanageState(PlayerState::Idle);
	}


	AddPos(MovePos);
	GetLevel()->GetMainCamera()->AddPos(MovePos);


	if (true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		ChanageState(PlayerState::Attack);
		return;
	}

	if (true == GameEngineInput::IsUp(VK_SPACE))
	{
		ChanageState(PlayerState::Dash);
		return;
	}

}

void Player::DashUpdate(float _Delta)
{

	DirCheck();

	float Speed = 400.0f;

	float4 MovePos = float4::ZERO;

	if (Dir == PlayerDir::Left)
	{
		MovePos = { -Speed * _Delta, 0.0f };
	}

	else if (Dir == PlayerDir::Right)
	{
		MovePos = { Speed * _Delta, 0.0f };
	}

	else if (Dir == PlayerDir::Up)
	{
		MovePos = { 0.0f, -Speed * _Delta };
	}

	else if (Dir == PlayerDir::Down)
	{
		MovePos = { 0.0f, Speed * _Delta};
	}

	AddPos(MovePos);
	GetLevel()->GetMainCamera()->AddPos(MovePos);

	if (1.5f <= GetLiveTime())
	{

		if (true == GameEngineInput::IsPress('A') || true == GameEngineInput::IsPress('W') || 
			true == GameEngineInput::IsPress('S') || true == GameEngineInput::IsPress('D'))
		{
			ChanageState(PlayerState::Run);
		}

		else
		{
			ChanageState(PlayerState::Idle);
		}

		ResetLiveTime();
	}


	return;
}


// 수정 필요
void Player::AttackUpdate(float _Delta)
{

	if (1.5f <= GetLiveTime())
	{
		DirCheck();
		ChanageState(PlayerState::Idle);

		ResetLiveTime();
	}

	return;
}