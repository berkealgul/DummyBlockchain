#include <iostream>
#include "blockchain.h"

int main()
{
	BlockChain someShitCoin;

	someShitCoin.addBlock(new Block(0, "lmafo"));
	someShitCoin.addBlock(new Block(1, "lmafoasd"));
	someShitCoin.addBlock(new Block(2, "lmasadsadfo"));

	return 0;
}