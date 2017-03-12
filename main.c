#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
#include <time.h>
#include "console_draw3.h"
#include "kb_input2.h"
#include "image.h"
#include "font.h"
#include "audio.h"

#define NUM_KEYS 5
#define YELLOW 14
#define DIM_YELLOW 6
#define WHITE 15
#define RED 12
#define TOP 40
#define DOWN 65
#define LEFT 10
#define RIGHT 230
#define MAX_BULLET 15
#define RANK_NUM 3

Font *large_font;
Audio start_music;

int win = 0;

int key_const[] = {VK_A, VK_D, VK_W, VK_S, VK_SPACE, VK_ESCAPE};

typedef struct {
    DWORD start;
    DWORD end;
} Time;
Time st, nd, rd;

typedef struct {
    double time_double;
    char time_char[100];
} showTime;
showTime game1, game2, game3;

struct _bullet {
    int x;
    double y;
    int appear;
    Audio laser;
    Audio bomb;
};

struct _alien {
    int x;
    int y;
    int live;
    int attect;
    int direction;
    struct _bullet a_bullet[MAX_BULLET];
    Image *image;
};

struct _player {
    int x;
    int y;
    int life;
    Image *image;
} player;

struct _alien alien[8];

struct _bullet bullet[MAX_BULLET];

int range(int a, int b, int c) {
    if (a <= b && b <= c) return 1;
    else return 0;
}

void double_to_str(double d, char *s) {
    _ltoa(d, s, 10);
}

void int_to_str(int i, char *s) {
    _itoa(i, s, 10);
}

void starting(void)
{
    playAudio(&start_music);

    int roc_x = -100;
    int student_ID_x = -200;
    int exchange =0;

    Image *s105062262 = read_image("image\\s105062262.pixel","image\\s105062262.color");
    Image *s104062361 = read_image("image\\s104062361.pixel","image\\s104062361.color");
    Image *start_animate_0 = read_image("image\\start_animate_0.pixel", "image\\start_animate_0.color");
    Image *start_animate_1 = read_image("image\\start_animate_1.pixel", "image\\start_animate_1.color");

    while(1)
    {
        if (KEY_DOWN(VK_ESCAPE)) break;

        clearScreen();
        putStringLarge(large_font, 115, 70, "W - up", 15);
        putStringLarge(large_font, 190, 70, "A - left", 15);
        putStringLarge(large_font, 115, 80, "S - down", 15);
        putStringLarge(large_font, 190, 80, "D - right", 15);
        putStringLarge(large_font, 0, 70, "Space - enter", 15);
        putStringLarge(large_font, 16, 80, "Esc - Back", 15);
        show_image(s105062262, student_ID_x, 13);
        show_image(s104062361, student_ID_x, 32);


        if (roc_x != 400)
        {
            roc_x += 1;
            exchange = exchange + 1;

            if (exchange <= 50 || exchange > 100 && exchange <= 150 || exchange > 200 && exchange <= 250 || exchange > 300)
                show_image(start_animate_0, roc_x, 12);
            else if (exchange > 50 && exchange <= 100 || exchange > 150 && exchange <= 200 || exchange > 250 && exchange <= 300)
                show_image(start_animate_1, roc_x, 12);

            if (student_ID_x != 82)
            {
                student_ID_x += 1;
            }
        }

        drawCmdWindow();
        Sleep(10);

        if (roc_x >= 400) break;
    }

    destroy_image(s104062361);
    destroy_image(s105062262);
    destroy_image(start_animate_0);
    destroy_image(start_animate_1);

    initializeKeyInput();

    pauseAudio(&start_music);

    menu();
}

