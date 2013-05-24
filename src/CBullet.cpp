#include "headers.h"

CBullet::CBullet()
{

}

CBullet::CBullet(sf::RenderWindow & App, sf::Vector2f pStartPosition, float pRotation, int pBulletDmg)
{
	m_vel = 500.f;
	m_lifetime = 0;
	m_damage = pBulletDmg;

	this->m_startPos = pStartPosition;
	this->m_toDelete = false;
	this->m_rotation = pRotation;

	m_ImousePos = sf::Mouse::getPosition(App);
	m_mousePos = App.mapPixelToCoords(m_ImousePos);
		
	m_dis.x = m_startPos.x - m_mousePos.x;
	m_dis.y = m_startPos.y - m_mousePos.y;

	DLen = sqrt(m_dis.x * m_dis.x + m_dis.y * m_dis.y);
	m_dis.x /= DLen;
	m_dis.y /= DLen;

	m_dis.x *= m_vel;
	m_dis.y *= m_vel;

	//m_texture = new sf::Texture;
	//m_texture->loadFromImage( *gResources.getImagePointer("res/img/bullet1.png") );
	m_textureU = std::make_shared<sf::Texture>(sf::Texture());
	m_textureU->loadFromImage( *gResources.getImagePointer("res/img/bullet1.png") );

	m_sprite.setTexture( *m_textureU );
	m_sprite.setOrigin( (float)m_textureU->getSize().x /2, (float)m_textureU->getSize().y /2);
	m_sprite.setPosition(m_startPos);
	m_sprite.setRotation(-m_rotation);

	fRect.width = (float)m_textureU->getSize().x-5;
	fRect.height = (float)m_textureU->getSize().y-5;
	fRect.top = m_startPos.x;
	fRect.left = m_startPos.y;

}

void CBullet::update(sf::RenderWindow & App, float deltaTime)
{
	if( m_lifetime < 100 && !m_toDelete )
	{
		m_sprite.move(-m_dis * deltaTime);
		//m_sprite.setPosition( m_sprite.getPosition().x + (-m_dis.x *deltaTime), (float)sin(m_sprite.getPosition().x/100)*100 );
		fRect.top = m_sprite.getPosition().x - m_textureU->getSize().x/2;
		fRect.left = m_sprite.getPosition().y - m_textureU->getSize().y/2;
		//App.draw( m_sprite );
		m_lifetime++;

		sf::RectangleShape pshape;
		pshape.setSize(sf::Vector2f(fRect.width, fRect.height));
		pshape.setPosition(fRect.top,  fRect.left);
		pshape.setFillColor(sf::Color::Magenta);
		App.draw(pshape);

		
	}
	else
	{
		m_toDelete = true;
	}
	
}

bool CBullet::toDelete() const
{
	return m_toDelete;
}

void CBullet::setToDelete()
{
	m_toDelete = true;
}

int CBullet::getBulletDamage() const
{
	return m_damage;
}

sf::Vector2f CBullet::getPosition() const
{
	return m_sprite.getPosition();
}