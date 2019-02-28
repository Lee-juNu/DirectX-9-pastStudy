#pragma once

struct Vertex
{
	Vertex() {}

	Vertex(float x, float y, float z)
	{
		_x = x;	 _y = y;  _z = z;
	}

	float _x, _y, _z;

	static const DWORD FVF;
};

class triangle
{

private:
	IDirect3DVertexBuffer9* Triangle = 0; // vertex buffer to store

public:
	triangle();
	~triangle();

	bool init();
	void release();
	void update();
	void render();
};

