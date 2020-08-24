#include "particleGenerator.h"

#include "glm/gtc/matrix_transform.hpp"

ParticleGenerator* ParticleGenerator::gunpoint;


ParticleGenerator::ParticleGenerator(const std::vector<float>& verts, Camera* cam)
{
    _parVerts = verts;
    _parCount = verts.size() / 4;
    _camera = cam;

    for (int i = 0; i < PARTICLE_AMOUNT; i++)
        _allParticles.push_back(Particle());
}

void ParticleGenerator::prepareParticles(Camera* cam)
{
    float singleParticleVerts[] = {
        0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 1.0f
    };
    std::vector<float> verts;
    for (int i = 0; i < 16; i ++) {
        verts.push_back(singleParticleVerts[i]);
    }
    gunpoint = new ParticleGenerator(verts, cam);
}

bool ParticleGenerator::renderParticles(glm::mat4 V, glm::mat4 M)
{
    updateParticles();

    if (_lifeLeft > 0.0f)
    {
        glm::mat4 gunpointM = glm::translate(M, glm::vec3(0, 0, -2.0f));
        // canceling out rotation in the view matrix so that particles always face the camera
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                gunpointM[col][row] = V[row][col];
            }
        }
        glUniformMatrix4fv(ShaderProgram::particleShader->u("V"), 1, false, glm::value_ptr(V));

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, _parVerts.data());
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        for (int i = 0; i < PARTICLE_AMOUNT; i++) {
            Particle& p = _allParticles[i];

            glm::mat4 tmpM = glm::translate(gunpointM, p.parPosition);
            tmpM = glm::scale(tmpM, glm::vec3(p.parScale));
            glUniformMatrix4fv(ShaderProgram::terenShader->u("M"), 1, false, glm::value_ptr(tmpM));

            std::vector<float> uv;
            for (int i = 0; i < 4; i++) {
                uv.push_back(p.parColor.r);
                uv.push_back(p.parColor.g);
                uv.push_back(p.parColor.b);
                uv.push_back(p.parColor.a);
            }

            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, uv.data());
            // needs to be glDrawArraysInstanced for better performance
            glDrawArrays(GL_TRIANGLE_STRIP, 0, _parCount);
            glDisableVertexAttribArray(1);
        }

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisableVertexAttribArray(0);

        return true;
    }
    else
        return false;

}

void ParticleGenerator::updateParticles()
{   
    glm::vec3 camPosition = _camera->getCamPosition();
    float dt = 0.04f;
    _lifeLeft -= dt;
    if (_lifeLeft > 0) {
        for (int i = 0; i < PARTICLE_AMOUNT; i++) {
            Particle& p = _allParticles[i];
            float randomX = ((rand() % 15) - 7) / 100.0f;
            float randomY = ((rand() % 15) - 7) / 100.0f;
            float randomZ = ((rand() % 21)) / 100.0f;
            p.parPosition += glm::vec3(randomX, randomY, p.parVelocity.z * dt + randomZ);
            p.parColor.a -= dt;
            p.parCameraDistance = glm::distance(p.parPosition, camPosition);
        }
        std::sort(&_allParticles[0], &_allParticles[PARTICLE_AMOUNT-1]);
    }
}

void ParticleGenerator::respawnParticles()
{
    _lifeLeft = 1.0f;
    for (int i = 0; i < PARTICLE_AMOUNT; i++) {
        Particle& p = _allParticles[i];
        p.parColor.a = 1.0f;
        p.parPosition = glm::vec3(0.0f);
    }
}

void ParticleGenerator::deleteParticles()
{
    delete gunpoint;
}