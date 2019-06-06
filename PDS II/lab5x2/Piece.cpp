#include "Piece.hpp"
#include <iostream>
#define BOARD_SIZE 8

Piece::Piece(std::string symbol, std::string currentPosition, std::string nextPosition){
	this->symbol = symbol;
	this->currentPosition.first = int(currentPosition[0]%97);
	this->currentPosition.second = int(currentPosition[1]%48);
	this->nextPosition.first = int(nextPosition[0]%97);
	this->nextPosition.second = int(nextPosition[1]%48);
	if(symbol == "N")
		this->name = "Knight";
	else if(symbol == "B")
		this->name = "Bishop";
	else
		this->name = "Rook";
}

void Piece::setNextPosition(std::string nextPosition){
	this->nextPosition.first = int(nextPosition[0]%97);
	this->nextPosition.second = int(nextPosition[1]%48);
}

void Piece::checkMovement(){
	for (unsigned int i=0; i<this->movement.size(); i++){
		if(this->currentPosition.first + this->movement[i].first == this->nextPosition.first &&
			this->currentPosition.second + this->movement[i].second == this->nextPosition.second){
			std::cout<<"Moving from ("<<char((this->currentPosition.first+97))<<this->currentPosition.second<<") to ("<<char((this->nextPosition.first+97))<<this->nextPosition.second<<")"<<std::endl;
			this->currentPosition.first = this->nextPosition.first;
			this->currentPosition.second = this->nextPosition.second;
		}
	}
	std::cout<<"I cannot move from ("<<char((this->currentPosition.first+97))<<this->currentPosition.second<<") to ("<<char((this->nextPosition.first+97))<<this->nextPosition.second<<")"<<std::endl;
}

void Piece::printPossibleMoves(){
	this->legalMovements.clear();
	for (std::size_t i=0; i<this->movement.size(); i++){
		int finalLetterCoordinate = this->currentPosition.first + this->movement[i].first;
		int finalNumberCoordinate = this->currentPosition.second + this->movement[i].second;
		if(finalLetterCoordinate < BOARD_SIZE && finalLetterCoordinate >= 0 &&
			finalNumberCoordinate <= BOARD_SIZE && finalNumberCoordinate > 0){
				std::string key = char(finalLetterCoordinate+97) + std::to_string(finalNumberCoordinate);
				this->legalMovements.insert(key);
		}
	}
	std::cout<<"("<<this->name<<")"<<" Current Position: ("<<char((this->currentPosition.first+97))<<this->currentPosition.second<<")"<<std::endl;
	std::cout<<"I have "<<legalMovements.size()<<" legal movements."<<std::endl;
	for(auto move : this->legalMovements){
		std::cout<<"("<<char(this->currentPosition.first+97)<<this->currentPosition.second<<")->("<<move<<")"<<std::endl;
	}
}

void Knight::setMovements(){
	this->movement = {
        {1,-2},{2,-1},{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2}
    };
}

void Bishop::setMovements(){
	for(int i=1; i<=BOARD_SIZE; i++){
		this->movement.push_back({i,i});
		this->movement.push_back({-i,-i});
		this->movement.push_back({i,-i});
		this->movement.push_back({-i,i});
	}
}

void Rook::setMovements(){
	for(int i=0; i<=BOARD_SIZE; i++){
	    if(i - this->currentPosition.first != 0)
            this->movement.push_back({i - this->currentPosition.first, 0});
        if(i - this->currentPosition.second != 0)
	        this->movement.push_back({0, i - this->currentPosition.second});
	}
}