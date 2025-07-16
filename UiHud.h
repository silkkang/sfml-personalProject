#pragma once
#include "GameObject.h"
#include "TextGo.h"

class Zombie;

class UiHud : public GameObject
{
protected:
	sf::Font font;
	sf::Vector2f levelBarSize;

	std::string fontId;
	sf::RectangleShape expBar;
	sf::Vector2f expBarSize;
public:
	UiHud(const std::string& name = "");
	virtual ~UiHud() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void SetExpBar(float value);

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};
