#pragma once


class GameEngineMath
{

};

class float4
{
public:
	static const float4 ZERO;

	float X = 0.0f;
	float Y = 0.0f;
	float Z = 0.0f;
	float W = 0.0f;

	// �Ǽ��� X�� int�� ����ȯ �� ���� �������ִ� �Լ�
	inline int iX() const
	{
		return static_cast<int>(X);
	}

	// �Ǽ��� Y�� int�� ������ �� ���� �������ִ� �Լ�
	inline int iY() const
	{
		return static_cast<int>(Y);
	}

	// �Ǽ��� X���� ���� ���� int�� ����ȯ �� ���� �������ִ� �Լ�
	inline int ihX() const
	{
		return static_cast<int>(X * 0.5f);
	}

	// �Ǽ��� Y���� ���� ���� int�� ����ȯ �� ���� �������ִ� �Լ�
	inline int ihY() const
	{
		return static_cast<int>(Y * 0.5f);
	}


	// �� ��ǥ ���� ���ڷ� ���޹��� ���� �����������ִ� ������ 
	float4& operator+=(const float4& _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		Z += _Other.Z;

		return *this;
	}

};
