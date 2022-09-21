//
// Created by kieru on 2022/9/14.
//

#ifndef OBJIMPORT_SPHCOOR_H
#define OBJIMPORT_SPHCOOR_H


class SphCoor{
public:
    SphCoor() = default;
    SphCoor(double r, double phi, double theta) :
            r_(r), phi_(phi), theta_(theta) {}
    double& r() { return r_; }
    double& phi() { return phi_; }
    double& theta() { return theta_; }

    void calCart();
    double x() const { return x_; }
    double y() const { return y_; }
    double z() const { return z_; }
private:
    double r_ = 0;
    double phi_ = 0;
    double theta_ = 0;
    double x_ = 0;
    double y_ = 0;
    double z_ = 0;
};


#endif //OBJIMPORT_SPHCOOR_H
