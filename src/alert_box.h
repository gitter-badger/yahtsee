
class alert_box
{
public:

    alert_box(caca_canvas_t *canvas, caca_display_t *display, int x, int y, int width, int height, function<void(const alert_box &)> callback) :
        canvas_(canvas), display_(display), x_(x), y_(y), width_(width), height_(height), callback_(callback)
    {
    }

    void display()
    {
        caca_fill_box(canvas_, x_, y_, width_, height_, ' ');

        caca_draw_thin_box(canvas_, x_, y_, width_, height_);

        callback_(*this);

        caca_refresh_display(display_);
    }

    int width() const
    {
        return width_;
    }

    int height() const
    {
        return height_;
    }

    int x() const
    {
        return x_;
    }

    int y() const
    {
        return y_;
    }

    caca_canvas_t *canvas() const
    {
        return canvas_;
    }

    void center(const string &text) const
    {
        int x = center_x() - (text.length() / 2);
        int y = center_y();

        caca_put_str(canvas_, x, y, text.c_str());
    }
    void center_x(int y, const string &text) const 
    {
        int x = center_x() - (text.length() / 2);

        caca_put_str(canvas_, x, y, text.c_str());
    }

    int center_y() const {
        return y_ + (height_ / 2);
    }

    int center_x() const {
        return x_ + (width_ / 2);
    }

private:
    caca_canvas_t *canvas_;
    caca_display_t *display_;
    int x_, y_;
    int width_, height_;
    function<void(const alert_box &)> callback_;
};