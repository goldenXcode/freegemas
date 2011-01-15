#include <GosuImpl/Graphics/TexChunk.hpp>
#include <GosuImpl/Graphics/Texture.hpp>
#include <GosuImpl/Graphics/DrawOpQueue.hpp>
#include <Gosu/Bitmap.hpp>
#include <Gosu/Graphics.hpp>

Gosu::TexChunk::TexChunk(Graphics& graphics, Transforms& transforms, DrawOpQueueStack& queues,
    boost::shared_ptr<Texture> texture, int x, int y, int w, int h, int padding)
:   graphics(&graphics), transforms(&transforms), queues(&queues),
    texture(texture), x(x), y(y), w(w), h(h), padding(padding)
{
    info.texName = texture->texName();
    info.left    = float(x) / texture->size();
    info.top     = float(y) / texture->size();
    info.right   = float(x + w) / texture->size();
    info.bottom  = float(y + h) / texture->size();
}

Gosu::TexChunk::~TexChunk()
{
    texture->free(x - padding, y - padding);
}

void Gosu::TexChunk::draw(double x1, double y1, Color c1,
    double x2, double y2, Color c2,
    double x3, double y3, Color c3,
    double x4, double y4, Color c4,
    ZPos z, AlphaMode mode) const
{
    DrawOp newDrawOp(transforms->back());
    
    reorderCoordinatesIfNecessary(x1, y1, x2, y2, x3, y3, c3, x4, y4, c4);
    
    newDrawOp.usedVertices = 4;
    newDrawOp.vertices[0] = DrawOp::Vertex(x1, y1, c1);
    newDrawOp.vertices[1] = DrawOp::Vertex(x2, y2, c2);
// TODO: Should be harmonized
#ifdef GOSU_IS_IPHONE
    newDrawOp.vertices[2] = DrawOp::Vertex(x3, y3, c3);
    newDrawOp.vertices[3] = DrawOp::Vertex(x4, y4, c4);
#else
    newDrawOp.vertices[3] = DrawOp::Vertex(x3, y3, c3);
    newDrawOp.vertices[2] = DrawOp::Vertex(x4, y4, c4);
#endif
    newDrawOp.chunk = this;
    newDrawOp.mode = mode;
    
    queues->back().scheduleDrawOp(newDrawOp, z);
}

boost::optional<Gosu::GLTexInfo> Gosu::TexChunk::glTexInfo() const
{
    return info;
}

Gosu::Bitmap Gosu::TexChunk::toBitmap() const
{
    return texture->toBitmap(x, y, w, h);
}
