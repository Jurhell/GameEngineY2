#pragma once
#include "ColliderComponent.h"

namespace GamePhysics
{
	class AABBColliderComponent : public ColliderComponent
	{
	public:
		AABBColliderComponent(float width, float height) : ColliderComponent() { m_width = width; m_height = height; };

		GamePhysics::Collision* checkCollisionCircle(CircleColliderComponent* other) override;
		GamePhysics::Collision* checkCollisionAABB(AABBColliderComponent* other) override;

		void draw() override;

		float getWidth() { return m_width; }
		float getHeight() { return m_height; }
		float getRadius() { return m_radius; };

	private:
		float m_width;
		float m_height;
		float m_radius;
	};
}