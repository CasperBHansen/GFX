// initialization
int dx = (b.x - a.x);
int abs_2dx = (int)std::abs(dx) << 1;
int x_step = (dx < 0) ? -1 : 1;

int dy = (b.y - a.y);
int abs_2dy = (int)std::abs(dy) << 1;
int y_step = (dy < 0) ? -1 : 1;
 
Point2D pixel = a;
bool dom = abs_2dx > abs_2dy;
    
// x-dominant loop
if (dom) {
    bool left_right = (x_step > 0);
    int d = abs_2dy - (abs_2dx >> 1);
    while (true) {
        draw->point(pixel);
        if (pixel.x == b.x) return; 
        if ( (d > 0) || ((d == 0) && left_right) ) {
            pixel.y += y_step;
            d -= abs_2dx;
        }
        pixel.x += x_step;
        d += abs_2dy;
    }
}
// y-dominant loop
else {
    bool left_right = (y_step > 0);
    int d = abs_2dx - (abs_2dy >> 1);
    while (true) {
        draw->point(pixel);
        if (pixel.y == b.y) return;
        if ( (d > 0) || ((d == 0) && left_right) ) {
            pixel.x += x_step;
            d -= abs_2dy;
        }
        pixel.y += y_step;
        d += abs_2dx;
    }
}
