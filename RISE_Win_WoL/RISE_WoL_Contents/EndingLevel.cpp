#include "EndingLevel.h"
#include "BackGround.h"
#include <GameEngineCore/ResourcesManager.h>

EndingLevel::EndingLevel()
{
}

EndingLevel::~EndingLevel()
{
}


void EndingLevel::Start()
{
	BackGround* EndingBackGround = CreateActor<BackGround>();
//	EndingBackGround->Init("Background12.Bmp", 0.75f, { 640, 400 });
	EndingBackGround->Init("Background12.Bmp", 0.75f, { 640, 400 });
}