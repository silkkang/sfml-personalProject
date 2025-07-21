#include "stdafx.h"
#include "SceneGame.h"
#include "PlayerUi.h"
#include "Store.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "UiHud.h"


SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	texIds.push_back("graphics/player.png");
	texIds.push_back("graphics/background_sheet.png");
	texIds.push_back("graphics/bloater.png");
	texIds.push_back("graphics/crawler.png");
	texIds.push_back("graphics/chaser.png");
	texIds.push_back("graphics/crosshair.png");
	texIds.push_back("graphics/Trajectile.png");
	texIds.push_back("graphics/blood.png");
	texIds.push_back("graphics/moneyicon.png");
	texIds.push_back("graphics/mouseLeft.png");
	texIds.push_back("graphics/mouseRight.png");
	texIds.push_back("graphics/skillE.png");
	texIds.push_back("graphics/skillR.png");
	texIds.push_back("graphics/rock.png");
	texIds.push_back("graphics/Emotion.png");
	texIds.push_back("graphics/Rmotion.png");
	texIds.push_back("graphics/Characteristic.png");
	texIds.push_back("graphics/store.png");
	
	if (!tilemap.Load("map/untitled.tmx", "map/imagetile.png", 1))
		std::cout << "Failed to load tilemap!" << std::endl;
	tilemap.setPosition(0.f, 0.f);

	player = (Player*)AddGameObject(new Player("Player"));
	hud = (UiHud*)AddGameObject(new UiHud("UiHud"));


	playerUi = (PlayerUi*)AddGameObject(new PlayerUi("PlayerUi"));
	playerUi->SetActive(false);

	store = (Store*)AddGameObject(new Store("Store"));
	store->SetActive(false);
	store->SetPlayer(player);

	tilemapPtr = &tilemap;
	player->sceneGame = this;

	for (int i = 0; i < 100; ++i)
	{
		Zombie* zombie = (Zombie*)AddGameObject(new Zombie());
		zombie->SetActive(false);
		zombiePool.push_back(zombie);
	}

	Scene::Init();
	

}

void SceneGame::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);



	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	hud->SetPosition({ windowSize.x * 0.1f, windowSize.y + 10.f });
	gameView.setSize(windowSize);
	gameView.setCenter({ 0.f, 0.f });

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);


	


	Scene::Enter();

	//SpawnZombies3(3, 20);
	SpawnZombies(200);
	
	cursor.setTexture(TEXTURE_MGR.Get("graphics/crosshair.png"));
	Utils::SetOrigin(cursor, Origins::MC);

	moneyIcon.setTexture(TEXTURE_MGR.Get("graphics/moneyicon.png"));
	moneyIcon.setOrigin(moneyIcon.getLocalBounds().width * 0.5f, moneyIcon.getLocalBounds().height * 0.5f);
	moneyIcon.setPosition(300.f, 665.f);
	moneyIcon.setScale(0.15f,0.15f);

	mouseLeft.setTexture(TEXTURE_MGR.Get("graphics/mouseLeft.png"));
	mouseLeft.setOrigin(mouseLeft.getLocalBounds().width * 0.5f, mouseLeft.getLocalBounds().height * 0.5f);
	mouseLeft.setPosition({ windowSize.x * 0.425f, windowSize.y-50 });
	mouseLeft.setScale(0.5f, 0.5f);

	mouseRight.setTexture(TEXTURE_MGR.Get("graphics/mouseRight.png"));
	mouseRight.setOrigin(mouseLeft.getLocalBounds().width * 0.5f, mouseLeft.getLocalBounds().height * 0.5f);
	mouseRight.setPosition({ windowSize.x * 0.475f, windowSize.y - 50 });
	mouseRight.setScale(0.5f, 0.5f);

	skillE.setTexture(TEXTURE_MGR.Get("graphics/skillE.png"));
	skillE.setOrigin(mouseLeft.getLocalBounds().width * 0.5f, mouseLeft.getLocalBounds().height * 0.5f);
	skillE.setPosition({ windowSize.x * 0.525f, windowSize.y - 50 });
	skillE.setScale(0.5f, 0.5f);
	
	skillR.setTexture(TEXTURE_MGR.Get("graphics/skillR.png"));
	skillR.setOrigin(mouseLeft.getLocalBounds().width * 0.5f, mouseLeft.getLocalBounds().height * 0.5f);
	skillR.setPosition({ windowSize.x * 0.575f, windowSize.y - 50 });
	skillR.setScale(0.5f, 0.5f);

	rock.setTexture(TEXTURE_MGR.Get("graphics/rock.png"));
	rock.setOrigin(mouseLeft.getLocalBounds().width * 0.5f, mouseLeft.getLocalBounds().height * 0.5f);
	rock.setPosition({ windowSize.x * 0.575f, windowSize.y - 50 });
	rock.setScale(0.5f, 0.5f);


}