void menu(void)
{
    restartAudio(&start_music);

    int i, j, temp;
    //int w[3]= {1,15};
    int w[3] = {YELLOW, DIM_YELLOW, DIM_YELLOW}; //Color for exit page choice
    //int key_down[NUM_KEYS] = {0};
    //int key_val[NUM_KEYS] = {VK_UP, VK_DOWN, VK_ESCAPE, VK_RETURN};
    int x[4]= {YELLOW,DIM_YELLOW,DIM_YELLOW}; //Color for main page choice
    char ch;

    Image *start = read_image("image\\start_full.pixel", "image\\start_full.color");
    Image *logo_0 = read_image("image\\logo_0.pixel", "image\\logo_0.color");
    Image *logo_1 = read_image("image\\logo_1.pixel", "image\\logo_1.color");
    Image *end = read_image("image\\end.pixel", "image\\end.color");

    int flag=0;

    clearScreen();
    initializeKeyInput();

    show_image(start, 70, 3);

    flag = (flag+1)%2;
    if(flag == 0)
        show_image(logo_0, 20, 30);
    else
        show_image(logo_1, 20, 30);

    putStringLarge(large_font, 180, 40, "Start", x[0]);
    putStringLarge(large_font, 160, 55, "Score", x[1]);
    putStringLarge(large_font, 145, 70, "Exit", x[2]);
    drawCmdWindow();
    Sleep(300);

    while(1){
        if(waitForKeyDown(10)) {
            ch = getKeyEventASCII();
            switch(ch) {
            case 's':
                temp=x[0];
                x[0]=x[2];
                x[2]=x[1];
                x[1]=temp;
                clearScreen();
                show_image(start, 70, 3);

                flag = (flag+1)%2;
                if(flag == 0)
                    show_image(logo_0, 20, 30);
                else
                    show_image(logo_1, 20, 30);

                putStringLarge(large_font, 180, 40, "Start", x[0]);
                putStringLarge(large_font, 160, 55, "Score", x[1]);
                putStringLarge(large_font, 145, 70, "Exit", x[2]);
                drawCmdWindow();
                break;
            case 'w':
                clearScreen();
                temp=x[0];
                x[0]=x[1];
                x[1]=x[2];
                x[2]=temp;
                clearScreen();
                show_image(start, 70, 3);

                flag = (flag+1)%2;
                if(flag == 0)
                    show_image(logo_0, 20, 30);
                else
                    show_image(logo_1, 20, 30);

                putStringLarge(large_font, 180, 40, "Start", x[0]);
                putStringLarge(large_font, 160, 55, "Score", x[1]);
                putStringLarge(large_font, 145, 70, "Exit", x[2]);
                drawCmdWindow();
                break;
            }
        if(ch==' ') break;
        }
    }


    if (x[0]==YELLOW)
    {
        pauseAudio(&start_music);
        first_game();
    }

    if (x[1]==YELLOW)
    {
        pauseAudio(&start_music);
        Scoreboard();
    }

    if(x[2]==YELLOW) {
        clearScreen();
        exitgame(w[1], w[0]);
        while(1) {
            if(waitForKeyDown(30)) {
                ch = getKeyEventASCII();
                switch(ch) {
                case 'a':
                    exitgame(w[0], w[1]);
                    temp=w[0];
                    w[0]=w[1];
                    w[1]=temp;
                }
                switch(ch) {
                case 'd':
                    exitgame(w[0], w[1]);
                    temp=w[0];
                    w[0]=w[1];
                    w[1]=temp;
                }
            }
            if(ch==' ')break;
        }

        if(w[0]==YELLOW) {
            clearScreen();
            show_image(end, 165, 10);
            Font *large_font = read_font("font.txt");
            putStringLarge(large_font, 0, 10,"------------",15);
            putStringLarge(large_font, 0, 25,"------------------------",15);
            putStringLarge(large_font, 50, 40,"GOOD BYEEE",10);
            putStringLarge(large_font, 0, 55,"--------------------",15);
            putStringLarge(large_font, 0, 70,"----------------",15);
            drawCmdWindow();
            system("pause");
            exit(1);
        }
        if(w[1]==YELLOW) {
            clearScreen();
            //no_start=1;
            menu();
            drawCmdWindow();
        }
    }

    destroy_image(start);
    destroy_image(logo_0);
    destroy_image(logo_1);
    destroy_image(end);

    pauseAudio(&start_music);
}

void exitgame(int w0, int w1)
{
    int temp;
    temp = w0;
    w0 = w1;
    w1 = temp;
    clearScreen();
    putStringLarge(large_font, 85,30,"ARE YOU SURE",10);
    putStringLarge(large_font, 85,50,"11111",w0);
    putStringLarge(large_font, 135,50,"00000",w1);
    putStringLarge(large_font, 50,10,"-",15);
    putStringLarge(large_font, 50,20,"-",15);
    putStringLarge(large_font, 50,30,"-",15);
    putStringLarge(large_font, 50,40,"-",15);
    putStringLarge(large_font, 50,50,"-",15);
    putStringLarge(large_font, 50,60,"-",15);
    putStringLarge(large_font, 50,70,"-",15);
    putStringLarge(large_font, 210,10,"-",15);
    putStringLarge(large_font, 210,20,"-",15);
    putStringLarge(large_font, 210,30,"-",15);
    putStringLarge(large_font, 210,40,"-",15);
    putStringLarge(large_font, 210,50,"-",15);
    putStringLarge(large_font, 210,60,"-",15);
    putStringLarge(large_font, 210,70,"-",15);
    drawCmdWindow();
    return;

}

