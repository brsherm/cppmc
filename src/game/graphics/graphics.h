#if !defined(GRAPHICS_H)
#define GRAPHICS_H

#include "../chunk/chunk.h"
#include "./chunk/chunk.h"
#include <unordered_map>
#include <memory>

namespace Graphics
{
  struct ChunkLoader
  {
    bool success;
    std::string error;
  };

  struct ChunkUnloader
  {
    bool success;
    std::string error;
  };
}

class GraphicsManager
{
  private:
    std::unordered_map<
      int,
      std::unordered_map<int, std::unique_ptr<ChunkGraphicsController>>
    > chunk_controllers;
    ChunkGraphicsController* get_chunk_controller_ptr(
      const int chunk_index_x,
      const int chunk_index_y
    );
    void add_chunk_controller(
      const int chunk_index_x,
      const int chunk_index_y
    );
    void remove_chunk_controller(
      const int chunk_index_x,
      const int chunk_index_y
    );
    void draw_chunks();
  public:
    GraphicsManager();
    ~GraphicsManager();
    void draw();
    void load_chunk(const Chunk& chunk, Graphics::ChunkLoader& loader);
    void unload_chunk(const Chunk& chunk, Graphics::ChunkUnloader& unloader);
    std::string loaded_chunks() const;
};

#endif // GRAPHICS_H
