package gr.auth.ee.dsproject.crush.player;

import gr.auth.ee.dsproject.crush.CrushUtilities;
import gr.auth.ee.dsproject.crush.board.Board;
import gr.auth.ee.dsproject.crush.board.Tile;

import java.util.ArrayList;

public class HeuristicPlayer implements AbstractPlayer
{
  // TODO Fill the class code.

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

  int findBestMoveIndex (ArrayList<int[]> availableMoves, Board board)
  {
	  double[] evals = new double[availableMoves.size()];
    // TODO Fill the missing code.

	  int bestmove=0;//bestmove :μεταβλτητη στην οποια θα αποθηκευτεί ο δείκτης της καλύτερης κίνησης
	  double bestscore=0;//bestscore :το σκορ της καλύτερης κίνησης
	  double movescore=0;// movescoreτο σκορ κάθε κίνησης



	  for(int i=0;i<evals.length;i++){//Για καθε διαθέσιμη κίνηση

		  movescore=moveEvaluation(availableMoves.get(i),board);//Υπολογίζουμε το σκορ της κίνησης

		  if(movescore>bestscore){//Αν το σκορ της κίνησης ειναι μεγαλύτερο

			  //Αντικαθιστούμε την παλία καλύτερη κίνηση με την νέα
			  bestscore=movescore;
			  bestmove=i;
		  }

	  }

	  return bestmove;//Επιστρέφουμε τον δείκτη της καλύτερης κίνησης



  }