void animation1(void)
{
    restartAudio(&start_music);

    int spaceship_x = 300;
    int meteorite_x;

    clearScreen();

    Image *spaceship = read_image("image\\animation1_spaceship.pixel", "image\\animation1_spaceship.color");

    while(1)
    {
        clearScreen();

        show_image(spaceship, spaceship_x, 23);

        if (spaceship_x != -100)
        {
            spaceship_x -= 1;
        }

        drawCmdWindow();
        Sleep(10);

        if (spaceship_x <= -100) break;
    }

    destroy_image(spaceship);
}

void first_game(void)
{
    int i;
    int j;
    int finish_game = 0;
    int live_alien;
    char ch;
    char test_str[2];

    //load the player image in the first game only, and destroy it after third game
    player.image = read_image("image\\player.pixel", "image\\player.color");
    for(i = 0; i < 4; i++) {
        alien[i].x = 25 + i*30;
        alien[i].y = 5;
        alien[i].live = 1;
        alien[i].direction = 1;
        alien[i].image = read_image("image\\alien_0.pixel", "image\\alien_0.color");
    }

    player.x = 122;
    player.y = 55;

    for(i = 4; i < 8; i++) {
        alien[i].x = 140 + (i-4)*30;
        alien[i].y = 20;
        alien[i].live = 1;
        alien[i].direction = 0;
        alien[i].image = read_image("image\\alien_0.pixel", "image\\alien_0.color");
    }

    for (i = 0; i < MAX_BULLET; i++) {
        bullet[i].appear = 0;
        openAudioFile("audio\\laser.wav", &bullet[i].laser);
        openAudioFile("audio\\bomb.wav", &bullet[i].bomb);
    }

    st.start = timeGetTime();
    while (1) {
        clearScreen();
        initializeKeyInput();

        //enemy's movement
        for (i = 0; i < 8; i++) {
            if (alien[i].direction == 1) {
                alien[i].x++;
                if (alien[i].x > RIGHT) alien[i].direction = 0;
            } else if (alien[i].direction == 0) {
                alien[i].x--;
                if (alien[i].x < LEFT) alien[i].direction = 1;
            }
        }

        //spaceship movement with keyboard control
        if (KEY_DOWN(VK_A)) {
            if (LEFT < player.x) player.x -= 5;
        }
        if (KEY_DOWN(VK_D)) {
            if (player.x < RIGHT) player.x += 5;
        }
        if (KEY_DOWN(VK_W)) {
            if (TOP < player.y) player.y -= 1;
        }
        if (KEY_DOWN(VK_S)) {
            if (player.y < DOWN) player.y += 1;
        }
        if (KEY_DOWN(VK_SPACE)) {
            //emit bullet with sound
            for(i = 0; i < MAX_BULLET; i++)
                if (bullet[i].appear == 0) {
                    bullet[i].appear = 1;
                    bullet[i].x = player.x+10;
                    bullet[i].y = player.y;
                    playAudio(&bullet[i].laser);
                    break;
                }
        }

        //bullet's movement
        for(i = 0; i < MAX_BULLET; i++)
            if (bullet[i].appear && bullet[i].y > 0) {
                bullet[i].y -= 2;
            } else {
                bullet[i].appear = 0;
            }

        //enemy and bullet disappear with bomb sound
        for(i = 0; i < MAX_BULLET; i++)
            for(j = 0; j < 8; j++)
                if (alien[j].x <= bullet[i].x && bullet[i].x <= alien[j].x + 20)
                    if (bullet[i].y <= alien[j].y+10 && alien[j].y <= bullet[i].y)
                        if (alien[j].live > 0 && bullet[i].appear) {
                            playAudio(&bullet[i].bomb);
                            bullet[i].appear = 0;
                            alien[j].live = 0;
                }

        //show image
        show_image(player.image, player.x, player.y);
        for (i = 0; i < 8; i++)
            if (alien[i].live)
                show_image(alien[i].image, alien[i].x, alien[i].y);

        for(i = 0; i < MAX_BULLET; i++)
            if (bullet[i].appear) {
                putString(bullet[i].x, bullet[i].y, "T", YELLOW, RED);
            }

        st.end = timeGetTime();

        game1.time_double = (st.end - st.start)/1000.0;

        double_to_str(game1.time_double, game1.time_char);

        putStringLarge(large_font, 10,80, game1.time_char, 10);

        drawCmdWindow();

        Sleep(100);

        //detect if the game is end
        live_alien = 8;
        for (i = 0; i < 8; i++)
            if (alien[i].live == 0)
                live_alien--;

        if (live_alien == 0)
            break;

    }

    //to end the game, the program will destroy the image
    for (i = 0; i < 8; i++) {
        destroy_image(alien[i].image);
    }

    animation1();
    second_game();
}

