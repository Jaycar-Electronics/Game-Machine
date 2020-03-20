#include <SPI.h>
#include <Gamebuino.h>
Gamebuino gb;

const uint8_t gamelogo[] PROGMEM={
  84,20,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00011111,B11111111,B11110000,B01111111,B11111111,B11000001,B11111111,B11111111,B00000000,B00000000,B00000000,
B00011111,B11111111,B11110000,B01111111,B11111111,B11000001,B11111111,B11111111,B00000000,B00000000,B00000000,
B00000000,B00110000,B00000000,B00000000,B11000000,B00000000,B00000011,B00000000,B00000000,B00000000,B00000000,
B00000000,B00110000,B00000000,B00000000,B11000000,B00000000,B00000011,B00000000,B00000000,B00000000,B00000000,
B00000000,B00110000,B00000000,B00000000,B11000000,B00000000,B00000011,B00000000,B00000000,B00000000,B00000000,
B00000000,B00110000,B00000000,B00000000,B11000000,B00000000,B00000011,B00000000,B00000000,B00000000,B00000000,
B00000000,B00110000,B00000000,B00000000,B11000000,B00000000,B00000011,B00000000,B00000000,B00000000,B00000000,
B00000000,B00110000,B00000000,B00000000,B11000000,B00000000,B00000011,B00000000,B00000000,B00000000,B00000000,
B00000000,B00110000,B10000111,B11100000,B11000010,B00001111,B11000011,B00111111,B00011111,B00000000,B00000000,
B00000000,B00110000,B10001000,B00000000,B11000101,B00010000,B00000011,B01000000,B10100000,B00000000,B00000000,
B00000000,B00110000,B10001000,B00000000,B11001000,B10010000,B00000011,B01000000,B10100000,B00000000,B00000000,
B00000000,B00110000,B10001000,B00000000,B11010000,B01010000,B00000011,B01000000,B10111111,B00000000,B00000000,
B00000000,B00110000,B10001000,B00000000,B11011111,B11010000,B00000011,B01000000,B10100000,B00000000,B00000000,
B00000000,B00110000,B10001000,B00000000,B11010000,B01010000,B00000011,B01000000,B10100000,B00000000,B00000000,
B00000000,B00110000,B10000111,B11100000,B11010000,B01001111,B11000011,B00111111,B00011111,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
};

const uint8_t gamex[] PROGMEM={
  16,16,
B00000000,  B00000000,
B01000000,  B00000010,
B00110000,  B00000100,
B00011100,  B00001100,
B00000110,  B00001000,
B00000011,  B00011000,
B00000001,  B10110000,
B00000000,  B11100000,
B00000000,  B11100000,
B00000001,  B10110000,
B00000011,  B00011000,
B00000110,  B00001000,
B00011100,  B00001100,
B00110000,  B00000100,
B01000000,  B00000010,
B00000000,  B00000000,
};

const uint8_t gameo[] PROGMEM={
  16,16,
B00000000,  B00000000,
B00000111,  B11100000,
B00001111,  B11110000,
B00011000,  B00000000,
B00110000,  B00111100,
B01100000,  B00000110,
B01100000,  B00000110,
B01100000,  B00000110,
B01100000,  B00000110,
B01100000,  B00000110,
B01100000,  B00000110,
B00110000,  B00001100,
B00011000,  B00011000,
B00001111,  B11110000,
B00000111,  B11100000,
B00000000,  B00000000,
};

char game[] ="O4O444X4X";       //game board, anything under @ is empty, 'X' and 'O' are occupied
int mv=-1;                      //-1 no game, 0 player move, 1 computer move, 2 player win, 3 computer win, 4 tie
int cx=1;     //player cursor position
int cy=1;
int wgl=0;

void setup(){
  randomSeed(analogRead(4));
  gb.begin();
  gb.titleScreen(gamelogo);
}

