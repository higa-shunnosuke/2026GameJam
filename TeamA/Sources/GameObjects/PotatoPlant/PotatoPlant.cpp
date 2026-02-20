#include "PotatoPlant.h"

#include "../ObjectManager.h"
#include "../../System/ResourceManager.h"

#include "../Potato/PoisonPotato.h"
#include "../Potato/Potato.h"
#include "../Potato/RainbowPotato.h"
#include "../../Utilitys/Random.h"
#include "../ObjectManager.h"

#include <DxLib.h>

PotatoPlant::PotatoPlant()
{

}

PotatoPlant::~PotatoPlant()
{

}

void PotatoPlant::Initialize()
{
	ResourceManager& rm = ResourceManager::GetInstance();

	m_rank = Random::GetRand() % 3;

	//m_rank = 0; //à íuí≤êÆóp


	m_leavesnekkoImages[0] = rm.GetImageResource("Assets/Sprites/Potato/Leaves_Nekko1.PNG")[0];
	m_leavesnekkoImages[1] = rm.GetImageResource("Assets/Sprites/Potato/Leaves_Nekko2.PNG")[0];
	m_leavesnekkoImages[2] = rm.GetImageResource("Assets/Sprites/Potato/Leaves_Nekko3.PNG")[0];

	CreationPotato();
}

void PotatoPlant::Draw() const
{
	DrawRotaGraph(m_location.x, m_location.y , 0.3, 0.0, m_leavesnekkoImages[m_rank], TRUE);

	DrawFormatString(50, 50, 0xffffff, "%d", m_rank);
}

void PotatoPlant::Finalize()
{

}

void PotatoPlant::CreationPotato()
{
	ObjectManager& object = ObjectManager::GetInstance();
	
	switch (m_rank)
	{
	case 1:
		object.RequestSpawn<Potato>({ m_location.x - 140 ,m_location.y + 265});
		object.RequestSpawn<Potato>({ m_location.x ,m_location.y + 325});
		object.RequestSpawn<Potato>({ m_location.x + 125,m_location.y + 125});
		object.RequestSpawn<Potato>({ m_location.x + 135 ,m_location.y + 300 });
			break;

	case 2:
		object.RequestSpawn<Potato>({ m_location.x - 160,m_location.y + 155 });
		object.RequestSpawn<Potato>({ m_location.x - 100,m_location.y + 330 });
		object.RequestSpawn<Potato>({ m_location.x + 150,m_location.y + 259 });
		object.RequestSpawn<Potato>({ m_location.x + 45,m_location.y + 295 });
			break;

	case 0:
		object.RequestSpawn<Potato>({ m_location.x + 10,m_location.y + 280});
		object.RequestSpawn<Potato>({ m_location.x - 110,m_location.y + 290 });
		object.RequestSpawn<Potato>({ m_location.x + 150,m_location.y + 240 });
		object.RequestSpawn<Potato>({ m_location.x - 150,m_location.y + 160 });
			break;
	}
}