void second_game(void)
{
    int i;
    int j;
    int finish_game = 0;
    int live_alien;
    char ch;
    char str[10];

    player.life = 10;

    pauseAudio(&start_music);

    //first line alien
    for(i = 0; i < 4; i++) {
        alien[i].x = 30 + i*30;
        alien[i].y = 5;
        alien[i].live = 1;
        alien[i].direction = 1;
        alien[i].image = read_image("image\\alien_1.pixel", "image\\alien_1.color");
        for(j = 0; j < MAX_BULLET; j++) {
            alien[i].a_bullet[j].appear = 0;
            alien[i].a_bullet[j].x = alien[i].x;
            alien[i].a_bullet[j].y = alien[i].y;
            openAudioFile("audio\\laser.wav", &alien[i].a_bullet[j].laser);
        }
    }

    player.x = 122;
    player.y = 55;
    //second line alien
    for(i = 4; i < 8; i++) {
        alien[i].x = 30 + (i-4)*30;
        alien[i].y = 20;
        alien[i].live = 1;
        alien[i].direction = 0;
        alien[i].image = read_image("image\\alien_1.pixel", "image\\alien_1.color");
    }

    for (i = 0; i < MAX_BULLET; i++) {
        bullet[i].appear = 0;
        openAudioFile("audio\\laser.wav", &bullet[i].laser);
        openAudioFile("audio\\bomb.wav", &bullet[i].bomb);
    }

    nd.start = timeGetTime();

    while (1) {
        clearScreen();
        initializeKeyInput();

        //enemy's movement
        for (i = 0; i < 8; i++) {
            if (alien[i].direction == 1) {
                alien[i].x += 4;
                if (alien[i].x > RIGHT) alien[i].direction = 0;
            } else if (alien[i].direction == 0) {
                alien[i].x -= 4;
                if (alien[i].x < LEFT) alien[i].direction = 1;
            }
        }

       //spaceship movement with keyboard control
        if (KEY_DOWN(VK_A)) {
            if (LEFT < player.x) player.x -= 5;
        }
        if (KEY_DOWN(VK_D)) {
            if (player.x < RIGHT) player.x += 5;
        }
        if (KEY_DOWN(VK_W)) {
            if (TOP < player.y) player.y -= 1;
        }
        if (KEY_DOWN(VK_S)) {
            if (player.y < DOWN) player.y += 1;
        }
        if (KEY_DOWN(VK_SPACE)) {
            //emit bullet with sound
            for(i = 0; i < MAX_BULLET; i++)
                if (bullet[i].appear == 0) {
                    bullet[i].appear = 1;
                    bullet[i].x = player.x + 10;
                    bullet[i].y = player.y;
                    playAudio(&bullet[i].laser);
                    break;
                }
        }

        //alien emit bullet
        for(i = 0; i < 8; i++)
        {
            if ((rand() % 100 + 1) % 40 == 2)
            //if (alien[i].x == player.x)
                for (j = 0; j < MAX_BULLET; j++)
                    if (alien[i].a_bullet[j].appear == 0) {
                        alien[i].a_bullet[j].appear = 1;
                        alien[i].a_bullet[j].x = alien[i].x + 15;
                        alien[i].a_bullet[j].y = alien[i].y + 9;
                        //playAudio(&alien[i].a_bullet[j].laser);
                        break;
                    }
        }

        //alien bullet's movement
        for(i = 0; i < 8; i++)
            if(alien[i].live == 1)
            for(j = 0; j < MAX_BULLET; j++)
                if(alien[i].a_bullet[j].appear && range(alien[i].y, alien[i].a_bullet[j].y, 86))
                {
                    alien[i].a_bullet[j].y += 1;
                } else {
                    alien[i].a_bullet[j].appear = 0;
                }

        //player bullet's movement
        for(i = 0; i < MAX_BULLET; i++)
            if (bullet[i].appear && bullet[i].y > 0) {
                bullet[i].y -= 2;
            } else {
                bullet[i].appear = 0;
            }
        //alien's bullet movement
        for(i = 0; i < 8; i++)
            for(j = 0; j < MAX_BULLET; j++)
                if(alien[i].a_bullet[j].appear && alien[i].a_bullet[j].y <= 86) {
                    alien[i].a_bullet[j].y += 0.5;
                } else {
                    alien[i].a_bullet[j].appear = 0;
                }


        //enemy and my bullet disappear with bomb sound
        for(i = 0; i < MAX_BULLET; i++)
            for(j = 0; j < 8; j++)
                if (alien[j].x <= bullet[i].x && bullet[i].x <= alien[j].x + 20)
                    if (bullet[i].y <= alien[j].y+10 && alien[j].y <= bullet[i].y)
                        if (alien[j].live && bullet[i].appear) {
                            playAudio(&bullet[i].bomb);
                            bullet[i].appear = 0;
                            alien[j].live = 0;
                }

        //player attack by bullet and bullet disappear
        for(i = 0; i < 8; i++)
            for(j = 0; j < MAX_BULLET; j++)
                if(alien[i].live && alien[i].a_bullet[j].appear)
                if(range(player.y, alien[i].a_bullet[j].y, player.y+9) && range(player.x, alien[i].a_bullet[j].x, player.x+17)) {
                    player.life -= 1;
                    alien[i].a_bullet[j].appear = 0;
                }


        //show image
        show_image(player.image, player.x, player.y);
        for (i = 0; i < 8; i++) {
            if (alien[i].live)
                show_image(alien[i].image, alien[i].x, alien[i].y);
            for (j = 0; j < MAX_BULLET; j++) {
                if (alien[i].a_bullet[j].appear == 1 && alien[i].live == 1) {
                    putString(alien[i].a_bullet[j].x, alien[i].a_bullet[j].y, "J", RED, YELLOW);
                }
            }
        }

        for(i = 0; i < MAX_BULLET; i++)
            if (bullet[i].appear) {
                putString(bullet[i].x, bullet[i].y, "T", YELLOW, RED);
            }

        //show life
        int_to_str(player.life, str);
        putStringLarge(large_font, 200, 80, str, YELLOW);

        nd.end = timeGetTime();

        game2.time_double = (nd.end - nd.start)/1000.0;

        double_to_str(game2.time_double + game1.time_double, game2.time_char);

        putStringLarge(large_font, 10,80, game2.time_char, 10);

        drawCmdWindow();
        Sleep(100);

        //detect if the game is end
        live_alien = 8;
        for (i = 0; i < 8; i++)
            if (alien[i].live == 0)
                live_alien--;

        if (live_alien == 0)
            break;

        if (player.life == 0)
            break;
    }
    //to end the game, the program will destroy the image
    for (i = 0; i < 8; i++) {
        destroy_image(alien[i].image);
    }

    if (player.life == 0) {
        game1.time_double = 0;
        game2.time_double = 0;
        menu();
    }
    else {
        animation1();
        third_game();
    }
}

