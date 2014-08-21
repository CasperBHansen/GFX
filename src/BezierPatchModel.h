/*
 * Introduction to Computer Graphics
 *
 * BezierPatchModel.h
 *
 */

#ifndef BEZIERPATCHMODEL_H
#define BEZIERPATCHMODEL_H

#include "Object.h"

#include <GL/glew.h>

#include <vector>

#include "utilities/glmutils.h"
#include "BezierPatch.h"

#ifndef BUFFER_COUNT
#define BUFFER_COUNT 3

typedef enum {
	VERTEX_BUFFER,
	NORMAL_BUFFER,
    TEXCOORD_BUFFER
} BufferId;
#endif

class BezierPatchModel : public Object
{
public:
	BezierPatchModel(const char * filename);
	~BezierPatchModel();
    
    void update();
    
    void render(int mask) const;
    
    void setLevel(int n);
    void increaseLevel();
    void decreaseLevel();

protected:
    void subdivide(const BezierPatch &patch, int n);
    
private:
    int level, num_vertices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<BezierPatch> patches;
    
    GLuint vao;
    GLuint buffers[BUFFER_COUNT]; 
};

#endif // BEZIERPATCHMODEL_H

