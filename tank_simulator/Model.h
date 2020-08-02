#pragma once

#include <vector>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

class Model
{
private:
	int _count;
	const std::vector<float> _vertices, _normals, _uvs;

	static Model* fromOBJfile(const std::string&);

public:
	Model(const std::vector<float>&, const std::vector<float>&, const std::vector<float>&);
	void render() const;
	
	static void loadModels();
	static void deleteModels();

	static const Model *body, *turret, *cannon, *antenna1, *antenna2, *hatch, *frontLight, *rearLight, 
		*track, *engineWheel, *wheel, *smallWheel;
};

