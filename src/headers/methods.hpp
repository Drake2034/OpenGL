#include <vector>
#include <iostream>
#include <stdexcept>

#ifndef METHODS_H
    #define METHODS_H

    #include <glad/glad.h>
    #include <GLFW/glfw3.h>

    GLFWwindow* createWindow(const char* window_name, unsigned int width, unsigned int height);
    void clearWindow();
    GLuint initShaderProgram();
    void cleanup();
    void setupMesh(GLuint VAO, GLuint VBO, const std::vector<float>& vertices);
    void handleInput(GLFWwindow* window);

    class mesh{
        private:
        bool initialized{0};
        public:
        GLuint VAO{0};
        GLuint VBO{0};
        size_t vertex_count{0};

        mesh(const std::vector<float>& vertices){
            if(vertices.empty()){
                throw std::invalid_argument("vertices not provided");
            }
            vertex_count = vertices.size();
            
            setupMesh(this->VBO, this->VAO, vertices);
            
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            
            initialized = true;
        }

        bool isInitialized() const { return initialized; }
    };
#endif