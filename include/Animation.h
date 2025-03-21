#pragma once
#include <SFML/Graphics.hpp>
#include <vector>



class SheetToBeAnimated
{
public:
	SheetToBeAnimated(const float& frameWidth, const float& frameHeight,const sf::Texture& spriteSheet)
	:m_width(frameWidth)
	,m_height(frameHeight)
	,m_spriteSheet(spriteSheet)
	
	{
		XmaxFrame = (m_spriteSheet.getSize().x / m_width);
		YmaxFrame = (m_spriteSheet.getSize().y / m_height);
		spriteCut();
	}

	void spriteCut()
	{
		sf::Sprite temp(m_spriteSheet);
		for (int row=0;row < YmaxFrame;++row)
		{
			for (int col = 0; col < XmaxFrame; ++col)
			{
				temp.setTextureRect(sf::IntRect(col * m_width, row * m_height, m_width, m_height));
				m_AllSprite.push_back( temp);
			}
		}

	}

	sf::Sprite testt()
	{
		return m_AllSprite[5];
	}
	void interruptAnimation()
	{
		m_interrupt = true;
	}

	sf::Sprite Animation(float deltaTime,const int& Line,const int& start,const int& end,const float& timeBetweenFrame=0.f,const bool& looping=false)
	{

		

		if (m_isFinished && !m_looping)
		{
			return m_AllSprite[0];
		}
		if (!m_isInitialized|| m_interrupt|| m_isFinished)
			AnimationInitialization(Line, start, end, timeBetweenFrame, looping);

		if (m_start == m_end)
		{
			m_isFinished = true;
			return m_AllSprite[m_Line * XmaxFrame + m_start-1];
		}
		m_time += deltaTime;


		if (m_time >= m_timeBetweenFrame)
		{

			if (m_currentFrame >= m_end -1)
			{
				m_isFinished = true;
				if (m_looping)
					m_currentFrame = m_start - 2;
			}

			
			m_currentFrame++;
			m_time = 0.0f;
			

		}

		return m_AllSprite[m_Line * XmaxFrame + m_currentFrame];
	}

	bool m_isFinished = false;
private:
	float m_width;
	float m_height;
	int XmaxFrame;
	int YmaxFrame;
	sf::Texture m_spriteSheet;
	std::vector<sf::Sprite> m_AllSprite;
private:
	
	bool m_interrupt =false;
	bool m_looping=false;
	bool m_isInitialized=false;
	int m_Line=1;
	int m_start=1;
	int m_end=1;
	int m_currentFrame=0;

	float m_timeBetweenFrame=0.f;
	float m_time;

	void AnimationInitialization(const int& Line, const int& start, const int& end, const float& timeBetweenFrame, const bool& looping)
	{
		m_isFinished = false;
		m_interrupt = false;
		m_looping = looping;
		m_Line = Line-1;
		m_start = start;
		m_end = end;
		m_currentFrame = m_start -1;
		m_timeBetweenFrame = timeBetweenFrame;
		m_time=0.f;
		m_isInitialized = true;
	}
};




