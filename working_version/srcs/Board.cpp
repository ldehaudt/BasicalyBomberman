#include "Board.hpp"
#include "Wall.hpp"
#include "BreakWall.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Portal.hpp"

void Board::eraseLevel(){
	for (i = 1; i < objs.size(); i++){
		eraseObject(objs[i]->getId());
	}
	bounds.x += 2;
	bounds.y += 2;
}

void Board::loadLevel(){

	Pos2D tmp;

	objs.reserve(bounds.x * bounds.y * sizeof(Object*));

	for (int i = 0; i < 3; i++){
		do{
			tmp.x = rand() % (bounds.x - 4) + 2;
			tmp.y = rand() % (bounds.y - 4) + 2;
		}while(inPos(tmp) || (tmp.x % 2 == 0 && tmp.y % 2 == 0) || tmp.x + tmp.y < 5);
		objs.push_back(new Enemy(tmp, *this));
		enemyPos.push_back(tmp);
		display.addObj(objs[objs.size() - 1]->getId(),
			objs[objs.size() - 1]->getType(), objs[objs.size() - 1]->getPos());
	}	

	tmp.x = bounds.x - 2;
	tmp.y = bounds.y - 2;
	portal = new Portal(tmp, *this, 3);
	objs.push_back(portal);
	display.addObj(objs[objs.size() - 1]->getId(),
		objs[objs.size() - 1]->getType(), objs[objs.size() - 1]->getPos());

	for (int x = 0; x < bounds.x; x++)
	{
		tmp.x = x;
		for (int y = 0; y < bounds.y; y++)
		{
			tmp.y = y;
			if (x == 0 || y == 0 || x == bounds.x - 1 || y == bounds.y - 1
				|| (x % 2 == 0 && y % 2 == 0))
			{
				objs.push_back(new Wall(tmp, *this));
				display.addObj(objs[objs.size() - 1]->getId(),
					objs[objs.size() - 1]->getType(), objs[objs.size() - 1]->getPos());
			}
			else if(x + y > 4){
				if (!inPos(tmp) && (x != bounds.x - 2 || y != bounds.y - 2)){
					if (rand() % 3 < 1){
						objs.push_back(new BreakWall(tmp, *this));
						display.addObj(objs[objs.size() - 1]->getId(),
							objs[objs.size() - 1]->getType(), objs[objs.size() - 1]->getPos());
					}
				}
			}
		}
	}
}

void Board::updateObjs()
{
	for (int j = 0; j < objs.size(); j++)
		objs[j]->update();
}

void Board::eraseObject(int id)
{
	for (int j = 0; j < objs.size(); j++)
		if (objs[j]->getId() == id){
			objs.erase(objs.begin() + j);
			i--;
			size--;
			break;
		}
	display.eraseObj(id);
}

bool Board::checkEmpty(int x, int y)
{
	for (i = 0; i < objs.size(); i++)
		if (objs[i]->getPos().x == x && objs[i]->getPos().y == y && objs[i]->isSolid())
			return false;
	return true;
}

bool Board::burn(Pos2D pos)
{
	size = objs.size();
	for (int i = 0; i < size; i++)
		if (objs[i]->getPos().x == pos.x && objs[i]->getPos().y == pos.y){
			if (objs[i]->getType() == FIRE_GAME){
				return 0;
			}
			if (objs[i]->isKillable()){
				objs[i]->onBomb();
			}
		}
	return 1;
}

int Board::checkFlameable(int x, int y)
{
	int num = 1;
	for (int i = 0; i < objs.size(); i++)
		if (objs[i]->getPos().x == x && objs[i]->getPos().y == y && objs[i]->isSolid()){
			if (objs[i]->getPos().x == x && objs[i]->getPos().y == y && objs[i]->isKillable()){
				num = 2;
			}
			else
				return 0;
		}
	return num;
}

bool Board::inPos(Pos2D pos){
	for (int j = 0; j < enemyPos.size(); j++){
		if (enemyPos[j].x == pos.x && enemyPos[j].y == pos.y){
			return true;
		}
	}
	return false;
}

void Board::moveDisplay(int id, char dir, float x, float y)
{
	display.moveObj(id, dir, x, y);
}

void	Board::playerMoved(int x, int y, Player& pl){
	size = objs.size();
	for (i = 0; i < size; i++){
		if (objs[i]->getPos().x == x && objs[i]->getPos().y == y){
			objs[i]->onPlayer(pl);
		}
	}
}

void	Board::enemyMoved(int x, int y, Enemy& en){
	
	for (int j = 0; j < objs.size(); j++){
		if (objs[j]->getPos().x == x && objs[j]->getPos().y == y){
			if (objs[j]->getType() == PLAYER_GAME){
				objs[j]->onBomb();
			}
			else if (objs[j]->getType() == FIRE_GAME){
				en.onBomb();
			}
		}
	}
}



Board::Board(int sX, int sY, Display& d) : display(d)
{
	bounds.x = sX;
	bounds.y = sY;

	Pos2D tmp;
	tmp.x = 1;
	tmp.y = 1;
	objs.push_back(new Player(tmp, *this));
	display.addObj(objs[objs.size() - 1]->getId(),
		objs[objs.size() - 1]->getType(), objs[objs.size() - 1]->getPos());

	loadLevel();
}

