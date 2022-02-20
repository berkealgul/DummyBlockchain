#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include "md5.h"

using namespace std;

class Block
{
public:
    string sPrevHash;
    Block* next;
    MD5 md5;

    Block(uint32_t nIndexIn, const string& sDataIn);

    string GetHash()
    {
        return _sHash;
    }

    void MineBlock(const uint32_t nDifficulty) 
    {
        char cstr[nDifficulty+1];

        for (uint32_t i = 0; i < nDifficulty; ++i) 
        {
            cstr[i] = '0';
        }

        cstr[nDifficulty] = '\0';

        string str(cstr);

        do {
            _nNonce++;
            _sHash = _CalculateHash();
        } while (_sHash.substr(0, nDifficulty) != str);

        cout << "Block mined: " << _sHash << endl;
    }

private:
    uint32_t _nIndex;
    int64_t _nNonce;
    string _sData;
    string _sHash;
    time_t _tTime;

    string _CalculateHash()
    {
        stringstream ss;
        ss << _nIndex << _tTime << _sData << _nNonce << sPrevHash;
        return md5(ss.str());
    }
};


class BlockChain
{
public:

    BlockChain()
    {
        _block = new Block(0, "Initial Block");
        _lastBlock = _block;
        _nDifficulty = 6;
    }

    void addBlock(Block* bNew)
    {
        bNew->sPrevHash = _lastBlock->GetHash();
        bNew->MineBlock(_nDifficulty);
        _lastBlock->next = bNew;
        _lastBlock = bNew;
    }

    Block* getLastBlock()
    {
        return _lastBlock;
    }

private:
    int _nDifficulty;

    Block* _block;
    Block* _lastBlock;
};