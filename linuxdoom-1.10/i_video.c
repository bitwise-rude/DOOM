#include "i_video.h"
#include <stdio.h>
#include <raylib.h>
#include "d_main.h"
#include "doomdef.h"
#include "v_video.h"
#include "d_event.h"

#define RAY_SCALE 3

static Color game_palette[256];

void I_InitGraphics (void){
    InitWindow(SCREENWIDTH * RAY_SCALE,SCREENHEIGHT * RAY_SCALE, "Doom, ported by Meyan");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);
}

void I_StartFrame (void)
{
}

void I_StartTic (void){
    event_t event;

    int keypresses[] = {
        KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN, 
        257, 256, 258, 32, 
        KEY_LEFT_CONTROL, KEY_RIGHT_CONTROL,

        // F - keys function keys
        290, 291, 292, 293, 294, 295, 296, 297,
        298, 299, 300, 301,

        KEY_LEFT_SHIFT, KEY_RIGHT_SHIFT,
        KEY_RIGHT_ALT, KEY_LEFT_ALT,

        259, 

        65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
        75, 76, 77, 78, 79, 80, 81, 82, 83, 84,
        85, 86, 87, 88,89,90,
    };

    int equivalents[] = {
        KEY_LEFTARROW, KEY_RIGHTARROW, KEY_UPARROW, KEY_DOWNARROW,
        KEY_ENTER, KEY_ESCAPE, KEY_TAB, KEY_SPACE, 
        KEY_RCTRL, KEY_RCTRL,

        // Function Keys
        KEY_F1,KEY_F2,KEY_F3,KEY_F4,KEY_F5,KEY_F6,		
        KEY_F7,KEY_F8,KEY_F9,KEY_F10,KEY_F11,KEY_F12,		

        // others
        KEY_RSHIFT, KEY_RSHIFT, KEY_RALT, KEY_LALT,
        
        KEY_BACKSPACE,

        97, 98, 99, 100, 101, 102, 103, 104, 105, 106,
        107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
        117, 118, 119, 120, 121, 122,
    }; 

    if (WindowShouldClose()) {
        CloseWindow();
        return;
        // TODO: Hanedling returns
    }

    for (int i=0; i < (sizeof(keypresses) / sizeof(int)); i++){
        if (IsKeyPressed(keypresses[i])){
            event.type = ev_keydown;
            event.data1 = equivalents[i];
	        D_PostEvent(&event);
        }
        if (IsKeyReleased(keypresses[i])){
            event.type = ev_keyup;
            event.data1 = equivalents[i];
	        D_PostEvent(&event);
        }
    }

    // mouse support?? TODO
}



void I_ShutdownGraphics(void){
    CloseWindow();
}

void I_SetPalette (byte* palette){
    int c;
    int r,g,b;

    for (int i=0; i<256; i++){
		    c = gammatable[usegamma][*palette++];
            r = (c<<8) + c;
            c = gammatable[usegamma][*palette++];
            g = (c<<8) + c;
            c = gammatable[usegamma][*palette++];
            b = (c<<8) + c;

            game_palette[i] = (Color) {
            .r = r,
            .g = g,
            .b = b,
            .a = 255,
        };
    }
}


// Each screen is [SCREENWIDTH*SCREENHEIGHT]; 

void I_FinishUpdate (void){
    ClearBackground(RAYWHITE);
    BeginDrawing();
        for (int j = 0; j < SCREENWIDTH; j++)
        {
            for (int i = 0; i < SCREENHEIGHT; i++)
            {
                Color color = game_palette[screens[0][i*SCREENWIDTH+j]];
                DrawRectangle(j*RAY_SCALE, i*RAY_SCALE, RAY_SCALE, RAY_SCALE, color);
            }
        }
    EndDrawing();
}

void I_UpdateNoBlit (void){
}

void I_ReadScreen (byte* scr){
    memcpy(scr, screens[0], SCREENHEIGHT*SCREENWIDTH);
}
