#include "alert_box.h"
#include "caca_game.h"
#include <mutex>
#include <string>

alert_box::alert_box(caca_game *game, int x, int y, int width, int height, function<void(const alert_box &)> callback) :
    game_(game), x_(x), y_(y), width_(width), height_(height), callback_(callback)
{
}

void alert_box::display()
{
    lock_guard<recursive_mutex> lock(game_->mutex_);

    caca_fill_box(game_->canvas_, x_, y_, width_, height_, ' ');

    caca_draw_thin_box(game_->canvas_, x_, y_, width_, height_);

    if (callback_ != nullptr)
        callback_(*this);

    game_->set_needs_display();
}

int alert_box::width() const
{
    return width_;
}

int alert_box::height() const
{
    return height_;
}

int alert_box::x() const
{
    return x_;
}

int alert_box::y() const
{
    return y_;
}

void alert_box::center(const string &text) const
{
    lock_guard<recursive_mutex> lock(game_->mutex_);

    int x = center_x() - (text.length() / 2);
    int y = center_y();

    caca_put_str(game_->canvas_, x, y, text.c_str());
}
void alert_box::center_x(int y, const string &text) const
{
    lock_guard<recursive_mutex> lock(game_->mutex_);

    int x = center_x() - (text.length() / 2);

    caca_put_str(game_->canvas_, x, y, text.c_str());
}

int alert_box::center_y() const
{
    return y_ + (height_ / 2);
}

int alert_box::center_x() const
{
    return x_ + (width_ / 2);
}

int alert_box::center_x(const string &str) const
{
    return x_ + ( (width_ - str.length()) / 2);
}