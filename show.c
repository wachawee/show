#include <stdlib.h>
#include <string.h>

// include NESLIB header
#include "neslib.h"

// include CC65 NES Header (PPU)
#include <nes.h>

// link the pattern table into CHR ROM
//#link "monster.s"

// BCD arithmetic support
#include "bcd.h"
//#link "bcd.c"

// VRAM update buffer
#include "vrambuf.h"
//#link "vrambuf.c"

/*{pal:"nes",layout:"nes"}*/
const char PALETTE[32] = { 
  0x03,			// screen color

  0x11,0x30,0x27,0x0,	// background palette 0
  0x1c,0x20,0x2c,0x0,	// background palette 1
  0x00,0x10,0x20,0x0,	// background palette 2
  0x06,0x16,0x26,0x0,   // background palette 3

  0x16,0x35,0x24,0x0,	// sprite palette 0
  0x00,0x37,0x25,0x0,	// sprite palette 1
  0x0d,0x2d,0x3a,0x0,	// sprite palette 2
  0x0d,0x27,0x2a	// sprite palette 3
};

// setup PPU and tables
void setup_graphics() {
  // clear sprites
  oam_clear();
  // set palette colors
  pal_all(PALETTE);
}

void main(void)
{
  int a;
  int i,j;
  int x,y,m,n;
  int num;
  int posx[] = {2,7,12,17,22,27};
  int posy[] = {2,7,12,17,22,27};
  
  char snum[3];
  char pad;
  setup_graphics();
  // draw message  
  num=0;
  for(m=0;m<6;m++)
  for(n=0;n<5;n++){
  x=posx[m]; y=posy[n];
  
  for(j=0;j<4;j++){
  for(i=0;i<4;i++){
      vram_adr(NTADR_A(x+i,y+j));
      vram_put(num);
      num = num +1;
  }
  }
  }
  
  // enable rendering
  ppu_on_all();
  // infinite loop
  while(1) {
    pad = pad_trigger(0);
    if(pad & PAD_A){
      	a++;
      	itoa(a,snum,10);
    	ppu_off();
        vram_adr(NTADR_A(2,2));
        vram_write(snum, 2);
      	ppu_on_all();
    }else if(pad & PAD_B){
      	a--;
      	itoa(a,snum,10);
    	ppu_off();
        vram_adr(NTADR_A(2,2));
        vram_write(snum, 2);
      	ppu_on_all();
    }
  }
}
                        