glm::vec2 Camera::getWindowCenter()
{
    return glm::vec2( (min.x + max.x) / 2.0f, (min.y + max.y) / 2.0f );
}
