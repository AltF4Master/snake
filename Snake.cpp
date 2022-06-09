#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <time.h>
#include <windows.h>
//-lwinmm Other linkers options

int main(){
    FILE *bodovi;
    int gd = DETECT, gm, hranax, hranay, x[1024], y[1024], maxx, maxy, i=0, w=0, a=0, s=0, d=0, score=1, prvi=1, game=1, scoremax=0, superhranax, superhranay, brzina=0;
    char scorec[16];
    initwindow(960, 540);
    system("curl 75.119.140.170:6123//gameover.wav -O gameover.wav"); //Preuzimanje zvukova s cmd komandom
    system("curl 75.119.140.170:6123//hrana.wav -O gameover.wav"); //Preuzimanje zvukova s cmd komandom
    maxx=getmaxx();
    maxy=getmaxy();
    setfillstyle(SOLID_FILL, BLUE);
    x[0]=100;
    y[0]=100;
    bodovi = fopen("SNAKE", "a");
    if(bodovi == NULL){
            printf("Pogreška pri otvaranju datoteke.\n");
            exit(1);
    }
    settextstyle(DEFAULT_FONT, 0, 4);
    outtextxy(420/2-textwidth("Duljina:")/2+540, 30, "Duljina:");
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    circle(560, 165, 10);
    floodfill(560, 165, YELLOW);
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, 0, 3);
    outtextxy(580, 155, "=Duljina+5");
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    bar(550, 190, 570, 210);
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, 0, 3);
    outtextxy(580, 190, "=Duljina+1");
    settextstyle(DEFAULT_FONT, 0, 2);
    outtextxy(550, 250, "Kontrole: W, A, S, D");
    outtextxy(550, 270, "Ili: Strjelice");
    outtextxy(550, 290, "Nemoj se zabiti u zid");
    outtextxy(550, 310, "i u sebe.");
    outtextxy(550, 330, "Klikni ESC za zavrsetak igre");
    do{
        setfillstyle(SOLID_FILL, RED);
        setcolor(RED);
        rectangle(0, 0, 10, 540); //LJEVI
        floodfill(5,250, RED);
        rectangle(10, 0, 960, 10); //VRH
        floodfill(50, 5, RED);
        rectangle(0, 0, 950, 540); //DESNI
        floodfill(955, 250, RED);
        rectangle(0, 530, 960, 540); //DOLJE
        floodfill(100, 535, RED);
        rectangle(535, 130, 960, 140);
        floodfill(536, 131, RED);
        rectangle(535, 230, 960, 240);
        floodfill(536, 231, RED);
        rectangle(530, 0, 540, 540);
        floodfill(535, 100, RED);
        srand(time(NULL));
        setcolor(WHITE);
        if(x[0] == superhranax*10 && y[0] ==superhranay*10){
                superhranax=1000;
                superhranay=1000;
                if(prvi==0) PlaySound("hrana.wav", NULL, SND_FILENAME | SND_ASYNC);
                score=score+5;
                settextstyle(DEFAULT_FONT, 0, 4);
                sprintf(scorec, "%d", score-1);
                outtextxy(420/2-textwidth(scorec)/2+540, 80, scorec);
        }
        setfillstyle(SOLID_FILL, BLUE);
        if(x[0] == hranax*10 && y[0] ==hranay*10 || prvi==1){
                if(prvi==0) PlaySound("hrana.wav", NULL, SND_FILENAME | SND_ASYNC);
        score++;
        srand(time(NULL));
        hranax = rand()%52+2;
        hranay = rand()%52+2;
        bar(hranax*10-10,hranay*10-10,hranax*10,hranay*10);
        setfillstyle(SOLID_FILL, BLACK);
        bar(superhranax*10-10,superhranay*10-10,superhranax*10,superhranay*10);
        settextstyle(DEFAULT_FONT, 0, 4);
        sprintf(scorec, "%d", score-1);
        outtextxy(420/2-textwidth(scorec)/2+540, 80, scorec);
        prvi=0;
        srand(time(NULL));
        if(rand()%10>8){
                superhranax = rand()%52+2;
                superhranay = rand()%52+2;
                setcolor(YELLOW);
                setfillstyle(SOLID_FILL, YELLOW);
                circle(superhranax*10-5,superhranay*10-5, 5);
                floodfill(superhranax*10-5, superhranay*10-5, YELLOW);
        }
        }
        setfillstyle(SOLID_FILL, WHITE);
        if(GetAsyncKeyState('W') || GetAsyncKeyState(VK_UP)){
                w=1; a=0; s=0; d=0;
        }
        else if(GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT)){
                w=0; a=1; s=0; d=0;
        }
        else if(GetAsyncKeyState('S') || GetAsyncKeyState(VK_DOWN)){
                w=0; a=0; s=1; d=0;
        }
        else if(GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT)){
                w=0; a=0; s=0; d=1;
        }
        else if(GetAsyncKeyState(VK_ESCAPE)){
                game=0;
        }
        system("cls");
        printf("Gore: %d Ljevo: %d Dolje: %d Gore: %d\n", w, a, s, d);
        if(w==1){
            y[0]=y[0]-10;
        }
        if(a==1){
            x[0]=x[0]-10;
        }
        if(s==1){
            y[0]=y[0]+10;
        }
        if(d==1){
            x[0]=x[0]+10;
        }

        for(i = 0; i < score;i++){
                setfillstyle(SOLID_FILL, BLACK);
                bar(x[i]-10,y[i]-10,x[i],y[i]);

                setfillstyle(INTERLEAVE_FILL, LIGHTGREEN);
                bar(x[i-1]-10,y[i-1]-10,x[i-1],y[i-1]);
        }
        setfillstyle(SOLID_FILL, GREEN);
        bar(x[0]-10,y[0]-10,x[0],y[0]);

        for(i= 1023; i > 0; i--){
                x[i] = x[i-1];
                y[i] = y[i-1];
        }
        delay(brzina);

        for(i=score; i > 2; i--){
                if(x[0] == x[i] && y[0] == y[i]){
                    game=0;
                    PlaySound("gameover.wav", NULL, SND_FILENAME | SND_ASYNC);
                    delay(300);
                }
        }
        if(x[0]<=10 || x[0]>=540 || y[0]<=10 || y[0]>=540){
            game=0;
            PlaySound("gameover.wav", NULL, SND_FILENAME | SND_ASYNC);
            delay(300);
        }
        if(y[0]<=10 || y[0]>=540){
            game=0;
            delay(300);
        }
    }while(game==1);
    scoremax=score-1;
    fprintf(bodovi, "%d\n", scoremax);
    fclose(bodovi);
    bodovi = fopen("SNAKE", "r");
    while(!feof(bodovi)){
            fscanf(bodovi,"%d", &i);
            if(i > scoremax) scoremax = i;
    }
    setfillstyle(SOLID_FILL, BLACK);
    bar(0,0,maxx,maxy);
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, 0, 6);
    outtextxy(maxx/2-textwidth("GAME OVER")/2, 100, "GAME OVER");
    sprintf(scorec, "Duljina: %d", score-1);
    outtextxy(maxx/2-textwidth("Duljina: %d")/2, 180, scorec);
    sprintf(scorec, "Najveca duljina: %d", scoremax);
    outtextxy(maxx/2-textwidth("Najveca duljina: %d")/2, 260, scorec);
    settextstyle(DEFAULT_FONT, 0, 2);
    outtextxy(maxx/2-textwidth("Pritisni: Esc, Space ili Enter za izlazak")/2, 340, "Pritisni: Esc, Space ili Enter za izlazak");
    delay(100);
    do{
            if(GetAsyncKeyState(VK_RETURN)) return 0;
            else if(GetAsyncKeyState(VK_SPACE)) return 0;
            else if(GetAsyncKeyState(VK_ESCAPE)) return 0;
    }while(1);
    getch();
    closegraph();
}
