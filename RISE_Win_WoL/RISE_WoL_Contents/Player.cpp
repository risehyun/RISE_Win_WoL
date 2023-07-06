#include "Player.h"
#pragma region Headers

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

#include "SKILL_PlayerNormalAttack.h"
#include "SKILL_PlayerWindBoomerang.h"
#include "SKILL_EarthenAegis.h"
#include "SKILL_SnowflakeChakrams.h"
#include "SKILL_Tornado.h"
#include "SKILL_Fireball.h"


#include "PlayUIManager.h"

#include "UI_Inventory.h"

#include <GameEngineCore/GameEngineCollision.h>

#include <GameEnginePlatform/GameEngineSound.h>
#include "UI_DamageText.h"

#pragma endregion

Player* Player::MainPlayer = nullptr;

Player::Player()
{

}

Player::~Player()
{

}

void Player::SetInitStat()
{
	// 이후 Define으로 변경
	m_fMoveSpeed = 100.0f;
	m_fDashSpeed = 200.0f;
	m_fAttackSpeed = 100.0f;
	m_iMaxHp = 500;
	m_iCurHp = m_iMaxHp;
	m_iMaxMp = 200;
	m_iCurMp = m_iMaxMp;
	m_fAttackRange = 100.0f;
	m_iTotalGold = 0;
	m_iTotalCrystal = 0;
}

void Player::OnDamaged(int _iAttackPower, float4 _AttackPos)
{
	m_iCurHp -= _iAttackPower;

	UI_DamageText* NewText = GetLevel()->CreateActor<UI_DamageText>();

	float4 DirDeg = _AttackPos - GetPos();

	if ((DirDeg.AngleDeg() > 0 && DirDeg.AngleDeg() < 45)
		|| (DirDeg.AngleDeg() > 315 && DirDeg.AngleDeg() < 360))
	{
		NewText->SetDir(float4::LEFT);
	}

	else if (DirDeg.AngleDeg() > 225 && DirDeg.AngleDeg() < 316)
	{
		NewText->SetDir(float4::LEFT);
	}

	else if (DirDeg.AngleDeg() > 135 && DirDeg.AngleDeg() < 225)
	{
		NewText->SetDir(float4::RIGHT);
	}

	else if (DirDeg.AngleDeg() > 44 && DirDeg.AngleDeg() < 135)
	{
		NewText->SetDir(float4::RIGHT);
	}

	NewText->GetMainRenderer()->SetText(std::to_string(_iAttackPower), 20, "Noto Sans Med");
	NewText->SetPos({ GetPos().X, GetPos().Y - 100.0f });

}

void Player::Start()
{

	SetInitStat();

	int a = m_iMaxHp;

	Dir = PlayerDir::Down;

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
		}

		if (false == ResourcesManager::GetInst().IsLoadTexture("DashAirBurst.Bmp"))
		{
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("DashAirBurst.bmp"));
		}

		// UI 임시
		if (false == ResourcesManager::GetInst().IsLoadTexture("UI_HPBAR.Bmp"))
		{
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_HPBAR.bmp"));

			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_PLAYERBAR.bmp"));

			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_MONEY.bmp"));

			//			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_SKILLBAR.bmp"));

			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_MANABAR.bmp"));

			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_MOUSE.bmp"));
		}

#pragma region 애니메이션 생성
		{
			// 렌더러 설정
			MainRenderer = CreateRenderer(1000);
			MainRenderer->SetRenderScale({ 100, 100 });
			MainRenderer->SetOrder(1);


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


			// DASH
			MainRenderer->CreateAnimation("Down_Dash", "FRONT_COMPLETE.bmp", 23, 25, 0.1f, false);
			MainRenderer->CreateAnimation("Up_Dash", "BACK_COMPLETE.bmp", 23, 25, 0.1f, false);
			MainRenderer->CreateAnimation("Left_Dash", "LEFT_COMPLETE.bmp", 23, 25, 0.1f, false);
			MainRenderer->CreateAnimation("Right_Dash", "RIGHT_COMPLETE.bmp", 23, 25, 0.1f, false);


			// NORMAL ATTACK
			MainRenderer->CreateAnimation("Down_Attack", "FRONT_COMPLETE.bmp", 33, 36, 0.05f, false);
			MainRenderer->CreateAnimation("Up_Attack", "BACK_COMPLETE.bmp", 55, 58, 0.05f, false);
			MainRenderer->CreateAnimation("Left_Attack", "LEFT_COMPLETE.bmp", 33, 36, 0.05f, false);
			MainRenderer->CreateAnimation("Right_Attack", "RIGHT_COMPLETE.bmp", 33, 36, 0.05f, false);


			// DAMAGE
			MainRenderer->CreateAnimation("Down_Damage", "FRONT_COMPLETE.bmp", 56, 57, 0.1f, false);
			MainRenderer->CreateAnimation("Up_Damage", "BACK_COMPLETE.bmp", 66, 67, 0.1f, false);
			MainRenderer->CreateAnimation("Left_Damage", "LEFT_COMPLETE.bmp", 66, 67, 0.1f, false);
			MainRenderer->CreateAnimation("Right_Damage", "RIGHT_COMPLETE.bmp", 66, 67, 0.1f, false);


			// DEATH
			MainRenderer->CreateAnimation("Down_Death", "FRONT_COMPLETE.bmp", 66, 72, 0.1f, false);
			MainRenderer->CreateAnimation("Up_Death", "FRONT_COMPLETE.bmp", 66, 72, 0.1f, false);
			MainRenderer->CreateAnimation("Left_Death", "FRONT_COMPLETE.bmp", 66, 72, 0.1f, false);
			MainRenderer->CreateAnimation("Right_Death", "FRONT_COMPLETE.bmp", 66, 72, 0.1f, false);

		}

