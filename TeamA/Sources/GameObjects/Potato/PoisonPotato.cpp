#include "PoisonPotato.h"

#include "../../System/ResourceManager.h"
#include "../ObjectManager.h"
#include <DxLib.h>

PoisonPotato::PoisonPotato()
{

}

PoisonPotato::~PoisonPotato()
{

}

void PoisonPotato::Initialize()
{
	ResourceManager& rm = ResourceManager::GetInstance();

	m_poisonpotatoImage = rm.GetImageResource("Assets/Sprites/Potato/PoisonPotato.PNG")[0];

	m_collision.m_radius = 25;
	m_collision.m_type = e_ObjectType::poisonpoteto;
	m_zLayer = 10;
}


void PoisonPotato::Draw() const
{
	DrawRotaGraph(m_location.x, m_location.y, 0.03, 0.0, m_poisonpotatoImage, TRUE);

#if _DEBUG
	// “–‚½‚è”»’è‚ð‰ÂŽ‹‰»
	DrawCircle(m_location.x, m_location.y, m_collision.GetRadius(), GetColor(255, 0, 0), FALSE);
#endif

}


void PoisonPotato::OnHitCollision(ObjectBase& other)
{
	ObjectManager& manager = ObjectManager::GetInstance();
	manager.DestroyObject(this);

}
