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

}

void Potato::Draw() const
{
	DrawRotaGraph(m_location.x, m_location.y, 0.1, 0.0, m_potatoImage, TRUE);

}


void Potato::OnHitCollision(ObjectBase& other)
{
	ObjectManager& manager = ObjectManager::GetInstance();
	manager.DestroyObject(this);


}