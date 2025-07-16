#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"
#include "Bullet.h"

Player::Player(const std::string& name)
	: GameObject(name)
{

}

void Player::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Player::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Player::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Player::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Player::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Player::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	//SetOrigin(Origins::MC);
}

void Player::Release()
{
}

void Player::Reset()
{
	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game)
	{
		sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
	}
	else
	{
		sceneGame = nullptr;
	}

	for (Bullet* bullet : bulletList)
	{
		bullet->SetActive(false);
		bulletPool.push_back(bullet);
	}
	bulletList.clear();


	body.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::MC);
	SetPosition({ 1920.f, 3200.f });
	SetRotation(0.f);

	direction = { 0.f, 0.f };
	look = { 1.0f, 0.f };
	maxHp = 200;
	hp = maxHp;
	level = 1;
	exp = 0.f;
	nextExp = 100.f;
	speed = 300.f;
}

void Player::Update(float dt)
{
	auto it = bulletList.begin();
	while (it != bulletList.end())
	{
		if (!(*it)->GetActive())
		{
			bulletPool.push_back(*it);
			it = bulletList.erase(it);
		}
		else
		{
			++it;
		}
	}

	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Normalize(direction);
	}

	sf::Vector2f nextPos = position;

	//2번타일 충돌
	sf::Vector2f testPosX = nextPos + sf::Vector2f(direction.x * speed * dt, 0.f);
	if (!sceneGame->tilemapPtr->IsBlocked(testPosX))
		nextPos.x = testPosX.x;


	sf::Vector2f testPosY = nextPos + sf::Vector2f(0.f, direction.y * speed * dt);
	if (!sceneGame->tilemapPtr->IsBlocked(testPosY))
		nextPos.y = testPosY.y;

	SetPosition(nextPos);
	

	sf::Vector2i mousePos = InputMgr::GetMousePosition();
	sf::Vector2f mouseWorldPos = sceneGame->ScreenToWorld(mousePos);
	look = Utils::GetNormal(mouseWorldPos - GetPosition());
	SetRotation(Utils::Angle(look));

	hitBox.UpdateTransform(body, GetLocalBounds());

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		Shoot();
	}

	if (exp > nextExp) {
		level++;
		exp -= nextExp;
		nextExp = 100 * pow(1.15, level - 1);
		
	}
	showPer = (exp / nextExp) * 100.f;


	
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

void Player::Shoot()
{
	Bullet* bullet = nullptr;
	std::cout << "플레이어의 레벨 : " << level << std::endl;
	std::cout << "플레이어의 경험치 : " << exp << " / " << nextExp << std::endl;
	std::cout << "플레이어의 경험치 퍼센트 : " << showPer << std::endl;
	std::cout << level << " " << exp << std::endl;
	if (bulletPool.empty())
	{
		bullet = new Bullet();
		bullet->Init();
	}
	else
	{
		bullet = bulletPool.front();
		bulletPool.pop_front();
		bullet->SetActive(true);
	}

	bullet->Reset();
	bullet->Fire(position + look * 10.f, look, 1000.f, 10);

	bulletList.push_back(bullet);
	sceneGame->AddGameObject(bullet);
}

void Player::OnDamage(int d) {
	if (!isAlive()) return;

	hp = Utils::Clamp(hp - d, 0, maxHp);
	std::cout << "플레이어의 체력 : " << hp << std::endl;
	if (!isAlive()) {
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
}