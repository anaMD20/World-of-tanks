#include "lab_m1/tema2/tema2.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about FrameStart, Update, FrameEnd
 *  and the order in which they are called, see world.cpp.
 * 
 */
struct Building {
    glm::vec3 position;
    glm::vec3 scale;
    float rotation;
};

std::vector<Building> buildings;


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    tankPosition = glm::vec3(0, 0, 0);
    tankDirection = glm::vec3(0, 0, 1);
    tankRotation = 0.0f;
    bazaPosition = glm::vec3(0, 0, 0);
    tunPosition = glm::vec3(0, 0, 0);
    senila1Position = glm::vec3(0, 0, 0);
    senila2Position = glm::vec3(0, 0, 0);
    turelaPosition = glm::vec3(0, 0, 0);
    rotatieTurela = 0.0f;
    lastFireTime = 0.0f;

    {
        Mesh* mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("turela");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "turela.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("senila1");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "senila1.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("senila2");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "senila2.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("baza");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "baza.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("tun");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "tun.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	} 
    {
        Mesh* mesh = new Mesh("cladire");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "cladire.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    for (int i = 0; i < 5; ++i) {
        Building building;
        building.position = glm::vec3(rand() % 30 - 30 / 2, 1, rand() % 20 - 20 / 2);
        building.scale = glm::vec3(0.5f +rand() % 1, 0.5f + rand() % 1, 0.5f + rand() % 1);
        building.rotation = static_cast<float>(rand() % 360);
        buildings.push_back(building);
    }
    for (int i = 0; i < 3; i++) {
        EnemyTank enemy;
        enemy.position = glm::vec3(10 * i, 0, -10); // Pozi?ii diferite pentru fiecare inamic
        enemy.direction = glm::vec3(0, 0, 1); 
        enemy.speed = 2.0f; // Viteza inamicului
        enemy.rotation = 0.0f;
        enemy.color = glm::vec3(1.0f - 0.3f * i, 0.2f * i, 0.4f * i); // Culori diferite
        enemy.direction = glm::normalize(glm::vec3(rand() % 3 - 1, 0, rand() % 3 - 1));
        enemy.changeDirectionTime = rand() % 5 + 3; // Schimb? direc?ia între 3 ?i 8 secunde
        enemy.timeSinceLastChange = 0.0f;
        enemyTanks.push_back(enemy);
    }


    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // Light & material properties
    {
        lightPosition = glm::vec3(0, 1, 1);
        materialShininess = 30;
        materialKd = 0.5;
        materialKs = 0.5;
    }
    

}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{
    
    {
        glm ::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        modelMatrix = glm::translate(modelMatrix, tankPosition);
        modelMatrix = glm::rotate(modelMatrix, tankRotation, glm::vec3(0, 1, 0));
        modelMatrix = glm::rotate(modelMatrix, rotatieTurela, glm::vec3(0, 1, 0));
        RenderSimpleMesh(meshes["turela"], shaders["LabShader"], modelMatrix, glm::vec3(0.11f, 0.56f, 1));
    }
    {
		glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		modelMatrix = glm::translate(modelMatrix, tankPosition);
        modelMatrix = glm::rotate(modelMatrix, tankRotation, glm::vec3(0, 1, 0));
		RenderSimpleMesh(meshes["senila1"], shaders["LabShader"], modelMatrix, glm::vec3(0, 1, 1));
	}
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        modelMatrix = glm::translate(modelMatrix, tankPosition);
        modelMatrix = glm::rotate(modelMatrix, tankRotation, glm::vec3(0, 1, 0));
        RenderSimpleMesh(meshes["senila2"], shaders["LabShader"], modelMatrix, glm::vec3(0, 1, 1));
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        modelMatrix = glm::translate(modelMatrix, tankPosition);
        modelMatrix = glm::rotate(modelMatrix, tankRotation, glm::vec3(0, 1, 0));
        RenderSimpleMesh(meshes["baza"], shaders["LabShader"], modelMatrix, glm::vec3(0, 0, 1));

    }
    {
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		modelMatrix = glm::translate(modelMatrix, tankPosition);
        modelMatrix = glm::rotate(modelMatrix, tankRotation, glm::vec3(0, 1, 0));
        modelMatrix = glm::rotate(modelMatrix, rotatieTurela, glm::vec3(0, 1, 0));
		RenderSimpleMesh(meshes["tun"], shaders["LabShader"], modelMatrix, glm::vec3(0, 1, 1));
	}
    


    // Render ground
     {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.01f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1));
        RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, glm::vec3(0.54f, 0.26f, 0.07f));
    }

     for (const auto& building : buildings) {
         glm::mat4 modelMatrix = glm::mat4(1);
         modelMatrix = glm::translate(modelMatrix, building.position);
         modelMatrix = glm::rotate(modelMatrix, glm::radians(building.rotation), glm::vec3(0, 1, 0));
         modelMatrix = glm::scale(modelMatrix, building.scale);
         RenderSimpleMesh(meshes["cladire"], shaders["LabShader"], modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
     }
     RenderProjectiles();
     for (auto& enemy : enemyTanks) {
         enemy.timeSinceLastChange += deltaTimeSeconds;
         if (enemy.timeSinceLastChange > enemy.changeDirectionTime) {
             enemy.direction = glm::normalize(glm::vec3(rand() % 3 - 1, 0, rand() % 3 - 1));
             enemy.changeDirectionTime = rand() % 5 + 3;
             enemy.timeSinceLastChange = 0.0f;
         }
             enemy.position -= glm::vec3(cos(enemy.rotation), 0, -sin(enemy.rotation)) * deltaTimeSeconds * enemy.speed;

         // Desenarea tancului inamic
         glm::mat4 modelMatrix = glm::mat4(1);
         modelMatrix = glm::translate(modelMatrix, enemy.position);
         modelMatrix = glm::rotate(modelMatrix, enemy.rotation, glm::vec3(0, 1, 0));
         modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f)); 
         RenderSimpleMesh(meshes["baza"], shaders["LabShader"], modelMatrix, glm::vec3(0.69f, 0.09f, 0.84f));
         RenderSimpleMesh(meshes["turela"], shaders["LabShader"], modelMatrix, glm::vec3(1, 0, 0.5f));
         RenderSimpleMesh(meshes["senila1"], shaders["LabShader"], modelMatrix, glm::vec3(0.5f, 0, 1));
         RenderSimpleMesh(meshes["senila2"], shaders["LabShader"], modelMatrix, glm::vec3(0.5f, 0, 1));
         RenderSimpleMesh(meshes["tun"], shaders["LabShader"], modelMatrix, glm::vec3(0.5f, 0, 1));
     }
}


