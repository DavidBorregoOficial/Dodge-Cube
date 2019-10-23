/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#define MAX_ENEMIGOS 100 //cantidad de bolas

typedef struct Enemies{ //estructura de los circulos
    int speed;
    Rectangle body;
} Enemies;

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1280;
    int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");


    Enemies bola [MAX_ENEMIGOS];
    for(int i = 0; i < MAX_ENEMIGOS; i++) //array con velocidad, tamaño, posicion de los enemigos
    {
        bola[i].body.width = 40;
        bola[i].body.height = 40;
        bola[i].body.x = GetRandomValue(screenWidth, screenWidth *2);
        bola[i].body.y = GetRandomValue(0, screenHeight-bola[i].body.height);
        bola[i].speed = GetRandomValue(-3, -6);
    }     
    Rectangle rec = { 0, 300, 20, 20 }; //jugador
    Rectangle fondo = { 0, 0, screenWidth, screenHeight }; //fondo gameover
    
    int puntoplayer = 0; //puntuacion
    int hightscore = 0; //record de puntuacion
    
    bool GameOver = true;
    bool pause = false;
    int framesCounter = 30;
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        if(GameOver) 
            {
                if (!pause)
                    {
                        if(IsKeyDown (KEY_UP)) rec.y -=10; // Controles
                        if(IsKeyDown (KEY_DOWN)) rec.y +=10;
                        if(IsKeyDown (KEY_LEFT)) rec.x -=10;
                        if(IsKeyDown (KEY_RIGHT)) rec.x +=10;
                     
                        if(rec.y <= 0) rec.y = 0; //limites de pantalla para el jugador
                        if(rec.x <= 0) rec.x = 0;
                        else if(rec.y + rec.height >= screenHeight) rec.y = screenHeight - rec.height;
                        else if(rec.x + rec.width >= screenWidth) rec.x = screenWidth - rec.width;
                     
                        for(int i = 0; i < MAX_ENEMIGOS; i++)
                            {        
                                if(bola[i].body.x <= -40) //reset de enemigos
                                {
                                    bola[i].body.x = GetRandomValue(screenWidth, screenWidth *2);
                                    bola[i].body.y = GetRandomValue(0, screenHeight-bola[i].body.height);
                                    puntoplayer += 10; //suma de puntuacion
                                    if(puntoplayer >= hightscore) //si el puntuaje supera el highscore
                                    {
                                        hightscore = puntoplayer;
                                    }
                                }
                                bola[i].body.x += bola[i].speed; //direccion de los enemigos
                                if(CheckCollisionRecs(bola[i].body,rec)) //colision con enemigos = derrotado
                                    {
                                        if(bola[i].body.x >= rec.x || bola[i].body.y <= rec.y + rec.width)
                                            {
                                                pause = !pause;                                        
                                                GameOver = !GameOver;
                                            }            
                                    }                            
                            }
                        
                    }
            }
        if (IsKeyPressed(KEY_SPACE)) //pausa
            {
                pause = !pause;
                framesCounter = 30;
            }
        if(!GameOver)
            {
                if(IsKeyPressed (KEY_K)) //tecla de reset
                    {
                        for(int i = 0; i < MAX_ENEMIGOS; i++) 
                        {
                            rec.x = 0;
                            rec.y = 300;
                            bola[i].body.x = GetRandomValue(screenWidth, screenWidth *2);
                            bola[i].body.y = GetRandomValue(0, screenHeight-bola[i].body.height);
                            puntoplayer = 0;                        
                            GameOver = true;  
                            pause = false;                            
                        }                    
                    }           
            }            
        else
        {
            framesCounter++;
        }
             
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText(FormatText("%i", puntoplayer), 500, 10, 80, RED); //puntuacion
            DrawText(FormatText("%i", hightscore), 700, 10, 80, GREEN); //alta puntuacion
            DrawRectangleRec(rec, BLUE);
            for(int i = 0; i < MAX_ENEMIGOS; i++)
            {
                DrawRectangle(bola[i].body.x,bola[i].body.y,bola[i].body.width,bola[i].body.height,RED); //enemigos
            }
                if(pause)
                {
                    if((framesCounter/50)%2) DrawText("PAUSE", (screenWidth - MeasureText("PAUSE", 85))/2, screenHeight/2.25 -5, 75, RED); //pausa
                }            
            if(!GameOver) 
            {
                DrawRectangleRec(fondo,BLACK); //fondo game over
                DrawText("GAMEOVER", 450, 300, 60, LIGHTGRAY);
                DrawText("Press k to restart", 350, 430, 60, LIGHTGRAY); // boton de reset
            }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}