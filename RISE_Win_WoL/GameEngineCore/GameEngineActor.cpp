#include "GameEngineActor.h"
#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineCamera.h"

GameEngineActor::GameEngineActor()
{
}

GameEngineActor::~GameEngineActor()
{
	// 릭 제거
	for (GameEngineRenderer* Render : AllRenderer)
	{
		delete Render;
		Render = nullptr;
	}
}

GameEngineRenderer* GameEngineActor::CreateRenderer(const std::string& _ImageName, int _Order)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	GetLevel()->MainCamera->PushRenderer(NewRenderer, _Order);
	NewRenderer->Master = this;
	NewRenderer->SetTexture(_ImageName);

	AllRenderer.push_back(NewRenderer);
	return NewRenderer;
}

/*
	<작동 방식>

	1. Actor가 렌더러를 만들어주면
	2. 카메라가 그 렌더러를 가지고 오브젝트를 그리거나 지우는 책임을 가지게 된다.


	ranged for는 그냥 돌리기만 할 때
	iterator는 돌리면서 뭔가를 해야 할 때
	사용하는 것이 좋다.

	map을 ranged for로 돌리려면 &를 사용할 때 const로 사용해야 하기 때문에 제약이 많아진다.
*/