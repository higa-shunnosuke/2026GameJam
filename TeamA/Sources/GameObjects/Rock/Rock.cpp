#include "Rock.h"

#include "../ObjectManager.h"
#include <DxLib.h>

Rock::Rock()
{

}

Rock::~Rock()
{

}

void Rock::Initialize()
{

}


void Rock::Draw() const
{
	DrawCircle(m_location.x, m_location.y, 10, GetColor(255, m_animeCount % 255, 0), TRUE);
}

void Rock::OnHitCollision(ObjectBase& other)
{
	ObjectManager& manager = ObjectManager::GetInstance();
	manager.DestroyObject(this);
}