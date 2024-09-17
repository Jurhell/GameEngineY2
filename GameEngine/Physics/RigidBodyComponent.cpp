#include "RigidBodyComponent.h"
#include "Engine/TransformComponent.h"
#include "Physics/ColliderComponent.h"
#include "Engine/Entity.h"

using namespace GameMath;

void GamePhysics::RigidBodyComponent::applyForce(GameMath::Vector2 force)
{
	m_velocity = m_velocity + force / getMass();
}

void GamePhysics::RigidBodyComponent::applyForceToEntity(RigidBodyComponent* rigidBody, GameMath::Vector2 force)
{
	applyForce(force * -1);
	rigidBody->applyForce(force);
}

void GamePhysics::RigidBodyComponent::fixedUpdate(float fixedDeltaTime)
{
	Vector2 position = getOwner()->getTransform()->getLocalPosition();
	getOwner()->getTransform()->setLocalPosition(position + m_velocity * fixedDeltaTime);

	Vector2 gravity = { 0, getGravity() };
	applyForce(gravity * getMass());
}

void GamePhysics::RigidBodyComponent::resolveCollision(GamePhysics::Collision* collisionData)
{
	//Creating variables to use in math
	RigidBodyComponent* otherRigid = collisionData->collider->getRigidBody();
	Vector2 normal = collisionData->normal;

	//If what we collided with doesn't have a rigid body
	if (!otherRigid)
		;

	//Physics Math, for Collision Resolution/Response
	float impulse = 2 * (normal.dotProduct(getVelocity() - otherRigid->getVelocity(), normal))
	/ normal.dotProduct(normal, normal) * (1 / getMass() + 1 / otherRigid->getMass());

	//Storing and applying force
	Vector2 force = normal * impulse;
	applyForceToEntity(otherRigid, force);
}
