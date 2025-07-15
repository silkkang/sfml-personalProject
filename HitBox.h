#pragma once
class HitBox
{
protected:
	bool active = true;

public:
	HitBox();

	void SetActive(bool a) { active = a; }
	bool GetActive() const { return active; }
	sf::RectangleShape rect;

	void UpdateTransform(const sf::Transformable& tr, const sf::FloatRect& localBounds);
	void Draw(sf::RenderWindow& window);
};

