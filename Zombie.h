#pragma once
#include "GameObject.h"
#include "HitBox.h"
#include "SceneGame.h"
class Player;
class SpriteGo;
class TileMap;

class Zombie : public GameObject
{
public:
	enum class Types
	{
		Bloater,
		Chaser,
		Crawler,
	};
	enum class ZombieState
	{
		Idle,
		Patrol,
		Chase,
		Return//µ¹¾Æ¿Í!
	};
	ZombieState state = ZombieState::Idle;
	sf::Vector2f spawnPos;
	sf::Vector2f patrolTarget;
	float patrolTimer = 0.f;
	static const int TotalTypes = 3;
	
protected:
	Types type = Types::Bloater;
	SceneGame* sceneGame = nullptr;
	sf::Sprite body;
	std::string texId;

	sf::Vector2f direction;
	float attackTimer =0.f;
	int maxHp = 0;
	float speed = 0.f;
	int damage = 0;
	float attackInterval = 0.f;

	int hp;

	Player* player = nullptr;
	SpriteGo* blood = nullptr;
	HitBox hitbox;

public:
	Zombie(const std::string& name = "");
	virtual ~Zombie() = default;

	int GetHp() const { return hp; }
	int GetMaxHp() const { return maxHp; }

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetType(Types type);

	sf::FloatRect GetLocalBounds() const override
	{
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return body.getGlobalBounds();
	}

	const HitBox& GetHitBox() const { return hitbox; }
	void OnDamage(int d);
	void OnDie();
};

