#include "BackGround.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>

// �̱۹��۸��� ����ϸ� ���� ĳ���͸� �Բ� ���� �� ������ ������ �����.
// ���� ������۸��� ����Ͽ� ĳ���͸� ����ص� ���¿���
// ������ �ʰ� �۵��ϵ��� �Ѵ�.
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