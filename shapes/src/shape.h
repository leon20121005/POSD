#ifndef SHAPE_H
#define SHAPE_H

class Shape
{
    public:
        virtual double area() const = 0;

        virtual double perimeter() const = 0;

        double compactness() const
        {
            if (this->area() == 0)
            {
                throw std::string("Division by zero");
            }
            return this->perimeter() * this->perimeter() / this->area();
        }
};

#endif
