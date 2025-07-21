#include "stdafx.h"
#include "Store.h"
Store::Store(const std::string& name)
	: GameObject(name)
{
}

void Store::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	background.setPosition(pos);
	icon1.setPosition(pos);
	icon2.setPosition(pos);
	icon3.setPosition(pos);
	icon4.setPosition(pos);

	selectBox1 = background.getGlobalBounds();
	selectBox2 = background.getGlobalBounds();
	selectBox3 = background.getGlobalBounds();
	selectBox4 = background.getGlobalBounds();
}

void Store::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	background.setRotation(rot);
	icon1.setRotation(rot);
	icon2.setRotation(rot);
	icon3.setRotation(rot);
	icon4.setRotation(rot);
}

void Store::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	background.setScale(s);
	icon1.setScale(s);
	icon2.setScale(s);
	icon3.setScale(s);
	icon4.setScale(s);

	selectBox1 = background.getGlobalBounds();
	selectBox2 = background.getGlobalBounds();
	selectBox3 = background.getGlobalBounds();
	selectBox4 = background.getGlobalBounds();
}

void Store::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	background.setOrigin(o);
	icon1.setOrigin(o);
	icon2.setOrigin(o);
	icon3.setOrigin(o);
	icon4.setOrigin(o);
}

void Store::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(background, preset);
		Utils::SetOrigin(icon1, preset);
		Utils::SetOrigin(icon2, preset);
		Utils::SetOrigin(icon3, preset);
		Utils::SetOrigin(icon4, preset);

	}
}
void Store::Show()
{
	isShow = true;
	SetActive(true);

}

void Store::Hide()
{
	isShow = false;
	SetActive(false);

}
void Store::SetOnSelected(const std::function<void()>& func)
{
	onSelected = func;
}

void Store::OnSelect()
{
	if (onSelected)
	{
		onSelected();
	}
}



void Store::Init()
{

	buy1.setFont(font);
	buy1.setCharacterSize(30);
	buy1.setFillColor(sf::Color::Yellow);
	buy1.setOrigin(0.5f * sf::Vector2f(icon1.getLocalBounds().width, icon1.getLocalBounds().height));

	buy2.setFont(font);
	buy2.setCharacterSize(30);
	buy2.setFillColor(sf::Color::Yellow);
	buy2.setOrigin(0.5f * sf::Vector2f(icon1.getLocalBounds().width, icon1.getLocalBounds().height));

	buy3.setFont(font);
	buy3.setCharacterSize(30);
	buy3.setFillColor(sf::Color::Yellow);
	buy3.setOrigin(0.5f * sf::Vector2f(icon2.getLocalBounds().width, icon2.getLocalBounds().height));

	buy4.setFont(font);
	buy4.setCharacterSize(30);
	buy4.setFillColor(sf::Color::Yellow);
	buy4.setOrigin(0.5f * sf::Vector2f(icon3.getLocalBounds().width, icon3.getLocalBounds().height));

	buy5.setFont(font);
	buy5.setCharacterSize(30);
	buy5.setFillColor(sf::Color::Yellow);
	buy5.setOrigin(0.5f * sf::Vector2f(icon4.getLocalBounds().width, icon4.getLocalBounds().height));


}

void Store::Release()
{
}

