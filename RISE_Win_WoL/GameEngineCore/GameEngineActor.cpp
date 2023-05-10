#include "GameEngineActor.h"
#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineCamera.h"

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
	<�۵� ���>

	1. Actor�� �������� ������ָ�
	2. ī�޶� �� �������� ������ ������Ʈ�� �׸��ų� ����� å���� ������ �ȴ�.


	ranged for�� �׳� �����⸸ �� ��
	iterator�� �����鼭 ������ �ؾ� �� ��
	����ϴ� ���� ����.

	map�� ranged for�� �������� &�� ����� �� const�� ����ؾ� �ϱ� ������ ������ ��������.
*/