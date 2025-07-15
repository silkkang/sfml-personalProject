#include "stdafx.h"
#include "Blood.h"

Blood::Blood(const std::string& name)
{
}


void Blood::Update(float dt)
{
	timer -= dt;
	if (timer <= 0.f)
		SetActive(false);
}