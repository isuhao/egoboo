//********************************************************************************************
//*
//*    This file is part of Egoboo.
//*
//*    Egoboo is free software: you can redistribute it and/or modify it
//*    under the terms of the GNU General Public License as published by
//*    the Free Software Foundation, either version 3 of the License, or
//*    (at your option) any later version.
//*
//*    Egoboo is distributed in the hope that it will be useful, but
//*    WITHOUT ANY WARRANTY; without even the implied warranty of
//*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//*    General Public License for more details.
//*
//*    You should have received a copy of the GNU General Public License
//*    along with Egoboo.  If not, see <http://www.gnu.org/licenses/>.
//*
//********************************************************************************************

/// @file   egolib/Math/Entity.hpp
/// @brief  Common properties of all entities in this library.
/// @author Michael Heilmann

#pragma once

#include "egolib/Math/Dimensionality.hpp"
#include "egolib/Math/Scalar.hpp"

namespace Ego {
namespace Math {
namespace Internal {

/**
 * @brief
 *  The base template of most entities in the Ego::Math library.
 * @param _ScalarType
 *  must fulfil the <em>scalar</em> concept
 * @param _Dimensionality
 *  must fulfil the <em>dimensionality</em> concept
 * @author
 *  Michael Heilmann
 */
template <typename _ScalarType, size_t _Dimensionality, typename _Enable = void>
struct Entity;

template <typename _ScalarType, size_t _Dimensionality>
struct Entity<_ScalarType, _Dimensionality, typename std::enable_if<IsScalar<_ScalarType>::value && IsDimensionality<_Dimensionality>::value>::type> {

	/**
     * @brief
     *  The scalar type.
     */
    typedef _ScalarType ScalarType;

	/**
	 * @brief
	 *  The scalar field type.
	 */
	typedef ScalarField<_ScalarType> ScalarFieldType;

    /**
     * @brief
     *  The vector type.
     */
    typedef Vector<_ScalarType, _Dimensionality> VectorType;

    /**
     * @brief
     *  Get the dimensionality.
     * @return
     *  the dimensionality
     */
    static size_t dimensionality() {
        return _Dimensionality;
    }
};

} // namespace Internal
} // namespace Math
} // namespace Ego
