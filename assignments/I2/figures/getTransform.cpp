glm::mat4 Object::getTranform()
{
    float s[16] =
    {
        _scale.x,   0.0f,       0.0f,       0.0f,
        0.0f,       _scale.y,   0.0f,       0.0f,
        0.0f,       0.0f,       _scale.z,   0.0f,
        0.0f,       0.0f,       0.0f,       1.0f
    };
    
    float r_x[16] =
    {
        1.0f,   0.0f,                   0.0f,                   0.0f,
        0.0f,   glm::cos(_rotation.x),  glm::sin(_rotation.x),  0.0f,
        0.0f,  -glm::sin(_rotation.x),  glm::cos(_rotation.x),  0.0f,
        0.0f,   0.0f,                   0.0f,                   1.0f
    };
    
    float r_y[16] =
    {
        glm::cos(_rotation.y),  0.0f,  -glm::sin(_rotation.y),  0.0f,
        0.0f,                   1.0f,   0.0f,                   0.0f,
        glm::sin(_rotation.y),  0.0f,   glm::cos(_rotation.y),  0.0f,
        0.0f,                   0.0f,   0.0f,                   1.0f
    };
    
    float r_z[16] =
    {
        glm::cos(_rotation.z),  glm::sin(_rotation.z),  0.0f,   0.0f,
       -glm::sin(_rotation.z),  glm::cos(_rotation.z),  0.0f,   0.0f,
        0.0f,                   0.0f,                   1.0f,   0.0f,
        0.0f,                   0.0f,                   0.0f,   1.0f
    };
    
    float t[16] =
    {
        1.0f,           0.0f,           0.0f,           0.0f,
        0.0f,           1.0f,           0.0f,           0.0f,
        0.0f,           0.0f,           1.0f,           0.0f,
        _position.x,    _position.y,    _position.z,    1.0f
    };
    
    glm::mat4 s_mtx = glm::make_mat4(s);
    glm::mat4 r_mtx = glm::make_mat4(r_z) * glm::make_mat4(r_y) * glm::make_mat4(r_x);
    glm::mat4 t_mtx = glm::make_mat4(t);
    
    matrix = t_mtx * r_mtx * s_mtx;
    
    return matrix;
}

