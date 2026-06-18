#ifndef METHODS_H
    #define METHODS_H

    #include <glad/glad.h>
    #include <GLFW/glfw3.h>

    #include <vector>
    #include <iostream>
    #include <stdexcept>

    GLFWwindow* createWindow(const char* window_name, int width, int height);
    GLuint initShaderProgram();
    void clearWindow();
    GLuint initVBO(GLsizei num, const std::vector<float>& vertices);
    GLuint initVAO(GLsizei num, const std::vector<float>& vertices);
    void handleInput(GLFWwindow* window);

    class mesh{
        private:
            GLuint vao_ID{0};
            GLuint vbo_ID{0};
            bool initialized = false;
        public:
            size_t vertex_count{0};
            
        GLuint getVAOID(){ return this->vao_ID; }
        GLuint getVBOID(){ return this->vbo_ID; }

        mesh(const std::vector<float>& vertices, GLenum usage = GL_STATIC_DRAW){
            if(vertices.empty()){
                initialized = false;
                throw std::invalid_argument("vertices not provided");
            }
            vertex_count = vertices.size();
            initialized = true;

            GLsizei vao_count = 1;
            GLsizei vbo_count = 1;
            vao_ID = initVAO(vao_count, vertices);
            vbo_ID = initVBO(vbo_count, vertices);

            glBufferData(
                GL_ARRAY_BUFFER,
                vertices.size() * sizeof(float),
                vertices.data(),
                usage
            );

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        bool isInitialized() const { return initialized; }
    };
#endif