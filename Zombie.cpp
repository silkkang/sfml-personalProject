#include "stdafx.h"
#include "Zombie.h"
#include "Player.h"
#include "SpriteGo.h"
#include "Blood.h"
#include "SceneGame.h"
#include "TileMap.h"
Zombie::Zombie(const std::string& name)
	: GameObject(name)
{
}

void Zombie::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Zombie::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Zombie::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Zombie::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Zombie::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Zombie::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	SetType(type);
}

void Zombie::Release()
{
}

void Zombie::Reset()
{
	player = (Player*)SCENE_MGR.GetCurrentScene()->FindGameObject("Player");
	hitbox.SetActive(true);
	body.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::MC);
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	spawnPos = GetPosition();


	SetRotation(0.f);
	SetScale({ 1.f, 1.f });

	state = ZombieState::Patrol;
	patrolTimer = 0.f;
	patrolTarget = spawnPos;
}

void Zombie::Update(float dt)
{
	if (!GetActive())
		return;
	hitbox.UpdateTransform(body, GetLocalBounds());

	sf::Vector2f toPlayer = player->GetPosition() - GetPosition();
	float playerDist = Utils::Length(toPlayer);

	sf::Vector2f toSpawn = spawnPos - GetPosition();
	float spawnDist = Utils::Length(toSpawn);


	switch (state)
	{
	case ZombieState::Patrol:
		patrolTimer -= dt;
		if (patrolTimer <= 0.f)
		{
			patrolTarget = spawnPos + Utils::RandomInUnitCircle() * 100.f;
			patrolTimer = Utils::RandomRange(0.f, 2.f);
		}
		if (Utils::Length(patrolTarget - GetPosition()) > 5.f)
		{
			direction = Utils::GetNormal(patrolTarget - GetPosition());
			SetRotation(Utils::Angle(direction));
			
		}
		else
		{
			direction = { 0.f, 0.f };
		}
		if(playerDist <= 250.f)
			state = ZombieState::Chase;
		break;
	case ZombieState::Chase:
		if (playerDist > 250.f || spawnDist > 300.f)
		{
			state = ZombieState::Return;
			direction = { 0.f, 0.f };
		}
		else
		{
			direction = Utils::GetNormal(toPlayer);
			SetRotation(Utils::Angle(direction));
			
		}
		break;
	case ZombieState::Return:
		if (spawnDist <= 10.f)
		{
			state = ZombieState::Patrol;
			patrolTimer = 0.f;
			direction = { 0.f, 0.f };
		}
		else
		{
			direction = Utils::GetNormal(toSpawn);
			SetRotation(Utils::Angle(direction));
			
		}
		
		break;
	}

	sf::Vector2f nextPos = position;
	sf::Vector2f move = direction * speed * dt;
	//2번타일 충돌
	sf::Vector2f testPosX = nextPos + sf::Vector2f(direction.x * speed * dt, 0.f);
	if (!sceneGame->tilemapPtr->IsBlocked(testPosX))
		nextPos.x = testPosX.x;


	sf::Vector2f testPosY = nextPos + sf::Vector2f(0.f, direction.y * speed * dt);
	if (!sceneGame->tilemapPtr->IsBlocked(testPosY))
		nextPos.y = testPosY.y;

	SetPosition(nextPos);

	attackTimer += dt;
	if (attackTimer > attackInterval) {
		if (Utils::CheckCollision(hitbox.rect, player->GetHitBox().rect)) {
			player->OnDamage(damage);
			attackTimer = 0.f;
		}
	}
	hitbox.UpdateTransform(body, GetLocalBounds());
	
}

void Zombie::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitbox.Draw(window);
}

void Zombie::SetType(Types type)
{
	this->type = type;
	switch (this->type)
	{
	case Types::Bloater:
		texId = "graphics/bloater.png";
		maxHp = 200;
		speed = 50;
		damage = 10.f;
		attackInterval = 1.f;
		break;
	case Types::Chaser:
		texId = "graphics/chaser.png";
		maxHp = 100;
		speed = 100.f;
		damage = 5.f;
		attackInterval = 1.f;
		break;
	case Types::Crawler:
		texId = "graphics/crawler.png";
		maxHp = 50;
		speed = 200;
		damage = 5.f;
		attackInterval = 1.f;
		break;
	}
}
void Zombie::OnDamage(int d)
{
	hp = Utils::Clamp(hp - d, 0, maxHp);
	std::cout << "좀비의 체력 : " << hp << std::endl;
	if (hp <= 0)
	{
		OnDie();
	}


}

void Zombie::OnDie()
{
	if (player != nullptr) {
		player->AddExp(Utils::RandomRange(1.f, 10.f));
		
	}
	Blood* blood = new Blood();
	blood->SetTexture("graphics/blood.png");
	blood->SetPosition(GetPosition());
	blood->SetOrigin(Origins::MC);
	SCENE_MGR.GetCurrentScene()->AddGameObject(blood);

	SceneGame* sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

	SetActive(false);
	hitbox.SetActive(false);
}