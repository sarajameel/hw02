#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string.h>


//Structure to keep track of various locations
struct Point
{
  int x;
  int y;

  Point(int _x, int _y): x(_x), y(_y)
  {

  }
};
//Structure of Player
struct Player
{
    int food;
    int health;
    bool alive;
    Point itsPosition;
    
    Player():itsPosition(0,0)
    {
        food = 64;
        health = 10;
        alive = true;
    }
    
    void loseHealth()
    {
        if(health>0)
            health--;
            
        if(health==0)
            alive = false;
    }
    void gainHealth()
    {
        if(health<10)
            health++;
    std::cout << "Gained Health \n";
    }
	
	void calculateCoordinates(int pPos,int pWidth,int pHeight){
	 	
	 	itsPosition.x = pPos%pWidth;
	 	itsPosition.y = pPos/pHeight;
		std::cout<<"XPos "<<itsPosition.x<<" "<<"YPos "<<itsPosition.y<<std::endl;
		
	}	

	void calculatePosition(int pPos, int width, int height ){
		itsPosition.x= pPos%width;
		itsPosition.y= pPos/width;
		int position = width*itsPosition.y+itsPosition.x;
		std::cout<<"Pos "<<position<<std::endl;
		std::cout <<" x "<<itsPosition.x<< " Y "<<itsPosition.y<<std::endl; 
	}
	
	
};



#define MAX_HEIGHT 64
#define MAX_WIDTH 64
#define MAX_LEN MAX_HEIGHT*MAX_WIDTH
//Class of Dungeon.
class Dungeon{

	char its_GRID_DUNGEON[MAX_LEN];
	unsigned int itsHeight;
	unsigned int itsWidth;
public:
	Dungeon(){
		itsHeight = 0;
		itsWidth = 0;
		memset(its_GRID_DUNGEON,' ',MAX_LEN); // Fill Complete Grid with spaces

	}
	char* create_dungeon(int width, int height, Point& ref_startPoint, Point& ref_exitPoint, Player &pPlayer);
	int initPlayerPos(Player &pPlayer);
	void PlaceExit();
	void PlayerPos(Player &pPlayer);
	void placeEnemy(int pMaxLen);	
	void placeHealth(int pMaxLen);
	void placeTrap(int pMaxLen);
	void placeWall(int pMaxLen);
	void placeFood(int pMaxLen);
	void placeExit(int pMaxLen);
	int UpdatedPlayerPosition(Player &pPlayer);
	int getValidRandEmptySpace(int pMaxLen);
	char getValueAt(int index);
	void setValueAt(char a, int index);

};




typedef const int cint;         //Google typedef to see what this means
typedef const Point cPoint;
char* dungeon = nullptr;
void Traversal(Dungeon dungeon , Point& startPoint, cPoint& exitPoint, cint width, cint height, Player &pPlayer);
void Combat(Player&, int);  //Used for simulating combat
void trap_statements();  //3 statements that show at random when the player activates a trap
void food_statements();  //3 statements that show at random when the player finds food
void hit_statements();   //3 statements that show at random when the player hits enemy
void get_hit_statements();//3 statements that show at random when the player gets hit

int main ()
{
  srand(time(0));

  int width = 0;
  int height = 0;


  Point startPoint(0,0);
  Point exitPoint(0,0);

  char* dungeon = nullptr;

	std::cout <<"Please try to keep it bigger than a 8 x 8 grid for best experiance.\n\n"; //creates the boundary of the user defined height and width.
    	std::cout << "Height ";
	std::cin>>height;
	std::cout<< "Width ";
	std::cin>>width;
	int food=64;
	
	
	if((width >=8) || (height>=8) ){

	Dungeon dungeon;
		Player pPlayer;
	dungeon.create_dungeon(width, height, startPoint, exitPoint, pPlayer);

	
	Traversal(dungeon, startPoint, exitPoint, width, height, pPlayer);
	}
  
    else{
    	std::cout << "\nPlease input values greater than 8 for the best experiance.\n";
	}



  return 0;
}
//3 statements that show at random when the player activates a trap
void trap_statements()
{
    int trap = rand()%3;
	if (trap ==0){
    std::cout << "You stepped into a bear trap and got yourself injured."<< std::endl;}

	else if (trap ==1){
    std::cout << "You walked into some spikes that sprung out of the floor."<< std::endl;}

	else if (trap ==2){
    std::cout << "An arrow flew out of a nearby wall and hit you in your posterior. That will leave a scar!"<< std::endl;}


}

