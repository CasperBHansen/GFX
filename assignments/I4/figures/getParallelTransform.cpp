glm::mat4 Camera::getParallelTransform()
{
    // translation
    glm::mat4 T_vrp({
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        -vrp.x, -vrp.y, -vrp.z, 1.0f
    });
    
    // z-rotation
    float l = glm::length(vpn);
    glm::vec3 rz = vpn / l;
    
    // x-rotation
    glm::vec3 vup_x_rz = glm::cross(vup, rz);
    l = glm::length(vup_x_rz);
    glm::vec3 rx = vup_x_rz / l;
    
    // y-rotation
    glm::vec3 rz_x_rx = glm::cross(rz, rx);
    l = glm::length(rz_x_rx);
    glm::vec3 ry = rz_x_rx / l;
    
    // rotation
    glm::mat4 R({
        rx.x, ry.x, rz.x, 0.0f,
        rx.y, ry.y, rz.y, 0.0f,
        rx.z, ry.z, rz.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
    
    // shear - Sh
    glm::vec3 dop = getDirectionOfProjection();
    float sh_x = -(dop.x / dop.z);
    float sh_y = -(dop.y / dop.z);
    glm::mat4 Sh({
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        sh_x, sh_y, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
    
    // translate
    glm::vec2 cw = getWindowCenter();
    glm::mat4 T_par({
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        -cw.x, -cw.y, -front, 1.0f
    });
    
    // scale
    glm::mat4 S_par({
        2.0f / (max.x - min.x), 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f / (max.y - min.y), 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f / (front - back), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
    
    return S_par * T_par * Sh * R * T_vrp * Object::getTransform();
}
