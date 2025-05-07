#define blank 32
#define X 88
#define O 79
using namespace std;
class player{
	
	private:
	u8 points=0;
	public:
	char name[12];
	char symbol;
	u8 print_p() {return points;}
	void incr_point() {points++;}
	void swap_order();
	bool check_win(char grid[3][3]);
	void starting_order(int o);
};
void player::swap_order()
{
	if(symbol==X)symbol=O;
	else symbol=X;
}
bool player::check_win(char grid[3][3])	//CONTROLLA
{
	bool winner=false;
	for(u8 i=0;i<3;i++)
	{
		if(grid[i][0]==grid[i][1]&&grid[i][0]!=blank&&grid[i][0]==grid[i][2])
		{
			winner=true;
		}
		
	}
	if(winner==false)
	{
		for(u8 i=0;i<3;i++)
		{
			if(grid[0][i]==grid[1][i]&&grid[0][i]!=blank&&grid[0][i]==grid[2][i])
			{
				winner=true;
			}
			
		}
		if(winner==false)
		{
			if(grid[0][0]==grid[1][1]&&grid[0][0]==grid[2][2]&&grid[0][0]!=blank) winner=true;
			else if(grid[0][2]==grid[1][1]&&grid[0][2]==grid[2][0]&&grid[0][2]!=blank) winner=true;
		}
	}
	return winner;
}
