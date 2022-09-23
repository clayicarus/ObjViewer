//
// Created by kieru on 2022/9/22.
//

#include "Transform.h"
#include <cmath>

void Transform::rotate(Vector3 eulerAngles) {
    eulerAngles_.x() = fmin(360, eulerAngles_.x());
    eulerAngles_.y() = fmin(360, eulerAngles_.y());
    eulerAngles_.z() = fmin(360, eulerAngles_.z());
}
