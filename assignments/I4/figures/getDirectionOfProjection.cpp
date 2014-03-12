glm::vec3 Camera::getDirectionOfProjection()
{
    glm::vec2 cw = getWindowCenter();
    return glm::vec3(prp.x - cw.x, prp.y - cw.y, prp.z);
}
