#include <methods.hpp>

#include <vector>
#include <span>

const char* vertex_shader_source =
"                                                       \
#version 330 core \n                                    \
layout (location = 0) in vec3 aPos;\n                   \
void main(){\n                                          \
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n   \
}                                                       \
\0";

const char* fragment_shader_source =
"                                               \
out vec4 FragColor;\n                           \
void main(){\n                                  \
   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n \
}                                               \
\0";

GLFWwindow* createWindow(const char* window_name, unsigned int width, unsigned int height){
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
    GLsizei shader_program_count = 1;
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(
        vertex_shader,
        shader_program_count, 
        &vertex_shader_source,
        NULL
    );
    glShaderSource(
        fragment_shader, 
        shader_program_count, 
        &fragment_shader_source, 
        NULL
    );

    glCompileShader(vertex_shader);
    glCompileShader(fragment_shader);
    

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram (shader_program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

    return shader_program;
}

void cleanup(GLuint* VAO, GLuint* VBO, GLuint shader_program){
    glDeleteBuffers(1, VBO);
    glDeleteVertexArrays(1, VAO);
    glDeleteProgram(shader_program);
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
