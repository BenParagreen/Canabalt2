#pragma once

// Library Includes
#include <SFML/Graphics.hpp>

class Platform
{
public:
	Platform();
	void Spawn();
	void Draw(sf::RenderTarget& _target);
	sf::FloatRect GetCollider();

private:
	//Assets
	sf::Sprite m_sprite;

};