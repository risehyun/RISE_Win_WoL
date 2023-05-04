#pragma once


class GameEngineMath
{


};

class float4
{
public:
	float X;
	float Y;
	float Z;
	float W;

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
