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
}


void PoisonPotato::Draw() const
{
	DrawRotaGraph(m_location.x, m_location.y, 0.1, 0.0, m_poisonpotatoImage, TRUE);

}


void PoisonPotato::OnHitCollision(ObjectBase& other)
{
	ObjectManager& manager = ObjectManager::GetInstance();
	manager.DestroyObject(this);


}
