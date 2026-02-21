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

	m_collision.m_radius = 35;
	m_collision.m_type = e_ObjectType::rainbowpoteto;
	m_zLayer = 10;

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
	DrawRotaGraph(m_location.x, m_location.y, 0.03, 0.0, m_rainbowpotatoImage, TRUE);

#if _DEBUG
	// 当たり判定を可視化
	DrawCircle(m_location.x, m_location.y, m_collision.GetRadius(), GetColor(255, 0, 0), FALSE);
#endif

}


void RainbowPotato::OnHitCollision(ObjectBase& other)
{
	ObjectManager& manager = ObjectManager::GetInstance();
	manager.DestroyObject(this);


}
