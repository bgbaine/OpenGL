/*
    Now create the same 2 triangles using two different VAOs and VBOs for their data.
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Vertex shader source code
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
    "}\0";

// Fragment shader source code
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

int main()
{
    /* GLFW STARTS HERE */

    // Initialize GLFW and set it up
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    /* WINDOW STARTS HERE */
    // Create window and make it the current context
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Check for GLAD error
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set viewport and update it everytime the window is resized
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* WINDOW ENDS HERE */
    /* SHADERS START HERE */

    /* VERTEX SHADER STARTS HERE */

    // Create a new vertex shader object
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Attach the vertex shader source code to the shader object and compile it
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check for compilation errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    /* VERTEX SHADER ENDS HERE */
    /* FRAGMENT SHADER STARTS HERE */

    // Create a new fragment shader object
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Attach the fragment shader source code to the shader object and compile it
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check for compilation errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    /* FRAGMENT SHADER ENDS HERE */
    /* SHADER PROGRAM STARTS HERE */

    // Create a shader program object
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    // Attach and link shaders to the program object
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for compilation errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM::COMPILATION_FAILED" << std::endl;
    }

    // Set program object as the current active shader
    glUseProgram(shaderProgram);

    // De-allocate shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    /* SHADER PROGRAM ENDS HERE */

    /* SHADERS END HERE */
    /* TRIANGLES START HERE */

    // Specify the vertices for both triangles (NDC)
    float firstTriangle[] {
        -0.75f, -0.5f, 0.0f,  // left-corner
         0.0f,  -0.5f, 0.0f,  // right-corner
        -0.350f, 0.5f, 0.0f   // top
    };
    float secondTriangle[] {
        0.0f,  -0.5f, 0.0f,   // left-corner
        0.75f, -0.5f, 0.0f,   // right-corner
        0.350f, 0.5f, 0.0f,   // top
    };

    // Generate new Vertex Buffer (VBO) and Vertex Array (VAO) objects
    unsigned int VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    // Bind the Vertex Array Object of the first triangle (VAO)
    glBindVertexArray(VAOs[0]);

    // Bind the the first triangle's VBO to the GL_ARRAY_BUFFER target and upload vertex data to the gpu
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);

    // Specify the layout of the vertex data in the vertex buffer and enable the vertex attribute array at location 0 for the first triangle
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);
    
    // Bind the Vertex Array Object of the second triangle (VAO)
    glBindVertexArray(VAOs[1]);

    // Bind the the second triangle's VBO to the GL_ARRAY_BUFFER target and upload vertex data to the gpu
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);

    // Specify the layout of the vertex data in the vertex buffer and enable the vertex attribute array at location 0 for the second triangle
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind the GL_ARRAY_BUFFER and the VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Draw wireframe polygons
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    /* TRIANGLES END HERE */
    /* RENDERING STARTS HERE */

    // Render loop (each iteration is a frame)
    while (!glfwWindowShouldClose(window)) {
        // Process input
        processInput(window);
        
        // State-setting and state-using functions
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Change current program to shaderProgram
        glUseProgram(shaderProgram);

        // Draw left triangle
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw the right triangle
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    /* RENDERING ENDS HERE */

    // De-allocate all remaining resources
    glDeleteVertexArrays(sizeof(VAOs), VAOs);
    glDeleteBuffers(sizeof(VBOs), VBOs);
    glDeleteProgram(shaderProgram);

    // Close GLFW
    glfwTerminate();
    return 0;

    /* GLFW ENDS HERE */
}

// Updates viewport after resizing window
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Checks for escape and closes window
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
