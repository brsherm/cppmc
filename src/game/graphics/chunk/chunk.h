#if !defined(CHUNK_GRAPHICS_H)
#define CHUNK_GRAPHICS_H

class ChunkGraphicsController
{
  public:
    ChunkGraphicsController();
    ~ChunkGraphicsController();
    void load(const unsigned char* chunk_data);
    void draw();
};

#endif // CHUNK_GRAPHICS_H