//3 statements that show at random when the player finds food
void food_statements()
{
    int food = rand()%3;
	if (food ==0){
    std::cout << "It is a rat as big as a rabbit. It will go down well with a bit of wasp juice."<< std::endl;}

	else if (food ==1){
    std::cout << "You looked at the food and it was a well cooked chicken ... well at least it looked like one."<< std::endl;}

	else if (food ==2){
    std::cout << "It is a bread roll in this dungeon? Maybe there is a secret bakery around here."<< std::endl;}

}
//3 statements that show at random when the player hits enemy
void hit_statements()
{
    int hit = rand()%3;
	if (hit ==0){
    std::cout << "Your roundhouse kick sent your enemy flying right into a gutter."<< std::endl;}

	else if (hit ==1){
    std::cout << "Your speed is unmatched and delivered a Stone Cold Stunner."<< std::endl;}

	else if (hit ==2){
    std::cout << "You made an excellent jab that knocked the lights out of your enemy."<< std::endl;}

}
//3 statements that show at random when the player gets hit
void get_hit_statements()
{
	int attack = rand()%3;
	if (attack==0){
    std::cout << "The enemy avoided your attack and gave you a nasty scratch."<< std::endl;}

	else if (attack ==1){
    std::cout << "The enemy threw a rock that hit you on the temple and shook you bad."<< std::endl;}

	else if (attack==2){
    std::cout << "You were not prepared for a sudden lunging attack that hit you hard."<< std::endl;}
    
}


//Traversal to of the player around the dungeon. 
void Traversal(Dungeon dungeon , Point& startPoint, cPoint& exitPoint, cint width, cint height, Player &pPlayer)
{

   int Location = 0;
	for(int i = 0;i<height*width;i++){
		if(i!= 0 && i%width==0){
			printf("\n");
		}
			

		printf("%c",dungeon.getValueAt(Location++));
	}
	printf("\n");	
	//updating the position and using the required statements when E,F,H,T appear.
	dungeon.UpdatedPlayerPosition(pPlayer);
	
	
   	
}

//Counts the number of enemies
int enemiesCount(Player &pPlayer,int width,int height,Dungeon dungeon, Point& startPoint, cPoint& exitPoint)//function where the player steps in next to enemy and have a combat with them

{

  if ( pPlayer.food > 0 )
  {
   pPlayer.food--;
   int random = ( 2 + ( rand() % ( 4 - 2 + 1 ) ) );
   std::cout << "You came across" << " " << random << " " << "enemies. You will have to fight." << std::endl;
   return random;

  }

  else
  {
    std::cout << "You ran out of food,you died" << std::endl;
    exit(0);//the program terminates
  }
  
}
	 

//The fight between the player and enemies. 
void Combat(Player& pPlayer, int enemies)
{
	std::cout <<"Start of combat****************************** \n";
	if ( pPlayer.health > 0 && pPlayer.food != 0)//checks if health and food is zero or less than zero
  {
    int random2 = ( rand() % 100 + 1 );//generates a random between 1 and 100

    if (random2 <= 30)//checks if the probability is less than 30
    {
      hit_statements();//calls the hit statement function
      enemies--;
      std::cout << "^_^ You killed one enemy!" << std::endl;//tells user he or she has killed an enemy
      int random1 =  ( rand() % 100 + 1 );//generates a random between 1 and 100

      if (random1 <= 10)//checks if the probability is less than 10
      {
        get_hit_statements();//calls the function
        pPlayer.loseHealth();//user loses health
        std::cout << "x_x You lost 1 health" << std::endl;//tells user he or she has lose health

        if ( pPlayer.health == false )
        {
          std::cout << "You died" << std::endl;
          exit(0);
        }
       }
    }

    else
    {
        std::cout <<"" <<std::endl;
		
        std::cout << "You died" << std::endl;//tells user has died
        exit(0);
    }
  }


	std::cout <<" " <<std::endl;
	std::cout << "***************   end of Combat   ***************" << std::endl;//prints that end of combat
}

//Creates dungeon
char* Dungeon::create_dungeon(int width, int height, Point& ref_startPoint, Point& ref_exitPoint, Player &pPlayer)

