#include "Potato.h"

#include "../../System/ResourceManager.h"
#include "../ObjectManager.h"

#include <DxLib.h>

Potato::Potato()
	:m_potatoImage()
{
	
}

Potato::~Potato()
{

}

void Potato::Initialize()
{
	// ‰æ‘œ‚Ì“Ç‚İ‚İ
	ResourceManager& rm = ResourceManager::GetInstance();
	m_potatoImage = rm.GetImageResource("Assets/Sprites/Potato/NormalPotato.PNG")[0];

	// zlayer‚Ìİ’è
	m_zLayer = 10;

	// “–‚½‚è”»’è‚Ìİ’è
	m_collision.m_type = e_ObjectType::potato;
	m_collision.m_radius = 35;
}

void Potato::Draw() const
{
	DrawRotaGraphF(m_location.x, m_location.y, 0.03, 0.0, m_potatoImage, TRUE);

#if _DEBUG
	// “–‚½‚è”»’è‚ğ‰Â‹‰»
	DrawCircle(m_location.x, m_location.y, m_collision.m_radius, GetColor(255, 0, 0), FALSE);
#endif
}

void Potato::OnHitCollision(ObjectBase& other)
{
	// ©g‚ğíœ‚·‚é
	ObjectManager& manager = ObjectManager::GetInstance();
	manager.DestroyObject(this);
}