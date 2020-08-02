#include "Model.h"

#include <fstream>

const Model *Model::body, *Model::turret, *Model::cannon, *Model::antenna1, *Model::antenna2, *Model::hatch, *Model::frontLight, 
	*Model::rearLight, *Model::track, *Model::engineWheel, *Model::wheel, *Model::smallWheel;


Model::Model(const std::vector<float>& vertices, const std::vector<float>& normals, const std::vector<float>& uvs) :
	_vertices(vertices), _normals(normals), _uvs(uvs), _count(vertices.size() / 4)
{}

void Model::render() const
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, _vertices.data());
	glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, _normals.data());
	glVertexAttribPointer(2, 4, GL_FLOAT, false, 0, _uvs.data());
	glDrawArrays(GL_TRIANGLES, 0, _count);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Model::loadModels()
{
	body = fromOBJfile("models/body.obj");
	turret = fromOBJfile("models/turret.obj");
	cannon = fromOBJfile("models/cannon.obj");
	//antenna1 = fromOBJfile("models/antenna_1.obj");
	//antenna2 = fromOBJfile("models/antenna_2.obj");
	//hatch = fromOBJfile("models/hatch.obj");
	//frontLight = fromOBJfile("models/light_front.obj");
	//rearLight = fromOBJfile("models/light_rear.obj");
	//track = fromOBJfile("models/track.obj");
	//engineWheel = fromOBJfile("models/engine_wheel.obj");
	//wheel = fromOBJfile("model/wheel.obj");
	//smallWheel = fromOBJfile("models/small_wheel.obj");
}

void Model::deleteModels()
{
	delete body;
	delete turret;
	delete cannon;
	delete antenna1;
	delete antenna2;
	delete hatch;
	delete frontLight;
	delete rearLight;
	delete track;
	delete engineWheel;
	delete wheel;
	delete smallWheel;
}

Model* Model::fromOBJfile(const std::string& filename)
{
	std::vector<glm::vec4> tmpVertices, tmpNormals;
	std::vector<glm::vec2> tmpUvs;
	std::vector<unsigned int> vertexIndices, normalIndices, uvIndices;
	std::ifstream file(filename);
	std::string head, line;
	float x, y, z;
	unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

	while (file >> head) {
		if (head == "v") {
			file >> x >> y >> z;
			tmpVertices.push_back(glm::vec4(x, y, z, 1.0f));
		}
		else if (head == "vt") {
			file >> x >> y;
			tmpUvs.push_back(glm::vec2(x, y));
		}
		else if (head == "vn") {
			file >> x >> y >> z;
			tmpNormals.push_back(glm::vec4(x, y, z, .0f));
		}
		else if (head == "f") {
			std::getline(file, line);
			if (sscanf_s(line.c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d", vertexIndex, uvIndex, normalIndex,
				vertexIndex + 1, uvIndex + 1, normalIndex + 1, vertexIndex + 2, uvIndex + 2, normalIndex + 2) != 9)
				return nullptr;
			vertexIndices.push_back(vertexIndex[0] - 1);
			vertexIndices.push_back(vertexIndex[1] - 1);
			vertexIndices.push_back(vertexIndex[2] - 1);
			uvIndices.push_back(uvIndex[0] - 1);
			uvIndices.push_back(uvIndex[1] - 1);
			uvIndices.push_back(uvIndex[2] - 1);
			normalIndices.push_back(normalIndex[0] - 1);
			normalIndices.push_back(normalIndex[1] - 1);
			normalIndices.push_back(normalIndex[2] - 1);
		}
	}

	std::vector<float> vertices, normals, uvs;
	for (int i = 0; i < vertexIndices.size(); i++) {
		glm::vec4 vertex = tmpVertices[vertexIndices[i]];
		vertices.push_back(vertex.x);
		vertices.push_back(vertex.y);
		vertices.push_back(vertex.z);
		vertices.push_back(vertex.w);
	}
	for (int i = 0; i < normalIndices.size(); i++) {
		glm::vec4 normal = tmpNormals[normalIndices[i]];
		normals.push_back(normal.x);
		normals.push_back(normal.y);
		normals.push_back(normal.z);
		normals.push_back(normal.w);
	}
	for (int i = 0; i < uvIndices.size(); i++) {
		glm::vec2 uv = tmpUvs[uvIndices[i]];
		uvs.push_back(uv.x);
		uvs.push_back(uv.y);
	}

	file.close();

	return new Model(vertices, normals, uvs);
}

