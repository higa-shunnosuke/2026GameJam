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
	m_animeTime = 0.0f; //虹色更新絵処理使うかも
	m_animeCount = 0;
	ResourceManager& rm = ResourceManager::GetInstance();

	m_rainbowpotatoImage = rm.GetImageResource("Assets/Sprites/Potato/RainbowPotato.PNG")[0];

}

void  RainbowPotato::Update(float delta) //虹色更新処理で使うかも
{
	m_animeTime += 0.01f;
	if (m_animeTime > 1.0f)
	{
		m_animeTime = 0.0f;
		m_animeCount += 1;
	}
}

void RainbowPotato::Draw() const
{
	DrawRotaGraph(m_location.x, m_location.y, 0.1, 0.0, m_rainbowpotatoImage, TRUE);

}


void RainbowPotato::OnHitCollision(ObjectBase& other)
{
	ObjectManager& manager = ObjectManager::GetInstance();
	manager.DestroyObject(this);


}
