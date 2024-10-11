
class TriangleProp {
private:
    double side1, side2, side3;

public:
    TriangleProp(double a, double b, double c);
    bool isTriangle() const;
    void printAngles() const;
    void printProperties() const;
};


