package gr.auth.ee.dsproject.crush.board;

public class Tile
{

  protected int id;
  private int x;
  private int y;
  private int color;
  private boolean mark;
  
  /*
	Constructor of the Tile class, which accepts as arguments and initializes the variables id (tile identity),
    x (position of the tile on the x'x axis), y (position of the tile on the y'y axis), color (color of the tile),
    mark (indication of selection or not of the tile)
  */
  Tile(int id,int x,int y,int color,boolean mark)
  {
	  this.id=id;
	  this.x=x;
	  this.y=y;
	  this.color=color;
	  this.mark=mark;
  }
  
  //Function that accepts and defines the variable x
  public void setX(int x)
  {
	  this.x=x;
  }
  
  // Function that accepts and defines the variable y
  public void setY(int y)
  {
	  this.y=y;
  }
  
  //Function that accepts and defines the variable color
  public void setColor(int color)
  {
	  this.color=color;
  }
  
  //Function that accepts and defines the variable mark
  public void setMark(boolean mark)
  {
	  this.mark=mark;
  }
  
  //Function that accepts and defines the variable color
  public int getColor()
  {
	  return color;
  }
  
  //Return function of the variable value x
  public int getX()
  {
	  return x;
  }
  
  //Return function of the variable value y
  public int getY()
  {
	  return y;
  }
  
  //Return function of the variable value id
  public int getId()
  { 
	 return id;
  }
  
  //Return function of the variable value mark
  public boolean getMark()
  {
	  return mark;
  }
  
}
