#include "GameEngineSprite.h"
#include <GameEngineBase/GameEngineDebug.h>

GameEngineSprite::GameEngineSprite()
{
}

GameEngineSprite::~GameEngineSprite()
{
}

void GameEngineSprite::CreateSpriteSheet(GameEngineWindowTexture* _Texture, int _XCount, int _YCount)
{
	float4 TexScale = _Texture->GetScale();

	AllSprite.resize(_XCount * _YCount);

	float4 StartPos = { float4::ZERO };
	float4 ImageSize = { TexScale.X / _XCount, TexScale.Y / _YCount };


	for (size_t y = 0; y < _YCount; y++)
	{
		for (size_t x = 0; x < _XCount; x++)
		{
			size_t Index = (y * _XCount) + x;

			AllSprite[Index].BaseTexture = _Texture;
			AllSprite[Index].RenderPos.X = StartPos.X;
			AllSprite[Index].RenderPos.Y = StartPos.Y;

			AllSprite[Index].RenderScale.X = ImageSize.X;
			AllSprite[Index].RenderScale.Y = ImageSize.Y;

			StartPos.X += ImageSize.X;
		}

		StartPos.X = 0;
		StartPos.Y += ImageSize.Y;
	}


}

const GameEngineSprite::Sprite& GameEngineSprite::GetSprite(size_t _Index)
{
	static GameEngineSprite::Sprite ReturnValue;

	if (0 > _Index)
	{
		MsgBoxAssert("0���� ���� ��������Ʈ �ε��� �Դϴ�.");
		return ReturnValue;
	}

	if (AllSprite.size() <= _Index)
	{
		MsgBoxAssert("��������Ʈ �ε��� ������ �����߽��ϴ�.");
		return ReturnValue;
	}

	return AllSprite[_Index];
}