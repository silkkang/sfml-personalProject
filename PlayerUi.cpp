#include "stdafx.h"
#include "PlayerUi.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "Scene.h"

PlayerUi::PlayerUi(const std::string& name)
	: GameObject(name)
{
}

void PlayerUi::SetPosition(const sf::Vector2f& pos)
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

void PlayerUi::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	background.setRotation(rot);
	icon1.setRotation(rot);
	icon2.setRotation(rot);
	icon3.setRotation(rot);
	icon4.setRotation(rot);
}

void PlayerUi::SetScale(const sf::Vector2f& s)
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

void PlayerUi::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	background.setOrigin(o);
	icon1.setOrigin(o);
	icon2.setOrigin(o);
	icon3.setOrigin(o);
	icon4.setOrigin(o);
}

void PlayerUi::SetOrigin(Origins preset)
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

void PlayerUi::Show()
{
	isShow = true;
	SetActive(true);
	
}

void PlayerUi::Hide()
{
	isShow = false;
	SetActive(false);
	
}

void PlayerUi::SetOnSelected(const std::function<void()>& func)
{
	onSelected = func;
}

void PlayerUi::OnSelect()
{
	if (onSelected)
	{
		std::cout << "OnSelect 호출됨!" << std::endl;
		onSelected();
	}
}


void PlayerUi::Init()
{
}

void PlayerUi::Release()
{
}

void PlayerUi::Reset()
{
	background.setTexture(TEXTURE_MGR.Get(backGroundId));
	icon1.setTexture(TEXTURE_MGR.Get(backIcon1));
	icon2.setTexture(TEXTURE_MGR.Get(backIcon2));
	icon3.setTexture(TEXTURE_MGR.Get(backIcon3));
	icon4.setTexture(TEXTURE_MGR.Get(backIcon4));

	background.setOrigin(0.f, 0.f);
	icon1.setOrigin(0.f, 0.f);
	icon2.setOrigin(0.f, 0.f);
	icon3.setOrigin(0.f, 0.f);
	icon4.setOrigin(0.f, 0.f);

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	background.setPosition({ windowSize.x * 0.1f, windowSize.y -400 });
	icon1.setPosition({ windowSize.x * 0.145f, windowSize.y - 320 });
	icon2.setPosition({ windowSize.x * 0.225f, windowSize.y - 320 });
	icon3.setPosition({ windowSize.x * 0.145f, windowSize.y - 235 });
	icon4.setPosition({ windowSize.x * 0.225f, windowSize.y - 235 });

	background.setScale(0.3f, 0.3f);
	icon1.setScale(1.f,1.f);
	icon2.setScale(1.f, 1.f);
	icon3.setScale(1.f, 1.f);
	icon4.setScale(1.f, 1.f);

	selectBox1 = icon1.getGlobalBounds();
	selectBox2 = icon2.getGlobalBounds();
	selectBox3 = icon3.getGlobalBounds();
	selectBox4 = icon4.getGlobalBounds();

}

void PlayerUi::Update(float dt)
{
	if (!isShow)
		return;




	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		sf::Vector2i mousePos = InputMgr::GetMousePosition();
		sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToUi(mousePos);

	

		if (selectBox1.contains(mouseWorldPos))
		{
			std::cout << "1선택 박스 클릭됨!" << std::endl;
			OnSelect();
		}
		if (selectBox2.contains(mouseWorldPos))
		{
			std::cout << "2선택 박스 클릭됨!" << std::endl;
			OnSelect();
		}
		if (selectBox3.contains(mouseWorldPos))
		{
			std::cout << "3선택 박스 클릭됨!" << std::endl;
			OnSelect();
		}
		if (selectBox4.contains(mouseWorldPos))
		{
			std::cout << "4선택 박스 클릭됨!" << std::endl;
			OnSelect();
		}
	}

}

void PlayerUi::Draw(sf::RenderWindow& window)
{
	isShow = true;
	SetActive(true);
	
	window.draw(background);
	window.draw(icon1);
	window.draw(icon2);
	window.draw(icon3);
	window.draw(icon4);

}