  double moveEvaluation (int[] move, Board board)
  {
    // TODO Fill the missing code.
	  int[] movedo=new int[4];//movedo :πίνακας που θα έχει τις παλίες και νέες συντεταγμένες του πλακιδίου
	  movedo=calculateNextMove ( move);//υπολογίζουμε τις συντεταγμένες
	  int x=movedo[2];//x :μεταβλητή αποθήκευσεις τις συντεταγμένης x
	  int y=movedo[3];//y :μεταβλητή αποθήκευσεις τις συντεταγμένης y
	  Tile movechange=new Tile() ;//movechange :δημιουργία ενός πλακίδιο με τις συντεταγμένες (x,y)
	  movechange.setX(x);//ορισμός τις συντεταγμένης x
	  movechange.setY(y);//ορισμός τις συντεταγμένης y


	  Board aBoard;//aBoard: το νέο ταμπλό ακριβώς μετά την κίνηση
	  aBoard =CrushUtilities.boardAfterFirstMove(board, move);//Δημιουργία του μεσώ τις συνάρτησης boardAfterFirstMove
	  double candies=calculateTilesThatWillCrush(aBoard);//Υπολογισμός των ζαχαρωτών που θα φύγουν

	  int height=heightofthemove(aBoard,movechange);//Υπολογισμός ύψους


	  double verorhor;
	  if(vertOrHor(aBoard,movechange)==true) verorhor=4;
	  else verorhor=8;

	  return candies+verorhor+10-height;

  }




//Συνάρτηση η οποία υπολογίζει τον αριθμό των ζαχαρωτών που ανήκουν σε 3άδα,4άδα,..ν-άδα.
double calculateTilesThatWillCrush(Board board){

	int verCandies=verCandies(board);//Υπολογισμός κάθετων πλακιδίων
	int horCandies=horCandies(board);//Υπολογισμός οριζόντιων πλακιδίων
	return verCandies+horCandies;//Επιστροφή του αθροισματός τους


}

int horCandies(Board board){

	  ArrayList <Tile>horArray=new ArrayList<Tile>();//horArray :λίστα με τα οριζόντια ζαχαρώτα

	  Tile a=new Tile();//a:αρχικό πλακίδιο
	  Tile b=new Tile();//πλάκιδιο που βρίσκεται μια θέση δίπλα από το α
	  Tile c=new Tile();//πλάκιδιο που βρίσκεται δύο θέσεις δίπλα από το α
	  Tile d=new Tile();//πλακίδιο counter για την λίστα


	  //Μέσα στα όρια του ταμπλό
	  for(int i=0;i<CrushUtilities.NUMBER_OF_PLAYABLE_ROWS;i++){
		  for(int j=0;j<(CrushUtilities.NUMBER_OF_COLUMNS-2);j++){

			 a.setX(j);//Το πλακίδιο a πέρνει της αρχικές συντεταγμένες
			 a.setY(i);
			 int matchType=a.getColor();


			  b.setX(j+1);//Το πλακίδιο b πέρνει της  συντεταγμένες που βρίσκεται μια θέση δίπλα από το α
			  b.setY(i);
			  c.setX(j+2);//Το πλακίδιο c πέρνει της αρχικές συντεταγμένες που βρίσκεται δύο θέσεις δίπλα από το α
			  c.setY(i);
			  d.setY(i);//Αρχικοποίηση του counter



		  if(b.getColor()==matchType && c.getColor()==matchType){//Aν τα πλακίδια είναι ίδιου χρώματος

			  do{
				  horArray.add(board.giveTileAt(j,i));//Προσθήκη του πλάκιδιο στην λίστα
				  j++;//αύξηση του j
				  d.setX(j);//ορισμός του x του d ως το νέο j

			  }
			  while(j<CrushUtilities.NUMBER_OF_COLUMNS && d.getColor()==matchType );//όσο τα πλακίδια έχουν το ίδιο χρώμα

		  } //equal color

		 }//for j


	  }//for i

	  return horArray.size();//Επιστροφή του μεγέθους της λίστας
}



//Συνάρτηση υπολογισμού των κάθετων ζαχαρωτών
int verCandies(Board board){


	  ArrayList <Tile>verArray=new ArrayList<Tile>();//verArray:λίστα με τα πλακίδια που ανήκουν σε κάθετη κίνηση

	  Tile a=new Tile();//a:αρχικό πλακίδιο
	  Tile b=new Tile();//πλάκιδιο που βρίσκεται μια θέση κάτω από το α
	  Tile c=new Tile();//πλάκιδιο που βρίσκεται δύο θέσεις κάτω από το α
	  Tile d=new Tile();//πλακίδιο counter για την λίστα

	 //Μέσα στα όρια του ταμπλό
	for(int i=0;i<CrushUtilities.NUMBER_OF_COLUMNS;i++){
		  for(int j=0;j<(CrushUtilities.NUMBER_OF_PLAYABLE_ROWS-2);j++){

			 a.setX(i);//Το πλακίδιο a πέρνει της αρχικές συντεταγμένες
			 a.setY(j);
			 int matchType=a.getColor();


			  b.setX(i);//Το πλακίδιο b πέρνει της  συντεταγμένες που βρίσκεται μια θέση πάνω από το α
			  b.setY(j+1);
			  c.setX(i);//Το πλακίδιο c πέρνει της αρχικές συντεταγμένες που βρίσκεται δύο θέσεις πάνω από το α
			  c.setY(j+2);
			  d.setX(i);//Αρχικοποίηση του counter



		  if(b.getColor()==matchType && c.getColor()==matchType){//Aν τα πλακίδια είναι ίδιου χρώματος

			  do{
				  verArray.add(board.giveTileAt(i,j));//Προσθήκη του πλάκιδιο στην λίστα
				  j++;//αύξηση του j
				  d.setY(j);//ορισμός του y του d ως το νέο j

			  }
			  while(j<CrushUtilities.NUMBER_OF_ROWS && d.getColor()==matchType );//όσο τα πλακίδια έχουν το ίδιο χρώμα

		  } //equal color

		 }//for j


	  }//for i

	return verArray.size();//Επιστροφή του μεγέθους της λίστας


}

//Συνάρτηση υπολογισμού αν η κίνηση είναι κάθετη(true) ή οριζόντια (false)
boolean vertOrHor(Board board,Tile plakidio){

	int x=plakidio.getX();//Ορισμός της μεταβλητής x ως το x του πλακιδίου της κίνησης
	int y=plakidio.getY();//Ορισμός της μεταβλητής y ως το y του πλακιδίου της κίνησης

	//Πλακίδια σύγκρισης
	Tile a=new Tile();
	Tile b=new Tile();


	if(x==0){//Περίπτωση του x=0

			if(y==0 ){//Περίπτωση του y=0
				a.setX(x+1);
				if(plakidio.getColor()==a.getColor())	return false;//οριζόντια κίνηση
				else return true;//κάθετη κίνηση
			}


			if(y==CrushUtilities.NUMBER_OF_PLAYABLE_ROWS ){//Περίπτωση του y=CrushUtilities.NUMBER_OF_PLAYABLE_ROWS
				a.setX(x+1);
				if(plakidio.getColor()==a.getColor())	return false;//οριζόντια κίνηση
				else return true;//κάθετη κίνηση
			}



			else{
				a.setX(x+1);
				if(plakidio.getColor()==a.getColor())	return false;//οριζόντια κίνηση
				else return true;//κάθετη κίνηση
			}

	}

	if(y==0){//Περίπτωση του y=0

			if(x==CrushUtilities.NUMBER_OF_COLUMNS){//Περίπτωση του x=CrushUtilities.NUMBER_OF_COLUMNS
				a.setX(x-1);
				if(plakidio.getColor()==a.getColor())return false;//οριζόντια κίνηση
				else return true;//κάθετη κίνηση
			}
			else{
					a.setX(x+1);
					b.setX(x-1);
					if(plakidio.getColor()==a.getColor() || plakidio.getColor()==b.getColor())return false;//οριζόντια κίνηση
					else return true;//κάθετη κίνηση
			}
	}

	if(x==CrushUtilities.NUMBER_OF_COLUMNS){//Περίπτωση του x=CrushUtilities.NUMBER_OF_COLUMNS

		if(y==CrushUtilities.NUMBER_OF_PLAYABLE_ROWS){//Περίπτωση του y=CrushUtilities.NUMBER_OF_PLAYABLE_ROWS
			a.setX(x-1);
			if(plakidio.getColor()==a.getColor() )return false;//οριζόντια κίνηση
			else return true;//κάθετη κίνηση
		}

		else{
			a.setX(x-1);
			if(plakidio.getColor()==a.getColor() )return false;//οριζόντια κίνηση
			else return true;//κάθετη κίνηση
		}
	}


	if(y==CrushUtilities.NUMBER_OF_PLAYABLE_ROWS){//Περίπτωση του y=CrushUtilities.NUMBER_OF_PLAYABLE_ROWS
		a.setX(x-1);
		b.setX(x+1);
		if(plakidio.getColor()==a.getColor() || plakidio.getColor()==b.getColor())return false;//οριζόντια κίνηση
		else return true;//κάθετη κίνηση
	}


	else{
		a.setX(x-1);
		b.setX(x+1);
		if(plakidio.getColor()==a.getColor() || plakidio.getColor()==b.getColor())return false;//οριζόντια κίνηση
		else return true;//κάθετη κίνηση
	}

}


//Συνάρτηση υπολογισμόυ της απόστασης του κοντινότερου πλακιδίου που ανήκει στην κίνηση απο τον άξονα yy'
int heightofthemove(Board board,Tile plakidio){

		Tile a=new Tile();//Πλακίδιο το οποίο βρίσκετε κάτω από το πλακίδιο της κίνησης
		int height=plakidio.getY();;//μεταβλήτη αποθήκευσεις του ύψους,αρχικό ύψος το y του πλακιδίου της κίνησης
		a.setY(plakidio.getY()-1);//Ορισμός του y του πλακιδίου α ως το από κάτω του πλακιδίου της κίνησης
		int k=1;//k:μετρητής των πλακιδίων που βρίσκονται κατω απο το πλακίδιο της κίνησης αλλά ανήκουν στην κίνηση

		//Όσο τα δύο πλακίδια έχουν ίδιο χρώμα και το ύψος είναι μεγαλύτερο ή ίσο του μηδέν
		while(plakidio.getColor()==a.getColor() && height>=0){

					height=plakidio.getY()-k;//Το ύψος πέρνει την τιμή του από κάτω πλακιδίου
					k++;//Ο μετρητής αυξάνεται κατά 1
					a.setY(plakidio.getY()-k);//Το πλακίδιο α γίνεται το από κάτω πλακίδιο

		}

		return height;//Επιστροφή του ύψους




}


}











