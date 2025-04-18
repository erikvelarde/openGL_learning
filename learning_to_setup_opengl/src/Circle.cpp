#include "../include/Circle.h"
#include <vector>

Circle::Circle(float x, float y, float radius, int segments)
	: x(x)
	, y(y)
	, radius(radius)
	, segments(segments)
{
	setupBuffers();
}

Circle::~Circle()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Circle::draw() const
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, segments + 2);
	glBindVertexArray(0);
}

void Circle::updateVertices(float aspectRatio)
{
	std::vector<float> vertices;
	vertices.push_back(x);
	vertices.push_back(y);

	for (int i = 0; i <= segments; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(segments);
		float xPos = radius * cosf(theta);
		float yPos = radius * sinf(theta) * aspectRatio;
		vertices.push_back(x + xPos);
		vertices.push_back(y + yPos);
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
		     vertices.data(), GL_STATIC_DRAW);
}

void Circle::move(float dx, float dy, float minBound, float maxBound)
{
	x = x + dx;
	y = y + dy;

	if (x < minBound) x = minBound;
	if (x > maxBound) x = maxBound;
	if (y < minBound) y = minBound;
	if (y > maxBound) y = maxBound;
}

float Circle::getX() const
{
	return x;
}
float Circle::getY() const
{
	return y;
}
float Circle::getRadius() const
{
	return radius;
}

void Circle::Circle::setupBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
			      (void *)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

;
