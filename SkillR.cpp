#include "stdafx.h"
#include "SkillR.h"
#include "SceneGame.h"
#include "Zombie.h"
SkillR::SkillR(const std::string& name)
	: GameObject(name)
{
}

void SkillR::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void SkillR::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void SkillR::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void SkillR::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void SkillR::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void SkillR::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = 1;
}

void SkillR::Release()
{
}

void SkillR::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

	body.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::MC);
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);
	SetScale({ 2.f, 2.f });

	dir = { 0.f, 0.f };
	speed = 0.f;
	RemoveBulletTime = 0.f;
	damageTimer = 0.f;
	damage = 0;

}

void SkillR::Update(float dt)
{
	RemoveBulletTime += dt;
	if (RemoveBulletTime >= duration)
	{
		SetActive(false);
		RemoveBulletTime = 0.f;
	}
	
	damageTimer += dt;
	if (damageTimer >= 0.5f)
	{
		damageTimer = 0.f;
		hitBox.UpdateTransform(body, GetLocalBounds());

		const std::list<Zombie*>& list = sceneGame->GetZombies();
		for (auto zombie : list) {
			if (!zombie->GetActive() || !zombie->GetHitBox().GetActive())
				continue;
			if (Utils::CheckCollision(hitBox.rect, zombie->GetHitBox().rect)) {

				zombie->OnDamage(damage);
			}
		}
	}

}

void SkillR::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

void SkillR::Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float s, int d)
{
	SetPosition(pos);
	
	speed = 0.f;
	damage = d;

	SetRotation(0.f);

}