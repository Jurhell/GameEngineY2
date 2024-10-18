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
	m_circle1->getTransform()->setLocalPosition({ 625, 175 });
	m_circle1->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CIRCLE);
	m_circle1->addComponent(new GamePhysics::CircleColliderComponent(31));
	m_circle1->addComponent(new GamePhysics::RigidBodyComponent());
	//m_circle1->getComponent<GamePhysics::RigidBodyComponent>()->setGravity(0);
	addEntity(m_circle1);

	//Set up box
	m_box = new GameEngine::Entity();
	m_box->getTransform()->setLocalScale({ 50, 50 });
	m_box->getTransform()->setLocalPosition({ 400, 700 });
	m_box->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);
	m_box->addComponent(new GamePhysics::AABBColliderComponent(60, 60));
	m_box->addComponent(new GamePhysics::RigidBodyComponent());
	//m_box->getComponent<GamePhysics::RigidBodyComponent>()->setGravity(0);
	addEntity(m_box);

	//Set up circle 2
	m_circle2 = new  GameEngine::Entity();
	m_circle2->getTransform()->setLocalScale({ 30, 30 });
	m_circle2->getTransform()->setLocalPosition({ 625, 100 });
	m_circle2->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CIRCLE);
	m_circle2->addComponent(new GamePhysics::CircleColliderComponent(31));
	m_circle2->addComponent(new GamePhysics::RigidBodyComponent());
	m_circle2->getComponent<GamePhysics::RigidBodyComponent>()->setMass(2);
	//addEntity(m_circle2);

#pragma region Room

	//Set up floor
	m_floor = new GameEngine::Entity();
	m_floor->getTransform()->setLocalScale({ 790, 50 });
	m_floor->getTransform()->setLocalPosition({ 400, 800 });
	m_floor->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);
	m_floor->addComponent(new GamePhysics::AABBColliderComponent(800, 60));
	addEntity(m_floor);

	//Set up ceiling
	m_ceiling = new GameEngine::Entity();
	m_ceiling->getTransform()->setLocalScale({ 790, 50 });
	m_ceiling->getTransform()->setLocalPosition({ 400, 0 });
	m_ceiling->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);
	m_ceiling->addComponent(new GamePhysics::AABBColliderComponent(800, 60));
	addEntity(m_ceiling);

	//Set up first wall
	m_wall1 = new GameEngine::Entity();
	m_wall1->getTransform()->setLocalScale({ 50, 700 });
	m_wall1->getTransform()->setLocalPosition({0, 400});
	m_wall1->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);
	m_wall1->addComponent(new GamePhysics::AABBColliderComponent(60, 710));
	addEntity(m_wall1);

	//Set up second wall
	m_wall2 = new GameEngine::Entity();
	m_wall2->getTransform()->setLocalScale({ 50, 700 });
	m_wall2->getTransform()->setLocalPosition({ 800, 400 });
	m_wall2->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);
	m_wall2->addComponent(new GamePhysics::AABBColliderComponent(60, 710));
	//addEntity(m_wall2);

#pragma endregion
}

void TestScene::onUpdate(double deltaTime)
{
	//GameMath::Vector2 position = m_circle1->getTransform()->getLocalPosition();
	//GameMath::Vector2 deltaPosition = { 50, 0 };
	//m_circle1->getTransform()->setLocalPosition(position + deltaPosition * deltaTime);
}
