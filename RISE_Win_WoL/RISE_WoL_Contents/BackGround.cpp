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

// 이제 자체적으로 Render를 하는 것이 아니라 Actor에서 생성한 렌더러를 카메라에서 출력하는 것으로 구조를 바꿨기 때문에 아래는 주석처리하였다.
// 이쪽은 앞으로 간단한 텍스트 등을 화면에 출력할 때만 사용하고 그 외에 이미지들은 모두 상술한 방식으로만 출력한다.
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