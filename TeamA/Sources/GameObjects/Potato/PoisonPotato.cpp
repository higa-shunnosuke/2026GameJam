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
	// ‰æ‘œ‚Ì“Ç‚İ‚İ
	ResourceManager& rm = ResourceManager::GetInstance();
	m_potatoImage = rm.GetImageResource("Assets/Sprites/Potato/PoisonPotato.PNG")[0];

	// zlayer‚Ìİ’è
	m_zLayer = 10;

	// “–‚½‚è”»’è‚Ìİ’è
	m_collision.m_type = e_ObjectType::poisonpoteto;
	m_collision.m_radius = 25;
}