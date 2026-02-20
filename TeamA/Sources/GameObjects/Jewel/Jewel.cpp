#include "Jewel.h"

#include "../ObjectManager.h"
#include "../../System/ResourceManager.h"
#include <DxLib.h>

Jewel::Jewel()
{

}

Jewel::~Jewel()
{

}

void Jewel::Initialize()
{
	m_animeTime = 0.0f;
	m_animeCount = 0;

	m_zLayer = 10;

	ResourceManager& rm = ResourceManager::GetInstance();

	m_emerald_image[0] = rm.GetImageResource("Assets/Sprites/Jewel/emerald/emerald1.PNG")[0];
	m_emerald_image[1] = rm.GetImageResource("Assets/Sprites/Jewel/emerald/emerald2.PNG")[0];
	m_emerald_image[2] = rm.GetImageResource("Assets/Sprites/Jewel/emerald/emerald3.PNG")[0];
	m_emerald_image[3] = rm.GetImageResource("Assets/Sprites/Jewel/emerald/emerald4.PNG")[0];
}

void Jewel::Update(float delta)
{
	m_animeTime += delta;
	if (m_animeTime > 0.4f)
	{
		m_animeTime = 0.0f;
		m_animeCount += 1;
	}
}

void Jewel::Draw() const
{
	DrawCircle(m_location.x, m_location.y, 10, GetColor(255, m_animeCount % 255, 0), TRUE);
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", m_animeCount);

	DrawRotaGraphF(m_location.x, m_location.y, 0.1f, 0.0f, m_emerald_image[m_animeCount % 4], TRUE);
}

void Jewel::Finalize()
{

}

void Jewel::OnHitCollision(ObjectBase& other)
{
	ObjectManager& manager = ObjectManager::GetInstance();
	//manager.DestroyObject(this);
}