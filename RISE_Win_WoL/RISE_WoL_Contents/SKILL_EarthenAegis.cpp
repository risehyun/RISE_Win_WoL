#include "SKILL_EarthenAegis.h"
#include <GameEngineCore/ResourcesManager.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"
#include "ContentsEnum.h"

void SKILL_EarthenAegis::Start()
{
	// 스킬 텍스처 로딩
	if (false == ResourcesManager::GetInst().IsLoadTexture("ARCANA_EarthenAegis_ALL.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Skill\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("ARCANA_EarthenAegis_ALL.bmp"), 12, 1);
	}

	// 렌더러 생성과 로딩된 텍스처 지정
	Renderer = CreateRenderer();
	Renderer->SetRenderScale({ 100, 100 });


	

	//// 애니메이션 생성
	// 렌더러는 계속 공전이동을 하고 각도 값이 바뀔 때 다음 각도에 해당하는 애니메이션으로 교체됨 => Switch문으로 애니메이션 이름을 추가해서 변경
	// 회전 함수 추가
	Renderer->CreateAnimation("ATTACK_EarthenAegis_Dgr360", "ARCANA_EarthenAegis_ALL.bmp", 0, 0, 0.2f, true);
	Renderer->CreateAnimation("ATTACK_EarthenAegis_Dgr30", "ARCANA_EarthenAegis_ALL.bmp", 1, 1, 0.2f, true);
	Renderer->CreateAnimation("ATTACK_EarthenAegis_Dgr60", "ARCANA_EarthenAegis_ALL.bmp", 2, 2, 0.2f, true);
	Renderer->CreateAnimation("ATTACK_EarthenAegis_Dgr90", "ARCANA_EarthenAegis_ALL.bmp", 3, 3, 0.2f, true);
	Renderer->CreateAnimation("ATTACK_EarthenAegis_Dgr120", "ARCANA_EarthenAegis_ALL.bmp", 4, 4, 0.2f, true);
	Renderer->CreateAnimation("ATTACK_EarthenAegis_Dgr150", "ARCANA_EarthenAegis_ALL.bmp", 5, 5, 0.2f, true);
	Renderer->CreateAnimation("ATTACK_EarthenAegis_Dgr180", "ARCANA_EarthenAegis_ALL.bmp", 6, 6, 0.2f, true);
	Renderer->CreateAnimation("ATTACK_EarthenAegis_Dgr210", "ARCANA_EarthenAegis_ALL.bmp", 7, 7, 0.2f, true);
	Renderer->CreateAnimation("ATTACK_EarthenAegis_Dgr240", "ARCANA_EarthenAegis_ALL.bmp", 8, 8, 0.2f, true);
	Renderer->CreateAnimation("ATTACK_EarthenAegis_Dgr270", "ARCANA_EarthenAegis_ALL.bmp", 9, 9, 0.2f, true);
	Renderer->CreateAnimation("ATTACK_EarthenAegis_Dgr300", "ARCANA_EarthenAegis_ALL.bmp", 10, 10, 0.2f, true);
	Renderer->CreateAnimation("ATTACK_EarthenAegis_Dgr330", "ARCANA_EarthenAegis_ALL.bmp", 11, 11, 0.2f, true);

	// 기본값 => 0도이자 360도
	Renderer->ChangeAnimation("ATTACK_EarthenAegis_Dgr360");

	// 충돌체 생성
	{
		BodyCollsion = CreateCollision(CollisionOrder::PlayerSkill);
		BodyCollsion->SetCollisionScale({ 100, 100 });
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
	}

	// 추후 define으로 이동
	m_iAttackPower = 25;


}

void SKILL_EarthenAegis::Update(float _Delta)
{
}
