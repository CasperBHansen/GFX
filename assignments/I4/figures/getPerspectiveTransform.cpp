glm::mat4 Camera::getPerspectiveTransform()
{
    // translation - T(-VRP)
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
    
    // rotation - R
    glm::mat4 R({
        rx.x, ry.x, rz.x, 0.0f,
        rx.y, ry.y, rz.y, 0.0f,
        rx.z, ry.z, rz.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
    
    // translation - T(-PRP)
    glm::mat4 T_prp({
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        -prp.x, -prp.y, -prp.z, 1.0f
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
    
    glm::mat4 S({
        (-2.0f * prp.z) / ( (max.x - min.x) * (back - prp.z)), 0.0f, 0.0f, 0.0f,
        0.0f, (-2.0f * prp.z) / ( (max.y - min.y) * (back - prp.z)), 0.0f, 0.0f,
        0.0f, 0.0f, -1.0f / (back - prp.z), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    });
    
    glm::mat4 P({
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 1.0f / (prp.z / (back - prp.z) ),
        0.0f, 0.0f, 0.0f, 0.0f,
    });
    
    return P * S * Sh * T_prp * R * T_vrp * Object::getTransform();
}
