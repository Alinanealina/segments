#include <iostream>
using namespace std;
class Vector3D
{
public:
    double X;
    double Y;
    double Z;
    Vector3D() : X(0), Y(0), Z(0)
    {

    }
    Vector3D(double X, double Y, double Z) : X(X), Y(Y), Z(Z)
    {

    }
    bool equal(Vector3D a)
    {
        if ((X == a.X) &&
            (Y == a.Y) &&
            (Z == a.Z))
            return true;
        else
            return false;
    }
    double get_length(Vector3D end)
    {
        return sqrt(pow(end.X - X, 2) +
            pow(end.Y - Y, 2) +
            pow(end.Z - Z, 2));
    }
    void print()
    {
        cout << "(" << X << "; " << Y << "; " << Z << ")" << endl;
    }
};

class Segment3D
{
public:
    Vector3D start;
    Vector3D end;
    Segment3D(Vector3D start, Vector3D end) : start(start), end(end)
    {

    }
    Vector3D get_guide()
    {
        return Vector3D(end.X - start.X,
            end.Y - start.Y,
            end.Z - start.Z);
    }
    double get_length()
    {
        return start.get_length(end);
    }
};

void set_system(double p[3][3], int i, Segment3D seg)
{
    p[0][i] = pow(-1, i) * seg.get_guide().X;
    p[1][i] = pow(-1, i) * seg.get_guide().Y;
    p[2][i] = pow(-1, i) * seg.get_guide().Z;

    p[0][2] -= pow(-1, i) * seg.start.X;
    p[1][2] -= pow(-1, i) * seg.start.Y;
    p[2][2] -= pow(-1, i) * seg.start.Z;
}
Vector3D Intersect(Segment3D seg_a, Segment3D seg_b)
{
    double p[3][3] = { 0 }, param[2] = { 0 };
    set_system(p, 0, seg_a);
    set_system(p, 1, seg_b);

    int i2 = 0;
    for (int i = 0; i < 3; i++, i2++)
    {
        double coef = p[i][i2];
        if (coef == 0)
        {
            i2--;
            continue;
        }
        for (int j = 0; j < 3; j++)
        {
            p[i][j] /= coef;
        }

        for (int j = i + 1; j < 3; j++)
        {
            double coeff2 = p[j][0];
            for (int k = 0; k < 3; k++)
            {
                p[j][k] -= p[i][k] * coeff2;
            }
        }
    }

    i2 = 1;
    for (int i = 2; i >= 0; i--, i2--)
    {
        if (p[i][i2] != 1)
        {
            i2++;
            continue;
        }
        for (int j = 1; j > i2; j--)
        {
            param[i2] -= p[i][j] * param[j];
        }
        param[i2] += p[i][2];
    }

    Vector3D res_a(param[0] * seg_a.get_guide().X + seg_a.start.X,
        param[0] * seg_a.get_guide().Y + seg_a.start.Y,
        param[0] * seg_a.get_guide().Z + seg_a.start.Z);
    Vector3D res_b(param[1] * seg_b.get_guide().X + seg_b.start.X,
        param[1] * seg_b.get_guide().Y + seg_b.start.Y,
        param[1] * seg_b.get_guide().Z + seg_b.start.Z);

    if (res_a.equal(res_b) &&
        (res_a.get_length(seg_a.end) <= seg_a.get_length()) && (res_a.get_length(seg_a.start) <= seg_a.get_length()) &&
        (res_a.get_length(seg_b.end) <= seg_b.get_length()) && (res_a.get_length(seg_b.start) <= seg_b.get_length()))
    {
        cout << "Отрезки пересекаются в точке: ";
        res_a.print();
        return res_a;
    }
    cout << "Отрезки не пересекаются.";
    return Vector3D();
}

int main()
{
    setlocale(LC_ALL, "Russian");
    /*Segment3D a(Vector3D(2, 1, 0), Vector3D(4, 3, 0));
    Segment3D b(Vector3D(2, 2, 0), Vector3D(5, 0, 0));
    Segment3D c(Vector3D(3, 1, 0), Vector3D(5, 1, 0));
    Intersect(a, b);
    Intersect(a, c);*/

    Segment3D a(Vector3D(1, 0, 3), Vector3D(0, 1, 0));
    Segment3D b(Vector3D(0, 1, 3), Vector3D(1, 0, 0));
    Intersect(a, b);
}