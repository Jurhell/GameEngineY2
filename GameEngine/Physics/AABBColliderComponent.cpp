#include "AABBColliderComponent.h"
#include "CircleColliderComponent.h"
#include "Engine/TransformComponent.h"
#include "Math/Vector2.h"
#include "Engine/Entity.h"
#include <raylib.h>
#include <iostream>

/// <summary>
/// Checks the collision between an AABB collider and a circle collider
/// </summary>
/// <param name="other">The circle collider.</param>
/// <returns>The data from the collision.</returns>
GamePhysics::Collision* GamePhysics::AABBColliderComponent::checkCollisionCircle(CircleColliderComponent* other)
{
    //Get direction to other collider
    float circleRadius = other->getRadius();
    GameMath::Vector2 dimensions = { m_width, m_height };
    GameMath::Vector2 dimensionMagnitudes = { circleRadius, dimensions.getMagnitude()};
    GameMath::Vector2 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 direction = otherPosition - position;
    float distance = direction.getMagnitude();

    //Do nothing if there is no collision
    if (distance > circleRadius)
        return nullptr;

    if (position.x < otherPosition.x + circleRadius && position.x + m_width > otherPosition.x &&
        position.y < otherPosition.y + circleRadius && position.y + m_height > otherPosition.y)
    {
        //Circle collision Data
        GamePhysics::Collision* collisionData = new Collision();
        collisionData->collider = other;
        //Needs work
        collisionData->normal = dimensionMagnitudes.getNormalized();
        collisionData->contactPoint = position + direction.getNormalized() * circleRadius;
        collisionData->penetrationDistance = (circleRadius + position.getMagnitude()) - distance;

        return collisionData;
    }
}

/// <summary>
/// Checks the collision between two AABB colliders.
/// </summary>
/// <param name="other">The other AABB collider.</param>
/// <returns>The data from the collision.</returns>
GamePhysics::Collision* GamePhysics::AABBColliderComponent::checkCollisionAABB(AABBColliderComponent* other)
{
    //Dimensions
    GameMath::Vector2 dimensions = { m_width, m_height };
    GameMath::Vector2 otherDimensions = { other->getWidth(), other->getHeight() };
    GameMath::Vector2 dimensionMagnitudes = { dimensions.getMagnitude(), otherDimensions.getMagnitude() };
    //Positions
    GameMath::Vector2 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();
    //Direction and distance
    GameMath::Vector2 direction = otherPosition - position; 
    float distance = direction.getMagnitude();

    //AABB Collision Check, halving other height to temp fix exception thrown error
    if (position.x < otherPosition.x + other->getWidth() && position.x + m_width > otherPosition.x &&
        position.y < otherPosition.y + other->getHeight() / 2 && position.y + m_height > otherPosition.y)
    {
        //AABB Collision Data
        GamePhysics::Collision* collisionData = new Collision();
        collisionData->collider = other;
        //Needs work
        collisionData->normal = dimensionMagnitudes.getNormalized();
        collisionData->contactPoint = position + direction.getNormalized() * dimensions.getMagnitude();
        collisionData->penetrationDistance = (dimensions.getMagnitude() + otherDimensions.getMagnitude()) - distance;
        
        return collisionData;
    }
    else
        return nullptr;
}

void GamePhysics::AABBColliderComponent::draw()
{
    //Grabbing position for drawing
    GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();

    RAYLIB_H::DrawRectangleLines(position.x - m_width / 2, position.y - m_height / 2, getWidth(), getHeight(), GetColor(getColor()));
}
