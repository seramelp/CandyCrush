package gr.auth.ee.dsproject.crush.player;

import gr.auth.ee.dsproject.crush.CrushUtilities;
import gr.auth.ee.dsproject.crush.board.Board;

import java.util.ArrayList;

public class RandomPlayer implements AbstractPlayer
{
  private int id;
  private String name;
  private int score;
  
  /*
  Constructor of the RandomPlayer class, which accepts the variable pid (player color index) as an argument
  and initializes the variables id (player color index), name (player name), score (number of player candies)
  */
  public RandomPlayer(Integer pid)
  {
	  id=pid;
	  name="Melpo_Christina";
      score=0;
  }
  
  //Function that accepts and defines the variable id
  public void setId (int id)
  {
	  this.id=id;
  }
  
  //Return function of the value of the variable id
  public int getId ()
  {
	  return id;
  }

  //Ófunction that accepts and defines the variable name
  public void setName (String name)
  {
	  this.name=name;
  }

  //Return value of the variable name
  public String getName ()
  {
	  return name;
  }

  //Function that accepts and defines the variable score
  public void setScore (int score)
  {
	  this.score=score;
  }

 //Return function of the value of the score variable
  public int getScore ()
  {
	  return score;
  }

  

  /*Method of randomly selecting the next move of the player through the variables
    index_: a random selection index of one of the available moves
    randomMove: table that accepts the getRandomMove result
    playerMove: return table of getNextMove results
  */
  public int[] getNextMove (ArrayList<int[]> availableMoves, Board board)
  {
	
	  int index_=(int) (Math.random()*availableMoves.size()); 
	  int[] randomMove=new int[3];  
	  int[] playerMove=new int[4];
	  randomMove= CrushUtilities.getRandomMove(availableMoves ,index_);
	  playerMove[0]=randomMove[0];
	  playerMove[1]=randomMove[1];
	  if (randomMove[2]== CrushUtilities.LEFT)
	  {
		  playerMove[2]=randomMove[0]-1;
		  playerMove[3]=randomMove[1];
	  }
	  if (randomMove[2]== CrushUtilities.DOWN)
	  {
		  playerMove[2]=randomMove[0];
		  playerMove[3]=randomMove[1]-1;
	  }
	  if (randomMove[2]== CrushUtilities.RIGHT)
	  {
		  playerMove[2]=randomMove[0]+1;
		  playerMove[3]=randomMove[1];
	  }
	  if (randomMove[2]== CrushUtilities.UP)
	  {
		  playerMove[2]=randomMove[0];
		  playerMove[3]=randomMove[1]+1;
	  }
	 
	  return playerMove;

   

  }

}
