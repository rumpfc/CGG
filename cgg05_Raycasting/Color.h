#ifndef COLOR_H_
#define COLOR_H_

/*
Color class for storing the colors red, green and blue
can be mixed (i.e. reflecting on colored surfaces)
*/

class Color
{
private:
	// Color channels red, green and blue
	float r_;
	float g_;
	float b_;

public:
	Color();             // starts with black
	Color(const float r, const float g, const float b);
	Color(const int colorcode);
	Color(const Color& src);
	virtual ~Color();

	// getter and setter methods (float and 8 Bit colors)

	void setColor(const float r, const float g, const float b);
	void setColor(const int colorcode);              // 0xRRGGBB
	void setColor(const Color& color);
	void setColor(const float color[3]);

	void setRed(const float red);
	void setGreen(const float green);
	void setBlue(const float blue);

	void setRed(const unsigned char red);
	void setGreen(const unsigned char green);
	void setBlue(const unsigned char blue);

	float getRed();
	float getGreen();
	float getBlue();

	unsigned char getRed8B();
	unsigned char getGreen8B();
	unsigned char getBlue8B();

	int getRGB();

	// overloaded operators (similar to Vector classes)

	friend Color operator+(const Color& c1, const Color& c2);
	friend Color operator-(const Color& c1, const Color& c2);
	friend Color operator*(const Color& c1, const Color& c2);
	friend Color operator*(const Color& c, const float d);
	friend Color operator*(const float d, const Color& c);
	friend Color operator*(const Color& c, const double d);
	friend Color operator*(const double d, const Color& c);
	friend Color operator/(const Color& c, const float d);
	friend Color operator/(const Color& c, const double d);

	void operator=(const Color& c);
	void operator+=(const Color& c);
	void operator-=(const Color& c);
	void operator*=(const float d);
};

#endif