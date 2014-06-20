#include "safemaze.h"
#include "safemazeinterface.h"


int main(int argc, char** argv)
{
	IMazeInterface* pSafeMazeInterface = new SafeMazeInterface();
	AbsMaze* pSafeMaze = new SafeMaze(pSafeMazeInterface);
	return 0;
}
