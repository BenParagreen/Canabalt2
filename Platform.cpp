// Library Includes
#include <cstdlib>


// Project Files
#include "Platform.h"
#include "AssetManager.h"

// Constants
#define SIZE_X_MIN 50
#define SIZE_Y_MIN 1
#define SIZE_X_MAX 100
#define SIZE_Y_MAX 5
#define POS_Y_MIN 800
#define POS_Y_MAX 1000

Platform::Platform()
	: m_sprite()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/block.png"));
}

void Platform::Spawn()
{
	//Choose a random size for the platform
	sf::Vector2f size;
	size.x = rand() % (SIZE_X_MAX - SIZE_X_MIN) + SIZE_X_MIN;
	size.y = rand() % (SIZE_Y_MAX - SIZE_Y_MIN) + SIZE_Y_MIN;
	m_sprite.setScale(size.x, size.y);

	sf::Vector2f position;
	position.y = rand() % (POS_Y_MAX - POS_Y_MIN) + POS_Y_MIN;
	position.x = 0;
	m_sprite.setPosition(position);
}

void Platform::Draw(sf::RenderTarget& _target)
{
	_target.draw(m_sprite);
}

sf::FloatRect Platform::GetCollider()
{
	return m_sprite.getGlobalBounds();
}