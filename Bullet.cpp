#include "stdafx.h"
#include "Bullet.h"
#include "SceneGame.h"
#include "Zombie.h"

Bullet::Bullet(const std::string& name)
	: GameObject(name)
{
}

void Bullet::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Bullet::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Bullet::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Bullet::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Bullet::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Bullet::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

void Bullet::Release()
{
}

void Bullet::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

	body.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::ML);

	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);
	SetScale({ 1.f, 1.f });

	dir = { 0.f, 0.f };
	speed = 0.f;
	RemoveBulletTime = 0.f;
	damage = 0;
}

void Bullet::Update(float dt)
{
	RemoveBulletTime += dt;
	if (RemoveBulletTime >= 2.f) {
		SetActive(false);
		RemoveBulletTime = 0.f;
	}
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Normalize(direction);
	}
	sf::Vector2f nextPos = position;

	sf::Vector2f testPosX = nextPos + sf::Vector2f(direction.x * speed * dt, 0.f);
	if (!sceneGame->tilemapPtr->IsBlocked(testPosX))
	{
		nextPos.x = testPosX.x;
	}
	else
	{
		speed = 0;
	}
	sf::Vector2f testPosY = nextPos + sf::Vector2f(0.f, direction.y * speed * dt);
	if (!sceneGame->tilemapPtr->IsBlocked(testPosY))
	{
		nextPos.y = testPosY.y;

	}
	else
	{
		speed = 0;
	}

	SetPosition(position + dir * speed * dt);
	hitBox.UpdateTransform(body, GetLocalBounds());


	const std::list<Zombie*>& list = sceneGame->GetZombies();
	for (auto zombie : list) {
		if (!zombie->GetActive() || !zombie->GetHitBox().GetActive())
			continue;
		if (Utils::CheckCollision(hitBox.rect, zombie->GetHitBox().rect)) {
			//zombie->SetActive(false);
			SetActive(false);
			zombie->OnDamage(damage);

			break;
		}
	}
}

void Bullet::Draw(sf::RenderWindow& window)
{
	if (speed > 0)
	{
		window.draw(body);
		hitBox.Draw(window);
	}

}

void Bullet::Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float s, int d)
{
	SetPosition(pos);
	this->dir = dir;
	speed = s;
	damage = d;

	SetRotation(Utils::Angle(this->dir));
}