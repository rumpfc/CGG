#include "Color.h"


Color::Color() : r_(0.0f), g_(0.0f), b_(0.0f)
{
}

Color::Color(const float r, const float g, const float b)
{
	setColor(r, g, b);
}

Color::Color(const int colorcode)
{
	setColor(colorcode);
}

Color::Color(const Color& src) : r_(src.r_), g_(src.g_), b_(src.b_)
{
}

Color::~Color()
{
}


// getter and setter

void Color::setColor(const float r, const float g, const float b)
{
	r_ = (r < 0.0f) ? 0.0f : (r > 1.0f) ? 1.0f : r;
	g_ = (g < 0.0f) ? 0.0f : (g > 1.0f) ? 1.0f : g;
	b_ = (b < 0.0f) ? 0.0f : (b > 1.0f) ? 1.0f : b;
}

void Color::setColor(const int colorcode)
{
	// colorcode: 0xRRGGBB  with R, G and B = 0, 1, ..., E, F
	r_ = static_cast<float>((colorcode >> 16) & 0xff) / 255.0f;
	g_ = static_cast<float>((colorcode >>  8) & 0xff) / 255.0f;
	b_ = static_cast<float>(colorcode & 0xff) / 255.0f;
}


void Color::setColor(const Color& color)
{
	r_ = color.r_; g_ = color.g_; b_ = color.b_;
}


void Color::setColor(const float color[3])
{
	r_ = color[0]; g_ = color[1]; b_ = color[2];
}

void Color::setRed(const float red) { r_ = (red < 0.0f) ? 0.0f : (red > 1.0f) ? 1.0f : red; }
void Color::setGreen(const float green) { g_ = (green < 0.0f) ? 0.0f : (green > 1.0f) ? 1.0f : green; }
void Color::setBlue(const float blue) { b_ = (blue < 0.0f) ? 0.0f : (blue > 1.0f) ? 1.0f : blue; }

void Color::setRed(const unsigned char red) { r_ = red / 255.0f; }
void Color::setGreen(const unsigned char green) { g_ = green / 255.0f; }
void Color::setBlue(const unsigned char blue) { b_ = blue / 255.0f; }

float Color::getRed()
{
	return r_;
}

float Color::getGreen()
{
	return g_;
}

float Color::getBlue()
{
	return b_;
}

unsigned char Color::getRed8B()
{
	return r_ < 1.0f ? static_cast<unsigned char>(r_ * 255) : 255;
}

unsigned char Color::getGreen8B()
{
	return g_ < 1.0f ? static_cast<unsigned char>(g_ * 255) : 255;
}

unsigned char Color::getBlue8B()
{
	return b_ < 1.0f ? static_cast<unsigned char>(b_ * 255) : 255;
}

int Color::getRGB()
{
	return (getRed8B() << 16) | (getGreen8B() << 8) | getBlue8B();
}


Color operator+(const Color& c1, const Color& c2)
{
	return Color(c1.r_ + c2.r_, c1.g_ + c2.g_, c1.b_ + c2.b_);
}

Color operator-(const Color& c1, const Color& c2)
{
	return Color(c1.r_ - c2.r_, c1.g_ - c2.g_, c1.b_ - c2.b_);
}

Color operator*(const Color& c1, const Color& c2)
{
	return Color(c1.r_ * c2.r_, c1.g_ * c2.g_, c1.b_ * c2.b_);
}

Color operator*(const Color& c, const float d)
{
	return Color(c.r_ * d, c.g_ * d, c.b_ * d);
}

Color operator*(const float d, const Color& c)
{
	return Color(c.r_ * d, c.g_ * d, c.b_ * d);
}

Color operator*(const Color& c, const double d)
{
	return Color(c.r_ * static_cast<float>(d), c.g_ * static_cast<float>(d), c.b_ * static_cast<float>(d));
}

Color operator*(const double d, const Color& c)
{
	return Color(c.r_ * static_cast<float>(d), c.g_ * static_cast<float>(d), c.b_ * static_cast<float>(d));
}

Color operator/(const Color& c, const float d) 
{
	return Color(c.r_ / d, c.g_ / d, c.b_ / d);
}

Color operator/(const Color& c, const double d)
{
	return Color(c.r_ / static_cast<float>(d), c.g_ / static_cast<float>(d), c.b_ / static_cast<float>(d));
}

void Color::operator=(const Color& c) 
{
	r_ = c.r_; g_ = c.g_; b_ = c.b_;
}

void Color::operator+=(const Color& c)
{
	r_ += c.r_; g_ += c.g_; b_ += c.b_;
}

void Color::operator-=(const Color& c)
{
	r_ -= c.r_; g_ -= c.g_; b_ -= c.b_;
}

void Color::operator*=(const float d)
{
	r_ *= d; g_ *= d; b_ *= d;
}