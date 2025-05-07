#include<stdio.h>
#include<nds.h>
#include "player.h"
#include "grid_logic.h"
#include<nf_lib.h>
#define cls consoleClear();
#define blank 32
#define X 88
#define O 79
#ifndef PLAYER_H
#define PLAYER_H
#ifndef GRID_LOGIC_H
#define GRID_LOGIC_H
using namespace std;

void OnKeyPressed(int key) {
   if(key > 0)
      iprintf("%c", key);
}
int main(void)
{
	//inizializzazione disegno immagine bmp
	consoleDemoInit();
	NF_SetRootFolder("NITROFS");
	NF_Set2D(0, 5);
	NF_InitBitmapBgSys(0, 1);
	NF_Init16bitsBgBuffers();
	NF_Init16bitsBackBuffer(0);
	NF_Enable16bitsBackBuffer(0);
	NF_LoadBMP("sfondo_di_gioco", 0);
	NF_Draw16bitsImage(0, 0, 0, 0, false);
	NF_Flip16bitsBackBuffer(0);

	//musica di sottofondo
/*	soundEnable();
	NF_InitRawSoundBuffers();
	NF_LoadRawSound("music",1,22050,0);
	NF_PlayRawSound(1,127,64,true,0);*/
	iprintf("\x1b[9,0H################################");
		iprintf("\x1b[10,0HPremi il tasto start per giocare");
		iprintf("\x1b[12,0H################################");
	while(1){
			
		swiWaitForVBlank();
		scanKeys();
			if(keysDown() & KEY_START) break;
	}
	cls
	touchPosition touch;
	bool flag,sl=false,win=false,swap=false;
	u8 r=3,c=3,turn=0,o=0;
	char pg[3][3];
	player p[2];
	p[0].symbol=X;
	p[1].symbol=O;
	for(u8 i=0;i<2;i++)
	{
		Keyboard *kbd = keyboardDemoInit();

		kbd->OnKeyPressed = OnKeyPressed;
	
	      iprintf("\x1b[3;0Hinserire nome player %d:\n",i+1);
	
	      scanf("%s", p[i].name);
	      swiWaitForVBlank();
		  cls
	}
	do
	{	
		clear_grid(pg);
		r=3;c=3;
		win=false;
		turn=0;
		do
		{
			swiWaitForVBlank();
			if(swap==false)o=turn%2;
			else{
				if(turn%2==0)o=1;
				else o=0;
			}
			do{
				iprintf("\x1b[%d;9H>",4+o*2);
				iprintf("\x1b[%d;8H>",4+o*2);
				iprintf("\x1b[4;9H%c %s:%d\x1b[6;9H%c %s:%d\x1b[8;9Hturno:%d",p[0].symbol,p[0].name,p[0].print_p(),p[1].symbol,p[1].name,p[1].print_p(),turn);
				print_grid(pg);
				swiWaitForVBlank();
				scanKeys();
				touchRead(&touch);
				r=rows(touch);
				c=columns(touch);
				flag=positioning(r,c,pg);
				if(r==3||c==3) flag=false;
				cls
			}while(flag==false);
			pg[r][c]=p[o].symbol;
			turn++;
			sl=check_grid(pg);
			win=p[o].check_win(pg);
		}while(win==false&&sl==true);	
		if(win==true)
		{
			p[o].incr_point();
			iprintf("\x1b[9;2Hvince %s %c in %d turni\n",p[o].name,p[o].symbol,turn);
		}
		else if(sl==false&&win==false) iprintf("\x1b[9;2Havete pareggiato\n");
		iprintf("\x1b[11;1H premere select per continuare\x1b[12;1He invertire l'ordine di gioco");	
		swiWaitForVBlank();
		do
		{
			scanKeys();
				if(keysDown() & KEY_SELECT)
				{
					p[0].swap_order();
					p[1].swap_order();
					if(swap==false)swap=true;
					else swap=false;
					break;
				}
		} while (1);	
	}while(1);
}
#endif
#endif

