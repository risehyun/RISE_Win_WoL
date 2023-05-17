#include "ContentCore.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "BossLevel.h"
#include "EndingLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "LabLevel.h"


ContentCore::ContentCore()
{
}

ContentCore::~ContentCore()
{
}

void ContentCore::Start()
{

	GameEngineWindow::MainWindow.SetPosAndScale({ 100, 100 }, { 1280, 800 });

	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<BossLevel>("BossLevel");
	GameEngineCore::CreateLevel<EndingLevel>("EndingLevel");




	GameEngineCore::CreateLevel<LabLevel>("LabLevel");



//	GameEngineCore::ChangeLevel("PlayLevel");
	GameEngineCore::ChangeLevel("TitleLevel");
//	GameEngineCore::ChangeLevel("LabLevel");
}

void ContentCore::Update(float _Delta)
{
}

void ContentCore::Render()
{
}

void ContentCore::Release()
{
}