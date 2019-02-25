#pragma once
#include "Shaders.h"
#include "../Utilities/Mesh.h"
#include "../Utilities/TextureData.h"
#include <string>
using namespace std;

class Object
{
private:
	Mesh* meshPointer;
public:
	Object(int numObject, string* objectPath);
	~Object();
};

