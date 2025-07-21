#pragma once
#include <functional>
#include "GameObject.h"
#include "TextGo.h"
#include "Player.h"

class Player;

class Store : public GameObject
{
protected:
	Player* player = nullptr;

	sf::Font font;
	sf::Text name;
	sf::Text explain;

	sf::Sprite background;
	sf::Sprite icon1;
	sf::Sprite icon2;
	sf::Sprite icon3;
	sf::Sprite icon4;

	sf::Text buy1;
	sf::Text buy2;
	sf::Text buy3;
	sf::Text buy4;
	sf::Text buy5;

	int price = 50;

	std::string backGroundId = "graphics/store.png";
	std::string backIcon1 = "graphics/mouseLeft.png";
	std::string backIcon2 = "graphics/mouseRight.png";
	std::string backIcon3 = "graphics/skillE.png";
	std::string backIcon4 = "graphics/skillR.png";

	bool isShow = false;
	std::function<void()> onSelected = nullptr;
	sf::FloatRect selectBox1;
	sf::FloatRect selectBox2;
	sf::FloatRect selectBox3;
	sf::FloatRect selectBox4;
public:
	Store(const std::string& name = "");
	virtual ~Store() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;


	void SetPlayer(Player* p) { player = p; }


	void Show();
	void Hide();
	void SetOnSelected(const std::function<void()>& func);
	void OnSelect();
	void SetNmae();
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

