#if !defined(CHUNK_H)
#define CHUNK_H

#include <array>
#include "src/config/config.h"

class Chunk
{
public:
  Chunk(const int chunk_index_x, const int chunk_index_y);
  ~Chunk();
  const int chunk_index_x;
  const int chunk_index_y;
  const unsigned char* get_data_ptr() const;
private:
  std::array<
    unsigned char,
    config::chunk_size  
  > m_data;
};

#endif // CHUNK_H
