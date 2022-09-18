#include "graphics.h"
#include <iostream>

GraphicsManager::GraphicsManager() {}

GraphicsManager::~GraphicsManager() {}

void GraphicsManager::draw() const
{
  draw_chunks();
}

void GraphicsManager::draw_chunks() const
{
  for (const auto& x : chunk_controllers) {
    for (const auto& y : x.second) {
      y.second->draw();
    }
  }
}

void GraphicsManager::load_chunk(
  const Chunk& chunk,
  Graphics::ChunkLoader& loader
)
{
  std::cout << "loading chunk " << &chunk << std::endl;
  const int ix = chunk.chunk_index_x;
  const int iy = chunk.chunk_index_y;
  if (get_chunk_controller_ptr(ix, iy) != nullptr)
  {
    loader.success = false;
    loader.error = "chunk already loaded";
    return;
  }
  add_chunk_controller(ix, iy);
  chunk_controllers.at(ix).at(iy)->load(chunk.get_data_ptr());
  std::cout << "success" << std::endl;
  loader.success = true;
}

void GraphicsManager::unload_chunk(
  const Chunk& chunk,
  Graphics::ChunkUnloader& unloader
)
{
  std::cout << "unloading chunk " << &chunk << std::endl;
  const int ix = chunk.chunk_index_x;
  const int iy = chunk.chunk_index_y;
  if (get_chunk_controller_ptr(ix, iy) == nullptr) {
    unloader.success = false;
    unloader.error = "chunk not loaded";
    return;
  }
  remove_chunk_controller(ix, iy);
  std::cout << "success" << std::endl;
  unloader.success = true;
}

ChunkGraphicsController* GraphicsManager::get_chunk_controller_ptr(
  const int chunk_index_x,
  const int chunk_index_y
)
{
  if (chunk_controllers.count(chunk_index_x) == 0) {
    return nullptr;
  }
  if (chunk_controllers.at(chunk_index_x).count(chunk_index_y) == 0) {
    return nullptr;
  }
  return chunk_controllers.at(chunk_index_x).at(chunk_index_y).get();
}

void GraphicsManager::add_chunk_controller(
  const int chunk_index_x,
  const int chunk_index_y
)
{
  if (chunk_controllers.count(chunk_index_x) == 0) {
    chunk_controllers[chunk_index_x] = std::unordered_map<
      int,
      std::unique_ptr<ChunkGraphicsController>
    >();
  }
  auto const& y = chunk_controllers.at(chunk_index_x).find(chunk_index_y);
  if (y != chunk_controllers.at(chunk_index_x).end()) {
    return;
  }
  chunk_controllers.at(chunk_index_x)[chunk_index_y] = std::unique_ptr<
    ChunkGraphicsController
  >(new ChunkGraphicsController());
}

void GraphicsManager::remove_chunk_controller(
  const int chunk_index_x,
  const int chunk_index_y
)
{
  if (chunk_controllers.count(chunk_index_x) == 0) {
    return;
  }
  if (chunk_controllers[chunk_index_x].count(chunk_index_y == 0)) {
    return;
  }
  chunk_controllers[chunk_index_x].erase(
    chunk_controllers[chunk_index_x].find(chunk_index_y)
  );
  if (chunk_controllers[chunk_index_x].size() == 0) {
    chunk_controllers.erase(
      chunk_controllers.find(chunk_index_x)
    );
  }
}

std::string GraphicsManager::loaded_chunks() const
{
  std::string s = "{";
  for (const auto& x : chunk_controllers) {
    for (const auto& y : x.second) {
      s = s + "[" + std::to_string(x.first) + ", ";
      s = s + std::to_string(y.first) + "], "; 
    }
  }
  s.resize(s.size() - 2);
  s += "}";
  return s;
}