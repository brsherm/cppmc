#include "chunk.h"

Chunk::Chunk(const int chunk_index_x, const int chunk_index_y) :
  chunk_index_x(chunk_index_x),
  chunk_index_y(chunk_index_y)
{

}

Chunk::~Chunk() {}

const unsigned char* Chunk::get_data_ptr() const
{
  return m_data.data();
}