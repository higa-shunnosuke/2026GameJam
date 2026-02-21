#include "PotatoPlant.h"

#include "../../System/ResourceManager.h"
#include "../../Utilitys/Random.h"
#include "../ObjectManager.h"

#include "../Potato/PoisonPotato.h"
#include "../Potato/Potato.h"
#include "../Potato/RainbowPotato.h"

#include <DxLib.h>

PotatoPlant::PotatoPlant()
	:m_leavesnekkoImages{}
, m_plantType()
{

}

PotatoPlant::~PotatoPlant()
{

}

void PotatoPlant::Initialize()
{
	// 3éÌÇÃÇ«ÇÍÇ©Ç…Ç∑ÇÈ
	m_plantType = Random::GetRand() % 3;

	// âÊëúÇÃì«Ç›çûÇ›
	ResourceManager& rm = ResourceManager::GetInstance();
	m_leavesnekkoImages[0] = rm.GetImageResource("Assets/Sprites/Potato/Leaves_Nekko1.PNG")[0];
	m_leavesnekkoImages[1] = rm.GetImageResource("Assets/Sprites/Potato/Leaves_Nekko2.PNG")[0];
	m_leavesnekkoImages[2] = rm.GetImageResource("Assets/Sprites/Potato/Leaves_Nekko3.PNG")[0];

	// zlayerÇÃê›íË
	m_zLayer = 0;

	// É|ÉeÉgÇê∂ê¨Ç∑ÇÈ
	SpawnPotatoAtDecidedPosition();
}

void PotatoPlant::Draw() const
{
	DrawRotaGraph(m_location.x, m_location.y , 0.3, 0.0, m_leavesnekkoImages[m_plantType], TRUE);
}

void PotatoPlant::Finalize()
{

}

void PotatoPlant::SpawnPotatoAtDecidedPosition()
{
	switch (m_plantType)
	{
	case 1:
		SpawnRandomPotato({ m_location.x - 140, m_location.y + 265});
		SpawnRandomPotato({ m_location.x ,m_location.y + 325 });
		SpawnRandomPotato({ m_location.x + 125,m_location.y + 125 });
		SpawnRandomPotato({ m_location.x + 135 ,m_location.y + 300 });

		break;

	case 2:
		SpawnRandomPotato({ m_location.x - 140, m_location.y + 265 });
		SpawnRandomPotato({ m_location.x - 100,m_location.y + 330 });
		SpawnRandomPotato({ m_location.x + 150,m_location.y + 259 });
		SpawnRandomPotato({ m_location.x + 45,m_location.y + 295 });

		break;

	case 0:
		SpawnRandomPotato({ m_location.x + 10,m_location.y + 280 });
		SpawnRandomPotato({ m_location.x - 110,m_location.y + 290 });
		SpawnRandomPotato({ m_location.x + 150,m_location.y + 240 });
		SpawnRandomPotato({ m_location.x - 150,m_location.y + 160 });

		break;
	}
}

void PotatoPlant::SpawnRandomPotato(const Vector2D& position)
{
	ObjectManager& object = ObjectManager::GetInstance();
	int tomato = Random::GetRand() % 100;
	
	int type;

	if (tomato < 80)
	{
		type = 0;
	}
	else if (tomato < 90)
	{
		type = 1;
	}
	else
	{
		type = 2;
	}

	switch (type)
	{
	case 0:
		object.RequestSpawn<Potato>(position);
		break;

	case 1:
		object.RequestSpawn<PoisonPotato>(position);
		break;

	case 2:
		object.RequestSpawn<RainbowPotato>(position);
		break;
	}
}
