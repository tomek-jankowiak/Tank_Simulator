#include "Model.h"

#include <fstream>

const Model *Model::antenna1, *Model::antenna2, *Model::body, *Model::cannon, *Model::hatch, *Model::leftEngineWheel,
	*Model::leftSmallWheel, *Model::leftWheel, *Model::frontLight, *Model::rearLight, *Model::machineGun,
	*Model::rightEngineWheel, *Model::rightSmallWheel, *Model::rightWheel, *Model::track, *Model::turret;


Model::Model(const std::vector<float>& vertices, const std::vector<float>& normals, const std::vector<float>& uvs, const std::vector<float>& tangents, 
	const std::vector<float>& bitangents) :
	_vertices(vertices), _normals(normals), _uvs(uvs), _tangents(tangents), _bitangents(bitangents),_count(vertices.size() / 4)
{}

void Model::render() const
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, _vertices.data());
	glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, _normals.data());
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, _uvs.data());
	glDrawArrays(GL_TRIANGLES, 0, _count);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Model::renderNormalMapping() const
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, _vertices.data());
	glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, _normals.data());
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, _uvs.data());
	glVertexAttribPointer(3, 4, GL_FLOAT, false, 0, _tangents.data());
	glVertexAttribPointer(4, 4, GL_FLOAT, false, 0, _bitangents.data());
	glDrawArrays(GL_TRIANGLES, 0, _count);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
}

void Model::loadModels()
{	antenna1 = fromOBJfile("models/antenna_1.obj");
	antenna2 = fromOBJfile("models/antenna_2.obj");
	body = fromOBJfile("models/body.obj");
	cannon = fromOBJfile("models/cannon.obj");
	hatch = fromOBJfile("models/hatch.obj");
	leftEngineWheel = fromOBJfile("models/left_engine_wheel.obj");
	leftSmallWheel = fromOBJfile("models/left_small_wheel.obj");
	leftWheel = fromOBJfile("models/left_wheel.obj");
	frontLight = fromOBJfile("models/light_front.obj");
	rearLight = fromOBJfile("models/light_rear.obj");
	machineGun = fromOBJfile("models/machine_gun.obj");
	rightEngineWheel = fromOBJfile("models/right_engine_wheel.obj");
	rightSmallWheel = fromOBJfile("models/right_small_wheel.obj");
	rightWheel = fromOBJfile("models/right_wheel.obj");
	track = fromOBJfile("models/track.obj");
	turret = fromOBJfile("models/turret.obj");

	printf("Models loaded.\n");
}

void Model::deleteModels()
{
	delete antenna1;
	delete antenna2;
	delete body;
	delete cannon;
	delete hatch;
	delete leftEngineWheel;
	delete leftSmallWheel;
	delete leftWheel;
	delete frontLight;
	delete rearLight;
	delete machineGun;
	delete rightEngineWheel;
	delete rightSmallWheel;
	delete rightWheel;
	delete track;
	delete turret;
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

	std::vector<float> vertices, normals, uvs, tangents, bitangents;
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

	tmpVertices.clear();
	tmpNormals.clear();
	tmpUvs.clear();
	for (int i = 0; i < vertices.size(); i += 4) {
		tmpVertices.push_back(glm::vec4(vertices[i], vertices[i + 1], vertices[i + 2], vertices[i + 3]));
		tmpNormals.push_back(glm::vec4(normals[i], normals[i + 1], normals[i + 2], normals[i + 3]));
	}
	for (int i = 0; i < uvs.size(); i+=2) {
		tmpUvs.push_back(glm::vec2(uvs[i], uvs[i + 1]));
	}

	for (int i = 0; i < tmpVertices.size(); i += 3) {
		glm::vec3 v0 = tmpVertices[i];
		glm::vec3 v1 = tmpVertices[i + 1];
		glm::vec3 v2 = tmpVertices[i + 2];

		glm::vec2 uv0 = tmpUvs[i];
		glm::vec2 uv1 = tmpUvs[i + 1];
		glm::vec2 uv2 = tmpUvs[i + 2];

		glm::vec3 deltaPos1 = v1 - v0;
		glm::vec3 deltaPos2 = v2 - v0;

		glm::vec2 deltaUV1 = uv1 - uv0;
		glm::vec2 deltaUV2 = uv2 - uv0;

		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		glm::vec4 tangent = glm::vec4((deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r, 0.0f);
		glm::vec4 bitangent = glm::vec4((deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r, 0.0f);

		for (int j = 0; j < 3; j++) {
			tangents.push_back(tangent.x);
			tangents.push_back(tangent.y);
			tangents.push_back(tangent.z);
			tangents.push_back(tangent.w);

			bitangents.push_back(bitangent.x);
			bitangents.push_back(bitangent.y);
			bitangents.push_back(bitangent.z);
			bitangents.push_back(bitangent.w);
		}
	}

	file.close();

	return new Model(vertices, normals, uvs, tangents, bitangents);
}

