#include <cmath>
#include "SMovement.h"

SMovement::SMovement() {}

SMovement::SMovement(Vec2 movAreaSize)
	: m_movAreaSize(movAreaSize) {}

void SMovement::process(EntityManager& entities)
{
	for (std::shared_ptr<Entity>& e : entities.getEntities())
	{
		if (e->cTransform && e->cShape)
		{
			if (e->cInput)
			{
				applyMovementFromInput(e);
			}
			else
			{
				bounceOnScreenEdges(e);
			}

			if (e->cMouseInput)
			{
				applyMovementFromMouseInput(e);
			}

			sf::Shape& shape = e->cShape->shape;
			Vec2 newPos = e->cTransform->pos + e->cTransform->velocity;
			shape.setPosition(newPos.x, newPos.y);

			e->cTransform->angle += e->cTransform->rotationVelocity;
			if (e->cTransform->angle > 360)
			{
				e->cTransform->angle = 0;
			}
			shape.setRotation(e->cTransform->angle);
		}
	}
}

void SMovement::applyMovementFromInput(std::shared_ptr<Entity>& e)
{
	double velocity = e->cTransform->maxVelocity;
	if (e->cInput->right)
	{
		double rightVelocity = adaptVelocityToStayInsideMovArea(
			(float) e->cTransform->pos.x + (e->cShape->shape.getLocalBounds().width / 2),
			(float) m_movAreaSize.x,
			velocity);
		e->cTransform->velocity.x = rightVelocity;
	}
	else if (e->cInput->left)
	{
		double leftVelocity = adaptVelocityToStayInsideMovArea(
			(float) e->cTransform->pos.x - (e->cShape->shape.getLocalBounds().width / 2),
			0.0f,
			velocity);
		e->cTransform->velocity.x = -1 * leftVelocity;
	}
	else
	{
		e->cTransform->velocity.x = 0;
	}

	if (e->cInput->up)
	{
		double upVelocity = adaptVelocityToStayInsideMovArea(
			(float) e->cTransform->pos.y - (e->cShape->shape.getLocalBounds().height / 2),
			0.0f,
			velocity);

		e->cTransform->velocity.y = -1 * upVelocity;
	}
	else if (e->cInput->down)
	{
		double downVelocity = adaptVelocityToStayInsideMovArea(
			(float) e->cTransform->pos.y + (e->cShape->shape.getLocalBounds().height / 2),
			(float) m_movAreaSize.y,
			velocity);
		e->cTransform->velocity.y = downVelocity;
	}
	else
	{
		e->cTransform->velocity.y = 0;
	}
}

void SMovement::applyMovementFromMouseInput(std::shared_ptr<Entity>& e)
{
	if (e->cMouseInput->moved || e->cInput->up || e->cInput->down || e->cInput->left || e->cInput->right)
	{
		double mAngle = calculateMouseAngle(e->cTransform->pos, e->cMouseInput->pos);
		e->cTransform->angle = mAngle;
	}
}

void SMovement::bounceOnScreenEdges(std::shared_ptr<Entity>& e)
{
	if (e->cTransform->pos.x + (e->cShape->shape.getLocalBounds().width / 2) >= m_movAreaSize.x
			|| e->cTransform->pos.x - (e->cShape->shape.getLocalBounds().width / 2) <= 0)
	{
		e->cTransform->velocity.x *= -1;
	}

	if (e->cTransform->pos.y + (e->cShape->shape.getLocalBounds().height / 2) >= m_movAreaSize.y
			|| e->cTransform->pos.y - (e->cShape->shape.getLocalBounds().height / 2) <= 0)
	{
		e->cTransform->velocity.y *= -1;
	}
}

double SMovement::adaptVelocityToStayInsideMovArea(float pos, float limit, double velocity)
{
	float distanceUntilBorder = fabs(limit - pos);
	if (distanceUntilBorder < velocity)
	{
		velocity = distanceUntilBorder;
	}

	return velocity;
}

double SMovement::calculateMouseAngle(Vec2 ep, Vec2 mp)
{
	Vec2 distance = mp - ep;
	return atan2(distance.y, distance.x) * (180 / M_PI);
}
