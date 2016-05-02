#pragma once

#include "egolib/Math/Intersects.hpp"
#include "egolib/Math/Cube.hpp"

namespace Ego {
namespace Math {
/**
 * @brief Functor which determines if a sphere contains another sphere.
 * @remark Two cubes \$x\f$ and \$y\f$ do <em>not</em> intersect if for at least one
 * axis \f$k\f$ at least one of the following conditions is true:
 * - \f$x_{min_k} > y_{max_k}\f$
 * - \f$x_{max_k} < y_{min_k}\f$
 * Otherwise \f$x\f$ and \f$y\f$ intersect.
 * This is a variant of the Separating Axis Theorem (aka SAT).
 */
template <typename EuclideanSpaceType>
struct Intersects<
    Cube<EuclideanSpaceType>,
    Cube<EuclideanSpaceType>
> {
    typedef Cube<EuclideanSpaceType> Type;
    bool operator()(const Type& a, const Type& b) const {
        for (size_t i = 0; i < EuclideanSpaceType::dimensionality();  ++i) {
            // If the minimum of a is greater than the maximum of b along one axis,
            // then they can not intersect.
            if (a.getMin()[i] > b.getMax()[i]) {
                return false;
            }
            // If the maximum of a is smaller than the minimum of b along one axis,
            // then they can not intersect.
            if (a.getMax()[i] < b.getMin()[i]) {
                return false;
            }
        }
        return true;
    }
}; // struct Intersects
} // namespace Math
} // namespace Ego
