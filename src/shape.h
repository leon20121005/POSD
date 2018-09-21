class Shape
{
    public:
        virtual double area() const = 0;

        virtual double perimeter() const = 0;

        double compactness() const
        {
            try
            {
                if (this->area() == 0)
                {
                    throw "Division by zero";
                }
                return this->perimeter() * this->perimeter() / this->area();
            }
            catch (const char* string)
            {
                std::cout << string << std::endl;
            }
        }
};
