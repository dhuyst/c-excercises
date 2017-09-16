#include "renderer.h"

#include <iostream>

namespace Draw {

void Renderer::Render(Scenes& scenes)
{
	for (auto& scene : scenes) {
		Render(scene);
		window.Display(surface);
		Display::Delay(5000);		
	}
}

void Renderer::Render(Scene& scene)
{
	for (auto& shape : scene.GetShapes()) {
		Render(shape);
	}
}

void Renderer::Render(Shape& shape)
{
	for (auto& primitive : shape.GetPrimitives()){

		std::cout << *primitive << std::endl;

		if (dynamic_cast<Point*>(primitive.get()))
		{
			Render(dynamic_cast<Point&>(*primitive));
		}
		else if (dynamic_cast<Line*>(primitive.get()))
		{
			Render(dynamic_cast<Line&>(*primitive));
		}
		else
		{
			Render(dynamic_cast<Triangle&>(*primitive));
		}
	}

}

void Renderer::Render(Point& point)
{
	Vector3D v = point.idx0->vector;
	Color color = point.idx0->color;

	Pixel pixel;
	pixel.x = v.x * surfaceWidth/20;
	pixel.y = v.y * surfaceHeight/20;
	SetPixel(pixel, color);
}

void Renderer::Render(Line& line)
{
	Vector3D v1 = line.idx0->vector;
	Color color1 = line.idx0->color;

	Vector3D v2 = line.idx1->vector;
	Color color2 = line.idx1->color;

	Pixel pixel;
	pixel.x = v1.x;
	pixel.y = v2.y;
	SetPixel(pixel, color1);
}

void Renderer::Render(Triangle& triangle)
{

}

void Renderer::SetPixel(Pixel p, Color c)
{
	std::cout << "SetPixel(" << p.x << "," << p.y << "," << c << ")" << std::endl;
	surface.SetPixel(p.x, p.y, c.r, c.g, c.b);
}

Display::Window Renderer::DefaultWindow()
{
	return Display::Window("Hello", 10, 10, 800, 600);
}

Display::Surface Renderer::DefaultSurface()
{
	return Display::Surface(200,150);
}

Renderer::Renderer(int surfaceWidth, int surfaceHeight):
window(DefaultWindow()), surface(DefaultSurface()),
surfaceWidth(surfaceWidth), surfaceHeight(surfaceHeight) {}

}
