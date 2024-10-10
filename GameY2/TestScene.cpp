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

void TestScene::onStart()
{
	//Set up circle
	m_circle1 = new GameEngine::Entity();
	m_circle1->getTransform()->setLocalScale({ 30, 30 });
	m_circle1->getTransform()->setLocalPosition({ 400, 175 });
	m_circle1->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CIRCLE);
	m_circle1->addComponent(new GamePhysics::CircleColliderComponent(31));
	m_circle1->addComponent(new GamePhysics::RigidBodyComponent());
	//m_circle1->getComponent<GamePhysics::RigidBodyComponent>()->setGravity(0);
	addEntity(m_circle1);

	//Set up box
	m_box = new GameEngine::Entity();
	m_box->getTransform()->setLocalScale({ 50, 50 });
	m_box->getTransform()->setLocalPosition({ 545, 400 });
	m_box->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);
	m_box->addComponent(new GamePhysics::AABBColliderComponent(60, 60));
	m_box->addComponent(new GamePhysics::RigidBodyComponent());
	//m_box->getComponent<GamePhysics::RigidBodyComponent>()->setGravity(0);
	addEntity(m_box);

	//Set up circle 2
	m_circle2 = new  GameEngine::Entity();
	m_circle2->getTransform()->setLocalScale({ 30, 30 });
	m_circle2->getTransform()->setLocalPosition({ 545, 100 });
	m_circle2->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CIRCLE);
	m_circle2->addComponent(new GamePhysics::CircleColliderComponent(31));
	m_circle2->addComponent(new GamePhysics::RigidBodyComponent());
	//addEntity(m_circle2);

	//Set up floor
	m_floor = new GameEngine::Entity();
	m_floor->getTransform()->setLocalScale({ 1000, 50 });
	m_floor->getTransform()->setLocalPosition({ 400, 800 });
	m_floor->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);
	m_floor->addComponent(new GamePhysics::AABBColliderComponent(1010, 60));
	addEntity(m_floor);

#pragma region Walls

	//Set up ceiling
	m_ceiling = new GameEngine::Entity();
	m_ceiling->getTransform()->setLocalScale({ 1000, 50 });
	m_ceiling->getTransform()->setLocalPosition({ 400, 0 });
	m_ceiling->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);
	m_ceiling->addComponent(new GamePhysics::AABBColliderComponent(1010, 60));
	addEntity(m_ceiling);

	//Set up first wall
	m_wall1 = new GameEngine::Entity();
	m_wall1->getTransform()->setLocalScale({ 50, 1500 });
	m_wall1->getTransform()->setLocalPosition({0, 0});
	m_wall1->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);
	m_wall1->addComponent(new GamePhysics::AABBColliderComponent(60, 1510));
	//addEntity(m_wall1);

#pragma endregion
}

void TestScene::onUpdate(double deltaTime)
{
	//GameMath::Vector2 position = m_circle1->getTransform()->getLocalPosition();
	//GameMath::Vector2 deltaPosition = { 50, 0 };
	//m_circle1->getTransform()->setLocalPosition(position + deltaPosition * deltaTime);
}
