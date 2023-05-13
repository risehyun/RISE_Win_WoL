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
	EndingBackGround->Init("Ending.Bmp");
}