#include "CircleColliderComponent.h"
#include "AABBColliderComponent.h"
#include "Engine/TransformComponent.h"
#include "Math/Vector2.h"
#include "Engine/Entity.h"
#include <raylib.h>
#include <iostream>

/// <summary>
/// Checks collision between two circle collideres.
/// </summary>
/// <param name="other">The other circle collider.</param>
/// <returns>The data from the collision.</returns>
GamePhysics::Collision* GamePhysics::CircleColliderComponent::checkCollisionCircle(CircleColliderComponent* other)
{
    //Get direction to other collider
    GameMath::Vector2 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 direction = otherPosition - position;
    float distance = direction.getMagnitude();

    //Do nothing if there is no collision
    if (distance > other->m_radius + m_radius)
        return nullptr;

    //Circle Collision Data
    GamePhysics::Collision* collisionData = new Collision();
    collisionData->collider = other;
    collisionData->normal = direction.getNormalized();
    collisionData->contactPoint = position + direction.getNormalized() * getRadius();
    collisionData->penetrationDistance = (other->m_radius + m_radius) - distance;
    
    return collisionData;
}

/// <summary>
/// Checks collision between a circle collider and a AABB collider.
/// </summary>
/// <param name="other">The AABB Collider the circle has collided with.</param>
/// <returns>The collidion data of the two colliders.</returns>
GamePhysics::Collision* GamePhysics::CircleColliderComponent::checkCollisionAABB(AABBColliderComponent* other)
{
    //Dimension stuff
    GameMath::Vector2 dimensions = { other->getWidth(), other->getHeight() };
    GameMath::Vector2 collisionNormal = { m_radius, dimensions.getMagnitude() };
    //Positions
    GameMath::Vector2 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();
    //Direction and distance
    GameMath::Vector2 direction = otherPosition - position;
    float distance = direction.getMagnitude();

    //Calculations for the normal
    if (collisionNormal.x > collisionNormal.y && collisionNormal.x > 0)
        collisionNormal = { 1, 0 };
    else if (collisionNormal.y > collisionNormal.x && collisionNormal.y > 0)
        collisionNormal = { 0, 1 };
    else if (collisionNormal.x < collisionNormal.y && collisionNormal.x < 0)
        collisionNormal = { -1, 0 };
    else if (collisionNormal.y < collisionNormal.x && collisionNormal.y < 0)
        collisionNormal = { 0, -1 };

    //AABB Collision Check
    if (position.x < otherPosition.x + other->getWidth() && position.x + m_radius * 2 > otherPosition.x &&
        position.y < otherPosition.y + other->getHeight() && position.y + m_radius * 2 > otherPosition.y)
    {
        //AABB Collision Data
        GamePhysics::Collision* collisionData = new Collision();
        collisionData->collider = other;
        collisionData->normal = collisionNormal.getNormalized();
        collisionData->contactPoint = position + direction.getNormalized() * dimensions.getMagnitude();
        collisionData->penetrationDistance = (dimensions.getMagnitude() + m_radius) - distance;
        
        return collisionData;
    }
    else
        return nullptr;
}

void GamePhysics::CircleColliderComponent::draw()
{
    //Grabbing position for drawing
    GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();

    RAYLIB_H::DrawCircleLines(position.x, position.y, getRadius(), GetColor(getColor()));
}
