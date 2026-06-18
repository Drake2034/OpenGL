#include <methods.hpp>

#include <vector>
#include <span>

const char* vertexShaderSource =
"                                                       \
#version 330 core \n                                    \
layout (location = 0) in vec3 aPos;\n                   \
void main(){\n                                          \
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n   \
}                                                       \
\0";

const char* fragmentShaderSource =
"                                               \
out vec4 FragColor;\n                           \
void main(){\n                                  \
   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n \
}                                               \
\0";

GLFWwindow* createWindow(const char* window_name, int width, int height){
    glfwWindowHint(GLFW_SAMPLES, 4); //4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* monitor = NULL;
    GLFWwindow* share = NULL;

    GLFWwindow* window = glfwCreateWindow(
        width,
        height,
        window_name,
        monitor,
        share
    );

    glfwSetWindowAttrib(window, GLFW_FLOATING, GL_TRUE);
    glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH, GL_TRUE);

    glfwMakeContextCurrent(window);

    clearWindow();
    glfwSwapBuffers(window);

    // x, y are the coordinates of the lower-left corner of the viewport rectangle
    GLuint x = 0 , y = 0;
    glViewport(x, y, width, height);

    return window;
}

GLuint initShaderProgram(){
    GLsizei count = 1;
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, count, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, count, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram (shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

    return shaderProgram;
}

void clearWindow(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   //black
    glClear(GL_COLOR_BUFFER_BIT);
}

void setupMesh(GLuint VAO, GLuint VBO, const std::vector<float>& vertices){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices) * vertices.size(),
        vertices.data(),
        GL_STATIC_DRAW
    );

    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        vertices.size(),
        GL_FLOAT,
        GL_FALSE,
        sizeof(float) * vertices.size(),
        (void*) 0
    );
}

void handleInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}
