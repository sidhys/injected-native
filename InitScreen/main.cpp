#define GLFW_EXPOSE_NATIVE_WIN32
#include <windows.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <iostream>
#include <time.h>


#include <windows.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nShowCmd);

    clock_t timeStart = clock();

    GLFWwindow* window;
    int windowSizeW = 1920, windowSizeH = 1080;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    int count, windowWidth, windowHeight, monitorX, monitorY;

    GLFWmonitor** monitors = glfwGetMonitors(&count);
    const GLFWvidmode* videoMode = glfwGetVideoMode(monitors[0]);

    windowWidth = static_cast<int>(videoMode->width / 1);

    windowHeight = static_cast<int>(videoMode->height / 16 * 9);

    glfwGetMonitorPos(monitors[0], &monitorX, &monitorY);

    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);


    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    window = glfwCreateWindow(windowSizeW, windowSizeH, "..............", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    HWND hwn = glfwGetWin32Window(window);
    DWORD style = GetWindowLong(hwn, GWL_EXSTYLE);
    SetWindowLong(hwn, GWL_EXSTYLE, (style & ~WS_EX_APPWINDOW) | WS_EX_TOOLWINDOW);

    glfwMakeContextCurrent(window);

    glfwDefaultWindowHints();

    glfwSetWindowPos(window,
        monitorX ,
        monitorY);

    glfwShowWindow(window);

    glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);

    float fAngle = 0.0f;
    int r = 0, g = 0, b = 0;
    double gay = 0;

    while (!glfwWindowShouldClose(window))
    {
        using namespace std;

        glClearColor(r,g,b,0);
        gay += 0.00001;
        if (gay == 1)
        {
            r++;
            g++;
            b++;
            gay = 0;
        }

        glLoadIdentity();
        glRotatef(fAngle, 10, 100, 1);
        glBegin(GL_QUADS

        );
        glColor3f(0, 0, 1);
        glVertex3f(-5.5, 2, 1);
        glColor3f(0, 1, 5);
        glVertex3f(2.5, -10.1, -1);
        glColor3f(1, 4, 2);
        glVertex3f(1.5, 10.1, -1);
        glColor3f(1, 1, 3);
        glVertex3f(-0.5, 10.5, -1);
        glEnd();
            
        fAngle += 0.2;  

        glfwSwapBuffers(window);

        glfwPollEvents();

        if ((clock() - timeStart) / CLOCKS_PER_SEC >= 10) 
            break;
    }

    glfwTerminate();
    return 0;
}