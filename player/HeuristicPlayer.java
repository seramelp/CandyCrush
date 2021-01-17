package gr.auth.ee.dsproject.crush.player;

import gr.auth.ee.dsproject.crush.CrushUtilities;
import gr.auth.ee.dsproject.crush.board.Board;
import gr.auth.ee.dsproject.crush.board.Tile;

import java.util.ArrayList;

public class HeuristicPlayer implements AbstractPlayer
{

  int score;
  int id;
  String name;

  public HeuristicPlayer (Integer pid)
  {
    id = pid;
    score = 0;
  }

  @Override
  public String getName ()
  {

    return "evaluation";

  }

  @Override
  public int getId ()
  {
    return id;
  }

  @Override
  public void setScore (int score)
  {
    this.score = score;
  }

  @Override
  public int getScore ()
  {
    return score;
  }

  @Override
  public void setId (int id)
  {

    this.id = id;

  }

  @Override
  public void setName (String name)
  {

    this.name = name;

  }

  @Override
  public int[] getNextMove (ArrayList<int[]> availableMoves, Board board)
  {

    int[] move = availableMoves.get(findBestMoveIndex(availableMoves, board));

    return calculateNextMove(move);

  }

  int[] calculateNextMove (int[] move)
  {

    int[] returnedMove = new int[4];

    if (move[2] == CrushUtilities.UP) {
      // System.out.println("UP");
      returnedMove[0] = move[0];
      returnedMove[1] = move[1];
      returnedMove[2] = move[0];
      returnedMove[3] = move[1] + 1;
    }
    if (move[2] == CrushUtilities.DOWN) {
      // System.out.println("DOWN");
      returnedMove[0] = move[0];
      returnedMove[1] = move[1];
      returnedMove[2] = move[0];
      returnedMove[3] = move[1] - 1;
    }
    if (move[2] == CrushUtilities.LEFT) {
      // System.out.println("LEFT");
      returnedMove[0] = move[0];
      returnedMove[1] = move[1];
      returnedMove[2] = move[0] - 1;
      returnedMove[3] = move[1];
    }
    if (move[2] == CrushUtilities.RIGHT) {
      // System.out.println("RIGHT");
      returnedMove[0] = move[0];
      returnedMove[1] = move[1];
      returnedMove[2] = move[0] + 1;
      returnedMove[3] = move[1];
    }
    return returnedMove;
  }

	// function for calculate the best move
  int findBestMoveIndex (ArrayList<int[]> availableMoves, Board board)
  {
	  double[] evals = new double[availableMoves.size()];

	  int bestmove=0;
	  double bestscore=0;
	  double movescore=0;


	  for(int i=0;i<evals.length;i++){

		  movescore=moveEvaluation(availableMoves.get(i),board);

		  if(movescore>bestscore){

			  
			  bestscore=movescore;
			  bestmove=i;
		  }

	  }

	  return bestmove;



  }

