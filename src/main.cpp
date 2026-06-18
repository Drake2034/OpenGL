#include <iostream>
#include <stdexcept>
#include <exception>
#include <cmath>
#include <vector>

#include "./headers/methods.hpp"

#define WIN_HEIGHT 1080
#define WIN_WIDTH 1920

int main(/* int argc, char* argv[] */){
    glfwInit();

    std::vector<float> v_triangle = {
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f
    };

    try{
        mesh triangle = mesh(v_triangle);
        if(!triangle.isInitialized()){
            throw std::runtime_error("could not initialize mesh");
        }

        GLFWwindow* window = createWindow("opengl babyyy", WIN_WIDTH, WIN_HEIGHT);
        if(!window){
            throw std::runtime_error("could not initialize window");
        }

        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            glfwDestroyWindow(window);
            throw std::runtime_error("glad loader failed");
        }

        GLuint shader_program = initShaderProgram();
        if(!shader_program){
            glfwDestroyWindow(window);
            throw std::runtime_error("could not initialize shader program");
        }

        while(!glfwWindowShouldClose(window)){
            glfwPollEvents();
            clearWindow();

            glUseProgram(shader_program);

            glBindVertexArray(triangle.VAO);
            glDrawElements(
                GL_TRIANGLES, 
                triangle.vertex_count, 
                GL_UNSIGNED_INT, 
                (void*) 0 //byte offset: 1
            );
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            handleInput(window);
            glfwSwapBuffers(window);
        }

        cleanup();
        glfwDestroyWindow(window);

    }catch(const std::exception& e){
        std::cout << "error: " << e.what() << '\n';
        glfwTerminate();
        return -1;
    }

    glfwTerminate();
    return 0;
}
