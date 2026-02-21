#include "Potato.h"

#include "../../System/ResourceManager.h"
#include "../ObjectManager.h"

#include <DxLib.h>

Potato::Potato()
{
	
}

Potato::~Potato()
{

}

void Potato::Initialize()
{
	ResourceManager& rm = ResourceManager::GetInstance();

	m_potatoImage = rm.GetImageResource("Assets/Sprites/Potato/NormalPotato.PNG")[0];

	m_collision.m_radius = 35;
	m_collision.m_type = e_ObjectType::potato;
	m_zLayer = 10;

}

void Potato::Draw() const
{
	DrawRotaGraph(m_location.x, m_location.y, 0.03, 0.0, m_potatoImage, TRUE);

#if _DEBUG
	// “–‚½‚è”»’è‚ð‰ÂŽ‹‰»
	DrawCircle(m_location.x, m_location.y, m_collision.GetRadius(), GetColor(255, 0, 0), FALSE);
#endif
}


void Potato::OnHitCollision(ObjectBase& other)
{
	ObjectManager& manager = ObjectManager::GetInstance();
	manager.DestroyObject(this);

}