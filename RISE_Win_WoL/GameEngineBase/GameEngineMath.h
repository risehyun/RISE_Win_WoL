#pragma once
#include "GameEngineDebug.h"

class GameEngineMath
{
public:
	static const float PI;
	static const float PI2;

	static const float D2R;
	static const float R2D;
};

class float4
{
public:
	static const float4 ZERO;
	static const float4 LEFT;
	static const float4 RIGHT;
	static const float4 UP;
	static const float4 DOWN;

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

	inline float hX() const
	{
		return X * 0.5f;
	}
	inline float hY() const
	{
		return Y * 0.5f;
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
	inline float4 Half() const
	{
		return { hX(), hY(), Z, W };
	}

	float4 operator-() const
	{
		float4 ReturnValue = *this;

		ReturnValue.X = -ReturnValue.X;
		ReturnValue.Y = -ReturnValue.Y;
		ReturnValue.Z = -ReturnValue.Z;
		return ReturnValue;
	}

	float4 operator-(const float4& _Other) const
	{
		float4 ReturnValue;

		ReturnValue.X = X - _Other.X;
		ReturnValue.Y = Y - _Other.Y;
		ReturnValue.Z = Z - _Other.Z;

		return ReturnValue;
	}

	float4 operator+(const float4& _Other) const
	{
		float4 ReturnValue;

		ReturnValue.X = X + _Other.X;
		ReturnValue.Y = Y + _Other.Y;
		ReturnValue.Z = Z + _Other.Z;

		return ReturnValue;
	}

	float4 operator*(const float4& _Other) const
	{
		float4 ReturnValue;

		ReturnValue.X = X * _Other.X;
		ReturnValue.Y = Y * _Other.Y;
		ReturnValue.Z = Z * _Other.Z;

		return ReturnValue;
	}


	float4 operator*(const float _Value) const
	{
		float4 ReturnValue;

		ReturnValue.X = X * _Value;
		ReturnValue.Y = Y * _Value;
		ReturnValue.Z = Z * _Value;

		return ReturnValue;
	}

	float4& operator+=(const float4& _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		Z += _Other.Z;

		return *this;
	}


	float4& operator-=(const float4& _Other)
	{
		X -= _Other.X;
		Y -= _Other.Y;
		Z -= _Other.Z;

		return *this;
	}

	float4& operator*=(const float4& _Other)
	{
		X *= _Other.X;
		Y *= _Other.Y;
		Z *= _Other.Z;

		return *this;
	}

	float4& operator*=(const float _Value)
	{
		X *= _Value;
		Y *= _Value;
		Z *= _Value;

		return *this;
	}

	bool operator==(const float4 _Value) const
	{
		return X == _Value.X &&
			Y == _Value.Y &&
			Z == _Value.Z;
	}

	inline void Normalize()
	{
		float Len = Size();
		if (0.0f == Len)
		{
			return;
		}
		X /= Len;
		Y /= Len;
		Z /= Len;
	}

	inline float4 NormalizeReturn()
	{
		float4 Result = *this;
		Result.Normalize();
		return Result;
	}

	inline float Size()
	{
		float Value = X * X + Y * Y;
		Value;
		return sqrtf(Value);
	}

	float Max2D() const
	{
		return X > Y ? X : Y;
	}

public:

	inline float AngleDeg()
	{
		return AngleRad() * GameEngineMath::R2D;
	}

	inline float AngleRad()
	{
		float4 AngleVector = NormalizeReturn();

		float Angle = acosf(AngleVector.X);

		if (0 >= AngleVector.Y)
		{
			Angle = GameEngineMath::PI + GameEngineMath::PI - Angle;
		}
			return Angle;
		
	}

	static float4 GetUnitVectorFromDeg(const float _Degree)
	{
		return GetUnitVectorFromRad(_Degree * GameEngineMath::D2R);
	}

	static float4 GetUnitVectorFromRad(const float _Rad)
	{
		return { cosf(_Rad), sinf(_Rad) };
	}
};