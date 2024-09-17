#include "AABBColliderComponent.h"
#include "CircleColliderComponent.h"
#include "Engine/TransformComponent.h"
#include "Math/Vector2.h"
#include "Engine/Entity.h"
#include <raylib.h>

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

    //Circle collision Data
    GamePhysics::Collision* collisionData = new Collision();
    collisionData->collider = other;
    collisionData->normal = direction.getNormalized();
    collisionData->contactPoint = position + direction.getNormalized() * getRadius();
    collisionData->penetrationDistance = (otherRadius + m_radius) - distance;

    return collisionData;
}

GamePhysics::Collision* GamePhysics::AABBColliderComponent::checkCollisionAABB(AABBColliderComponent* other)
{
    GameMath::Vector2 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 direction = otherPosition - position;

    //AABB Colliding
    if (position.x < otherPosition.x + other->getWidth() && position.x + m_width > otherPosition.x &&
        position.y < otherPosition.y + other->getHeight() && position.y + m_height > otherPosition.y)
    {
        //AABB Collision Data
        GamePhysics::Collision* collisionData = new Collision();
        collisionData->collider = other;
        collisionData->normal = direction.getNormalized();
        collisionData->contactPoint = position + direction.getNormalized() * getRadius();
        collisionData->penetrationDistance = (other->getRadius() + getRadius());

        return collisionData;
    }
    else
        return nullptr;
}

void GamePhysics::AABBColliderComponent::draw()
{
    GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();

    RAYLIB_H::DrawRectangle(position.x, position.y, getWidth(), getHeight(), GetColor(getColor()));
}
