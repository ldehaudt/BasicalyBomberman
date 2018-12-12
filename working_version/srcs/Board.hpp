#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "Position.hpp"
#include "Display.hpp"

class Object;
class Player;
class Enemy;
class Portal;

using namespace std;

class Board{
	public:
		vector<Object*> objs;
		Pos2D bounds;
		Board(int sX, int sY, Display& d);
		void swap(int x, int y, int nX, int nY);
		void moveDisplay(int, char, float, float);
		void eraseLevel();
		void loadLevel();
		void updateObjs();
		void enemyMoved(int x, int y, Enemy& en);
		void playerMoved(int x, int y, Player& pl);
		bool checkEmpty(int x, int y);
		int checkFlameable(int x, int y);
		bool burn(Pos2D pos);
		void eraseObject(int id);
		bool inPos(Pos2D pos);
		Display& display;
		Portal *portal;

	private:
		vector<Pos2D> enemyPos;
		int i;
		int size;

};

#endif