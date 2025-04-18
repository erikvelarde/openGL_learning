#pragma once

#ifndef CIRCLE_H
#define CIRCLE_H

#include <cmath>
#include <glad/glad.h>
// #include <vector>

class Circle {
    public:
	Circle(float x, float y, float radius, int segments);

	~Circle();

	void draw() const;

	void updateVertices(float aspectRatio);

	void move(float dx, float dy, float minBound, float maxBound);

	float getX() const;
	float getY() const;
	float getRadius() const;

    private:
	float x, y;
	float radius;
	int segments;
	unsigned int VAO, VBO;

	void setupBuffers();
};

#endif // !CIRCLE_H
