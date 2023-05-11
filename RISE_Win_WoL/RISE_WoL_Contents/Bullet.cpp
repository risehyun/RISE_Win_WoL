﻿#include "Bullet.h"
#include <GameEngineCore/GameEngineRenderer.h>

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Start()
{
	Renderer = CreateRenderer();
}

void Bullet::Update(float _Delta)
{
	AddPos(Dir * _Delta * Speed);

	if (1.0f < GetLiveTime())
	{
		Renderer->Death();
	}

}

void Bullet::Render()
{

}