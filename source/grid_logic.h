#define blank 32
#define X 88
#define O 79
using namespace std;
void clear_grid(char grid[3][3])
{
	for(u8 i=0;i<3;i++)
		for(int j=0;j<3;j++) grid[i][j]=blank;
}
void print_grid(char grid[3][3])
{
	iprintf("\x1b[10;9H#############\n");
	for(u8 i=0,k=0;i<3;i++)
	{	
		iprintf("\x1b[%d;9H#   #   #   #",10+k+1);
		iprintf("\x1b[%d;9H# %c # %c # %c #",10+k+2,grid[i][0],grid[i][1],grid[i][2]);
		iprintf("\x1b[%d;9H#   #   #   #",10+k+3);
		iprintf("\x1b[%d;9H#############",10+k+4);
		k+=4;
	}
}

bool positioning(u8 x,u8 y,char grid[3][3])
{
	if(grid[x][y]==blank)
	return true;
	else return false;
}
bool check_grid(char grid[3][3])
{
	bool space_left=false;
	for(u8 i=0;i<3;i++)
		for(u8 j=0;j<3;j++)
			if(grid[i][j]==blank) space_left=true;
	return space_left;
}
int columns(touchPosition t)
{
	if(t.px>=0x4F&&t.px<=0x68) return 0;
	if(t.px>=0x6F&&t.px<=0x88) return 1;
	if(t.px>=0x8F&&t.px<=0xA8) return 2;
	else return 3;
}
int rows(touchPosition t)
{
	if(t.py>=0x57&&t.py<=0x6F) return 0;
	if(t.py>=0x77&&t.py<=0x8F) return 1;
	if(t.py>=0x97&&t.py<=0xAF) return 2;
	else return 3;
}
