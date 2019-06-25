/*
 * 
 * ADA Self Study-Gautham,Anirudh,Arvindh,Anannya
 * MANCALA - A GAME OF GEMS
 * 
*/

#include <iostream>
#include<stdlib.h>
#include<iomanip>
using namespace std;


int mancalaBoard[14] = { 0 };
int currentPlayer;
void capture(int landingPit);
void initialiseBoard();
void displayBoard();
void playerTurn(int);
bool checkIfBoardIsEmpty(int currentPlayer);
void finalcount();
void mainDisplay();

//starting the game with 4 stones in each pit
void initialiseBoard(){
//mancalaBoard[6] = player 1's store and mancalaBoard[13] = player 2's store
  for(int i = 0;i < 14; i++){
    if(i!=6 && i!=13){
      mancalaBoard[i] = 4;
    }  
  currentPlayer = 1;
  }
}

//capture opposite stones if the player lands in an empty pit.
void capture(int landingPit, int currentPlayer){
  landingPit += 2;
  if(landingPit!=6 && landingPit != 13 && mancalaBoard[landingPit-1] == 0){
    if (currentPlayer == 1){
      mancalaBoard[6] +=  mancalaBoard[12- landingPit] + mancalaBoard[landingPit];
      mancalaBoard[landingPit] = mancalaBoard[12-landingPit] = 0;
    }
    else{
      mancalaBoard[13] +=  mancalaBoard[12- landingPit] + mancalaBoard[landingPit];
      mancalaBoard[landingPit] = mancalaBoard[12-landingPit] = 0;
    }
  }
}   

//printing out the current state of the mancala board 
void displayBoard(){
  for(int i = 12; i >= 7; i--){
    cout<<"\t:"<<i<<":";
  }
  cout<<endl;
  for(int i = 12; i >= 7; i--){
    cout<<"\t|"<<mancalaBoard[i]<<"|";
  }
  cout<<endl<<endl;
  for(int i = 0; i < 6; i++){
    cout<<"\t:"<<i<<":";
  }
  cout<<endl;
  for(int i = 0; i < 6; i++){
    cout<<"\t|"<<mancalaBoard[i]<<"|";
  }
  cout<<endl;
  cout<<"\nPlayer 1's store: "<<mancalaBoard[6];
  cout<<"\nPlayer 2's store: "<<mancalaBoard[13];
  
} 

//checking if the a player's board is empty after every turn (to end the game)
bool checkIfBoardIsEmpty(int currentPlayer){
  int flag =0;
  if(currentPlayer == 1){
    for (int i = 0;i < 6; i++){
      if(mancalaBoard[i] != 0){
        flag = 1;
        break;
      }
    }
    if(flag == 0)
      return true;
    else
      return false;
  }
  else{
    for (int i = 7;i < 13; i++){
      if(mancalaBoard[i] != 0){
        flag = 1;
        break;
      }
    }
    if(flag == 0)
      return true;
    else
      return false;
  }
  
}

//final counting of stones in each player's store
void finalcount(){

  if(mancalaBoard[6] > mancalaBoard[13]){
    cout<<"\nPlayer 1 wins!";
  }
  else if(mancalaBoard[6] < mancalaBoard[13]){
    cout<<"\nPlayer 2 wins!";
  }
  else{
    cout<<"\nThe game is a draw.";
  }
}

