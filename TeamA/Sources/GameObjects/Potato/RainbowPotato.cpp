#include "RainbowPotato.h"

#include "../../System/ResourceManager.h"
#include "../ObjectManager.h"
#include <DxLib.h>

RainbowPotato::RainbowPotato()
{

}

RainbowPotato::~RainbowPotato()
{

}

void RainbowPotato::Initialize()
{
	// ‰æ‘œ‚Ì“Ç‚İ‚İ
	ResourceManager& rm = ResourceManager::GetInstance();
	m_potatoImage = rm.GetImageResource("Assets/Sprites/Potato/RainbowPotato.PNG")[0];

	// zlayer‚Ìİ’è
	m_zLayer = 10;

	// “–‚½‚è”»’è‚Ìİ’è
	m_collision.m_type = e_ObjectType::rainbowpoteto;
	m_collision.m_radius = 35;

}
