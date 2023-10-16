#include <glew.h>
#include <glfw3.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#define mapW 22
#define mapH 22

float gravitySquare = 1;


void DrawSquare(int cnt) {
    glBegin(GL_QUADS);
    glVertex2f((mapW) / 2 - 1, mapH); // top left
    glVertex2f((mapW) / 2, mapH); // top right 
    glVertex2f((mapW) / 2, mapH - 1); // bottom right
    glVertex2f((mapW) / 2 - 1, mapH - 1); // bottom left
    glEnd();
}

typedef struct {
    int x, y;
    int dx, dy;

} TSquare;

TSquare square;

void TSquare_Init(TSquare* obj, float x1, float y1, float dx1, float dy1) {
    obj->x = x1;
    obj->y = y1;
    obj->dx = dx1;
    obj->dy = dy1;
}
void Game_Init() {
    glScalef(2.0 / mapW, 2.0 / mapH, 1);
    glTranslatef(-mapW * 0.5, -mapH * 0.5, 0);
    TSquare_Init(&square, 0, 0, 0, 1);
}

void TSquare_Show(TSquare obj) {

    glPushMatrix();
    glTranslatef(obj.x, obj.y, 0);
    DrawSquare(1);
    glPopMatrix();
}

int TSquare_Move(TSquare* obj) {
    obj->x += obj->dx;
    obj->y -= obj->dy;
    if (GetKeyState(VK_LEFT) < 0) obj->x -= 1;
    if (GetKeyState(VK_RIGHT) < 0) obj->x += 1;
    if (GetKeyState(VK_DOWN) < 0) obj->y -= 1;

    if (obj->y < -mapH + 1) {
        obj->y = -mapH + 1;
        obj->dy *= 0;
        //Game_Init();
        return 0;
    }
    return 1;
}



int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    if (!glewInit())
        return 1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1200, 1200, "Tetris", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    Game_Init();
    int fin = 1;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1, 1, 0);
        TSquare_Show(square);
        while (fin) {
            fin = TSquare_Move(&square);

            printf("%d", fin);


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
            Sleep(500);
        }
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}