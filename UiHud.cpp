#include "stdafx.h"
#include "UiHud.h"


UiHud::UiHud(const std::string& name)
	: GameObject(name)
{
}

void UiHud::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	
}

void UiHud::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	
}

void UiHud::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
}

void UiHud::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);

}

void UiHud::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);

}
void UiHud::SetExpBar(float value)
{
	expBar.setSize({ expBarSize.x * value, expBarSize.y });
	HpBar.setSize({ HpBarSize.x * value, HpBarSize.y });

}
void UiHud::Init()
{
	fontId ="fonts/KOMIKAP_.ttf";

	expBarSize  ={ 100.f, 5.f };
	expBar.setFillColor(sf::Color::Blue);
	expBar.setSize(expBarSize);
	expBar.setOrigin(0.5f * expBar.getSize());

	HpBarSize = { 200.f, 20.f };
	HpBar.setFillColor(sf::Color::Green);
	HpBar.setSize(HpBarSize);
	HpBar.setOrigin(0.5f * HpBar.getSize());


	LevelShape.setPointCount(4);
	LevelShape.setPoint(0, sf::Vector2f(0.f, -50.f));   
	LevelShape.setPoint(1, sf::Vector2f(50.f, 0.f));  
	LevelShape.setPoint(2, sf::Vector2f(0.f, 50.f));   
	LevelShape.setPoint(3, sf::Vector2f(-50.f, 0.f));   
	LevelShape.setFillColor(sf::Color::White);
}

void UiHud::Release()
{
}

void UiHud::Reset()
{
	SetExpBar(1.f);
}

void UiHud::Update(float dt)
{
	expBar.setPosition(position + sf::Vector2f(18.f, -75.f));
	HpBar.setPosition(position + sf::Vector2f(50.f, -62.5f));
	LevelShape.setPosition(50.f, 658.f);
}

void UiHud::Draw(sf::RenderWindow& window)
{
	window.draw(HpBar);
	window.draw(expBar);
	window.draw(LevelShape);

}