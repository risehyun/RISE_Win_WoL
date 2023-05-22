#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <string>

class BackGround : public GameEngineActor
{
public:
	BackGround();
	~BackGround();

	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(BackGround&& _Other) noexcept = delete;

	void Init(const std::string& _FileName, const float _Scale, const float4& _Pos);
	void Init(const std::string& _FileName, const std::string& _DebugFileName);
//	void Init(const std::string& _FileName, const std::string& _DebugFileName, const float _Scale, const float4& _Pos);
	void SwitchRender();

protected:

private:
	bool SwitchRenderValue = true;

	std::string FileName;

	class GameEngineRenderer* Renderer;
	class GameEngineRenderer* DebugRenderer;

	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;

};