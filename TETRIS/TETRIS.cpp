#include <glew.h>
#include <glfw3.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <math.h>
#include <time.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_easy_font.h>

#define HEIGHT 20
#define WIDTH 10
#define _WIN32_WINNT 0xA00

int field[HEIGHT][WIDTH] = { 0 };
int w = 34; // size of block
int old = 0;
int score = -10;
int tmp_score = score;
int lvl = 1;

struct Point {
    int x, y;
}a[4], b[4], c[4];

struct Button {
    int x, y;
} arr[4];

int check_n = 0;

int figs[7][4] = {
    1, 3, 5, 7,
    2, 4, 5, 7,
    3, 5, 4, 6,
    3, 5, 4, 7,
    2, 3, 5, 7,
    3, 5, 7, 6,
    2, 3, 4, 5,
};



void DrawSquare(Point a[], int n) {
    glBegin(GL_QUADS);
    if (n == 0) glColor3f(1, 0, 0);
    if (n == 1) glColor3f(0, 1, 0);
    if (n == 2) glColor3f(0, 0, 1);
    if (n == 3) glColor3f(1, 1, 0);
    if (n == 4) glColor3f(1, 0, 1);
    if (n == 5) glColor3f(0, 1, 1);
    if (n == 6) glColor3f(0.5, 0.5, 0.5);
    for (int i = 0; i < 4; i++) {
        //printf("%d\n", a[i].x);
        if (a[i].y > 0 && check_n == 0) {
            glVertex2f(a[i].x, a[i].y); // top left
            glVertex2f(a[i].x + 10, a[i].y); // top right 
            glVertex2f(a[i].x + 10, a[i].y - 10); // bottom right
            glVertex2f(a[i].x, a[i].y - 10); // bottom left
        }
        else {
            check_n++;
            glVertex2f(a[i].x, a[i].y); // top left
            glVertex2f(a[i].x + 10, a[i].y); // top right 
            glVertex2f(a[i].x + 10, a[i].y + 10); // bottom right
            glVertex2f(a[i].x, a[i].y + 10); // bottom left
        }
    }
    glEnd();
}

void ShowPutted(int a[HEIGHT][WIDTH], int n) {
    
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            //printf("%d %d\n", i, j);
            if (a[i][j] != 0) {
                if (a[i][j] == 1) glColor3f(1, 0, 0);
                if (a[i][j] == 2) glColor3f(0, 1, 0);
                if (a[i][j] == 3) glColor3f(0, 0, 1);
                if (a[i][j] == 4) glColor3f(1, 1, 0);
                if (a[i][j] == 5) glColor3f(1, 0, 1);
                if (a[i][j] == 6) glColor3f(0, 1, 1);
                if (a[i][j] == 7) glColor3f(0.5, 0.5, 0.5);

                glBegin(GL_QUADS);
                glVertex2f((j) * 10, (i) * 10 + 10); // top left
                glVertex2f((j) * 10 + 10, (i) * 10 + 10); // top right
                glVertex2f((j) * 10 + 10, (i) * 10); // bottom right
                glVertex2f((j) * 10, (i) * 10); // bottom left
                glEnd();
            }
        }
    }
}

