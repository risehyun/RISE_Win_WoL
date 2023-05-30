#include "UI_Button.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>

UI_Button::UI_Button()
{

}

UI_Button::~UI_Button()
{
}

void UI_Button::Start()
{
	Collision = CreateCollision(CollisionOrder::PlayerBody);
	Collision->SetCollisionScale({ 800, 800 });
	Collision->SetCollisionType(CollisionType::CirCle);
	//HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	//CollisionData Data;

	//Data.Pos = { 2800, 2800 };
	//Data.Scale = { 500,500 };

	//Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
}

void UI_Button::Update(float _Delta)
{
}