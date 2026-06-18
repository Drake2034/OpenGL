#ifndef METHODS_H
    #define METHODS_H

    #include <glad/glad.h>
    #include <GLFW/glfw3.h>

    GLFWwindow* createWindow(const char* window_name, int width, int height);
    GLuint initShaderProgram();
    void clearWindow();
    GLuint initVBO(GLsizei num);
    GLuint initVAO(GLsizei num);
    void handleInput(GLFWwindow* window);

    template<typename vertex>
    
    //TODO
    class mesh{
        private:
            GLuint vao_{0};
            Gluint vbo_{0};
        size_t vertexCount_{0};
        public:

        mesh(const std::vector<vertex>& vertices, GLenum usage = GL_STATIC_DRAW){
            vertexCount_ = vertices.size();

            vao_ = initVAO();
            vbo_ = initVBO();
            glBufferData(
                GL_ARRAY_BUFFER,
                vertices.size() * sizeof(Vertex),
                vertices.data(),
                usage
            );

            vertex::setupAttributes();

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
    };
#endif