	// function for calculate the score of the move
  double moveEvaluation (int[] move, Board board)
  {
    
	  int[] movedo=new int[4];
	  movedo=calculateNextMove ( move);
	  int x=movedo[2];
	  int y=movedo[3];
	  Tile movechange=new Tile() ;
	  movechange.setX(x);
	  movechange.setY(y);/


	  Board aBoard;
	  aBoard =CrushUtilities.boardAfterFirstMove(board, move);
	  double candies=calculateTilesThatWillCrush(aBoard);

	  int height=heightofthemove(aBoard,movechange);


	  double verorhor;
	  if(vertOrHor(aBoard,movechange)==true) verorhor=4;
	  else verorhor=8;

	  return candies+verorhor+10-height;

  }




//A function that calculates the number of candies belonging to 3 groups, 4 groups, .. n-groups.
double calculateTilesThatWillCrush(Board board){

	int verCandies=verCandies(board);
	int horCandies=horCandies(board);
	return verCandies+horCandies;


}

//Calculation function of horizontal candies
int horCandies(Board board){

	  ArrayList <Tile>horArray=new ArrayList<Tile>();

	  Tile a=new Tile();/
	  Tile b=new Tile();
	  Tile c=new Tile();
	  Tile d=new Tile();


	  
	  for(int i=0;i<CrushUtilities.NUMBER_OF_PLAYABLE_ROWS;i++){
		  for(int j=0;j<(CrushUtilities.NUMBER_OF_COLUMNS-2);j++){

			 a.setX(j);
			 a.setY(i);
			 int matchType=a.getColor();


			  b.setX(j+1);
			  b.setY(i);
			  c.setX(j+2);
			  c.setY(i);
			  d.setY(i);



		  if(b.getColor()==matchType && c.getColor()==matchType){

			  do{
				  horArray.add(board.giveTileAt(j,i));
				  j++;
				  d.setX(j);

			  }
			  while(j<CrushUtilities.NUMBER_OF_COLUMNS && d.getColor()==matchType );

		  } //equal color

		 }//for j


	  }//for i

	  return horArray.size();
}



//Calculation function of vertical candies
int verCandies(Board board){


	  ArrayList <Tile>verArray=new ArrayList<Tile>();

	  Tile a=new Tile();
	  Tile b=new Tile();
	  Tile c=new Tile();
	  Tile d=new Tile();

	 
	for(int i=0;i<CrushUtilities.NUMBER_OF_COLUMNS;i++){
		  for(int j=0;j<(CrushUtilities.NUMBER_OF_PLAYABLE_ROWS-2);j++){

			 a.setX(i);
			 a.setY(j);
			 int matchType=a.getColor();


			  b.setX(i);
			  b.setY(j+1);
			  c.setX(i);
			  c.setY(j+2);
			  d.setX(i);



		  if(b.getColor()==matchType && c.getColor()==matchType){

			  do{
				  verArray.add(board.giveTileAt(i,j));
				  j++;
				  d.setY(j);

			  }
			  while(j<CrushUtilities.NUMBER_OF_ROWS && d.getColor()==matchType );

		  } //equal color

		 }//for j


	  }//for i

	return verArray.size();


}

//Calculation function if the motion is vertical (true) or horizontal (false)
boolean vertOrHor(Board board,Tile plakidio){

	int x=plakidio.getX();
	int y=plakidio.getY();

	
	Tile a=new Tile();
	Tile b=new Tile();


	if(x==0){

			if(y==0 ){/
				a.setX(x+1);
				if(plakidio.getColor()==a.getColor())	return false;
				else return true;
			}


			if(y==CrushUtilities.NUMBER_OF_PLAYABLE_ROWS ){
				a.setX(x+1);
				if(plakidio.getColor()==a.getColor())	return false;
				else return true;
			}



			else{
				a.setX(x+1);
				if(plakidio.getColor()==a.getColor())	return false;
				else return true;
			}

	}

	if(y==0){/

			if(x==CrushUtilities.NUMBER_OF_COLUMNS){
				a.setX(x-1);
				if(plakidio.getColor()==a.getColor())return false;
				else return true;
			}
			else{
					a.setX(x+1);
					b.setX(x-1);
					if(plakidio.getColor()==a.getColor() || plakidio.getColor()==b.getColor())return false;
					else return true;
			}
	}

	if(x==CrushUtilities.NUMBER_OF_COLUMNS){

		if(y==CrushUtilities.NUMBER_OF_PLAYABLE_ROWS){
			a.setX(x-1);
			if(plakidio.getColor()==a.getColor() )return false;
			else return true;
		}

		else{
			a.setX(x-1);
			if(plakidio.getColor()==a.getColor() )return false;
			else return true;
		}
	}


	if(y==CrushUtilities.NUMBER_OF_PLAYABLE_ROWS){
		a.setX(x-1);
		b.setX(x+1);
		if(plakidio.getColor()==a.getColor() || plakidio.getColor()==b.getColor())return false;
		else return true;
	}


	else{
		a.setX(x-1);
		b.setX(x+1);
		if(plakidio.getColor()==a.getColor() || plakidio.getColor()==b.getColor())return false;
		else return true;
	}

}


//Function for calculating the distance of the nearest tile belonging to the motion from the yy axis'
int heightofthemove(Board board,Tile plakidio){

		Tile a=new Tile();
		int height=plakidio.getY();
		a.setY(plakidio.getY()-1);
		int k=1;

		
		while(plakidio.getColor()==a.getColor() && height>=0){

					height=plakidio.getY()-k;
					k++;
					a.setY(plakidio.getY()-k);

		}

		return height;




}


}











