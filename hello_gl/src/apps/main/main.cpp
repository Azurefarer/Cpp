#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>
#include <iostream>

int main(void)
{
    const char** description;
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glfwGetError(description);
        std::cout << description << std::endl;
        std::cout << "pinching break point start" << std::endl; // Pinched the break point with comments
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
        std::cout << "pinching break point end" << std::endl; // Pinched the break point with comments

    glfwTerminate();
    return 0;
}