void SceneGame::Exit()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);

	for (Zombie* zombie : zombieList)
	{
		zombie->SetActive(false);
		zombiePool.push_back(zombie);
	}
	zombieList.clear();

	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	cursor.setPosition(ScreenToUi(InputMgr::GetMousePosition()));
	

	Scene::Update(dt);

	gameView.setCenter(player->GetPosition());
	worldView = gameView;

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SpawnZombies(100);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	window.setView(gameView);
	tilemap.Draw(window);

	Scene::Draw(window);

	window.setView(uiView);
	
	hud->Draw(window);
	window.draw(moneyIcon);
	window.draw(mouseLeft);
	window.draw(mouseRight);
	window.draw(skillE);
	if (player->GetLevel() > 5)
	{
		window.draw(skillR);
	}
	if (player->GetLevel() <= 5)
	{
		window.draw(rock);
	}
	if (playerUi->GetActive())
		playerUi->Draw(window);
	if (store->GetActive())
		store->Draw(window);
	window.draw(cursor);
}

void SceneGame::SpawnZombies(int count)
{

	for (int i = 0; i < count; ++i)
	{
		Zombie* zombie = nullptr;
		if (zombiePool.empty())
		{
			zombie = (Zombie*)AddGameObject(new Zombie());
			zombie->Init();
		}
		else
		{
			zombie = zombiePool.front();
			zombiePool.pop_front();
			zombie->SetActive(true);
		}

		zombie->SetType((Zombie::Types)Utils::RandomRange(0, Zombie::TotalTypes));
		sf::Vector2f spawnPos;
		int spawnTile = 0;

		do
		{
			spawnPos = 
			{
				Utils::RandomRange(0.f, 3840.f),
				Utils::RandomRange(0.f, 6400.f)
			};
			spawnTile = tilemapPtr->IsSpawn(spawnPos);

		} while (spawnTile == 5 || spawnTile == 2);
		zombie->SetPosition(spawnPos);
		zombie->Reset();



		zombieList.push_back(zombie);
	}
}

void SceneGame::SpawnZombies3(int tileNum, int zombieCountPerTile)
{
	for (int y = 0; y < tilemapPtr->GetMapHeight(); ++y)
	{
		for (int x = 0; x < tilemapPtr->GetMapWidth(); ++x)
		{
			if (tilemapPtr->GetTileData(y, x) == tileNum)
			{
				sf::Vector2f tileCenter = {
					x * tilemapPtr->GetTileWidth() + tilemapPtr->GetTileWidth() * 0.5f,
					y * tilemapPtr->GetTileHeight() + tilemapPtr->GetTileHeight() * 0.5f
				};
	
				for (int i = 0; i < zombieCountPerTile; ++i)
				{
					sf::Vector2f offset = Utils::RandomInsideCircle(300.f);
					sf::Vector2f spawnPos = tileCenter + offset;

					Zombie* zombie = nullptr;
					if (zombiePool.empty())
					{
						zombie = (Zombie*)AddGameObject(new Zombie());
						zombie->Init();
					}
					else
					{
						zombie = zombiePool.front();
						zombiePool.pop_front();
						zombie->SetActive(true);
					}

					zombie->SetType((Zombie::Types)Utils::RandomRange(0, Zombie::TotalTypes));
					zombie->SetPosition(spawnPos);
					zombie->Reset();

					zombieList.push_back(zombie);
					
				}
			}
		}
	}
}