void Show_Next(int n) {
    for (int i = 0; i < 4; i++) {
        if (1) {
            //sn = rand() % 7;
            //colorNum = n + 1;
            for (int j = 0; j < 4; j++) {
                c[j].x = 140 + (10 * (figs[n][j] % 2));
                c[j].y = 140 + (10 * (figs[n][j] / 2));
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        glBegin(GL_QUADS);
        if (n == 0) glColor3f(1, 0, 0);
        if (n == 1) glColor3f(0, 1, 0);
        if (n == 2) glColor3f(0, 0, 1);
        if (n == 3) glColor3f(1, 1, 0);
        if (n == 4) glColor3f(1, 0, 1);
        if (n == 5) glColor3f(0, 1, 1);
        if (n == 6) glColor3f(0.5, 0.5, 0.5);
        glVertex2f(c[i].x, c[i].y); // top left
        glVertex2f(c[i].x + 10, c[i].y); // top right 
        glVertex2f(c[i].x + 10, c[i].y - 10); // bottom right
        glVertex2f(c[i].x, c[i].y - 10); // bottom left
        glEnd();
    }
}


void Show_Game_Matrix() {
    glLineWidth(1.0);
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0, 100);
    glVertex2f(200, 100);
    glEnd();
    for (int i = 0; i < HEIGHT * 10; i += 10) {
        glBegin(GL_LINE_STRIP);
        glVertex2f(0, i);
        glVertex2f(WIDTH * 10, i);
        glEnd();
    }
    for (int i = 0; i < WIDTH * 10 + 1; i += 10) {
        glBegin(GL_LINE_STRIP);
        glVertex2f(i, 0);
        glVertex2f(i, HEIGHT * 10);
        glEnd();
    }
    for (int i = WIDTH * 10 + 40; i < WIDTH * 10 + 70; i += 10) {
        glBegin(GL_LINE_STRIP);
        glVertex2f(i, 130);
        glVertex2f(i, 170);
        glEnd();
    }
    for (int i = 130; i <= 170; i += 10) {
        glBegin(GL_LINE_STRIP);
        glVertex2f(160, i);
        glVertex2f(140, i);
        glEnd();
    }
}

void clearField() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            field[i][j] = 0;
        }
    }
}

static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos);

void Show_Button_Start() {
    glBegin(GL_QUADS);
    glColor3f(0.7, 0.7, 0.7);
    glVertex2f(130, 30); // top left
    glVertex2f(170, 30); // top right
    glVertex2f(170, 10); // bottom right
    glVertex2f(130, 10); // bottom left
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.7, 0.7, 0.7);
    glVertex2f(130, 60); // top left
    glVertex2f(170, 60); // top right
    glVertex2f(170, 40); // bottom right
    glVertex2f(130, 40); // bottom left
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.7, 0.7, 0.7);
    glVertex2f(130, 90); // top left
    glVertex2f(170, 90); // top right
    glVertex2f(170, 70); // bottom right
    glVertex2f(130, 70); // bottom left
    glEnd();

}


bool check() {
    for (int i = 0; i < 4; i++) {
        
        if (a[i].x < 0 || a[i].x >= 100 || a[i].y <= 0) {
            
            return 0;
        }
        else if ((a[i].y / 10 - 1 < 20) && (field[a[i].y / 10 - 1][a[i].x / 10])) {
            return 0;
        }
    }
    return 1;
}

int flag_entered = 0;
int flag_start = 0;
int flag_restart = 0;
int flag_pause = 0;

static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos) {
    //printf("%lf %lf\n", xPos, yPos);
    if (xPos > 443 && yPos > 477 && xPos < 577 && yPos < 541) {
        flag_entered = 1;
    }
    else if (xPos > 443 && yPos > 578 && xPos < 577 && yPos < 643) {
        flag_entered = 2;
    }
    else if (xPos > 443 && yPos > 374 && xPos < 577 && yPos < 440) {
        flag_entered = 3;
    }
    else {
        flag_entered = 0;
    }
}
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        if (flag_entered == 1) {
            printf("START\n");
            flag_start = 1;
        }
        else if (flag_entered == 2) {
            printf("RESTART\n");
            flag_restart = 1;
        }
        else if (flag_entered == 3) {
            printf("PAUSE\n");
            if (flag_pause == 0) {
                flag_pause = 1;
            }
            else {
                flag_pause = 0;
            }
            
        }
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (old != 6) {
        if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
            Point p = a[1];
            for (int i = 0; i < 4; i++) {
                int x = a[i].y - p.y;
                int y = a[i].x - p.x;
                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }
            if (check() == 0) {
                for (int i = 0; i < 4; i++) {
                    a[i] = b[i];
                }
            }
        }
    }
}




bool Game_End(int a[HEIGHT][WIDTH]) {
    for (int i = 0; i < WIDTH; i++) {
        if (a[HEIGHT - 1][i] != 0) {
            
            return 1;
        }
    }
    return 0;
}

