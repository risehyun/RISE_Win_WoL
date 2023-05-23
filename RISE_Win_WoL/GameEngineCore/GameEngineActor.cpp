#include "GameEngineActor.h"
#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineCamera.h"
#include <GameEngineBase/GameEngineDebug.h>

GameEngineActor::GameEngineActor()
{

}

GameEngineActor::~GameEngineActor()
{
	// �� ����
	for (GameEngineRenderer* Render : AllRenderer)
	{
		delete Render;
		Render = nullptr;
	}
}

void GameEngineActor::ActorRelease()
{
	std::list<GameEngineRenderer*>::iterator ObjectStartIter = AllRenderer.begin();
	std::list<GameEngineRenderer*>::iterator ObjectEndIter = AllRenderer.end();

	for (; ObjectStartIter != ObjectEndIter; )
	{
		GameEngineRenderer* Renderer = *ObjectStartIter;
		if (false == Renderer->IsDeath())
		{
			++ObjectStartIter;
			continue;
		}


		if (nullptr == Renderer)
		{
			MsgBoxAssert("nullptr�� ���Ͱ� ������ ����Ʈ�� �� �־����ϴ�.");
			continue;
		}

		delete Renderer;
		Renderer = nullptr;

		ObjectStartIter = AllRenderer.erase(ObjectStartIter);

	}
}


GameEngineRenderer* GameEngineActor::CreateRenderer(const std::string& _ImageName, int _Order)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

//	GetLevel()->MainCamera->PushRenderer(NewRenderer, _Order);
	NewRenderer->Master = this;
	NewRenderer->Start();
	NewRenderer->SetOrder(_Order);

	// �̹����� ����Ǿ� ���� ���� �������� ������ �� �����Ƿ� üũ�� �ؼ� ������ �̹����� �ִ� ��쿡�� �ؽ�ó�� �����մϴ�.
	if (_ImageName != "")
	{
		NewRenderer->SetTexture(_ImageName);
	}

	AllRenderer.push_back(NewRenderer);

	return NewRenderer;
}

GameEngineRenderer* GameEngineActor::CreateCollision(int _Order/* = 0*/)
{
	return nullptr;
}

/*
	<�۵� ���>

	1. Actor�� �������� ������ָ�
	2. ī�޶� �� �������� ������ ������Ʈ�� �׸��ų� ����� å���� ������ �ȴ�.


	ranged for�� �׳� �����⸸ �� ��
	iterator�� �����鼭 ������ �ؾ� �� ��
	����ϴ� ���� ����.

	map�� ranged for�� �������� &�� ����� �� const�� ����ؾ� �ϱ� ������ ������ ��������.
*/