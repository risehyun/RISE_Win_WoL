#include "UI_DamageText.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "ContentsEnum.h"

UI_DamageText::UI_DamageText()
{
}

UI_DamageText::~UI_DamageText()
{
}

void UI_DamageText::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);
	MainRenderer->SetRenderScale({ 200, 200 });

	RandomPos = GameEngineRandom::MainRandom.RandomFloat(0.1f, 0.5f);
}

void UI_DamageText::Update(float _Delta)
{
	fDamageRendererDuration -= _Delta;
	float4 Pos = Dir * _Delta * fDamageRenderSpeed;

	Pos.Y -= RandomPos;

	AddPos(Pos);

	if (fDamageRendererDuration <= 0)
	{
		Death();
	}


}