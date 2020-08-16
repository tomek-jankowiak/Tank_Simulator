#include "Teren.h"
#include "shaderProgram.h"


const Teren* Teren::grass;

Teren::Teren(const std::vector<float>& verts, const std::vector<float>& norms, const std::vector<float>& uvs) :
    _terVerts(verts), _terNorms(norms), _terUV(uvs), _terCount(verts.size() / 4)
{}


void Teren::prepareTeren(float size, float height, int max)
{
    std::vector<glm::vec3> tmpTerVerts;
    std::vector<float> terNorms, terUV, terVerts;

    for (int z = 0; z < max; z++) {
        for (int x = 0; x < max; x++) {
            //v0
            tmpTerVerts.push_back(glm::vec3(x * size, height, z * size));
            terUV.push_back(1.0f);
            terUV.push_back(0.0f);
            //v1
            tmpTerVerts.push_back(glm::vec3(x * size, height, (z + 1) * size));
            terUV.push_back(0.0f);
            terUV.push_back(0.0f);
            //v2
            tmpTerVerts.push_back(glm::vec3((x + 1) * size, height, z * size));
            terUV.push_back(1.0f);
            terUV.push_back(1.0f);
            //v3
            tmpTerVerts.push_back(glm::vec3((x + 1) * size, height, (z + 1) * size));
            terUV.push_back(0.0f);
            terUV.push_back(1.0f);
        }
        //degenerate triangles
        tmpTerVerts.push_back(glm::vec3(max * size, height, (z+1) * size));
        tmpTerVerts.push_back(glm::vec3(.0f, height, (z+1) * size));
    }

    int count = tmpTerVerts.size();
    for (int i = 0; i < count; i++) {
        glm::vec3 current = tmpTerVerts[i];
        glm::vec3 next = tmpTerVerts[(i + 1) % count];
        terVerts.push_back(current.x);
        terVerts.push_back(current.y);
        terVerts.push_back(current.z);
        terVerts.push_back(1.0f);

        glm::vec3 normal = glm::vec3(.0f, .0f, .0f);
        normal.x += (current.y - next.y) * (current.z + next.z);
        normal.y += (current.z - next.z) * (current.x + next.x);
        normal.z += (current.x - next.x) * (current.y + next.y);
        normalize(normal);
        terNorms.push_back(normal.x);
        terNorms.push_back(normal.y);
        terNorms.push_back(normal.z);
        terNorms.push_back(.0f);
    }

    grass = new Teren(terVerts, terNorms, terUV);
}

void Teren::renderTeren(glm::vec3 center) const {
    glm::mat4 terM = glm::mat4(1.0f);
    terM = glm::translate(terM, center);
    glUniformMatrix4fv(ShaderProgram::basicShader->u("M"), 1, false, glm::value_ptr(terM));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, _terVerts.data());
    glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, _terNorms.data());
    glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, _terUV.data());
    glDrawArrays(GL_TRIANGLE_STRIP, 0, _terCount);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}
