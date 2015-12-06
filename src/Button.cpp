#include "Button.h"

#include "Assets.h"
#include "EntityTags.h"

Button::Button(SpriteInfo& info, sf::Vector2f pos, std::string label) :
    SpriteObject(info, pos),
    mState(ButtonStates::Up),
    mPressed(false),
    mLabel(label),
    mText(mLabel, Assets::fonts["8bit"].mFont, 14)
{
    //ctor
}

Button::~Button()
{
    //dtor
}

void Button::update()
{
    if (sf::FloatRect(mRenderPosition, mSpriteInfo.mFrameDim).contains(mMousePosition))
    {
        mState = ButtonStates::Hover;
    }
    else
    {
        mState = ButtonStates::Up;
    }
}

void Button::draw(sf::RenderTarget& target, float alpha)
{
    SpriteObject::draw(target, alpha);

    if (mState == ButtonStates::Up)
        setFrameLoop(0, 0);
    else if (mState == ButtonStates::Down)
        setFrameLoop(1, 1);
    else if (mState == ButtonStates::Hover)
        setFrameLoop(2, 2);

    if (mLabel != "" && mText.getString() != "")
    {
        mText.setPosition(mRenderPosition+getCenter() - sf::Vector2f(mText.getGlobalBounds().width/2, mText.getGlobalBounds().height/2));
        target.draw(mText);
    }
}

void Button::handleEvents(sf::Event& event)
{
    if (event.type == sf::Event::MouseMoved)
    {
        mMousePosition = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
    }

    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (sf::FloatRect(mRenderPosition, mSpriteInfo.mFrameDim).contains(mMousePosition))
        {
            mPressed = true;
            mState = ButtonStates::Hover;
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                mState = ButtonStates::Down;
            }
        }
    }
}