void third_game(void)
{
    int i;
    int j;
    int finish_game = 0;
    int live_alien;
    char ch;
    char str[10];

    pauseAudio(&start_music);

    //first line alien
    for(i = 0; i < 4; i++) {
        alien[i].x = 10 + i*50;
        alien[i].y = 5;
        alien[i].live = 1;
        alien[i].direction = 1;
        alien[i].image = read_image("image\\alien_1.pixel", "image\\alien_1.color");
        for(j = 0; j < MAX_BULLET; j++) {
            alien[i].a_bullet[j].appear = 0;
            alien[i].a_bullet[j].x = alien[i].x;
            alien[i].a_bullet[j].y = alien[i].y;
            openAudioFile("audio\\laser.wav", &alien[i].a_bullet[j].laser);
        }
    }

    player.x = 122;
    player.y = 55;
    //alien[4] means boss
    for(i = 4; i < 5; i++) {
        alien[i].x = 160;
        alien[i].y = 20;
        alien[i].live = 15;
        alien[i].direction = 0;
        alien[i].image = read_image("image\\alien_2.pixel", "image\\alien_2.color");
    }

    for (i = 0; i < MAX_BULLET; i++) {
        bullet[i].appear = 0;
        openAudioFile("audio\\laser.wav", &bullet[i].laser);
        openAudioFile("audio\\bomb.wav", &bullet[i].bomb);
    }

    rd.start = timeGetTime();

    while (1) {
        clearScreen();
        initializeKeyInput();

        //enemy's movement (not boss)
        for (i = 0; i < 4; i++) {
            if (alien[i].direction == 1) {
                alien[i].x += 4;
                if (alien[i].x > RIGHT) alien[i].direction = 0;
            } else if (alien[i].direction == 0) {
                alien[i].x -= 4;
                if (alien[i].x < LEFT) alien[i].direction = 1;
            }
        }

        //boss's movement
        i = 4;
        if (player.x < alien[i].x)
            alien[i].direction = -1;
        else if (alien[i].x < player.x) alien[i].direction = 1;
        else  alien[i].direction = 0;

        if (alien[i].direction == 1)
            alien[i].x += 1;
        else if (alien[i].direction == -1 ) alien[i].x -= 1;


       //spaceship movement with keyboard control
        if (KEY_DOWN(VK_A)) {
            if (LEFT < player.x) player.x -= 5;
        }
        if (KEY_DOWN(VK_D)) {
            if (player.x < RIGHT) player.x += 5;
        }
        if (KEY_DOWN(VK_W)) {
            if (TOP < player.y) player.y -= 1;
        }
        if (KEY_DOWN(VK_S)) {
            if (player.y < DOWN) player.y += 1;
        }
        if (KEY_DOWN(VK_SPACE)) {
            //emit bullet with sound
            for(i = 0; i < MAX_BULLET; i++)
                if (bullet[i].appear == 0) {
                    bullet[i].appear = 1;
                    bullet[i].x = player.x+10;
                    bullet[i].y = player.y;
                    playAudio(&bullet[i].laser);
                    break;
                }
        }

        //alien emit bullet
        for(i = 0; i < 5; i++)
        {
            if ((rand() % 10 + 1) % 10 == 2)
                for (j = 0; j < MAX_BULLET; j++)
                    if (alien[i].a_bullet[j].appear == 0) {
                        alien[i].a_bullet[j].appear = 1;
                        alien[i].a_bullet[j].x = alien[i].x + 15;
                        alien[i].a_bullet[j].y = alien[i].y + 9;
                        break;
                    }
        }

        //alien bullet's movement include boss
        for(i = 0; i < 5; i++)
            if(alien[i].live == 1)
            for(j = 0; j < MAX_BULLET; j++)
                if(alien[i].a_bullet[j].appear && range(alien[i].y, alien[i].a_bullet[j].y, 86))
                {
                    alien[i].a_bullet[j].y += 1;
                } else {
                    alien[i].a_bullet[j].appear = 0;
                }

        //player bullet's movement
        for(i = 0; i < MAX_BULLET; i++)
            if (bullet[i].appear && bullet[i].y > 0) {
                bullet[i].y -= 2;
            } else {
                bullet[i].appear = 0;
            }

        //alien's bullet movement include boss
        for(i = 0; i < 4; i++)
            for(j = 0; j < MAX_BULLET; j++)
                if(alien[i].a_bullet[j].appear && alien[i].a_bullet[j].y <= 86) {
                    alien[i].a_bullet[j].y += 0.5;
                } else {
                    alien[i].a_bullet[j].appear = 0;
                }
        i = 4;
        for(j = 0; j < MAX_BULLET; j++)
            if(alien[i].a_bullet[j].appear && alien[i].a_bullet[j].y <= 86) {
                alien[i].a_bullet[j].y += 2;
            } else {
                alien[i].a_bullet[j].appear = 0;
            }

        //enemy and my bullet disappear with bomb sound
        for(i = 0; i < MAX_BULLET; i++)
        {
            for(j = 0; j < 4; j++)
                if (alien[j].x <= bullet[i].x && bullet[i].x <= alien[j].x + 20)
                    if (bullet[i].y <= alien[j].y+10 && alien[j].y <= bullet[i].y)
                        if (alien[j].live && bullet[i].appear)
                        {
                            playAudio(&bullet[i].bomb);
                            bullet[i].appear = 0;
                            alien[j].live -= 1;
                        }
            if (alien[j].x <= bullet[i].x && bullet[i].x <= alien[j].x + 26)
                if (bullet[i].y <= alien[j].y+10 && alien[j].y <= bullet[i].y)
                    if (alien[j].live && bullet[i].appear)
                    {
                        playAudio(&bullet[i].bomb);
                        bullet[i].appear = 0;
                        alien[j].live -= 1;
                    }
        }

        //player attack by bullet and bullet disappear
        for(i = 0; i < 4; i++)
            for(j = 0; j < MAX_BULLET; j++)
                if(alien[i].live && alien[i].a_bullet[j].appear)
                    if(range(player.y, alien[i].a_bullet[j].y, player.y+9) && range(player.x, alien[i].a_bullet[j].x, player.x+17)) {
                        player.life -= 1;
                        alien[i].a_bullet[j].appear = 0;
                }
        i = 4;
        for(j = 0; j < MAX_BULLET; j++)
            if(alien[i].live && alien[i].a_bullet[j].appear)
                if(range(player.y, alien[i].a_bullet[j].y, player.y+9) && range(player.x, alien[i].a_bullet[j].x, player.x+17)) {
                    player.life -= 1;
                    alien[i].a_bullet[j].appear = 0;
                }

        //show image
        show_image(player.image, player.x, player.y);
        for (i = 0; i < 5; i++) {
            if (alien[i].live)
                show_image(alien[i].image, alien[i].x, alien[i].y);
            for (j = 0; j < MAX_BULLET; j++) {
                if (alien[i].a_bullet[j].appear == 1 && alien[i].live > 0 ) {
                    putString(alien[i].a_bullet[j].x, alien[i].a_bullet[j].y, "J", RED, YELLOW);
                }
            }
        }

        for(i = 0; i < MAX_BULLET; i++)
            if (bullet[i].appear) {
                putString(bullet[i].x, bullet[i].y, "T", YELLOW, RED);
            }

        //show life
        int_to_str(player.life, str);
        putStringLarge(large_font, 200, 80, str, YELLOW);
        int_to_str(alien[4].live, str);
        putStringLarge(large_font, 110, 80, str, RED);
        rd.end = timeGetTime();

        game3.time_double = (rd.end - rd.start)/1000.0;
        double_to_str(game3.time_double + game2.time_double + game1.time_double, game3.time_char);
        putStringLarge(large_font, 10,80, game3.time_char, 10);
        drawCmdWindow();
        Sleep(100);

        //detect if the game is end
        live_alien = 5;
        for (i = 0; i < 5; i++)
            if (alien[i].live == 0)
                live_alien--;

        if (live_alien == 0)
            break;

        if (player.life == 0) {
            game1.time_double = 0;
            game2.time_double = 0;
            game3.time_double = 0;
            break;
        }

    }

    //to end the game, the program will destroy the image
    for (i = 0; i < 5; i++) {
        destroy_image(alien[i].image);
    }
    destroy_image(player.image);

    if (player.life == 0)
        menu();
    else
    {
        win = cmp_scoreboard((int)(game1.time_double + game2.time_double + game3.time_double));
        rank();
    }
}

