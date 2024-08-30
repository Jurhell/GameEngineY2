#include "TestScene.h"
#include "Engine/Entity.h"
#include "Graphics/ShapeComponent.h"
#include "Engine/TransformComponent.h"
#include <chrono>
#include <cmath>

using namespace GameEngine;
using namespace GameMath;
using namespace GameGraphics;
using namespace std::chrono;

void TestScene::onStart()
{
	Entity* m_test = new Entity();
	m_test->getTransform()->setLocalScale({ 100, 100 });
	m_test->getTransform()->setLocalPosition({ 400, 400 });

	ShapeComponent* testShape = new ShapeComponent();
	testShape->setShapeType(ShapeType::CIRCLE);
	testShape->setColor(0xFFFFFFFF);
	m_test->addComponent(testShape);

	addEntity(m_test);
}

void TestScene::onUpdate(double deltaTime)
{
	//float currentTime = duration_cast<seconds>(high_resolution_clock::now().time_since_epoch()).count();

	//m_accumulatedTime += deltaTime;
	//
	//float circleRadius = 100;
	//float speedScale = 0.5f;
	//Vector2 newPosition = { sin(m_accumulatedTime * speedScale) * circleRadius + 400, cos(m_accumulatedTime * speedScale) * circleRadius + 400 };
	//m_test->getTransform()->setLocalPosition(newPosition);
}
