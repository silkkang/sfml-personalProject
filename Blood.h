#pragma once
#include "SpriteGo.h"
class Blood : public SpriteGo
{
protected:
	float timer = 1.f;
public:
	Blood(const std::string& name = "");
	virtual ~Blood() = default;

	void Update(float dt) override;
};

