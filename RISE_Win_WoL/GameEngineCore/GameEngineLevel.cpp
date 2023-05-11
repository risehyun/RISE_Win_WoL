#include "GameEngineLevel.h"
#include "GameEngineCamera.h"
#include <GameEngineBase/GameEngineDebug.h>

/*
	관리하는 클래스에서만 어떤 객체를 작동할 수 있도록 하기 위해서
	렌더러라는 것이 따로 존재하고, 이것을 그냥 private로 만들어서 아무도 접근하지 못하게 만든 다음
	friend로 선언된 클래스에서만 마음대로 가져다 쓸 수 있게 만들었다.
*/

GameEngineLevel::GameEngineLevel()
{
	MainCamera = new GameEngineCamera();
	UICamera = new GameEngineCamera();
}

GameEngineLevel::~GameEngineLevel()
{
	if (nullptr != MainCamera)
	{
		delete MainCamera;
		MainCamera = nullptr;
	}

	if (nullptr != UICamera)
	{
		delete UICamera;
		UICamera = nullptr;
	}

	for (const std::pair<int, std::list<GameEngineActor*>>& _Pair : AllActors)
	{
		const std::list<GameEngineActor*>& Group = _Pair.second;

		for (GameEngineActor* _Actor : Group)
		{
			if (nullptr != _Actor)
			{
				delete _Actor;
				_Actor = nullptr;
			}
		}
	}
}

void GameEngineLevel::ActorInit(GameEngineActor* _Actor, int _Order)
{
	_Actor->Level = this;
	_Actor->SetOrder(_Order);
	_Actor->Start();
}

void GameEngineLevel::ActorUpdate(float _Delta)
{
	for (const std::pair<int, std::list<GameEngineActor*>>& _Pair : AllActors)
	{
		const std::list<GameEngineActor*>& Group = _Pair.second;

		for (GameEngineActor* _Actor : Group)
		{
			if (false == _Actor->IsUpdate())
			{
				continue;
			}

			_Actor->AddLiveTime(_Delta);
			_Actor->Update(_Delta);
		}
	}
}

void GameEngineLevel::ActorRender()
{
	MainCamera->Render();

	for (const std::pair<int, std::list<GameEngineActor*>>& _Pair : AllActors)
	{
		const std::list<GameEngineActor*>& Group = _Pair.second;

		for (GameEngineActor* _Actor : Group)
		{
			if (false == _Actor->IsUpdate())
			{
				continue;
			}

			_Actor->Render();
		}
	}
}

// ranged for 사용시 내부에서 구조가 변하면 안되기 때문에 Release에서는 ranged for를 쓸 수가 없다
void GameEngineLevel::ActorRelease()
{
	MainCamera->Release();

	std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = AllActors.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = AllActors.end();

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<GameEngineActor*>& Group = GroupStartIter->second;

		std::list<GameEngineActor*>::iterator ObjectStartIter = Group.begin();
		std::list<GameEngineActor*>::iterator ObjectEndIter = Group.end();

		for (; ObjectStartIter != ObjectEndIter; )
		{
			GameEngineActor* Actor = *ObjectStartIter;
			if (false == Actor->IsDeath())
			{
				++ObjectStartIter;
				continue;
			}

			if (nullptr == Actor)
			{
				MsgBoxAssert("nullptr인 액터가 레벨의 리스트에 들어가 있었습니다.");
				continue;
			}

			delete Actor;
			Actor = nullptr;

			ObjectStartIter = Group.erase(ObjectStartIter);

		}
	}

}