#include <iostream>

#include "../src/shape.h"
#include "../src/circle.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"

#include <vector>
#include "../src/sort.h"

#include <string>
#include <fstream>
#include <sstream>

using namespace std;

vector<string>* ReadFile(char* fileName);
Shape* ParseShapeString(string shapeString);
vector<string>* Split(string s, string delimiter);
string RemoveNoise(string s);
double ConvertStringToDouble(string s);
void SortShapes(vector<Shape*>* shapes, string method, string order);
void WriteAreaToFile(char* fileName, vector<Shape*>* shapes);
void WritePerimeterToFile(char* fileName, vector<Shape*>* shapes);

int main(int argc, char* argv[])
{
    vector<string>* lines = ReadFile(argv[1]);
    vector<Shape*>* shapes = new vector<Shape*>();

    for (int index = 0; index < lines->size() - 1; index++)
    {
        Shape* shape = ParseShapeString((*lines)[index]);
        shapes->push_back(shape);
    }

    SortShapes(shapes, (string)argv[3], (string)argv[4]);

    if ((string)argv[3] == "area")
    {
        WriteAreaToFile(argv[2], shapes);
    }
    else if ((string)argv[3] == "perimeter")
    {
        WritePerimeterToFile(argv[2], shapes);
    }
}

vector<string>* ReadFile(char* fileName)
{
    fstream file(fileName);
    string line;
    vector<string>* lines = new vector<string>();

    while (!file.eof())
    {
        getline(file, line);
        lines->push_back(line);
    }
    file.close();
    return lines;
}

Shape* ParseShapeString(string shapeString)
{
    string classString = shapeString.substr(0, shapeString.find(" "));
    string parameterString = shapeString.substr(shapeString.find(" ") + sizeof(" "));
    vector<string>* parameterStrings = Split(RemoveNoise(parameterString), ",");

    vector<double>* parameters = new vector<double>();
    for (int index = 0; index < parameterStrings->size(); index++)
    {
        parameters->push_back(ConvertStringToDouble((*parameterStrings)[index]));
    }

    if (classString == "Circle")
    {
        return new Circle((*parameters)[0]);
    }
    if (classString == "Rectangle")
    {
        return new Rectangle((*parameters)[0], (*parameters)[1]);
    }
    if (classString == "Triangle")
    {
        return new Triangle((*parameters)[0], (*parameters)[1], (*parameters)[2], (*parameters)[3], (*parameters)[4], (*parameters)[5]);
    }
    else
    {
        return nullptr;
    }
}

vector<string>* Split(string s, string delimiter)
{
    vector<string>* result = new vector<string>();

    for (int index = 0; index < s.size();)
    {
        result->push_back(s.substr(index, s.find(delimiter, index) - index));

        if (s.find(delimiter, index) == string::npos)
        {
            break;
        }
        index = index + (s.find(delimiter, index) - index + delimiter.size());
    }
    return result;
}

string RemoveNoise(string s)
{
    for (int index = 0; index < s.size(); index++)
    {
        if (s[index] == '(' || s[index] == ')' || s[index] == ' ')
        {
            s.erase(index, sizeof(' '));
        }
    }
    return s;
}

double ConvertStringToDouble(string s)
{
    double result;
    stringstream stringStream(s);
    stringStream >> result;
    return result;
}

void SortShapes(vector<Shape*>* shapes, string method, string order)
{
    Sort* sort = new Sort(shapes);

    if (method == "area" && order == "inc")
    {
        sort->sortArea([](Shape* a, Shape* b)
        {
            return a->area() < b->area();
        });
        return;
    }
    if (method == "area" && order == "dec")
    {
        sort->sortArea([](Shape* a, Shape* b)
        {
            return a->area() > b->area();
        });
        return;
    }
    if (method == "perimeter" && order == "inc")
    {
        sort->sortPerimeter(perimeterAscendingComparison);
        return;
    }
    if (method == "perimeter" && order == "dec")
    {
        sort->sortPerimeter(perimeterDescendingComparison);
        return;
    }
}

void WriteAreaToFile(char* fileName, vector<Shape*>* shapes)
{
    ofstream file(fileName);
    file << "[";
    for (int index = 0; index < shapes->size() - 1; index++)
    {
        file << (*shapes)[index]->area() << ",";
    }
    file << (*shapes)[shapes->size() - 1]->area() << "]\n";
    file.close();
}

void WritePerimeterToFile(char* fileName, vector<Shape*>* shapes)
{
    ofstream file(fileName);
    file << "[";
    for (int index = 0; index < shapes->size() - 1; index++)
    {
        file << (*shapes)[index]->perimeter() << ",";
    }
    file << (*shapes)[shapes->size() - 1]->perimeter() << "]\n";
    file.close();
}