void loop(){
  if(gb.update()){
    if(mv==-1){         //start game menu
      for(int n=0;n<9;n++){game[n]='0';}    //clear grid
      gb.display.setColor(1);
      gb.display.cursorX=30;
      gb.display.cursorY=5;
      gb.display.print("Press:");
      gb.display.cursorX=5;
      gb.display.cursorY=15;
      gb.display.print("A for Player Start");
      gb.display.cursorX=10;
      gb.display.cursorY=25;
      gb.display.print("B for Computer");
      if(gb.buttons.pressed(BTN_A)){mv=0;}
      if(gb.buttons.pressed(BTN_B)){mv=1;}
    }else{
      gb.display.drawLine(5,15,53,18);
      gb.display.drawLine(5,31,53,34);
      gb.display.drawLine(21,0,23,47);
      gb.display.drawLine(37,0,39,47);
      for(int n=0;n<9;n++){
        if(game[n]=='O'){gb.display.drawBitmap((n%3)*16+5,(n/3)*16,gameo);}
        if(game[n]=='X'){gb.display.drawBitmap((n%3)*16+5,(n/3)*16,gamex);}
      }
      if(mv==0){      //player move
        gb.display.drawBitmap(cx*16+4+abs(wgl),cy*16,gamex);
        wgl++;
        if(wgl>3){wgl=-3;}
      }
      if(mv<2){                         //game in progress
        int k=0;
        for(int n=0;n<9;n++){
          if(game[n]<'@'){k++;}       //any vacant squares
        }
        if(k==0){mv=4;}               //No? tie!
        gb.display.cursorX=60;
        gb.display.cursorY=5;
        gb.display.print("Turn:");
        gb.display.cursorX=52;
        gb.display.cursorY=15;
        if(mv==0){
          gb.display.print(" Player");
          if(gb.buttons.pressed(BTN_UP)){cy--;if(cy<0){cy=0;}}
          if(gb.buttons.pressed(BTN_DOWN)){cy++;if(cy>2){cy=2;}}
          if(gb.buttons.pressed(BTN_LEFT)){cx--;if(cx<0){cx=0;}}
          if(gb.buttons.pressed(BTN_RIGHT)){cx++;if(cx>2){cx=0;}}
          if(gb.buttons.pressed(BTN_A)){        //make a move!
            if(game[cx+cy*3]>'@'){              //invalid!
              gb.sound.playNote(50,20,0);
            }else{
              game[cx+cy*3]='X';
              mv=1;                             //computer's move
              if(threeinarow(game,'X')){mv=2;}  //player wins
            }
          }
        }
        if(mv==1){gb.display.print("Computer");
          computerAI();
          mv=0;                             //player's move
          if(threeinarow(game,'O')){mv=3;}  //player wins
          gb.sound.playNote(800,3,0);
        }
      }else{                            //game over
        if(gb.buttons.pressed(BTN_A)){mv=-1;}        //back to menu if game over
        gb.display.cursorX=52;
        gb.display.cursorY=25;
        if(mv==2){gb.display.print(" Player");}
        if(mv==3){gb.display.print("Computer");}
        gb.display.cursorX=57;
        gb.display.cursorY=35;
        if(mv==4){
          gb.display.print(" TIE");
        }else{
          gb.display.print("WINS");
        }
        gb.display.cursorX=50;
        gb.display.cursorY=5;
        gb.display.print("PRESS A!");
      }
    }
  }
}

int threeinarow(char game[],char a){
  if((game[0]==a)&&(game[1]==a)&&(game[2]==a)){return 1;}
  if((game[3]==a)&&(game[4]==a)&&(game[5]==a)){return 1;}
  if((game[6]==a)&&(game[7]==a)&&(game[8]==a)){return 1;}
  if((game[0]==a)&&(game[4]==a)&&(game[8]==a)){return 1;}
  if((game[2]==a)&&(game[4]==a)&&(game[6]==a)){return 1;}
  if((game[0]==a)&&(game[3]==a)&&(game[6]==a)){return 1;}
  if((game[1]==a)&&(game[4]==a)&&(game[7]==a)){return 1;}
  if((game[2]==a)&&(game[5]==a)&&(game[8]==a)){return 1;}
  return 0;
}

void computerAI(){
  char cgame[]="333333333";      //computer's copy of the board
  int cscore[9]={0,0,0,0,0,0,0,0,0};      //score for each move
  for(int i=0;i<1000;i++){      //number of test moves
    for(int n=0;n<9;n++){
      cgame[n]=game[n];   //copy board
      if(cgame[n]<'@'){
        cgame[n]=(random(0,2)?'X':'O');
      }
    }
    for(int n=0;n<9;n++){     //scan board for wins
      if((cgame[n]=='O')&&(game[n]<'@')){ //is it a move that computer can make?
        if(threeinarow(cgame,'O')){   //possible computer win
          cscore[n]++;
        }
        if(threeinarow(cgame,'X')){   //possible computer win
          cscore[n]--;
        }
      }
    }
  }
    int nmax=-10000;
    int npos=-1;
      for(int n=0;n<9;n++){
      if(cscore[n]>nmax){
        nmax=cscore[n];
        npos=n;
      }
    }
    if(game[npos]>'@'){
      for(int n=0;n<9;n++){
        if(game[n]<'@'){game[n]='O';break;}     //make any move and continue
      }
    }else{
      game[npos]='O';       //make a move!
    }
}

