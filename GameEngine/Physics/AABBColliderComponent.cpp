#include "AABBColliderComponent.h"
#include "CircleColliderComponent.h"
#include "Engine/TransformComponent.h"
#include "Math/Vector2.h"
#include "Engine/Entity.h"
#include <raylib.h>

/// <summary>
/// Checks the collision between an AABB collider and a circle collider
/// </summary>
/// <param name="other">The circle collider.</param>
/// <returns>The data from the collision.</returns>
GamePhysics::Collision* GamePhysics::AABBColliderComponent::checkCollisionCircle(CircleColliderComponent* other)
{
    //Get direction to other collider
    GameMath::Vector2 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 direction = otherPosition - position;
    float distance = direction.getMagnitude();
    float otherRadius = other->getRadius();

    //Do nothing if there is no collision
    if (distance > otherRadius + m_radius)
        return nullptr;

    if (position.x < otherPosition.x + getRadius() && position.x + m_width > otherPosition.x &&
        position.y < otherPosition.y + other->getRadius() && position.y + m_height > otherPosition.y)
    {
        //Circle collision Data
        GamePhysics::Collision* collisionData = new Collision();
        collisionData->collider = other;
        collisionData->normal = direction.getNormalized();
        collisionData->contactPoint = position + direction.getNormalized() * getRadius();
        /*collisionData->penetrationDistance = (otherRadius + m_radius) - distance;*/

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
    GameMath::Vector2 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 direction = otherPosition - position;

    //AABB Collision Check
    if (position.x < otherPosition.x + other->getWidth() && position.x + m_width > otherPosition.x &&
        position.y < otherPosition.y + other->getHeight() && position.y + m_height > otherPosition.y)
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

void GamePhysics::AABBColliderComponent::draw()
{
    //Grabbing position for drawing
    GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();

    RAYLIB_H::DrawRectangleLines(position.x - m_width / 2, position.y - m_height / 2, getWidth(), getHeight(), GetColor(getColor()));
}
