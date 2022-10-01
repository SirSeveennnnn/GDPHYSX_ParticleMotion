#pragma once

#include<glad/glad.h>
#include <GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Model.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include"tiny_obj_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

#include<string>
#include<iostream>

#include "PerspectiveCamera.h"
#include "Light.h"
#include "Model.h"
#include "MyShaders.h"


#include<unordered_map>

using namespace std;

//Inputs
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

float delta;
bool firstMouse = true;
double lastX, lastY;
glm::vec2 mousePos;
bool usePerspective = true;
bool rotateObject = true;

unordered_map<string, bool> input;

int main(void)
{

    input["W"] = false;
    input["Q"] = false;
    input["E"] = false;
    
    float width = 800;
    float height = 800;
    GLFWwindow* window;
    

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Jae Macuha", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();

    glViewport(0, 0, width, height);
    
    glfwSetKeyCallback(window, keyCallback);

    glEnable(GL_DEPTH_TEST);

    Light light;
    PerspectiveCamera perspectiveCamera;

    Model* spaceship = new Model("3D/spaceship.obj");
    spaceship->SetupTexture("Textures/spaceship.jpg", "Textures/spaceship_normal.jpg");
    MyShaders* shader_Spaceship = new MyShaders("Shaders/shader.vert", "Shaders/shader.frag");


    ////////////////////////////////////////////////////////////////////////
    //Transform
    // Delta Time
    float lastTime = glfwGetTime();

    light.SetLightPosition(glm::vec3(0, 0, 0));
    light.SetLightBrightness(100);
    light.SetLightColor(1.f, 1.f, 1.f);

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Delta Time
        //current time
        GLfloat currTime = glfwGetTime();
        delta = currTime - lastTime;

        
        //perspectiveCamera.FollowTarget(spaceship->GetTransform(), input, mousePos);
        //perspectiveCamera.UpdateViewMatrix(spaceship->GetTransform());
        spaceship->PlayerControls(input, delta, perspectiveCamera);

        shader_Spaceship->UseShader();
        spaceship->Draw(shader_Spaceship->GetShaderProgram(), usePerspective, perspectiveCamera, light);
        spaceship->Update(delta);
       
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        lastTime = currTime; // delta time
    }
    //Free Memory
    spaceship->DeleteBuffers();

    glfwTerminate();
    return 0;

}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        input["W"] = true;
    }
    else if (key == GLFW_KEY_W && action == GLFW_RELEASE)
    {
        input["W"] = false;
    }

    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    {
        input["Q"] = true;
    }
    else if (key == GLFW_KEY_Q && action == GLFW_RELEASE)
    {
        input["Q"] = false;
    }

    if (key == GLFW_KEY_E && action == GLFW_PRESS)
    {
        input["E"] = true;
    }
    else if (key == GLFW_KEY_E && action == GLFW_RELEASE)
    {
        input["E"] = false;
    }

}
