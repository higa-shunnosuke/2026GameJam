#include "Rock.h"

#include "../../System/ResourceManager.h"
#include <DxLib.h>

Rock::Rock()
	:m_rockImage()
{

}

Rock::~Rock()
{

}

void Rock::Initialize()
{
	// âÊëúì«Ç›çûÇ›
	ResourceManager& rm = ResourceManager::GetInstance();
	m_rockImage = rm.GetImageResource("Assets/Sprites/Rock/Rock.PNG")[0];
}

void Rock::Draw() const
{
	DrawRotaGraphF(m_location.x, m_location.y, 0.1f, 0.0f, m_rockImage, TRUE);
}