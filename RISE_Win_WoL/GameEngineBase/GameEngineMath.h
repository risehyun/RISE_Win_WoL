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

	// 실수인 X를 int로 형변환 한 값을 리턴해주는 함수
	inline int iX() const
	{
		return static_cast<int>(X);
	}

	// 실수인 Y를 int로 형변한 한 값을 리턴해주는 함수
	inline int iY() const
	{
		return static_cast<int>(Y);
	}

	// 실수인 X값의 절반 값을 int로 형변환 한 값을 리턴해주는 함수
	inline int ihX() const
	{
		return static_cast<int>(X * 0.5f);
	}

	// 실수인 Y값의 절반 값을 int로 형변환 한 값을 리턴해주는 함수
	inline int ihY() const
	{
		return static_cast<int>(Y * 0.5f);
	}


	// 각 좌표 값에 인자로 전달받은 값을 덧셈대입해주는 연산자 
	float4& operator+=(const float4& _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		Z += _Other.Z;

		return *this;
	}

};
