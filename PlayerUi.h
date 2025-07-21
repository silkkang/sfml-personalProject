#pragma once
#include <functional>
#include "GameObject.h"

class Player;

class PlayerUi : public GameObject
{
protected:
	sf::Sprite background;
	sf::Sprite icon1;
	sf::Sprite icon2;
	sf::Sprite icon3;
	sf::Sprite icon4;
	sf::Sprite icon5;

	std::string backGroundId = "graphics/Characteristic.png";
	std::string backIcon1 = "graphics/mouseLeft.png";
	std::string backIcon2 = "graphics/mouseRight.png";
	std::string backIcon3 = "graphics/skillE.png";
	std::string backIcon4 = "graphics/skillR.png";
	std::string backIcon5 = "graphics/rock.png";

	bool isShow = false;
	std::function<void()> onSelected = nullptr;
	sf::FloatRect selectBox1;
	sf::FloatRect selectBox2;
	sf::FloatRect selectBox3;
	sf::FloatRect selectBox4;
	sf::FloatRect selectBox5;

	int playerLevel = 1;
	Player* player = nullptr;
public:
	PlayerUi(const std::string& name = "");
	virtual ~PlayerUi() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Show();
	void Hide();
	void SetOnSelected(const std::function<void()>& func);
	void OnSelect();
	void SetPlayerLevel(int level);
	void SetPlayer(Player* p) { player = p; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