{	int RandVal2=0;
	int pMaxLen=width*height;
	itsHeight = height;
	itsWidth = width;
	
	memset(its_GRID_DUNGEON,'w',width); // first Row
	memset(&its_GRID_DUNGEON[(width*(height-1))],'w',width);//last Row
	



	initPlayerPos(pPlayer);
	PlaceExit();
	for(int I = 1;I<height;I++){
	
		its_GRID_DUNGEON[(width*I)-1] = 'w';
		its_GRID_DUNGEON[(width*I)] = 'w';
	}
		// generate random number
	// We can control the difficulty level of the game by adding or subtracting health, food, traps and walls. 
	for (int I=0; I <16 ; I++){
	
	RandVal2 = 1 + rand ()%(pMaxLen-1);

	if ((RandVal2>0 )&& (RandVal2<=15)){
		
			placeEnemy(width * height);
		}	
		
	else if ((RandVal2>15) && (RandVal2<=30)){
			placeHealth(width * height);
		}
		
	else if ((RandVal2 > 30)&& (RandVal2<=45)){
			placeTrap(width*height);
		}
	
	else if ((RandVal2 >45) && (RandVal2 <=60)){
		placeFood(width*height);
	}
	else if (RandVal2 > 60){
		placeWall(width*height);
	}
}

#if 0	
	int Location = 0;
	for(int i = 0;i<height;i++){
		for(int j = 0;j<width;j++)
			printf("%c ",its_GRID_DUNGEON[Location++]);
		printf("\n");
	}
#endif
	return its_GRID_DUNGEON;
}
char Dungeon::getValueAt(int index){
	index = its_GRID_DUNGEON[index];
	
	return index;
}
//gets random value
int Dungeon::getValidRandEmptySpace(int pMaxLen){
	int RandVal = 0;
	do{
		 RandVal = 1 + rand ()%(pMaxLen-1);
		
	}while((its_GRID_DUNGEON[RandVal]!=' ')); 
	
	
	return RandVal;
}

//sets initial position of the player in the dungeon.
int Dungeon::initPlayerPos(Player &pPlayer){

		
		int Pos=(itsWidth+1);
	
	
		if (Pos!=0){
		std::cout << "Coordinates of Player \n";	
		pPlayer.calculateCoordinates(Pos,itsWidth,itsHeight);
		pPlayer.calculatePosition(Pos, itsWidth,itsHeight);
		std::cout << "Position of player is= "<<Pos<<" \n"; 
		its_GRID_DUNGEON[Pos]='P';
		
		}
		
		
		
		return Pos;

}