void print_string(float x, float y, char* text, float r, float g, float b)
{
    static char buffer[99999]; // ~500 chars
    int num_quads;

    num_quads = stb_easy_font_print(x, y, text, NULL, buffer, sizeof(buffer));

    glColor3f(r, g, b);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 16, buffer);
    glDrawArrays(GL_QUADS, 0, num_quads * 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void printLine() {
    char score_char[9] = "SCORE: \0";
    char pause_char[7] = "PAUSE\0";
    char start_char[7] = "START\0";
    char restart_char[6] = "REST\0";
    char ch_lvl[6] = "LVL:\0";
    char score_s[11] = { '\0' };
    char char_lvl[2] = { '\0' };
    int tmp = score;
    if (tmp < 0) tmp = 0;
    int tmp2 = lvl;
    for (int i = 9; i >= 0; i--) {
        score_s[i] = tmp % 10 + '0';
        tmp /= 10;
    }
    for (int i = 1; i >= 0; i--) {
        char_lvl[i] = tmp2 % 10 + '0';
        tmp2 /= 10;
    }

    glPushMatrix();
    glScalef(1, -1, 1);
    glTranslatef(120, -190, 0);
    print_string(0, 0, score_char, 0, 0, 0); //score
    print_string(15, 106, pause_char, 0, 0, 0); //pause
    print_string(15, 136, start_char, 0, 0, 0); //start
    print_string(18, 166, restart_char, 0, 0, 0); //restart
    print_string(0, 10, score_s, 0, 0, 0); //score_int
    print_string(0, 80, char_lvl, 0, 0, 0); //lvl_int
    print_string(0, 70, ch_lvl, 0, 0, 0); //lvl_char
    glPopMatrix();
}


int endFlag_entered = 0;
static void cursorPositionCallback2(GLFWwindow* window2, double xPos, double yPos) {
    if (xPos > 35 && yPos > 579 && xPos < 643 && yPos < 643) {
        endFlag_entered = 1;
    }
    else {
        endFlag_entered = 0;
    }
}

int loop_flag = 0;
void mouseButtonCallback2(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        if (endFlag_entered == 1) {
            printf("START\n");
            loop_flag = 1;
        }
    }
}

double TIME_FIN = 0;
double TIME_EX_PAUSE = 0;
int min = 0;
char minute[2] = { '\0' };
char seconds[2] = { '\0' };
void printEndGame() {
    glBegin(GL_QUADS);
    glColor3f(0.7, 0.7, 0.7);
    glVertex2f(10, 30); // top left
    glVertex2f(190, 30); // top right
    glVertex2f(190, 10); // bottom right
    glVertex2f(10, 10); // bottom left
    glEnd();

    char score_char[9] = "SCORE: \0";
    char time_char[13] = "TIME:   :  \0";
    char ch_lvl[6] = "LVL:\0";
    char restart_char[9] = "EXIT\0";
    char score_s[11] = { '\0' };
    char char_lvl[2] = { '\0' };
    int tmp = score;
    int tmp2 = lvl;
    for (int i = 9; i >= 0; i--) {
        score_s[i] = tmp % 10 + '0';
        tmp /= 10;
    }
    for (int i = 1; i >= 0; i--) {
        char_lvl[i] = tmp2 % 10 + '0';
        tmp2 /= 10;
    }
    
    
    


    glPushMatrix();
    glScalef(1, -1, 1);
    glTranslatef(0, -190, 0);
    print_string(10, 0, score_char, 0, 0, 0); //score
    print_string(10, 50, time_char, 0, 0, 0); //time
    print_string(10, 100, ch_lvl, 0, 0, 0); //lvl_char
    print_string(45, 0, score_s, 0, 0, 0); //score_int
    print_string(35, 100, char_lvl, 0, 0, 0); //lvl_int
    print_string(90, 166, restart_char, 0, 0, 0); //restart
    print_string(45, 50, minute, 0, 0, 0); //min
    print_string(58, 50, seconds, 0, 0, 0); //sec
    glPopMatrix();
}

