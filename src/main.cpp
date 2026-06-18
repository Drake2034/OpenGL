#include <iostream>
#include <stdexcept>
#include <exception>
#include <cmath>
#include <vector>

#include <methods.hpp>

#define WIN_HEIGHT 1080
#define WIN_WIDTH 1920

int main(int argc, char* argv[]){
    glfwInit();

    try{
        GLFWwindow* window = createWindow("opengl babyyy", WIN_WIDTH, WIN_HEIGHT);
        if(!window) throw std::runtime_error("could not initialize window");

        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw std::runtime_error("glad loader failed")
        ;

        GLsizei vertexArrayID = 1;
        GLsizei bufferID = 1;

        GLuint VAO = initVAO(vertexArrayID);
        GLuint VBO = initVBO(bufferID);

        std::vector<vertex> v_triangle = {

        };
        mesh triangle = mesh(v_triangle);
        if(!triangle) throw std::runtime_error("could not initialize triangle");

        GLuint shaderProgram = initShaderProgram();

        while(!glfwWindowShouldClose(window)){
            glfwPollEvents();
            clearWindow();

            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);

            glDrawArrays(GL_TRIANGLES, 0, 3);

            handleInput(window);
            glfwSwapBuffers(window);
        }

        glDeleteVertexArrays(vertexArrayID, &VAO);
        glDeleteBuffers(bufferID, &VBO);
        glDeleteProgram(shaderProgram);

        glfwDestroyWindow(window);

    }catch(const std::runtime_error& e){
        std::cout << "error: " << e.what() << '\n';
        glfwTerminate();
        return -1;
    }

    glfwTerminate();
    return 0;
}
