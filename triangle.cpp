#include "stdafx.h"
#include "triangle.h"

const DWORD Vertex::FVF = D3DFVF_XYZ;

triangle::triangle()
{
}


triangle::~triangle()
{

}


bool triangle::init()    
{
	Device->CreateVertexBuffer(
		3 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&Triangle,
		0
	);

	Vertex* vertices;
	Triangle->Lock(0, 0, (void**)&vertices, 0);

	vertices[0] = Vertex(-1.0f, 0.0, 2.0f);
	vertices[1] = Vertex( 0.0f, 1.0, 2.0f);
	vertices[2] = Vertex( 1.0f, 0.0, 2.0f);

	Triangle->Unlock();

	return true;
}
void triangle::release() 
{

}
void triangle::update()	 
{

}
void triangle::render()	 
{
	Device->SetStreamSource(0, Triangle, 0, sizeof(Vertex));
	Device->SetFVF(Vertex::FVF);

	Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);	
}
