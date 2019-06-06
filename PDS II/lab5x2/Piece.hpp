#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <vector>
#include <set>

class Piece{
	public:
		std::string symbol;
		std::string name;
		std::pair<int, int> currentPosition;
		std::pair<int, int> nextPosition;
		std::vector<std::pair<int,int>> movement;
		std::set<std::string> legalMovements;
		Piece(std::string, std::string, std::string);
		virtual void setMovements() {};
		virtual void printPossibleMoves();
		virtual void setNextPosition(std::string);
		virtual void checkMovement();
};

class Rook : public Piece{
	public:
		using Piece::Piece;
		void setMovements();
};

class Bishop : public Piece{
	public:
		using Piece::Piece;
		void setMovements();
};

class Knight : public Piece{
	public:
		using Piece::Piece;
		void setMovements();
};

#endif