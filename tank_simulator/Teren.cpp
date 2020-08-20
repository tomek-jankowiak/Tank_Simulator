#include "Teren.h"
#include "shaderProgram.h"
#include "Texture.h"


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
            terUV.push_back(x * size / 3);
            terUV.push_back(z * size / 3);
            //v1
            tmpTerVerts.push_back(glm::vec3(x * size, height, (z + 1) * size));
            terUV.push_back(x * size / 3);
            terUV.push_back((z + 1) * size / 3);
            //v2
            tmpTerVerts.push_back(glm::vec3((x + 1) * size, height, z * size));
            terUV.push_back((x + 1) * size / 3);
            terUV.push_back(z * size / 3);
            //v3
            tmpTerVerts.push_back(glm::vec3((x + 1) * size, height, (z + 1) * size));
            terUV.push_back((x + 1) * size / 3);
            terUV.push_back((z + 1) * size / 3);
        }
        //degenerate triangles
        tmpTerVerts.push_back(glm::vec3(max * size, height, (z + 1) * size));
        terUV.push_back(max * size / 3);
        terUV.push_back((z + 1) * size / 3);
        tmpTerVerts.push_back(glm::vec3(.0f, height, (z + 1) * size));
        terUV.push_back(.0f);
        terUV.push_back((z + 1) * size / 3);
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
        if (normal == glm::vec3(.0f, .0f, .0f))
            normal.y = 1.0f;
        if (normal.y < 0)
            normal.y = -normal.y;
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
    glUniformMatrix4fv(ShaderProgram::terenShader->u("M"), 1, false, glm::value_ptr(terM));

    glUniform1f(ShaderProgram::terenShader->u("maxFurLength"), 0.1f);
    // while changing the value below: remember to change the corresponding value in `glDrawArraysInstanced`
    glUniform1f(ShaderProgram::terenShader->u("maxLayer"), 20);
    
    glUniform1i(ShaderProgram::terenShader->u("texMap0"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture::grassPattern);

    glUniform1i(ShaderProgram::terenShader->u("texMap1"), 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, Texture::grass);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, _terVerts.data());
    glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, _terNorms.data());
    glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, _terUV.data());
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, _terCount, 20);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void Teren::deleteTeren()
{
    delete grass;
}