//Places the exit in the dungeon.
void Dungeon::PlaceExit(){

		
		
		int Pos= (itsWidth*itsHeight)-itsWidth-2;
		
		if (Pos !=0){
		Player pPlayer;
		std::cout << "Coordinates of Exit are \n";
		pPlayer.calculateCoordinates(Pos,itsWidth,itsHeight);	
	
		its_GRID_DUNGEON[Pos]='X';
		std::cout << "Position of exit is= "<<Pos<<" \n"; 
		
		}
		
}
//Updates the position, coordinates, food and health of  the player
int Dungeon::UpdatedPlayerPosition(Player &pPlayer){

	Point startPoint(0,0);
	Point exitPoint(0,0);
	char input;
	Dungeon dungeon;
	int set;
    int food = 64;
	while (input !='x'&& food!=0){
        
        
		std::cout << "Where do you want to go? please enter U, D, L, R" << std::endl;
		std::cin >> input;
		if (input == 'x'){
        std::cout << "You quit the game\n";
        exit(0);}
		
		set=pPlayer.itsPosition.y*itsWidth+pPlayer.itsPosition.x;
		if ((input== 'r' || input== 'R')){
		
				its_GRID_DUNGEON[set]=' ';
				
				if (its_GRID_DUNGEON[set+1]=='w'){
					std::cout << "please choose another location you are next to the  wall"<<std::endl;
					its_GRID_DUNGEON[set]='P';
					continue;
				}
				
				else if (its_GRID_DUNGEON[set+1]=='H'){
					pPlayer.gainHealth();
					
					
				}
				
				else if (its_GRID_DUNGEON[set+1]=='T'){
					trap_statements();
					
					
				}
				
				else if (its_GRID_DUNGEON[set+1]=='F'){
					food_statements();
					food++;
					
				}
				
				else if (its_GRID_DUNGEON[set+1]=='E'){
					Combat(pPlayer, enemiesCount(pPlayer,itsWidth,itsHeight,dungeon, startPoint,exitPoint));
				}
				
				
				pPlayer.itsPosition.x+=1;
				set=pPlayer.itsPosition.y*itsWidth+pPlayer.itsPosition.x;
			
				
				if (its_GRID_DUNGEON[set]=='X'){
				
					std::cout << "YOU WIN!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
					exit(0);
				}
				its_GRID_DUNGEON[set]='P';
		}
		
		if (input== 'l' || input== 'L') {
			its_GRID_DUNGEON[set]=' ';

				if (its_GRID_DUNGEON[set-1]=='w'){
					
					std::cout << "please choose another location you are next to the wall"<<std::endl;
					its_GRID_DUNGEON[set]='P';
					continue;
				}
				else if (its_GRID_DUNGEON[set-1]=='H'){
					pPlayer.gainHealth();	
				}
				
				else if (its_GRID_DUNGEON[set-1]=='T'){
					trap_statements();
					
				}
				
				else if (its_GRID_DUNGEON[set-1]=='F'){
					food_statements();
				    food++;
				    
				}
				
				else if (its_GRID_DUNGEON[set-1]=='E'){
					Combat(pPlayer, enemiesCount(pPlayer,itsWidth,itsHeight,dungeon, startPoint,exitPoint));
				}
	
				
				pPlayer.itsPosition.x-=1;
				set=pPlayer.itsPosition.y*itsWidth+pPlayer.itsPosition.x;
				
			
				if (its_GRID_DUNGEON[set]=='X'){
				
					std::cout << "YOU WIN!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
					exit(0);
				}
				its_GRID_DUNGEON[set]='P';
		}
			
		
		
		if ((input== 'u' || input== 'U')){
				if (its_GRID_DUNGEON[set-itsWidth]=='w'){
					std::cout << "please choose another location you are next to the wall"<<std::endl;
					its_GRID_DUNGEON[set]='P';
					continue;
				}
				if (its_GRID_DUNGEON[set-itsWidth]=='H'){
					pPlayer.gainHealth();	
				}
				
				else if (its_GRID_DUNGEON[set-itsWidth]=='T'){
					trap_statements();
				}
	
				else if (its_GRID_DUNGEON[set-itsWidth]=='F'){
					food_statements();
					food++;
				
					
				}
				
				else if (its_GRID_DUNGEON[set-itsWidth]=='E'){
					Combat(pPlayer, enemiesCount(pPlayer,itsWidth,itsHeight,dungeon, startPoint,exitPoint));
				}
			
				its_GRID_DUNGEON[set]=' ';
				pPlayer.itsPosition.y-=1;
				set=pPlayer.itsPosition.y*itsWidth+pPlayer.itsPosition.x;
			
				
				if (its_GRID_DUNGEON[set]=='X'){
				
					std::cout << "YOU WIN!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
					exit(0);
				}
				its_GRID_DUNGEON[set]='P';
			}
		
		if ((input== 'd' || input== 'D')){
				if (its_GRID_DUNGEON[set+itsWidth]=='w'){
					std::cout << "please choose another location you are next to the  wall"<<std::endl;
					its_GRID_DUNGEON[set]='P';
					continue;
				}
				if (its_GRID_DUNGEON[set+itsWidth]=='H'){
					pPlayer.gainHealth();	
				}
				
				else if (its_GRID_DUNGEON[set+itsWidth]=='T'){
					trap_statements();	
				}
				
				else if (its_GRID_DUNGEON[set+itsWidth]=='F'){
					
					food_statements
					();
					food++;
				}
				
				else if (its_GRID_DUNGEON[set+itsWidth]=='E'){
					Combat(pPlayer, enemiesCount(pPlayer,itsWidth,itsHeight,dungeon, startPoint,exitPoint));
				}
	
				its_GRID_DUNGEON[set]=' ';
				pPlayer.itsPosition.y+=1;
				set=pPlayer.itsPosition.y*itsWidth+pPlayer.itsPosition.x;
				if (its_GRID_DUNGEON[set]=='X'){
				
					std::cout << "YOU WIN!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
					exit(0);
				}
				its_GRID_DUNGEON[set]='P';

		}
	
	int Location =0;
	for(int i = 0;i<itsHeight*itsWidth;i++){
		if(i!= 0 && i%itsWidth==0){
			printf("\n");
		}
		
		printf("%c",getValueAt(Location++));
	}
	printf("\n");
	
	    std::cout <<"Food  "<< food << std::endl;
		food--;}
	    if (food ==0){
	        std::cout << "You ran out of food. ";
	    }
	}

//Places enemies
void Dungeon::placeEnemy(int pMaxLen){
	
		its_GRID_DUNGEON[getValidRandEmptySpace(pMaxLen)]='E';
	
}
//places health
void Dungeon::placeHealth(int pMaxLen){
	its_GRID_DUNGEON[getValidRandEmptySpace(pMaxLen)]='H';
}

void Dungeon::placeTrap(int pMaxLen){
	its_GRID_DUNGEON[getValidRandEmptySpace(pMaxLen)]='T';
}
//places wall
void Dungeon::placeWall(int pMaxLen){
	its_GRID_DUNGEON[getValidRandEmptySpace(pMaxLen)]='w';
}
//places food
void Dungeon::placeFood(int pMaxLen){
	its_GRID_DUNGEON[getValidRandEmptySpace(pMaxLen)]='F';	
}