//main working code that makes the moves for each player's turn.
void playerTurn(int currentPlayer){
  
  int chosenPit, totStones, i,flag=0;

  cout << "\nPLAYER " <<currentPlayer<<"'S TURN!" << endl;
  if(currentPlayer == 1){
    a:
      cout<<"\nEnter the index of the pit to start playing (0,1,2,3,4,5): ";
      cin>>chosenPit;
    if(chosenPit>5){
      cout<<"\nWrong pit chosen!..try again." << endl;
      goto a;
    }
  }
  else{
    b:
      cout<<"\nEnter the index of the pit to start playing (7,8,9,10,11,12): ";
      cin>>chosenPit;
    if(chosenPit<7){
      cout<<"\nWrong pit chosen!..try again." << endl;
      goto b;
    }
  }
  
  //traversal till stones in chosen pit become 0
  

    totStones = mancalaBoard[chosenPit];
    for(i = 1; i <= totStones; i++){
    	mancalaBoard[chosenPit]=0;
       if((chosenPit + i)%14 == 13 && currentPlayer == 1){
          //skipping 13 for player 1
          flag=1;
          continue;
       }
       if((chosenPit + i)%14 == 6 && currentPlayer == 2){
          //skipping 6 for player 2
          flag=1;
          continue;
       }

       if((chosenPit + i) > 13){
          mancalaBoard[(chosenPit + i)%14] += 1;  
       }
       else{
         mancalaBoard[chosenPit + i] += 1;  
        }  
    }

  //finding the landing pit
  int landingPit = ((chosenPit + i - 1)% 14);
  if(flag == 1){
    //executing skip
    mancalaBoard[landingPit+1]++;
    flag=0;
  }
  capture(landingPit,currentPlayer);

  cout << "\nPit Player "<< currentPlayer<<" landed in is: "<< landingPit << endl;
  displayBoard();

  //check if the board is empty after every move for the corresponding player
  if(checkIfBoardIsEmpty(currentPlayer)){
    cout<<"\nPlayer "<<currentPlayer<< "has completed the game. \nCapturing opponent's stones...\n";
    if(currentPlayer == 1){
      for(i = 7;i <= 12;i++){
        mancalaBoard[6] += mancalaBoard[i];
      }
    }
    else{
      for(i = 0;i <= 5;i++){
        mancalaBoard[13] += mancalaBoard[i];
      }
    }
    displayBoard();
    finalcount();
    exit(0);
  }

  //get another turn if you land in your store
  if(currentPlayer == 1){
    if(landingPit == 6){
    cout << "\nExtra turn for player " << currentPlayer << endl;
    playerTurn(currentPlayer);
      }
    else{
      currentPlayer = 2;
      playerTurn(currentPlayer);
      }
  }

  else if(currentPlayer == 2){
    if(landingPit == 13){
      cout << "\nExtra turn for player " << currentPlayer << endl;
      playerTurn(currentPlayer);
    }
    else{
      currentPlayer = 1;
      playerTurn(currentPlayer);
    }
  } 
}

//start screen for the game
void mainDisplay(){
  char ch;
  cout<<setw(95)<<"------------MANCALA!------------";
  cout<<"\nGame rules: ";
  cout<<"\n· The Mancala board is made up of two rows of six holes, or pits, each. Four marbles are placed in each of the 12 holes."

"\n· Each player has a store (called a Mancala) to the right side of the Mancala board."

"\n· The game begins with one player picking up all of the pieces in any one of the holes on their side."

"\n· Moving counter-clockwise, the player deposits one of the stones in each hole until the stones run out."

"\n· If you run into your own store, deposit one piece in it. If you run into your opponent's store, skip it."

"\n· If the last piece you drop is in your own store, you get a free turn."

"\n· If the last piece you drop is in an empty hole on your side, you capture that piece and any pieces in the hole directly opposite."

"\n· Always place all captured pieces in your store."

"\n· The game ends when all six spaces on one side of the Mancala board are empty."

"\n· The player who still has pieces on his side of the board when the game ends capture all of those pieces."

"\n· Count all the pieces in each store. The winner is the player with the most pieces.";

  cout<<"Start new game?(y/n) : ";
    cin>>ch;
  if(ch == 'y'|| ch == 'Y'){
    cout<<"\n\n";
    initialiseBoard();
    displayBoard();
    playerTurn(1);
  }
  else{
    cout<<"Quitting...";
    exit(0);
  }
}

//main function
int main(){
  mainDisplay();

  return 0;
}