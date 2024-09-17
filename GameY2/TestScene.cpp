#include "TestScene.h"
#include "Engine/Entity.h"
#include "Graphics/ShapeComponent.h"
#include "Engine/TransformComponent.h"
#include "Physics/AABBColliderComponent.h"
#include "Physics/CircleColliderComponent.h"
#include "Physics/RigidBodyComponent.h"
#include <chrono>
#include <cmath>

using namespace GameEngine;
using namespace GameMath;
using namespace GameGraphics;
using namespace std::chrono;

void TestScene::onStart()
{
	//Set up circle 1
	m_circle1 = new GameEngine::Entity();
	m_circle1->getTransform()->setLocalScale({ 40, 40 });
	m_circle1->getTransform()->setLocalPosition({ 100, 100 });
	m_circle1->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CIRCLE);
	m_circle1->addComponent(new GamePhysics::CircleColliderComponent(50));
	m_circle1->addComponent(new GamePhysics::RigidBodyComponent());
	//m_circle1->getComponent<GamePhysics::RigidBodyComponent>()->setGravity(0);
	addEntity(m_circle1);

	//Set up circle 2
	/*m_circle2 = new  GameEngine::Entity();
	m_circle2->getTransform()->setLocalScale({ 40, 40 });
	m_circle2->getTransform()->setLocalPosition({ 600, 100 });
	m_circle2->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CIRCLE);
	m_circle2->addComponent(new GamePhysics::CircleColliderComponent(50));
	m_circle2->addComponent(new GamePhysics::RigidBodyComponent());
	addEntity(m_circle2);*/

	//Set up box
	m_aabb = new GameEngine::Entity();
	m_aabb->getTransform()->setLocalScale({ 50, 50 });
	m_aabb->getTransform()->setLocalPosition({ 145, 400 });
	m_aabb->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);
	m_aabb->addComponent(new GamePhysics::AABBColliderComponent(60, 60));
	m_aabb->addComponent(new GamePhysics::RigidBodyComponent());
	m_aabb->getComponent<GamePhysics::RigidBodyComponent>()->setGravity(0);
	addEntity(m_aabb);

	//Set up floor
	m_floor = new GameEngine::Entity();
	m_floor->getTransform()->setLocalScale({ 1000, 100 });
	m_floor->getTransform()->setLocalPosition({ 400, 750 });
	m_floor->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);
	m_floor->addComponent(new GamePhysics::AABBColliderComponent(1010, 110));
	//m_floor->addComponent(new GamePhysics::RigidBodyComponent());
	//m_floor->getComponent<GamePhysics::RigidBodyComponent>()->setGravity(0);
	addEntity(m_floor);
}

void TestScene::onUpdate(double deltaTime)
{
	//GameMath::Vector2 position = m_circle1->getTransform()->getLocalPosition();
	//GameMath::Vector2 deltaPosition = { 50, 0 };
	//m_circle1->getTransform()->setLocalPosition(position + deltaPosition * deltaTime);
}
