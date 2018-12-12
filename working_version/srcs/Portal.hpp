#ifndef PORTAL_HPP
#define PORTAL_HPP

#include "Position.hpp"
#include "Object.hpp"
#include "Player.hpp"

class Portal : public Object{
	public:
		Portal(Pos2D pos, Board& b, int);
		void onPlayer(Player& player);
		void deadEnemy();
	private:
		int numEnemy;
};

#endif