int compare(const void *a, const void *b) {
    const int *ia = (const int *) a;
    const int *ib = (const int *) b;
    return *ia - *ib;
    //ascending order
}

/*

typedef struct
{
    int rank_data[3];
    char name[3];
} scoreboard;

void rewrite_rank(int total)
{
    int i, k;
    int x = 150, y = 40;

    int key_down[28] = {0};
    int key_val[28] = {VK_A, VK_B, VK_C, VK_D, VK_E, VK_F, VK_G, VK_H, VK_I, VK_J, VK_K, VK_L, VK_M, VK_N, VK_O,
                      VK_P, VK_Q, VK_R, VK_S, VK_T, VK_U, VK_V, VK_W, VK_X, VK_Y, VK_Z, VK_ESCAPE};
    scoreboard *data = malloc(3 * sizeof(scoreboard));
    scoreboard temp;
    FILE *fin, *fout;

    fin = fopen("scoreboard.txt","r");

    for(i = 0; i < 3; i++)
    {
        fscanf(fin, "%s", &data[i].name);
        fscanf(fin, "%d", &data[i].rank_data);
    }
    fclose(fin);
}

void showScoreboard(void)
{
    clearScreen();
    scoreboard *data = malloc(RANK_NUM * sizeof(SBdata));

    FILE *fin;
    initializeKeyInput();
    fin = fopen("scoreboard.txt","r");
    for(i = 0; i < RANK_NUM; i++)
    {
        fscanf(fin, "%s", &data[i].name);
        fscanf(fin, "%d", &data[i].rank_data);
    }
    fclose(fin);

    putStringLarge(large_font, 90, 20, "SCOREBOARD", WHITE);
    putStringLarge(large_font, 55, 30, "- - - - - - - - - -", WHITE);
    putStringLarge(large_font, 60, 40, "1st", WHITE);
    putStringLarge(large_font, 60, 50, "2nd", WHITE);
    putStringLarge(large_font, 60, 60, "3rd", WHITE);

    int_to_str(data.rank_data[0], str);
    putStringLarge(large_font, 120, 40, str, WHITE);
    putStringLarge(large_font, 170, 40, data[i].name,WHITE);

    int_to_str(data.rank_data[1], str);
    putStringLarge(large_font, 120, 50, str, WHITE);
    putStringLarge(large_font, 170, 40, data[i].name,WHITE);

    int_to_str(data.rank_data[2], str);
    putStringLarge(large_font, 120, 60, str, WHITE);
    putStringLarge(large_font, 170, 40, data[i].name, WHITE);

    drawCmdWindow();

    while(1)
    {
        if (KEY_DOWN(VK_ESCAPE))
        {
            break;
        }
    }

    pauseAudio(&start_music);
    menu();

}
*/

