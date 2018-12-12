#include "Portal.hpp"

Portal::Portal(Pos2D pos, Board& b, int num) : Object(PORTAL_GAME, 0, false, false, pos, b){
	numEnemy = num;
}

void	Portal::deadEnemy(){
	numEnemy--;
}

void	Portal::onPlayer(Player& player){
	if (numEnemy <= 0){
		player.resetPos();
		board.eraseLevel();
		board.loadLevel();
	}
}