#include "GameEngineCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include "GameEngineLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>

std::string GameEngineCore::WindowTitle = "";
std::map<std::string, class GameEngineLevel*> GameEngineCore::AllLevel;
CoreProcess* GameEngineCore::Process = nullptr;
GameEngineLevel* GameEngineCore::CurLevel = nullptr;
GameEngineLevel* GameEngineCore::NextLevel = nullptr;

GameEngineCore::GameEngineCore()
{
}

GameEngineCore::~GameEngineCore()
{
}

void GameEngineCore::CoreStart(HINSTANCE _Inst)
{
	// 엔진 영역의 준비를 모두 마친 다음
	GameEngineWindow::MainWindow.Open(WindowTitle, _Inst);

	// Input 시스템을 사용하기 위해 사용 가능한 Key들을 세팅해줍니다.
	GameEngineInput::InputInit();

	// 이어서 유저 영역의 준비를 합니다.
	Process->Start();
}

void GameEngineCore::CoreUpdate()
{
	if (nullptr != NextLevel)
	{

		if (nullptr != CurLevel)
		{
			CurLevel->LevelEnd(NextLevel);
			CurLevel->ActorLevelEnd();
		}

		NextLevel->LevelStart(CurLevel);
		NextLevel->ActorLevelStart();

		CurLevel = NextLevel;
		NextLevel = nullptr;
		GameEngineTime::MainTimer.Reset();
	}


	GameEngineTime::MainTimer.Update();
	float Delta = GameEngineTime::MainTimer.GetDeltaTime();


	if (true == GameEngineWindow::IsFocus())
	{
		GameEngineInput::Update(Delta);
	}
	else
	{
		GameEngineInput::Reset();
	}

	CurLevel->AddLiveTime(Delta);

	CurLevel->Update(Delta);

	CurLevel->ActorUpdate(Delta);

	GameEngineWindow::MainWindow.ClearBackBuffer();
	CurLevel->ActorRender(Delta);

	CurLevel->Render(Delta);
	GameEngineWindow::MainWindow.DoubleBuffering();
	CurLevel->ActorRelease();

}

void GameEngineCore::CoreEnd()
{
	Process->Release();

	if (nullptr != Process)
	{
		delete Process;
		Process = nullptr;
	}

	for (std::pair<std::string, GameEngineLevel*> _Pair : AllLevel)
	{
		if (nullptr != _Pair.second)
		{
			delete _Pair.second;
			_Pair.second = nullptr;
		}
	}
}

void GameEngineCore::EngineStart(const std::string& _Title, HINSTANCE _Inst, CoreProcess* _Ptr)
{
	GameEngineDebug::LeakCheck();

	Process = _Ptr;
	WindowTitle = _Title;
	GameEngineWindow::MessageLoop(_Inst, CoreStart, CoreUpdate, CoreEnd);
}

void GameEngineCore::LevelInit(GameEngineLevel* _Level)
{
	_Level->Start();
}