int rank_data[3] = {0};

int cmp_scoreboard(int total)
{
    int i;

    if (rank_data[0] == 0) return ;
    else if (rank_data[1] == 0 && total != 0)
    {
        return 1;
    }
    else if (rank_data[2] == 0 && total != 0)
    {
        return 2;
    }
    else if (total != 0 && total < rank_data[2])
    {
        for(i = 2; i >= 0; i--)
            if (total < rank_data[i] && total >= rank_data[i - 1])
            {
                return i;
            }
    }
    else return -1;
}

void rank(void)
{
    char str[10];
    int total;

    restartAudio(&start_music);

    initializeKeyInput();

    total = game1.time_double + game2.time_double + game3.time_double;

    clearScreen();

    if (win != -1)
    {
        clearScreen();
        putStringLarge(large_font, 95, 20, "NEW SCORE", WHITE);
        drawCmdWindow();
        Sleep(800);
        putStringLarge(large_font, 110, 40, "SCORE", WHITE);
        int_to_str(total, str);
        putStringLarge(large_font, 120, 50, str, YELLOW);
        drawCmdWindow();
        Sleep(2000);
        pauseAudio(&start_music);
        Scoreboard();
    }
    else
    {
        putStringLarge(large_font, 110, 10, "SORRY", WHITE);
        drawCmdWindow();
        Sleep(800);
        putStringLarge(large_font, 90, 30, "TRY HARDER", WHITE);
        drawCmdWindow();
        Sleep(800);
        putStringLarge(large_font, 110, 50, "SCORE",WHITE);
        int_to_str(total, str);
        putStringLarge(large_font, 120, 60, str, YELLOW);
        drawCmdWindow();
        Sleep(800);

        if (KEY_DOWN(VK_ESCAPE))
        {
            pauseAudio(&start_music);
            menu();
        }
    }
}

