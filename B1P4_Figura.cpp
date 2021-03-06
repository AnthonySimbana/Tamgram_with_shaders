#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <learnopengl/shader_ClassB1P4.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 360;
const unsigned int SCR_HEIGHT = 400;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "B1T4 FIGURA - TAMGRAM", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("shaders/shader_B1P4.vs", "shaders/shader_B1P4.fs"); // you can name your shader files however you like

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions         // colors
        -0.17f, 0.93f, 0.0f, 0.98f, 0.40f, 0.40f,
        -0.29f, 0.68f, 0.0f, 0.98f, 0.40f, 0.40f,
	    0.0f, 0.55f, 0.0f,0.99f, 0.8f, 0.0f,

	    -0.17f, 0.93f, 0.0f, 0.98f, 0.40f, 0.40f,
        0.13f, 0.8f, 0.0f,0.98f, 0.40f, 0.40f,
	    0.0f, 0.55f, 0.0f,0.99f, 0.8f, 0.0f,

	    0.13f, 0.8f, 0.0f,0.98f, 0.40f, 0.40f,
	    0.43f, 0.93f, 0.0f,0.40f, 0.39f, 0.79f,
        0.6f, 0.67f, 0.0f,0.40f, 0.39f, 0.79f,

	    0.43f, 0.93f, 0.0f,0.40f, 0.39f, 0.79f,
        0.86f, 0.82f, 0.0f,0.40f, 0.39f, 0.79f,
        0.6f, 0.67f, 0.0f,0.40f, 0.39f, 0.79f,

        0.0f, 0.55f, 0.0f,0.99f, 0.8f, 0.0f,
        -0.46f, 0.150f, 0.0f,0.99f, 0.8f, 0.0f,
	    0.0f, -0.26f, 0.0f, 0.58f,  0.8f, 0.22f,

	    -0.11f, -0.16f, 0.0f, 0.20f, 0.80f, 0.39f,
	    0.51f, -0.65f, 0.0f,  0.20f, 0.80f, 0.39f,
	    -0.11f, -0.65f, 0.0f,0.58f,  0.8f, 0.22f,

	    -0.11f, -0.27f, 0.0f,0.58f,  0.8f, 0.22f,
	    -0.57f, -0.65f, 0.0f, 0.58f,  0.8f, 0.22f,
	    -0.11f, -0.65f, 0.0f, 0.20f, 0.80f, 0.39f,

	    -0.91f, -0.65f, 0.0f,1.0f, 0.60f, 0.2f,
        -0.46f, -0.65f, 0.0f,0.58f,  0.8f, 0.22f,
	    -0.69f, -0.87f, 0.0f,1.0f, 0.60f, 0.2f,

	    0.23f, -0.65f, 0.0f,0.20f, 0.80f, 0.39f,
	    0.57f, -0.77f, 0.0f,0.18f, 0.62f, 0.98f,
        0.39f, -0.99f, 0.0f,0.18f, 0.62f, 0.98f,
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render the triangle
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 27);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}