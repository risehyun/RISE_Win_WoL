#include "UI_Dialog.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

UI_Dialog::UI_Dialog()
{
}

UI_Dialog::~UI_Dialog()
{
}

void UI_Dialog::Start()
{



	static UI_Dialog* MainDialog;


	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");

	GameEnginePath FolderPath = FilePath;

	FilePath.MoveChild("ContentsResources\\Texture\\UI");

	if (false == ResourcesManager::GetInst().IsLoadTexture("NPC_OUTFIT_INDEX0.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("NPC_OUTFIT_INDEX0.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("NPC_OUTFIT_INDEX1.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("NPC_OUTFIT_INDEX1.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("NPC_OUTFIT_INDEX2.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("NPC_OUTFIT_INDEX2.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("NPC_OUTFIT_INDEX3.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("NPC_OUTFIT_INDEX3.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("NPC_COLLECTOR_INDEX.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("NPC_COLLECTOR_INDEX.bmp"));
	}
	
	MainRenderer = CreateUIRenderer();
	MainRenderer->SetRenderScale({ 1160, 200 });
	MainRenderer->SetTexture("NPC_OUTFIT_INDEX0.bmp");
	MainRenderer->Off();
}

void UI_Dialog::Update(float _Delta)
{
}
