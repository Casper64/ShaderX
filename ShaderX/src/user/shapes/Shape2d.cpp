#include "pch.h"
#include "Shape2d.h"


double Shape2d::Area()
{
	double area, sum1, sum2;
	int size = vertices.size() - 1;
	sum1 = sum2 = 0.0;
	for (int i = 0; i < size; i++) {
		sum1 += (double)vertices[i].x * (double)vertices[(i + 1)].y;
		sum2 += (double)vertices[(i + 1)].x * (double)vertices[i].y;
	}
	sum1 += (double)vertices[size].x * (double)vertices[0].y;
	sum2 += (double)vertices[0].x * (double)vertices[size].y;
	area = abs(sum1 - sum2) / 2.0;
	return area;
}

void Shape2d::printVertices()
{
	printf("number of vertices = %d\n", vertices.size());
	for (int i = 0; i < vertices.size(); i++) {
		printf("x: %f, y: %f\n", vertices[i].x, vertices[i].y);
	}
}
