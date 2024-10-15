#include "CircleColliderComponent.h"
#include "AABBColliderComponent.h"
#include "Engine/TransformComponent.h"
#include "Math/Vector2.h"
#include "Engine/Entity.h"
#include <raylib.h>

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
    GameMath::Vector2 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 direction = otherPosition - position;

    //AABB Collision Check
    if (position.x < otherPosition.x + other->getWidth() && position.x + getRadius() * 2 > otherPosition.x &&
        position.y < otherPosition.y + other->getHeight() && position.y + getRadius() * 2 > otherPosition.y)
    {
        //AABB Collision Data
        GamePhysics::Collision* collisionData = new Collision();
        collisionData->collider = other;
        collisionData->normal = direction.getNormalized();
        collisionData->contactPoint = position + direction.getNormalized() * getRadius();
        //collisionData->penetrationDistance = (other->getRadius() + getRadius());

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
