#include "Background_Stage1.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

Background_Stage1::Background_Stage1()
{
}

Background_Stage1::~Background_Stage1()
{
}

void Background_Stage1::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("stage_sort.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		GameEnginePath FolderPath = FilePath;
		FilePath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("stage_sort.bmp"));
	}

	MainRenderer = CreateRenderer();
	MainRenderer->SetTexture("stage_sort.bmp");
	MainRenderer->SetRenderScale({4500, 3600});
	MainRenderer->SetRenderPos({ 4500/2, 3600/2 });
	MainRenderer->SetOrder(10);

	
}

void Background_Stage1::Update(float _Delta)
{
}
