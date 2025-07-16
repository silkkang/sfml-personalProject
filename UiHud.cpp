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
}
void UiHud::Init()
{
	fontId ="fonts/KOMIKAP_.ttf";

	expBarSize  ={ 400.f, 0.f };
	expBar.setFillColor(sf::Color::Blue);
	expBar.setSize(expBarSize);
	expBar.setOrigin(0.5f * expBar.getSize());
	expBar.setPosition(position + sf::Vector2f(0.f, -50.f));
}

void UiHud::Release()
{
}

void UiHud::Reset()
{
}

void UiHud::Update(float dt)
{

}

void UiHud::Draw(sf::RenderWindow& window)
{

	window.draw(expBar);
}