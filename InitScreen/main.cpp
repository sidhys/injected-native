#define GLFW_EXPOSE_NATIVE_WIN32

// Include necessary libraries
#include <windows.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <iostream>
#include <time.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    // Suppress unused parameter warnings
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nShowCmd);

    // Get the start time
    clock_t startTime = clock();

    // Declare a pointer to a GLFWwindow object
    GLFWwindow* mainWindow;
    
    // Set window dimensions
    int windowWidth = 1920, windowHeight = 1080;

    // Initialize the GLFW library
    if (!glfwInit())
        return -1;

    // Set the GLFW window hint for a transparent framebuffer
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    
    // Declare variables to hold monitor details
    int monitorCount, screenWidth, screenHeight, monitorPosX, monitorPosY;

    // Get monitor details
    GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
    const GLFWvidmode* videoMode = glfwGetVideoMode(monitors[0]);

    screenWidth = static_cast<int>(videoMode->width / 1);
    screenHeight = static_cast<int>(videoMode->height / 16 * 9);
    glfwGetMonitorPos(monitors[0], &monitorPosX, &monitorPosY);

    // Set additional GLFW window hints
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    // Create a window and a OpenGL context
    mainWindow = glfwCreateWindow(windowWidth, windowHeight, "Window", NULL, NULL);
    if (!mainWindow)
    {
        glfwTerminate();
        return -1;
    }

    // Get the HWND of the window and set window styles
    HWND hwnd = glfwGetWin32Window(mainWindow);
    DWORD style = GetWindowLong(hwnd, GWL_EXSTYLE);
    SetWindowLong(hwnd, GWL_EXSTYLE, (style & ~WS_EX_APPWINDOW) | WS_EX_TOOLWINDOW);

    // Make the context of the specified window current
    glfwMakeContextCurrent(mainWindow);

    // Reset all window hints to their default values
    glfwDefaultWindowHints();

    // Set the window position
    glfwSetWindowPos(mainWindow, monitorPosX, monitorPosY);

        // Make the window visible
    glfwShowWindow(mainWindow);

    // Set window attributes
    glfwSetWindowAttrib(mainWindow, GLFW_DECORATED, GLFW_FALSE);

    // Initialize variables for color and rotation
    float rotationAngle = 0.0f;
    int red = 0, green = 0, blue = 0;
    double colorIncrement = 0;

    // Enter the main event loop
    while (!glfwWindowShouldClose(mainWindow))
    {
        // Clear the buffer to the specified color
        glClearColor(red, green, blue, 0);
        
        colorIncrement += 0.00001;
        if (colorIncrement == 1)
        {
            red++;
            green++;
            blue++;
            colorIncrement = 0;
        }

        // Replace the current matrix with the identity matrix
        glLoadIdentity();
        // Rotate the matrix
        glRotatef(rotationAngle, 10, 100, 1);

        // Begin drawing quadrilaterals
        glBegin(GL_QUADS);
        glColor3f(0, 0, 1);
        glVertex3f(-5.5, 2, 1);
        glColor3f(0, 1, 5);
        glVertex3f(2.5, -10.1, -1);
        glColor3f(1, 4, 2);
        glVertex3f(1.5, 10.1, -1);
        glColor3f(1, 1, 3);
        glVertex3f(-0.5, 10.5, -1);
        glEnd();
            
        rotationAngle += 0.2;

        // Swap front and back buffers
        glfwSwapBuffers(mainWindow);

        // Poll for and process events
        glfwPollEvents();

        // Exit loop after 10 seconds
        if ((clock() - startTime) / CLOCKS_PER_SEC >= 10) 
            break;
    }

    // Clean up and close GLFW
    glfwTerminate();
    return 0;
}
