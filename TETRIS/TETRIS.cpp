#include <glew.h>
#include <glfw3.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_easy_font.h>

#define HEIGHT 20
#define WIDTH 10
#define _WIN32_WINNT 0xA00


short n = rand() % 7;
int field[HEIGHT][WIDTH] = { 0 };
short w = 34; // size of block
short old = 0;
short score = -10;
short tmp_score = score;
short lvl = 1;
int line_field = 0;

struct Point {
    int x, y;
}a[4], b[4], c[4];

struct Button {
    short x, y;
} arr[4];

short check_n = 0;

int figs[7][4] = {
    1, 3, 5, 7,
    2, 4, 5, 7,
    3, 5, 4, 6,
    3, 5, 4, 7,
    2, 3, 5, 7,
    3, 5, 7, 6,
    2, 3, 4, 5,
};



void DrawSquare(Point a[], short n) {
    glBegin(GL_QUADS);
    switch (n)
    {
    case 0:
        glColor3f(1, 0, 0);
        break;
    case 1:
        glColor3f(0, 1, 0);
        break;
    case 2:
        glColor3f(0, 0, 1);
        break;
    case 3:
        glColor3f(1, 1, 0);
        break;
    case 4:
        glColor3f(1, 0, 1);
        break;
    case 5:
        glColor3f(0, 1, 1);
        break;
    case 6:
        glColor3f(0.5, 0.5, 0.5);
        break;
    default:
        break;
    }
    for (short i = 0; i < 4; i++) {
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

void ShowPutted(int a[HEIGHT][WIDTH], short n) {
    
    for (short i = 0; i < HEIGHT; i++) {
        for (short j = 0; j < WIDTH; j++) {
            if (*(*(a + i) + j) != 0) {
                switch (*(*(a + i) + j))
                {
                case 1:
                    glColor3f(1, 0, 0);
                    break;
                case 2:
                    glColor3f(0, 1, 0);
                    break;
                case 3:
                    glColor3f(0, 0, 1);
                    break;
                case 4:
                    glColor3f(1, 1, 0);
                    break;
                case 5:
                    glColor3f(1, 0, 1);
                    break;
                case 6:
                    glColor3f(0, 1, 1);
                    break;
                case 7:
                    glColor3f(0.5, 0.5, 0.5);
                    break;
                default:
                    break;
                }
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

void Show_Next(short n) {
    for (short i = 0; i < 4; i++) {
        if (1) {
            //sn = rand() % 7;
            //colorNum = n + 1;
            for (int j = 0; j < 4; j++) {
                c[j].x = 140 + (10 * (figs[n][j] % 2));
                c[j].y = 140 + (10 * (figs[n][j] / 2));
            }
        }
    }
    for (short i = 0; i < 4; i++) {
        glBegin(GL_QUADS);
        switch (n)
        {
        case 0:
            glColor3f(1, 0, 0);
            break;
        case 1:
            glColor3f(0, 1, 0);
            break;
        case 2:
            glColor3f(0, 0, 1);
            break;
        case 3:
            glColor3f(1, 1, 0);
            break;
        case 4:
            glColor3f(1, 0, 1);
            break;
        case 5:
            glColor3f(0, 1, 1);
            break;
        case 6:
            glColor3f(0.5, 0.5, 0.5);
            break;
        default:
            break;
        }
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
    for (short i = 0; i < HEIGHT * 10; i += 10) {
        glBegin(GL_LINE_STRIP);
        glVertex2f(0, i);
        glVertex2f(WIDTH * 10, i);
        glEnd();
    }
    for (short i = 0; i < WIDTH * 10 + 1; i += 10) {
        glBegin(GL_LINE_STRIP);
        glVertex2f(i, 0);
        glVertex2f(i, HEIGHT * 10);
        glEnd();
    }
    for (short i = WIDTH * 10 + 40; i < WIDTH * 10 + 70; i += 10) {
        glBegin(GL_LINE_STRIP);
        glVertex2f(i, 130);
        glVertex2f(i, 170);
        glEnd();
    }
    for (short i = 130; i <= 170; i += 10) {
        glBegin(GL_LINE_STRIP);
        glVertex2f(160, i);
        glVertex2f(140, i);
        glEnd();
    }
}

inline
void clearField() {
    memset(field, 0, sizeof(field));
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
    printf("LF: %d\n", line_field);
    short min_pos_x = min(a[0].x, a[3].x);
    short max_pos_x = max(a[0].x, a[3].x);
    short min_pos_y = min(a[0].y, a[3].y);
    short max_pos_y = max(a[0].y, a[3].y);
    if (old == 3) {
        min_pos_x = min(a[2].x, min_pos_x);
        max_pos_x = max(a[2].x, max_pos_x);
    }
    if (min_pos_x < 0 || max_pos_x >= 100 || min_pos_y <= 0) {
        return 0;
    }
    if (min_pos_y < line_field + 20) {
        if (max_pos_y / 10 - 1 < 20) {
            if (field[a[0].y / 10 - 1][a[0].x / 10]) {
                return 0;
            }
            else if (field[a[3].y / 10 - 1][a[3].x / 10]) {
                return 0;
            }
            else if (field[a[2].y / 10 - 1][a[2].x / 10]) {
                return 0;
            }
            else if (field[a[1].y / 10 - 1][a[1].x / 10]) {
                return 0;
            }
        }
        /*for (short i = 0; i < 4; i++) {
            if ((max_pos_y / 10 - 1 < 20) && (field[a[i].y / 10 - 1][a[i].x / 10])) {
                return 0;
            }
        }*/
    }
    return 1;
}

short flag_entered = 0;
short flag_start = 0;
short flag_restart = 0;
short flag_pause = 0;

inline
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

inline
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
            flag_pause = (flag_pause == 0);
        }
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (old != 6) {
        if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
            Point p = a[1];
            for (short i = 0; i < 4; i++) {
                short x = a[i].y - p.y;
                short y = a[i].x - p.x;
                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }
            if (check() == 0) {
                for (short i = 0; i < 4; i++) {
                    *(a + i) = *(b + i);
                }
            }
        }
    }
}




bool Game_End(int a[HEIGHT][WIDTH]) {
    for (short i = 0; i < WIDTH; i++) {
        if (a[HEIGHT - 1][i] != 0) {
            return 1;
        }
    }
    return 0;
}

void print_string(float x, float y, char* text, float r, float g, float b)
{
    static char buffer[99999]; // ~500 chars
    short num_quads;

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
    short tmp = score;
    if (tmp < 0) tmp = 0;
    short tmp2 = lvl;
    for (short i = 9; i >= 0; i--) {
        *(score_s + i) = tmp % 10 + '0';
        tmp /= 10;
    }
    for (short i = 1; i >= 0; i--) {
        *(char_lvl + i) = tmp2 % 10 + '0';
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


inline
static void cursorPositionCallback2(GLFWwindow* window2, double xPos, double yPos) {
    if (xPos > 35 && yPos > 579 && xPos < 643 && yPos < 643) {
        endFlag_entered = 1;
    }
    else {
        endFlag_entered = 0;
    }
}


int loop_flag = 0;
inline
void mouseButtonCallback2(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        loop_flag = (endFlag_entered == 1);
    }
}

float TIME_FIN = 0;
float TIME_EX_PAUSE = 0;
short min = 0;
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
    short tmp = score;
    short tmp2 = lvl;
    for (short i = 9; i >= 0; i--) {
        *(score_s + i) = tmp % 10 + '0';
        tmp /= 10;
    }
    for (short i = 1; i >= 0; i--) {
        *(char_lvl + i) = tmp2 % 10 + '0';
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

short test = 0;


int main(void)
{
    srand(time(0));
    GLFWwindow* window;
    double EXP = 0.0;
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

    short dx = 0, colorNum = 1;
    float timer = 0, timer_2 = 0, delay = 0.3;
    bool time_normalize = 0;
    clock_t clock_start;
    clock_t clock_end;
    old = n;
    colorNum = n + 1;
    short t = 0;
    int cycles = 0;
    clock_t TIME_EX_START;
    clock_t TIME_EX_END;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        cycles++;
        if (!Game_End(field)){
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
            clock_t BEGIN = clock();
            clock_end = clock();
            float time = (float)(clock_end - clock_start) / CLOCKS_PER_SEC;
            timer += time;
            timer_2 += time;
        
        
            for (short i = 0; i < 4; i++) {
                *(b + i) = *(a + i);
                a[i].x += dx;
            }
        
            if (check() == 0) {
                a[0] = b[0];
                a[1] = b[1];
                a[2] = b[2];
                a[3] = b[3];
            }
        
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glLoadIdentity();
            glTranslatef(-1, -1, 0);
            glScalef(0.01, 0.01, 1);
        
            dx = 0;

            if (timer > delay) {
                for (short i = 0; i < 4; i++) {
                    *(b + i) = *(a + i);
                    a[i].y -= 10;
                }
                if (check() == 0) {
                    old = n;
                    for (short i = 0; i < 4; i++) {
                        *(*(field + (a[i].y / 10)) + (a[i].x / 10)) = colorNum;
                        line_field = max(a[i].y, line_field);
                        a[i].x = 50 + (10 * (*(*(figs + old) + i) % 2));
                        a[i].y = 210 + (10 * (*(*(figs + old) + i) / 2));
                    }
                    colorNum = n + 1;
                    n = rand() % 7;
                    score += 10;
                    tmp_score += 10;
                    printf("S: %d\n", score);
                    if (tmp_score >= 300) {
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
                    for (short i = 0; i < 4; i++)
                        a[i].y -= 10;
                    if (check() == 0) {
                        old = n;
                        for (short i = 0; i < 4; i++) {
                            *(*(field + (a[i].y / 10)) + (a[i].x / 10)) = colorNum;
                            line_field = max(a[i].y, line_field);
                            a[i].x = 50 + (10 * ((*(*(figs + old) + i)) % 2));
                            a[i].y = 210 + (10 * ((*(*(figs + old) + i)) / 2));
                        }           
                        colorNum = n + 1;
                        n = rand() % 7;

                        score += 10;
                        tmp_score += 10;
                        printf("S: %d\n", score);
                        if (tmp_score >= 300) {
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

            short k = 0;
            for (short i = 0; i < HEIGHT; i++) {
                short count = 0;
                for (short j = 0; j < WIDTH; j++) {
                    if (*(*(field + i) + j)) count++;
                        *(*(field + k) + j) = *(*(field + i) + j);
                }
                if (count < WIDTH) {
                    k++;
                }
                else if (count == WIDTH) {
                    score += 100;
                    tmp_score += 100;
                    printf("S: %d\n", score);
                    if (tmp_score >= 300) {
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
                for (short j = 0; j < 4; j++) {
                    a[j].x = 50 + (10 * ((*(*(figs + old) + j)) % 2));
                    a[j].y = 210 + (10 * ((*(*(figs + old) + j)) / 2));
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

            flag_pause = Game_End(field);
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

            clock_t END = clock();
            if (cycles < 1000) {
                EXP += (double)(END - BEGIN) / CLOCKS_PER_SEC;
            }
            else {
                printf("%lf\n", EXP);
            }
          
        }
        if (Game_End(field)) {
            glfwSetCursorPosCallback(window, cursorPositionCallback2);
            glfwSetMouseButtonCallback(window, mouseButtonCallback2);
            if (!time_normalize) {
                TIME_EX_END = clock();
                TIME_FIN = (TIME_EX_END - TIME_EX_START) / CLOCKS_PER_SEC;
                TIME_FIN -= TIME_EX_PAUSE;
                for (short i = 1; i <= TIME_FIN; i++) {
                    if (i % 60 == 0) {
                        min++;
                    }
                }
                for (short i = 0; i < min; i++) {
                    TIME_FIN -= 60;
                }
                for (short i = 1; i >= 0; i--) {
                    *(minute + i) = min % 10 + '0';
                    min /= 10;
                }
                for (short i = 1; i >= 0; i--) {
                    *(seconds + i) = (int)TIME_FIN % 10 + '0';
                    TIME_FIN /= 10;
                }
            }
            time_normalize = 1;
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
            glfwSwapBuffers(window);
            glfwPollEvents();

        }
        if (test) { 
            return 0; 
        }
    }
    
    glfwTerminate();
    return 0;
}

