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

/// <summary>
/// Collision Resolution. Calculates the force to apply when two entities collide.
/// </summary>
/// <param name="collisionData">The data from two colliders that have made contact.</param>
void GamePhysics::RigidBodyComponent::resolveCollision(GamePhysics::Collision* collisionData)
{
	//Creating variables to use in math
	RigidBodyComponent* otherRigid = collisionData->collider->getRigidBody();
	Vector2 normal = collisionData->normal;
	float impulse;

	if (!otherRigid)
	{
		//Creating new temp rigid body
		otherRigid = new RigidBodyComponent();

		//Physics Math, for when one object has infinite mass
		impulse = 2 * getMass() * normal.dotProduct(getVelocity(), normal);
		Vector2 force = normal * impulse;

		applyForceToEntity(otherRigid, force);
		return;
	}
	else if (getMass() != otherRigid->getMass())
	{
		//Physics Math, for when both objects have different masses
		//Do Math
		return;
	}

	//Physics Math, for Collision Resolution/Response
	impulse = 2 * (normal.dotProduct(getVelocity() - otherRigid->getVelocity(), normal))
		/ normal.dotProduct(normal, normal) * (1 / getMass() + 1 / otherRigid->getMass());

	//Storing and applying force
	Vector2 force = normal * impulse;
	applyForceToEntity(otherRigid, force);
}
