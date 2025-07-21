#pragma once
#include "GameObject.h"
#include "hitBox.h"

class SceneGame;
class SkillR :public GameObject
{
protected:
	sf::Sprite body;
	std::string texId = "graphics/Rmotion.png";

	sf::Vector2f dir;
	float speed = 0.f;
	int damage = 0;
	float duration = 5.f;

	float RemoveBulletTime = 0.f;
	float damageTimer = 0.f;

	bool isRemove = false;
	sf::Vector2f direction;
	HitBox hitBox;

	SceneGame* sceneGame;
public:
	SkillR(const std::string& name = "");
	virtual ~SkillR() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void SetDuration(float d) { duration = d; }

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

	void Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float s, int d);
};