void Store::Reset()
{
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	background.setTexture(TEXTURE_MGR.Get(backGroundId));
	icon1.setTexture(TEXTURE_MGR.Get(backIcon1));
	icon2.setTexture(TEXTURE_MGR.Get(backIcon2));
	icon3.setTexture(TEXTURE_MGR.Get(backIcon3));
	icon4.setTexture(TEXTURE_MGR.Get(backIcon4));

	background.setOrigin(0.5f * sf::Vector2f(background.getLocalBounds().width, background.getLocalBounds().height));
	icon1.setOrigin(0.5f * sf::Vector2f(icon1.getLocalBounds().width, icon1.getLocalBounds().height));
	icon2.setOrigin(0.5f * sf::Vector2f(icon2.getLocalBounds().width, icon2.getLocalBounds().height));
	icon3.setOrigin(0.5f * sf::Vector2f(icon3.getLocalBounds().width, icon3.getLocalBounds().height));
	icon4.setOrigin(0.5f * sf::Vector2f(icon4.getLocalBounds().width, icon4.getLocalBounds().height));

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	background.setPosition({ windowSize.x*0.5f,  windowSize.y * 0.5f });
	icon1.setPosition({ windowSize.x * 0.3f, windowSize.y * 0.35f });
	buy1.setPosition({ windowSize.x * 0.375f, windowSize.y * 0.8f });
	buy2.setPosition({ windowSize.x * 0.28f, windowSize.y * 0.63f });

	icon2.setPosition({ windowSize.x * 0.45f, windowSize.y * 0.35f });
	buy3.setPosition({ windowSize.x * 0.42f, windowSize.y * 0.63f });

	icon3.setPosition({ windowSize.x * 0.3f, windowSize.y * 0.55f });
	buy4.setPosition({ windowSize.x * 0.28f, windowSize.y * 0.42f });

	icon4.setPosition({ windowSize.x * 0.45f, windowSize.y * 0.55f });
	buy5.setPosition({ windowSize.x * 0.42f, windowSize.y * 0.42f });


	background.setScale(0.5f, 0.5f);
	icon1.setScale(1.f, 1.f);
	icon2.setScale(1.f, 1.f);
	icon3.setScale(1.f, 1.f);
	icon4.setScale(1.f, 1.f);

	selectBox1 = icon1.getGlobalBounds();
	selectBox2 = icon2.getGlobalBounds();
	selectBox3 = icon3.getGlobalBounds();
	selectBox4 = icon4.getGlobalBounds();

	name.setFont(font);
	name.setCharacterSize(40);
	name.setFillColor(sf::Color::Black);
	name.setOrigin(0.5f * sf::Vector2f(name.getLocalBounds().width, name.getLocalBounds().height));

}

void Store::Update(float dt)
{
	if (!isShow)
		return;

	buy2.setString(std::to_string(price) + "G");
	buy3.setString(std::to_string(price) + "G");
	buy4.setString(std::to_string(price) + "G");
	buy5.setString(std::to_string(price) + "G");

	if (player)
	{
		buy1.setString(std::to_string((int)player->GetMoney()) + " G");
	}

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		sf::Vector2i mousePos = InputMgr::GetMousePosition();
		sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToUi(mousePos);




		if (selectBox1.contains(mouseWorldPos))
		{
			if (player && player->GetMoney() >= price)
			{
				player->AddMoney(-price);  
				if (player)
				{
					player->DecreaseSkillLeft(0.3f);
				}
				std::cout << "구매 성공!" << std::endl;
				OnSelect();
				price += 50;
			}
			else
			{
				std::cout << "골드 부족!" << std::endl;
			}
		}
		if (selectBox2.contains(mouseWorldPos))
		{
			if (player && player->GetMoney() >= price)
			{
				player->AddMoney(-price);
				if (player)
				{
					player->IncreaseSkillRIght(1);
				}
				std::cout << "구매 성공!" << std::endl;
				OnSelect();
				price += 50;

			}
			else
			{
				std::cout << "골드 부족!" << std::endl;
			}
		}
		if (selectBox3.contains(mouseWorldPos))
		{
			if (player && player->GetMoney() >= price)
			{
				player->AddMoney(-price);
				if (player)
				{
					player->DecreaseSkillE(0.5f);
				}
				std::cout << "구매 성공!" << std::endl;
				OnSelect();
				price += 50;

			}
			else
			{
				std::cout << "골드 부족!" << std::endl;
			}
		}
		if (selectBox4.contains(mouseWorldPos))
		{
			if (player && player->GetMoney() >= price)
			{
				player->AddMoney(-price);
				std::cout << "r 강화!" << std::endl;
				if (player)
				{
					player->IncreaseSkillRDuration(1.f);
				}
				std::cout << "구매 성공!" << std::endl;
				OnSelect();
				price += 50;

			}
			else
			{
				std::cout << "골드 부족!" << std::endl;
			}
		}
	}
	name.setPosition(45.f, 650.f);

	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		FRAMEWORK.SetTimeScale(1.f);
		SetActive(false);
	}
}

void Store::Draw(sf::RenderWindow& window)
{

	isShow = true;
	SetActive(true);

	window.draw(background);
	window.draw(icon1);
	window.draw(icon2);
	window.draw(icon3);
	window.draw(icon4);
	window.draw(name);
	window.draw(buy1);
	window.draw(buy2);
	window.draw(buy3);
	window.draw(buy4);
	window.draw(buy5);
}