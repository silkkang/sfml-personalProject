#pragma once
#include "GameObject.h"
#include "TextGo.h"

class Zombie;

class UiHud : public GameObject
{
protected:
	sf::Font font;
	sf::Text Level;
	sf::Text Exp;
	sf::Text Money;
	float timer = 300;

	std::string fontId;
	sf::RectangleShape expBar;
	sf::RectangleShape expBarBack;
	sf::Vector2f expBarSize;

	sf::RectangleShape HpBar;
	sf::RectangleShape HpBarBack;
	sf::Vector2f HpBarSize;

	sf::RectangleShape TimeBar;
	sf::RectangleShape TimeBarBack;
	sf::Vector2f TimeBarSize;


	sf::ConvexShape LevelShape;

public:
	UiHud(const std::string& name = "");
	virtual ~UiHud() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void SetExpBar(float showPer);
	void SetHpBar(float hp);
	void SetLevel(int level);
	void SetExp(int exp,int nextExp);
	void SetMoney(int money);


	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};
