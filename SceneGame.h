#pragma once
#include "Scene.h"
#include "TileMap.h"

class Player;
class Zombie;
class TileMap;
class UiHud;
class PlayerUi;
class Store;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr;

	std::list<Zombie*> zombieList;
	std::list<Zombie*> zombiePool;

	sf::Sprite cursor;

	bool isMapOpen = false;

	sf::View gameView;
	sf::View mapView;

	TileMap tilemap;

	sf::RenderTexture miniMapTexture;
	sf::Sprite miniMapSprite;

	sf::Sprite moneyIcon;
	sf::Sprite mouseLeft;
	sf::Sprite mouseRight;
	sf::Sprite skillE;

	sf::Sprite skillR;
	sf::Sprite rock;

	sf::Sprite Charact;


public:
	TileMap* tilemapPtr = nullptr;
	UiHud* hud = nullptr;
	PlayerUi* playerUi = nullptr;
	Store* store = nullptr;
	SceneGame();
	~SceneGame() override = default;

	const std::list<Zombie*> GetZombies() const
	{
		return zombieList;
	}
	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SpawnZombies(int count);

	void SpawnZombies3(int tileNum, int zombieCountPerTile);
};

