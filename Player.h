#pragma once
#include "GameObject.h"
#include "HitBox.h"

class SceneGame;
class Bullet;
class SkillE;
class SkillR;
class TileMap;

class Player : public GameObject
{
protected:
	sf::Sprite body;
	std::string texId = "graphics/player.png";

	sf::Vector2f direction;
	sf::Vector2f look;

	float speed = 300.f;


	HitBox hitBox;

	std::list<Bullet*> bulletList;
	std::list<Bullet*> bulletPool;

	std::list<SkillE*> skillEList;
	std::list<SkillE*> skillEPool;

	std::list<SkillR*> skillRList;
	std::list<SkillR*> skillRPool;

	int hp = 0;
	int maxHp = 100;

	int level = 1;
	float exp = 0.f;
	float money = 0.f;
	float nextExp = 100.f;

	float showPer = 0.f;

	float skillRight = 0.f;
	bool isSkillRight = false;
	int skillRightCount = 0;

	float skillLeft = 2.f;
	float skillLeftTimer = 0.f;
	bool isSkillLeft = false;
	int skillRightadd = 5;

	float skillE = 0.f;
	bool isSkillE = false;
	float skillETimer = 0.f;


	float skillR = 0.f;
	bool isSkillR = false;
	float skillRDuration = 5.f;

	bool isLevelUp = false;
	sf::Vector2f pos;//position
	sf::Vector2f dir;//direction
	float s;//speed
	int d;//damage
public:
	SceneGame* sceneGame = nullptr;

	float getPer() const { return showPer; }
	bool isAlive() const { return hp > 0; }
	Player(const std::string& name = "");
	~Player() override = default;



	void AddExp(float f) { exp += f; }
	void AddMoney(float f);
	int GetLevel();
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

	sf::FloatRect GetLocalBounds() const override
	{
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return body.getGlobalBounds();
	}
	void DecreaseSkillLeft(float amount) { skillLeftTimer -= amount; }
	void IncreaseSkillRIght(int amount) { skillRightadd += amount; }
	void DecreaseSkillE(float amount) { skillETimer -= amount; }
	void IncreaseSkillRDuration(float d) { skillRDuration += d; }

	const HitBox& GetHitBox() const { return hitBox; }
	void Shoot();
	void SkillEUse();
	void SkillRUse();
	void OnDamage(int d);

	float GetMoney() {return money;}
};

