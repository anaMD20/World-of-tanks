#pragma once

#include "components/simple_scene.h"
#include "components/transform.h"


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        Tema2();
        ~Tema2();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color = glm::vec3(1));

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void FireProjectile();
        void RenderProjectiles();

        glm::vec3 lightPosition;
        glm::vec3 bazaPosition;
        glm::vec3 turelaPosition;
        glm::vec3 senila1Position;
        glm::vec3 senila2Position;
        glm::vec3 tunPosition;
        glm::vec3 tankPosition;
        glm::vec3 tankDirection;
        float lastFireTime;
        float tankRotation;
        float rotatieTurela;
        float inclinatieTun;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;
        struct Projectile {
            glm::vec3 position;
            glm::vec3 direction;
            float speed;
            bool isActive;
            float lifeTime;
            float timeStamp;

            //Projectile() : position(0, 0, 0), direction(0, 0, 1), speed(5.0f), isActive(false), lifeTime(5.0f), timeStamp(0) {}
        };
        std::vector<Projectile> projectiles;
        struct EnemyTank {
            glm::vec3 position;
            glm::vec3 direction;
            float speed;
            float rotation;
            glm::vec3 color;
            float changeDirectionTime;
            float timeSinceLastChange;
            // Alte propriet??i necesare
        };

        std::vector<EnemyTank> enemyTanks;
    };
}   // namespace m1
