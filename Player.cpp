//Project Includes
#include "Player.h"
#include "AssetManager.h"

// Constants
#define Jump_Speed -1500.0f
#define Gravity 2000.0f
#define RUN_SPEED_INITIAL 500.0f

Player::Player()
	: m_sprite()
	, m_jumpSound()
	, m_deathSound()
	, m_landSound()
	, m_animation()
	, m_velocity(0.0f, 0.0f)
	, m_touchingGround(false)
{
	//Sprite Setup
	m_sprite.setTexture(AssetManager::GetTexture("graphics/playerJump.png"));

	//Sound Setup
	m_jumpSound.setBuffer(AssetManager::GetSoundBuffer("Audio/jump.wav"));
	m_deathSound.setBuffer(AssetManager::GetSoundBuffer("Audio/death.wav"));
	m_landSound.setBuffer(AssetManager::GetSoundBuffer("Audio/landing.wav"));

	//Animation Setup
	m_animation.SetSprite(m_sprite);

	Animation& runAnimation = m_animation.CreateAnimation("run");
    runAnimation.AddFrame(AssetManager::GetTexture("graphics/playerRun1.png"));
	runAnimation.AddFrame(AssetManager::GetTexture("graphics/playerRun2.png"));
	runAnimation.SetLoop(true);
	runAnimation.SetPlayBackSpeed(10.0f);

	Animation& jumpAnimation = m_animation.CreateAnimation("jump");
	jumpAnimation.AddFrame(AssetManager::GetTexture("graphics/playerJump.png"));

	m_animation.Play("jump");

}

void Player::Input(sf::Event _gameEvent)
{
	// Check if the player has pressed the jump button
	if (_gameEvent.type == sf::Event::KeyPressed) 
	{
		//Check if the button was space
		if (_gameEvent.key.code == sf::Keyboard::Space)
		{
			if (m_touchingGround == true)
			{
				//Player has tried to jump
				//Play jump sound
				m_jumpSound.play();

				//Set the players upward velocity
				m_velocity.y = Jump_Speed;

				m_animation.Play("jump");
			}
			

		}
	}
}

void Player::Update(sf::Time _FrameTime)
{
	//Process the animation
	m_animation.Update(_FrameTime);

	//Apply gravity to the velocity
	if (m_touchingGround == false)
	{
		float velocityChange = Gravity * _FrameTime.asSeconds();
	    m_velocity.y += velocityChange;
	}
	

	//Move sprite based on velocity
	sf::Vector2f currentPosition = m_sprite.getPosition();
	sf::Vector2f positionChange = m_velocity * _FrameTime.asSeconds();
	m_sprite.setPosition(currentPosition + positionChange);


}

void Player::Draw(sf::RenderTarget& _target)
{
	_target.draw(m_sprite);
}

void Player::Spawn()
{
	m_sprite.setPosition(0, 0);
	m_animation.Play("jump");
	m_velocity.y = 0;
	m_velocity.x = RUN_SPEED_INITIAL;
}

sf::Vector2f Player::GetPosition()
{
	return m_sprite.getPosition();
}

void Player::HandleCollison(std::vector<sf::FloatRect> _platforms)
{
	bool wasTouchingGround = m_touchingGround;

	m_touchingGround = false;

	// Get the collider for the player bounds
	sf::FloatRect playerCollider = m_sprite.getGlobalBounds();

	//Loop through each platform collider
	for (auto it = _platforms.begin(); it != _platforms.end(); ++it)
	{
		sf::FloatRect platformCollider = *it;

		if (playerCollider.intersects(_platforms))
		{
			//Create feet collider
			//Check if the bottom of players feet is touching top of platform
			sf::FloatRect feetCollider = playerCollider;
			feetCollider.top += playerCollider.height - 10;
			// Set our feet collider height to be 10 pixels

			//Create platform top collider
			sf::FloatRect platformTop = platformCollider;
			platformTop.height = 10;

			if (feetCollider.intersects(platformTop))
			{
				m_touchingGround = true;
				if (m_velocity.y > 0 && wasTouchingGround == false)
				{
					m_animation.Play("run");
					m_landSound.play();
					m_velocity.y = 0;
					m_touchingGround = true;

				}
			}
		}
		if (m_touchingGround == false && wasTouchingGround == true)
		{
			m_animation.Play("jump");
		}
	}
}

	
	

