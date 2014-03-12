glm::vec2 Camera::getViewport()
{
    return glm::vec2( max.x - min.x, max.y - min.y );
}