#pragma endregion

		{
			GameEngineRenderer* Ptr = CreateRenderer("UI_MONEY.bmp", RenderOrder::Play);
			Ptr->SetRenderPos({ 0, 340 });
			Ptr->SetRenderScale({ 16, 16 });
			Ptr->SetTexture("UI_MONEY.bmp");
		}
	}

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	// 레벨별로 캐릭터 시작 위치가 다름
	// playLevel의 경우 { 1850, 1700 }
	// bossLevel의 경우 { 1710, 2610 }
	SetPos({ 2270, 1900 });
	ChangeState(PlayerState::Idle);

	{
		BodyCollsion = CreateCollision(CollisionOrder::PlayerBody);
		BodyCollsion->SetCollisionScale({ 100, 100 });
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
	}


	if (nullptr == GameEngineSound::FindSound("PLAYER_DIE.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("PLAYER_DIE.mp3"));
	}

	if (nullptr == GameEngineSound::FindSound("PLAYER_HITED.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("PLAYER_HITED.mp3"));
	}

}

void Player::Update(float _Delta)
{
	UpdateCooldown(_Delta);

	Update_ExplodingFireball_Cooldown(_Delta);

	Update_EarthenAegis_Cooldown(_Delta);

	Update_WhirlingTornado_Cooldown(_Delta);

	Update_SnowflakeChakrams_Cooldown(_Delta);


	if (true == GameEngineInput::IsDown(VK_F1))
	{
		IsInvincible = true;
	}


	// 일반 공격
	if (true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		ChangeState(PlayerState::Attack);

		SKILL_PlayerNormalAttack* NewAttack = GetLevel()->CreateActor<SKILL_PlayerNormalAttack>();

		DirCheck();

		if (Dir == PlayerDir::Left)
		{
			NewAttack->SetDir(float4::LEFT);
			NewAttack->SetPos(GetPos() + float4{ -100.0f, 0.0f, 0.0f, 0.0f });
			NewAttack->Renderer->ChangeAnimation("ATTACK_NORMAL_LEFT");
		}

		if (Dir == PlayerDir::Right)
		{
			NewAttack->SetDir(float4::RIGHT);
			NewAttack->SetPos(GetPos() + float4{ 100.0f, 0.0f, 0.0f, 0.0f });
			NewAttack->Renderer->ChangeAnimation("ATTACK_NORMAL_RIGHT");
		}

		if (Dir == PlayerDir::Up)
		{
			NewAttack->SetDir(float4::UP);
			NewAttack->SetPos(GetPos() + float4{ 0.0f, -100.0f, 0.0f, 0.0f });
			NewAttack->Renderer->ChangeAnimation("ATTACK_NORMAL_UP");
		}


		if (Dir == PlayerDir::Down)
		{
			NewAttack->SetDir(float4::DOWN);
			NewAttack->SetPos(GetPos() + float4{ 0.0f, 100.0f, 0.0f, 0.0f });
			NewAttack->Renderer->ChangeAnimation("ATTACK_NORMAL_DOWN");
		}

		return;
	}

	if (true == GameEngineInput::IsDown(VK_RBUTTON) && true == IsSkill_WhirlingTornado_Ready())
	{

		float4 MovePos = float4::ZERO;

		DirCheck();

		ChangeState(PlayerState::Attack);

		SKILL_Tornado* NewAttack = GetLevel()->CreateActor<SKILL_Tornado>();
		NewAttack->SetPos({ GetPos() });
		fWhirlingTornado_CurrentCooldown = fSkill_WhirlingTornado_Cooldown;
		return;

	}

	if (true == GameEngineInput::IsDown('E')
		&& true == IsSkill_EarthenAegis_Ready()
		&& true == IsHasEarthenAegis)
	{

		ChangeState(PlayerState::Skill_EarthenAegis);
		SKILL_EarthenAegis* NewAttack = GetLevel()->CreateActor<SKILL_EarthenAegis>();
		NewAttack->SetPos(GetPos() + float4{ 0.0f, 0.0f, 0.0f, 0.0f });
		fEarthenAegis_CurrentCooldown = fSkill_EarthenAegis_Cooldown;
		return;

	}

	if (true == GameEngineInput::IsDown('R') 
		&& true == IsSkill_SnowflakeChakrams_Ready()
		&& true == IsHasSnowflakeChakrams)
	{

		ChangeState(PlayerState::Skill_SnowflakeChakrams);
		SKILL_SnowflakeChakrams* NewAttack = GetLevel()->CreateActor<SKILL_SnowflakeChakrams>();
		NewAttack->SetPos(GetPos() + float4{ 0.0f, 0.0f, 0.0f, 0.0f });
		fSnowflakeChakrams_CurrentCooldown = fSkill_SnowflakeChakrams_Cooldown;
		return;

	}

	if (true == GameEngineInput::IsDown('Q') && true == IsSkill_ExplodingFireball_Ready())
	{

		ChangeState(PlayerState::Skill_ExplodingFireball);
		SKILL_Fireball* NewAttack = GetLevel()->CreateActor<SKILL_Fireball>();
		DirCheck();

		if (Dir == PlayerDir::Left)
		{
			NewAttack->SetDir(float4::LEFT);
			NewAttack->SetPos(GetPos() + float4{ -100.0f, 0.0f, 0.0f, 0.0f });
			NewAttack->Renderer->ChangeAnimation("ARCANA_Fireball_Left");
		}

		if (Dir == PlayerDir::Right)
		{
			NewAttack->SetDir(float4::RIGHT);
			NewAttack->SetPos(GetPos() + float4{ 100.0f, 0.0f, 0.0f, 0.0f });
			NewAttack->Renderer->ChangeAnimation("ARCANA_Fireball_Right");
			NewAttack->Renderer->SetRenderScale({ 120, 80 });
		}

		if (Dir == PlayerDir::Up)
		{
			NewAttack->SetDir(float4::UP);
			NewAttack->SetPos(GetPos() + float4{ 0.0f, -100.0f, 0.0f, 0.0f });
			NewAttack->Renderer->ChangeAnimation("ARCANA_Fireball_Up");
			NewAttack->Renderer->SetRenderScale({ 160, 120 });
		}

		if (Dir == PlayerDir::Down)
		{
			NewAttack->SetDir(float4::DOWN);
			NewAttack->SetPos(GetPos() + float4{ 0.0f, 100.0f, 0.0f, 0.0f });
			NewAttack->Renderer->ChangeAnimation("ARCANA_Fireball_Down");
			NewAttack->Renderer->SetRenderScale({ 160, 120 });
		}

		fExplodingFireball_CurrentCooldown = fSkill_ExplodingFireball_Cooldown;

	}

	if (true == GameEngineInput::IsUp(VK_SPACE))
	{
		ChangeState(PlayerState::Dash);
		return;
	}

	// 디버깅용 모든 몬스터를 없애는 함수 발동
	if (true == GameEngineInput::IsDown('L'))
	{
		Monster::AllMonsterDeath();
	}

	// 충돌 디버그
	if (true == GameEngineInput::IsDown('J'))
	{
		//	MainRenderer->SetOrder(-200);
		GameEngineLevel::CollisionDebugRenderSwitch();
	}

	BodyCollsion->CollisionCallBack
	(
		CollisionOrder::MonsterSkill
		, CollisionType::CirCle // _this의 충돌체 타입
		, CollisionType::CirCle // _Other의 충돌체 타입
		, [](GameEngineCollision* _this, GameEngineCollision* _Other)
		{

			GameEngineActor* thisActor = _this->GetActor();
			Player* PlayerPtr = dynamic_cast<Player*>(thisActor);

			GameEngineActor* Actor = _Other->GetActor();

			PlayerPtr->OnDamaged(Actor->GetAttackPower(), Actor->GetPos());

			//			PlayUIManager::UI->NewHpBar->GetMainRenderer()->AddRenderPos({ 0.1, 0 });

			if (PlayerPtr->m_iCurHp <= 0)
			{
				if (true == PlayerPtr->IsInvincible)
				{
					return;
				}

				else
				{
					PlayerPtr->ChangeState(PlayerState::Death);
				}
			}

			else
			{
				PlayerPtr->ChangeState(PlayerState::Damage);
			}

		}
	);

	StateUpdate(_Delta);

	DirCheck();

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

	case PlayerState::Damage:
		return OnDamagedUpdate(_Delta);

	case PlayerState::Death:
		return DeathUpdate(_Delta);

	case PlayerState::Skill_EarthenAegis:
		return Skill_EarthenAgis_Update(_Delta);

	case PlayerState::Skill_SnowflakeChakrams:
		return Skill_EarthenAgis_Update(_Delta);

	case PlayerState::Skill_ExplodingFireball:
		return Skill_Fireball_Update(_Delta);

	default:
		break;
	}
}

