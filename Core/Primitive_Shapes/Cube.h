#pragma once
#include "PrimitiveObject.h"


class Cube : public PrimitiveObject
{
	public:
	Cube() : PrimitiveObject(CUBE)
	{
		_vertices = {
			// positions        // texture Coords
			-0.5f, -0.5f, -0.5f, 
			0.5f, -0.5f, -0.5f, 
			0.5f,  0.5f, -0.5f, 
			0.5f,  0.5f, -0.5f, 
			-0.5f,  0.5f, -0.5f, 
			-0.5f, -0.5f, -0.5f, 

			-0.5f, -0.5f,  0.5f, 
			0.5f, -0.5f,  0.5f, 
			0.5f,  0.5f,  0.5f, 
			0.5f,  0.5f,  0.5f, 
			-0.5f,  0.5f,  0.5f, 
			-0.5f, -0.5f,  0.5f, 

			-0.5f,  0.5f,  0.5f, 
			-0.5f,  0.5f, -0.5f, 
			-0.5f, -0.5f, -0.5f, 
			-0.5f, -0.5f, -0.5f, 
			-0.5f, -0.5f,  0.5f, 
			-0.5f,  0.5f,  0.5f, 

			0.5f,  0.5f,  0.5f, 
			0.5f,  0.5f, -0.5f, 
			0.5f, -0.5f, -0.5f, 
			0.5f, -0.5f, -0.5f, 
			0.5f, -0.5f,  0.5f, 
			0.5f,  0.5f,  0.5f, 

			-0.5f, -0.5f, -0.5f, 
			0.5f, -0.5f, -0.5f, 
			0.5f, -0.5f,  0.5f, 
			0.5f, -0.5f,  0.5f, 
			-0.5f, -0.5f,  0.5f, 
			-0.5f, -0.5f, -0.5f, 

			-0.5f,  0.5f, -0.5f, 
			0.5f,  0.5f, -0.5f, 
			0.5f,  0.5f,  0.5f, 
			0.5f,  0.5f,  0.5f, 
			-0.5f,  0.5f,  0.5f, 
			-0.5f,  0.5f, -0.5f, 
		};
		setUpBuffers();
	}
	void draw() override;

	private:
	void setUpBuffers();

};


