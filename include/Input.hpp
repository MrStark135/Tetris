// just a wrapper class to organize stuff

#include <vector>
#include <string>

#define ARROW_UP 82
#define ARROW_DOWN 81
#define ARROW_RIGHT 79
#define ARROW_LEFT 80

struct Input
{
public:
	Input()
		: mousePosX(0), mousePosY(0), mouseLeftButton(false), mouseMiddleButton(false), mouseRightButton(false) {};
		
	bool isKeyDown(int key)
	{
		if (!keysDown) return false;
		if (keysDown[key])
			return true;		
		return false;
	}
	
	// mouse
	int mousePosX;
	int mousePosY;
	bool mouseLeftButton;
	bool mouseMiddleButton;
	bool mouseRightButton;
	
	// keyboard array
	const Uint8* keysDown;
};