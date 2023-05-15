#include "BackGround.h"
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>

#pragma comment(lib, "msimg32.lib")

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::Start()
{
}

void BackGround::Update(float _Delta) 
{

}

// ���� ��ü������ Render�� �ϴ� ���� �ƴ϶� Actor���� ������ �������� ī�޶󿡼� ����ϴ� ������ ������ �ٲ�� ������ �Ʒ��� �ּ�ó���Ͽ���.
// ������ ������ ������ �ؽ�Ʈ ���� ȭ�鿡 ����� ���� ����ϰ� �� �ܿ� �̹������� ��� ����� ������θ� ����Ѵ�.
void BackGround::Render()
{


}

void BackGround::Release() 
{

}

void BackGround::Init(const std::string& _FileName, const float _Scale, const float4 &_Pos)
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


		Scale.X *= _Scale;
		Scale.Y *= _Scale;


		float4 WinScale = GameEngineWindow::MainWindow.GetScale();

		GameEngineRenderer* Render = CreateRenderer(_FileName, RenderOrder::BackGround);
		Render->SetRenderScale(Scale);


		SetPos(_Pos);
	}
}