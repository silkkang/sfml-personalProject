#include "stdafx.h"
#include "UiHud.h"
#include "TextGo.h"

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
void UiHud::SetExpBar(float showPer)
{
	expBar.setSize({ expBarSize.x * showPer, expBarSize.y });
	expBarBack.setSize({ expBarSize.x, expBarSize.y });
}
void UiHud::SetHpBar(float hp)
{
	HpBar.setSize({ HpBarSize.x * hp, HpBarSize.y });
	HpBarBack.setSize({ HpBarSize.x , HpBarSize.y });
}
void UiHud::SetLevel(int level)
{
	Level.setString(std::to_string(level));
}
void UiHud::SetExp(int exp, int nextExp)
{
	std::ostringstream a;
	a << exp << "/" << nextExp;
	Exp.setString(a.str());
}
void UiHud::SetMoney(int money)
{
	Money.setString(std::to_string(money));
}
void UiHud::Init()
{

	font.loadFromFile("fonts/KOMIKAP_.ttf");
	expBarSize = { 100.f, 5.f };
	expBar.setFillColor(sf::Color::Blue);
	expBar.setSize(expBarSize);
	expBar.setOrigin(0.5f * expBar.getSize());

	expBarBack.setFillColor(sf::Color::Transparent);
	expBarBack.setOutlineColor(sf::Color::Black);
	expBarBack.setOutlineThickness(1.f);
	expBarBack.setSize(expBarSize);
	expBarBack.setOrigin(0.5f * expBar.getSize());

	HpBarSize = { 200.f, 20.f };
	HpBar.setFillColor(sf::Color::Green);
	HpBar.setSize(HpBarSize);
	HpBar.setOrigin(0.5f * HpBar.getSize());

	HpBarBack.setFillColor(sf::Color::Transparent);
	HpBarBack.setOutlineColor(sf::Color::Green);
	HpBarBack.setOutlineThickness(2.f);
	HpBarBack.setSize(HpBarSize);
	HpBarBack.setOrigin(0.5f * HpBar.getSize());

	LevelShape.setPointCount(4);
	LevelShape.setPoint(0, sf::Vector2f(0.f, -50.f));
	LevelShape.setPoint(1, sf::Vector2f(50.f, 0.f));
	LevelShape.setPoint(2, sf::Vector2f(0.f, 50.f));
	LevelShape.setPoint(3, sf::Vector2f(-50.f, 0.f));
	LevelShape.setFillColor(sf::Color::White);

	Level.setFont(font);
	Level.setCharacterSize(40);
	Level.setFillColor(sf::Color::Black);
	Level.setOrigin(0.5f * sf::Vector2f(Level.getLocalBounds().width, Level.getLocalBounds().height));

	Exp.setFont(font);
	Exp.setCharacterSize(12);
	Exp.setFillColor(sf::Color::White);
	Exp.setOrigin(0.5f * sf::Vector2f(Exp.getLocalBounds().width, Exp.getLocalBounds().height));
	
	Money.setFont(font);
	Money.setCharacterSize(10);
	Money.setFillColor(sf::Color::Yellow);
	Money.setOrigin(0.5f * sf::Vector2f(Level.getLocalBounds().width, Level.getLocalBounds().height));


	

}

void UiHud::Release()
{
}

void UiHud::Reset()
{
	SetExpBar(1.f);
	expBar.setSize({ 0.f,0.f });
	HpBarBack.setSize(HpBarSize);
	expBarBack.setSize(expBarSize);
}

void UiHud::Update(float dt)
{
	expBar.setPosition(position + sf::Vector2f(18.f, -75.f));
	expBarBack.setPosition(position + sf::Vector2f(18.f, -75.f));
	HpBar.setPosition(position + sf::Vector2f(50.f, -62.5f));
	HpBarBack.setPosition(position + sf::Vector2f(50.f, -62.5f));
	LevelShape.setPosition(50.f, 658.f);
	Level.setPosition(45.f, 650.f);
	Exp.setPosition(60.f, 600.f);
	Money.setPosition(300.f, 635.f);
	
}

void UiHud::Draw(sf::RenderWindow& window)
{
	window.draw(expBarBack);
	window.draw(expBar);
	window.draw(HpBarBack);
	window.draw(HpBar);
	window.draw(LevelShape);
	window.draw(Level);
	window.draw(Exp);
	window.draw(Money);
	

}