int test = 0;


int main(void)
{
    srand(time(0));
    GLFWwindow* window;
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    if (!glewInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH*w*2, HEIGHT*w, "Tetris", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetKeyCallback(window, key_callback);
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glLoadIdentity();
    glTranslatef(-1, -1, 0);
    glScalef(0.01, 0.01, 1);

    int dx = 0, colorNum = 1;
    bool rotate = false;
    double timer = 0, timer_2 = 0, timer_3 = 0, delay = 0.3;
    
    clock_t clock_start;
    clock_t clock_end;
    int n = rand() % 7;
    old = n;
    colorNum = n + 1;
    double s_time = 1;
    int t = 0;
    clock_t TIME_EX_START;
    clock_t TIME_EX_END;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Wait for start button */
        while (!flag_start) {
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glLoadIdentity();
            glTranslatef(-1, -1, 0);
            glScalef(0.01, 0.01, 1);
            Show_Game_Matrix();
            Show_Button_Start();
            printLine();
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        if (!t) { 
            TIME_EX_START = clock(); 
            t = 1;
        }

        clock_start = clock();
        Sleep(1);
        clock_end = clock();
        double time = (double)(clock_end - clock_start) / CLOCKS_PER_SEC;
        timer += time;
        timer_2 += time;
        timer_3 += time;
        
        
        for (int i = 0; i < 4; i++) {
            b[i] = a[i];
            a[i].x += dx;
        }
        
        if (check() == 0) {
            for (int i = 0; i < 4; i++) {
                a[i] = b[i];
            }
        }
        
        
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glLoadIdentity();
        glTranslatef(-1, -1, 0);
        glScalef(0.01, 0.01, 1);
        
        dx = 0;
        rotate = false;
        
        
        
        if (timer > delay) {
            
            for (int i = 0; i < 4; i++) {
                b[i] = a[i];
                a[i].y -= 10;
            }
            if (check() == 0) {
                for (int i = 0; i < 4; i++) {
                    field[a[i].y / 10][a[i].x / 10] = colorNum;
                    //printf("%d %d\n", a[i].x, a[i].y);
                }
                old = n;
                colorNum = n + 1;
                for (int j = 0; j < 4; j++) {
                    a[j].x = 50 + (10 * (figs[old][j] % 2));
                    a[j].y = 210 + (10 * (figs[old][j] / 2));
                }
                n = rand() % 7;
                score += 10;
                tmp_score += 10;
                printf("S: %d\n", score);
                if (tmp_score >= 300 && tmp_score != 0) {
                    tmp_score -= 300;
                    lvl++;
                    printf("LVL: %d\n", lvl);
                    if (lvl <= 3) {
                        delay -= 0.07;
                        printf("DELAY: %lf\n", delay);
                    }
                }
            }
            timer = 0;
        }
        if (timer_2 > 0.08) {

            if (GetKeyState(VK_RIGHT) < 0) {
                dx = 10;
            }
            if (GetKeyState(VK_LEFT) < 0) {
                dx = -10;
            }
            if (GetKeyState(VK_DOWN) < 0) {
                for (int i = 0; i < 4; i++)
                    a[i].y -= 10;
                if (check() == 0) {
                    //delay -= 0.1;
                    for (int i = 0; i < 4; i++) {
                        field[a[i].y / 10][a[i].x / 10] = colorNum;
                    }
                    //printf("SOBAKA");

                    old = n;
                    colorNum = n + 1;
                    for (int j = 0; j < 4; j++) {
                        a[j].x = 50 + (10 * (figs[old][j] % 2));
                        a[j].y = 210 + (10 * (figs[old][j] / 2));
                    }
                    n = rand() % 7;

                    score += 10;
                    tmp_score += 10;
                    printf("S: %d\n", score);
                    if (tmp_score >= 300 && tmp_score != 0) {
                        tmp_score -= 300;
                        lvl++;
                        printf("LVL: %d\n", lvl);
                        if (lvl <= 3) {
                            delay -= 0.07;
                            printf("DELAY: %lf\n", delay);
                        }
                    }
                }
                
            }
            timer_2 = 0;
        }
        if (timer_3 > 0.18) {
            if (GetKeyState(VK_UP) < 0) {
                rotate = true;
            }
            timer_3 = 0;
        }

        int k = 0;
        for (int i = 0; i < HEIGHT; i++) {
            int count = 0;
            for (int j = 0; j < WIDTH; j++) {
                if (field[i][j]) count++;
                field[k][j] = field[i][j];
                
            }
            if (count < WIDTH) {
                k++;
            }
            if (count == WIDTH) {
                score += 100;
                tmp_score += 100;
                printf("S: %d\n", score);
                if (tmp_score >= 300 && tmp_score != 0) {
                    tmp_score -= 300;
                    lvl++;
                    printf("LVL: %d\n", lvl);
                    if (lvl <= 3) {
                        delay -= 0.07;
                        printf("DELAY: %lf\n", delay);
                    }
                }
            }
            
        }

        
        if (flag_restart) {
            tmp_score = 0;
            score = 0;
            lvl = 1;
            delay = 0.3;
            TIME_EX_START = 0;
            TIME_EX_START = clock();
            flag_restart = 0;
            clearField();
            old = n;
            colorNum = n + 1;
            for (int j = 0; j < 4; j++) {
                a[j].x = 50 + (10 * (figs[old][j] % 2));
                a[j].y = 210 + (10 * (figs[old][j] / 2));
            }
            n = rand() % 7;
        }
        if (flag_pause == 1) {
            clock_t rez, rez_end;
            rez = clock();
            while (flag_pause) {
                if (flag_restart == 1) {
                    TIME_EX_START = 0;
                    TIME_EX_START = clock();
                    clearField();
                    flag_pause = 0;
                    break;
                }
                Show_Game_Matrix();
                Show_Button_Start();
                glfwPollEvents();
            }
            rez_end = clock();
            TIME_EX_PAUSE += (rez_end - rez) / CLOCKS_PER_SEC;
        }

        if (Game_End(field)) {
            flag_pause = 1;
        }
        ShowPutted(field, n);
        if (!Game_End(field)) {
            DrawSquare(a, old);
        }
        Show_Next(n);
        Show_Game_Matrix();
        Show_Button_Start();
        printLine();
        
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();

        if (Game_End(field)) {
            TIME_EX_END = clock();
            TIME_FIN = (TIME_EX_END - TIME_EX_START) / CLOCKS_PER_SEC;
            TIME_FIN -= TIME_EX_PAUSE;
            for (int i = 1; i <= TIME_FIN; i++) {
                if (i % 60 == 0) {
                    min++;
                }
            }
            for (int i = 0; i < min; i++) {
                TIME_FIN -= 60;
            }
            for (int i = 1; i >= 0; i--) {
                minute[i] = min % 10 + '0';
                min /= 10;
            }
            for (int i = 1; i >= 0; i--) {
                seconds[i] = (int)TIME_FIN % 10 + '0';
                TIME_FIN /= 10;
            }

            GLFWwindow* window2;
            window2 = glfwCreateWindow(WIDTH * w * 2, HEIGHT * w, "EndGame", NULL, NULL);
            if (!window2)
            {
                glfwTerminate();
                return -1;
            }
            glfwSetCursorPosCallback(window2, cursorPositionCallback2);
            glfwSetMouseButtonCallback(window2, mouseButtonCallback2);
            glfwMakeContextCurrent(window2);
            while (!glfwWindowShouldClose(window2))
            {
                glClear(GL_COLOR_BUFFER_BIT);
                glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
                glLoadIdentity();
                glTranslatef(-1, -1, 0);
                glScalef(0.01, 0.01, 1);

                printEndGame();
                if (loop_flag) {
                    clearField();
                    test = 1;
                    break;
                }
                glfwSwapBuffers(window2);
                glfwPollEvents();
            }
            glfwTerminate();
        }
        if (test) { 
            return 0; 
        }
    }
    
    glfwTerminate();
    return 0;
}