void Player::ChangeState(PlayerState _State)
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

		case PlayerState::Dash:
			DashStart();
			break;

		case PlayerState::Damage:
			OnDamagedStart();
			break;

		case PlayerState::Death:
			DeathStart();
			break;

		case PlayerState::Skill_EarthenAegis:
			Skill_EarthenAegis_Start();
			break;

		case PlayerState::Skill_SnowflakeChakrams:
			Skill_SnowflakeChakrams_Start();
			break;

		case PlayerState::Skill_ExplodingFireball:
			Skill_Fireball_Start();
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

void Player::Render(float _Delta)
{
	std::string Text = "";

	if (m_iCurHp < 0)
	{
		Text += "0";
	}

	else
	{
		Text += std::to_string(m_iCurHp);
	}

	Text += "/" + std::to_string(m_iMaxHp);

	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();



	HFONT hFont = CreateFont(28, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("Silkscreen"));
	HFONT hOldFont = (HFONT)SelectObject(dc, hFont);		// 폰트 설정
	SetTextColor(dc, RGB(255, 255, 255));					// 텍스트 색상 설정
	SetBkMode(dc, TRANSPARENT);

	TextOutA(dc, 150, 20, Text.c_str(), static_cast<int>(Text.size()));








	// 골드 보유량 표시
	std::string GoldText = std::to_string(m_iTotalGold);

	TextOutA(dc, 654, 724, GoldText.c_str(), static_cast<int>(GoldText.size()));

	//// 텍스트 출력
	SelectObject(dc, hOldFont);
	DeleteObject(hFont);






	// 게임 러닝 타임 표시 => 추후 따로 함수로 빼도 됨
	RunningTime += _Delta;

	int RunningTimeMin = static_cast<int>(RunningTime) / 60;
	int RunningTimeSec = static_cast<int>(RunningTime) % 60;

	std::string RunningTimeText = "";

	if (RunningTimeMin < 10 && RunningTimeSec < 10)
	{
		RunningTimeText += "0" + std::to_string(RunningTimeMin);
		RunningTimeText += " : 0" + std::to_string(RunningTimeSec);
	}

	else if (RunningTimeMin < 10)
	{
		RunningTimeText += "0" + std::to_string(RunningTimeMin);
		RunningTimeText += " : " + std::to_string(RunningTimeSec);
	}

	else if (RunningTimeSec < 10)
	{
		RunningTimeText += std::to_string(RunningTimeMin);
		RunningTimeText += " : 0" + std::to_string(RunningTimeSec);
	}

	else
	{
		RunningTimeText += std::to_string(RunningTimeMin);
		RunningTimeText += " : " + std::to_string(RunningTimeSec);
	}


	HFONT hFont2 = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("Lato"));
	HFONT hOldFont2 = (HFONT)SelectObject(dc, hFont2);		// 폰트 설정
	SetTextColor(dc, RGB(255, 255, 255));					// 텍스트 색상 설정
	SetBkMode(dc, TRANSPARENT);

	TextOutA(dc, 612, 80, RunningTimeText.c_str(), static_cast<int>(Text.size()));

	SelectObject(dc, hOldFont2);
	DeleteObject(hFont2);



	// 픽셀 충돌 작동 확인을 위한 디버깅용 충돌체
	//CollisionData Data;

	//Data.Pos = ActorCameraPos();
	//Data.Scale = { 5,5 };

	//// 캐릭터 중심점
	//Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

	//// 왼쪽
	//Data.Pos = ActorCameraPos() + LeftCheck;
	//Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

	//// 오른쪽
	//Data.Pos = ActorCameraPos() + RightCheck;
	//Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

	//// 위
	//Data.Pos = ActorCameraPos() + UpCheck;
	//Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());


	//// 아래
	//Data.Pos = ActorCameraPos() + DownCheck;
	//Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

}
