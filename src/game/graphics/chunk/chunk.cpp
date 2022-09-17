#include "chunk.h"
#include <iostream>

ChunkGraphicsController::ChunkGraphicsController()
{
  std::cout << "creating chunk graphics controller " << this << std::endl;
}

ChunkGraphicsController::~ChunkGraphicsController()
{
  std::cout << "destroying chunk graphics controller " << this << std::endl;
}

void ChunkGraphicsController::load(const unsigned char* chunk_data)
{
  
}

void ChunkGraphicsController::draw()
{

}