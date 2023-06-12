#pragma once
#include <GameEngineCore/GameEngineActor.h>
class Item : public GameEngineActor
{
public:
	Item();
	~Item();

	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

protected:
	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineCollision* BodyCollsion = nullptr;


private:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;
};
