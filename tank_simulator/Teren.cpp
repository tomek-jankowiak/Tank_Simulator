#include "Teren.h"
#include "shaderProgram.h"


const Teren* Teren::trawa;

Teren::Teren(const std::vector<float>& vertices) :
    terVerts(vertices), terCount(vertices.size() / 4)
{}


void Teren::przygotujTeren(float size, float height, int max)
{
    std::vector<float> tmpTerVerts;

    for (int z = 0; z < max; z++) {
        for (int x = 0; x < max; x++) {
            //v0
            tmpTerVerts.push_back(x * size);
            tmpTerVerts.push_back(height);
            tmpTerVerts.push_back(z * size);
            tmpTerVerts.push_back(1.0f);
            //v1
            tmpTerVerts.push_back(x * size);
            tmpTerVerts.push_back(height);
            tmpTerVerts.push_back((z+1) * size);
            tmpTerVerts.push_back(1.0f);
            //v2
            tmpTerVerts.push_back((x+1) * size);
            tmpTerVerts.push_back(height);
            tmpTerVerts.push_back(z * size);
            tmpTerVerts.push_back(1.0f);
            //v3
            tmpTerVerts.push_back((x+1) * size);
            tmpTerVerts.push_back(height);
            tmpTerVerts.push_back((z+1) * size);
            tmpTerVerts.push_back(1.0f);
        }
        //degenerate triangles
        tmpTerVerts.push_back(max * size);
        tmpTerVerts.push_back(height);
        tmpTerVerts.push_back(z * size);
        tmpTerVerts.push_back(1.0f);

        tmpTerVerts.push_back(0.0f);
        tmpTerVerts.push_back(height);
        tmpTerVerts.push_back(z * size);
        tmpTerVerts.push_back(1.0f);
    }

    trawa = new Teren(tmpTerVerts);
}

void Teren::renderTeren(glm::vec3 center) const {
    glm::mat4 terM = glm::mat4(1.0f);
    terM = glm::translate(terM, center);
    glUniformMatrix4fv(ShaderProgram::basicShader->u("M"), 1, false, glm::value_ptr(terM));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, terVerts.data());
    glDrawArrays(GL_TRIANGLE_STRIP, 0, terCount);
    glDisableVertexAttribArray(0);
}
