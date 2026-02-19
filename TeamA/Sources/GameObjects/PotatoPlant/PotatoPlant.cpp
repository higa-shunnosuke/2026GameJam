#include "PotatoPlant.h"

#include "../ObjectManager.h"
#include "../../System/ResourceManager.h"

#include "../Potato/PoisonPotato.h"
#include "../Potato/Potato.h"
#include "../Potato/RainbowPotato.h"
#include "../../Utilitys/Random.h"

#include <DxLib.h>

PotatoPlant::PotatoPlant()
{

}

PotatoPlant::~PotatoPlant()
{

}

void PotatoPlant::Initialize()
{
	ObjectManager& object = ObjectManager::GetInstance();
	object.RequestSpawn<Potato>({300,300});
	ResourceManager& rm = ResourceManager::GetInstance();

	m_rank = Random::GetRand() % 3;

	m_leavesImages[0] = rm.GetImageResource("Assets/Sprites/Drill/Up1.PNG")[0];
	m_leavesImages[1] = rm.GetImageResource("Assets/Sprites/Drill/Up2.PNG")[0];
	m_leavesImages[2] = rm.GetImageResource("Assets/Sprites/Drill/Up3.PNG")[0];

	m_nekkoImages[0] = rm.GetImageResource("Assets/Sprites/Drill/Drill1.PNG")[0];
	m_nekkoImages[1] = rm.GetImageResource("Assets/Sprites/Drill/Drill2.PNG")[0];
	m_nekkoImages[2] = rm.GetImageResource("Assets/Sprites/Drill/Drill3.PNG")[0];
}

void PotatoPlant::Draw() const
{
	DrawRotaGraph(m_location.x, m_location.y, 0.1, 0.0, m_leavesImages[m_rank], TRUE);

	DrawRotaGraph(m_location.x, m_location.y, 0.1, 0.0, m_nekkoImages[m_rank], TRUE);

}

void PotatoPlant::Finalize()
{

}

