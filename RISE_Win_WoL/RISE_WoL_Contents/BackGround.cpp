#include "BackGround.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>

// 싱글버퍼링을 사용하면 배경과 캐릭터를 함께 뒀을 때 깜빡임 문제가 생긴다.
// 따라서 더블버퍼링을 사용하여 캐릭터를 백업해둔 상태에서
// 지우지 않고도 작동하도록 한다.
#pragma comment(lib, "msimg32.lib")

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::Start()
{
	SetPos({ 640, 360 });
}

void BackGround::Update(float _Delta) 
{

}

void BackGround::Render()
{
	GameEngineWindowTexture* FindTexture = ResourcesManager::GetInst().FindTexture(FileName);

	if (nullptr == FindTexture)
	{
		return;
	}

	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();
	float4 Scale = FindTexture->GetScale();

	Scale *= 2.0f;
                                      
	BackBuffer->TransCopy(FindTexture, GetPos(), Scale, { 0,0 }, FindTexture->GetScale());

}

void BackGround::Release() 
{

}

void BackGround::Init(const std::string& _FileName)
{
	FileName = _FileName;

	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;

		FilePath.GetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\" + _FileName);

		GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());

		float4 Scale = Text->GetScale();

		Scale.X *= 10.0f;
		Scale.Y *= 10.0f;

		SetScale(Scale);
	}
}