void Tema2::FrameEnd()
{
    DrawCoordinateSystem();
}


void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Set shader uniforms for light & material properties
    // TODO(student): Set light position uniform
    GLint loc_light_position = glGetUniformLocation(shader->program, "light_position");
    glUniform3fv(loc_light_position, 1, glm::value_ptr(lightPosition));

    // TODO(student): Set eye position (camera position) uniform
    glm::vec3 eyePosition = GetSceneCamera()->m_transform->GetWorldPosition();
    GLint loc_eye_position = glGetUniformLocation(shader->program, "eye_position");
    glUniform3fv(loc_eye_position, 1, glm::value_ptr(eyePosition));

    // TODO(student): Set material property uniforms (shininess, kd, ks, object color)
    GLint loc = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(loc, materialShininess);

    loc = glGetUniformLocation(shader->program, "material_kd");  // componenta difuza
    glUniform1f(loc, materialKd);

    loc = glGetUniformLocation(shader->program, "material_ks");  // componenta speculara
    glUniform1f(loc, materialKs);

    loc = glGetUniformLocation(shader->program, "object_color");
    glUniform3fv(loc, 1, glm::value_ptr(color));

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see input_controller.h.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    float speedRotation = 1;
    float speed = 5;

    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 right = GetSceneCamera()->m_transform->GetLocalOXVector();
        glm::vec3 forward = GetSceneCamera()->m_transform->GetLocalOZVector();
        forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));

    }
    if (window->KeyHold(GLFW_KEY_W)) {
        tankPosition -= glm::vec3(cos(tankRotation), 0, -sin(tankRotation)) * deltaTime * speed;

    }
    if (window->KeyHold(GLFW_KEY_A)) {
        tankRotation += deltaTime * speedRotation;
              
    }
    if (window->KeyHold(GLFW_KEY_S)) {
        tankPosition += glm::vec3(cos(tankRotation), 0, -sin(tankRotation)) * deltaTime * speed;
    }
    if (window->KeyHold(GLFW_KEY_D)) {
        tankRotation -= deltaTime * speedRotation;
        
    }
        
    float projectileLifetime = 5.0f;
    for (auto& projectile : projectiles) {
        if (projectile.isActive) {
            projectile.lifeTime += deltaTime;
            if (projectile.lifeTime > projectileLifetime) {
                projectile.isActive = false;
            }
            else {
                projectile.position += projectile.direction * deltaTime; 
                
            }
        }
    }

    RenderProjectiles();

    
}
void Tema2::RenderProjectiles() {
    for (const auto& projectile : projectiles) {
        if (projectile.isActive) {
            
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, projectile.position);
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f)); 
            RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix, glm::vec3(1,0,0)); // Proiectile negre
        }
    }
}

void Tema2::FireProjectile() {
    std::cout << "Fire!\n";
    for (auto& projectile : projectiles) {
        if (!projectile.isActive) {
            projectile.position = tunPosition + glm::vec3(0, 0, 2); 
            projectile.direction = tankDirection;
            projectile.isActive = true;
            break;
        }
    }
}


void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
    if (key == GLFW_KEY_SPACE) { // De exemplu, foloseste tasta SPACE pentru a trage
        FireProjectile();
        // declari proiectilul si sa ii dai push
        /*Projectile projectile;
        projectile.position = tunPosition + glm::vec3(0, 0, 0);
        projectile.direction = tankDirection;
        projectile.isActive = true;
        projectiles.push_back(projectile);
        */
    }
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    float sensivityOX = 0.005f;
		rotatieTurela += sensivityOX * deltaX;
 


}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        auto currentTime = Engine::GetElapsedTime();
        if (currentTime - lastFireTime > 1.0f) { // Asigura-te ca a trecut o secunda
            FireProjectile();
            lastFireTime = currentTime;
        }
        Projectile projectile;
        projectile.position = tunPosition + glm::vec3(5, 10, 10);
        projectile.direction = tankDirection;
        projectile.isActive = true;
        projectiles.push_back(projectile);
    }
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}