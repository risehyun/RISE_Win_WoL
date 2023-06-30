#pragma once

enum class UpdateOrder
{
	Player,
	Monster,
};

enum class RenderOrder
{
	BackGround,
	Play,
	PlayUI,
};

enum class CollisionOrder
{
	Map,
	Potal,
	PlayerBody,
	PlayerSkill,
	MonsterBody,
	MonsterSkill,
	MonsterAttackRange,
	Item,
};
