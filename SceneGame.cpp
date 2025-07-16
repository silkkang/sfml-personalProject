#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"


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
	


	if (!tilemap.Load("map/untitled.tmx", "map/imagetile.png", 1))
		std::cout << "Failed to load tilemap!" << std::endl;
	tilemap.setPosition(0.f, 0.f);

	player = (Player*)AddGameObject(new Player("Player"));

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

	gameView.setSize(windowSize);
	gameView.setCenter({0.f, 0.f});

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	
	player->SetPosition({ 0.f,0.f });
	std::cout << "Player Pos = " << player->GetPosition().x << ", " << player->GetPosition().y << std::endl;
	Scene::Enter();
	SpawnZombies(200);
	cursor.setTexture(TEXTURE_MGR.Get("graphics/crosshair.png"));
	Utils::SetOrigin(cursor, Origins::MC);
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
	window.draw(cursor);
}

void SceneGame::SpawnZombies(int count)
{

	for (int i = 0; i < count; ++i)//
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
			spawnPos = {
				Utils::RandomRange(0.f, 3840.f),
				Utils::RandomRange(0.f, 6400.f)
			};
			spawnTile = tilemapPtr->IsSpawn(spawnPos);

		} while (spawnTile == 5|| spawnTile ==2);
		zombie->SetPosition(spawnPos);
		zombie->Reset();
		
		zombieList.push_back(zombie);
	}
}