void Scoreboard(void) {
    int i, total;
    char str[10];

    restartAudio(&start_music);

    initializeKeyInput();

    total = game3.time_double + game2.time_double + game1.time_double;

    clearScreen();

    if (rank_data[0] == 0) rank_data[0] = total;
    else if (rank_data[1] == 0 && total != 0)
    {
        rank_data[1] = total;
        qsort(rank_data, 2, sizeof(rank_data[0]), compare);
    }
    else if (rank_data[2] == 0 && total != 0)
    {
        rank_data[2] = total;
        qsort(rank_data, 3, sizeof(rank_data[0]), compare);
    }
    else if (total != 0)
    {
        for(i = 2; i >= 0; i--)
            if (total < rank_data[i] && total >= rank_data[i-1])
            {
                rank_data[i] = total;
                break;
            }
    }

    putStringLarge(large_font, 90, 10, "Scoreboard", 15);
    putStringLarge(large_font, 79, 20, " - - - - - - ", 15);
    putStringLarge(large_font, 90, 30, "1st", 15);
    putStringLarge(large_font, 90, 40, "2nd", 15);
    putStringLarge(large_font, 90, 50, "3rd", 15);

    int_to_str(rank_data[0], str);
    putStringLarge(large_font, 150, 30, str, YELLOW);

    int_to_str(rank_data[1], str);
    putStringLarge(large_font, 150, 40, str, YELLOW);

    int_to_str(rank_data[2], str);
    putStringLarge(large_font, 150, 50, str, YELLOW);

    drawCmdWindow();

    while(1)
    {
        if (KEY_DOWN(VK_ESCAPE))
        {
            break;
        }
    }

    game1.time_double = 0;
    game2.time_double = 0;
    game3.time_double = 0;
    pauseAudio(&start_music);
    menu();
}

int main(void)
{
    openAudioFile("audio\\start.wav", &start_music);

    large_font = read_font("font.txt");

    starting();

    menu();

    destroy_font(large_font);

}
