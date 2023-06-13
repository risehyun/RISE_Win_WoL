#include "Item.h"
#include "ContentsEnum.h"
#include <vector>

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>

Item::Item()
{
}

Item::~Item()
{
}

void Item::Start()
{
	MainRenderer->SetRenderScale({ 74, 100 });

}

void Item::Update(float _Delta)
{
	


}

void Item::Render(float _Delta)
{

}
