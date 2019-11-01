#pragma once


#include <cassert>
#include <cstdint>
#include <cstddef>




#define VECTOR_VECTOR_ASSIGNMENT_OPERATOR_DEFINITION(op)    \
    Derived& operator##op##(const Derived& rhs)             \
    {                                                       \
        Derived& lhs = static_cast<Derived&>(*this);        \
        for (std::size_t i = 0; i != size(); ++i)           \
        {                                                   \
            lhs[i] ##op## rhs[i];                           \
        }                                                   \
        return static_cast<Derived&>(*this);                \
    }

#define VECTOR_SCALAR_ASSIGNMENT_OPERATOR_DEFINITION(op)    \
    Derived& operator##op##(const Scalar& rhs)              \
    {                                                       \
        Derived& lhs = static_cast<Derived&>(*this);        \
        for (std::size_t i = 0; i != size(); ++i)           \
        {                                                   \
            lhs[i] ##op## rhs;                              \
        }                                                   \
        return static_cast<Derived&>(*this);                \
    }

#define VECTOR_BINARY_OPERATOR_DEFINITION(op, type)         \
    Derived operator##op##(##type## rhs) const              \
    {                                                       \
        Derived result = static_cast<const Derived&>(*this);\
        result ##op##= rhs;                                 \
        return result;                                      \
    }

#define VECTOR_VECTOR_BINARY_OPERATOR_DEFINITION(op) VECTOR_BINARY_OPERATOR_DEFINITION(op, const Derived&)
#define VECTOR_SCALAR_BINARY_OPERATOR_DEFINITION(op) VECTOR_BINARY_OPERATOR_DEFINITION(op, const Scalar&)



namespace clipp
{
namespace math
{

    template <typename T, std::size_t Dim, typename Derived>
    class VectorBase
    {
    public:
        using Scalar = T;

        constexpr static std::size_t size()
        {
            return Dim;
        }

        constexpr static Derived Constant(const Scalar& value)
        {
            Derived result;
            for (std::size_t i = 0; i != size(); ++i)
            {
                result[i] = value;
            }
        }

        constexpr static Derived Zero()
        {
            return Constant(static_cast<Scalar>(0.));
        }

        constexpr static Derived One()
        {
            return Constant(static_cast<Scalar>(1.));
        }

        VECTOR_VECTOR_ASSIGNMENT_OPERATOR_DEFINITION(+=);
        VECTOR_VECTOR_ASSIGNMENT_OPERATOR_DEFINITION(-=);
        VECTOR_VECTOR_ASSIGNMENT_OPERATOR_DEFINITION(*=);
        VECTOR_VECTOR_ASSIGNMENT_OPERATOR_DEFINITION(/=);
        VECTOR_VECTOR_ASSIGNMENT_OPERATOR_DEFINITION(<<=);
        VECTOR_VECTOR_ASSIGNMENT_OPERATOR_DEFINITION(>>=);

        VECTOR_SCALAR_ASSIGNMENT_OPERATOR_DEFINITION(+=);
        VECTOR_SCALAR_ASSIGNMENT_OPERATOR_DEFINITION(-=);
        VECTOR_SCALAR_ASSIGNMENT_OPERATOR_DEFINITION(*=);
        VECTOR_SCALAR_ASSIGNMENT_OPERATOR_DEFINITION(/=);
        VECTOR_SCALAR_ASSIGNMENT_OPERATOR_DEFINITION(<<=);
        VECTOR_SCALAR_ASSIGNMENT_OPERATOR_DEFINITION(>>=);

        VECTOR_VECTOR_BINARY_OPERATOR_DEFINITION(+);
        VECTOR_VECTOR_BINARY_OPERATOR_DEFINITION(-);
        VECTOR_VECTOR_BINARY_OPERATOR_DEFINITION(*);
        VECTOR_VECTOR_BINARY_OPERATOR_DEFINITION(/);
        VECTOR_VECTOR_BINARY_OPERATOR_DEFINITION(>>);
        VECTOR_VECTOR_BINARY_OPERATOR_DEFINITION(<<);

        VECTOR_SCALAR_BINARY_OPERATOR_DEFINITION(+);
        VECTOR_SCALAR_BINARY_OPERATOR_DEFINITION(-);
        VECTOR_SCALAR_BINARY_OPERATOR_DEFINITION(*);
        VECTOR_SCALAR_BINARY_OPERATOR_DEFINITION(/);
        VECTOR_SCALAR_BINARY_OPERATOR_DEFINITION(>>);
        VECTOR_SCALAR_BINARY_OPERATOR_DEFINITION(<<);

        Derived operator-() const
        {
            Derived result = static_cast<const Derived&>(*this);
            for (std::size_t i = 0; i != size(); ++i)
            {
                result = -result;
            }
            return result;
        }

        Derived& operator+() const
        {
            return *this;
        }

        constexpr const Scalar& operator[](const std::size_t index) const
        {
            return const_cast<const Derived&>(*this)[index];
        }
    };



    template <typename T>
    class Vector2 : public VectorBase<T, 2, Vector2<T>>
    {
    public:
        Vector2(const Scalar& x, const Scalar& y) :
            x(x), y(y)
        {
        }

        Vector2() : Vector2(static_cast<Scalar>(0.), static_cast<Scalar>(0.)) {}

        constexpr Scalar& operator[](const std::size_t index)
        {
            assert(index < size());
            return data[index];
        }

        union
        {
            Scalar data[size()];
            struct
            {
                Scalar x;
                Scalar y;
            };
        };
    };



    using Vector2i = Vector2<std::int32_t>;
    using Vector2u = Vector2<std::uint32_t>;
    using Vector2li = Vector2<std::int64_t>;
    using Vector2lu = Vector2<std::uint64_t>;
    using Vector2f = Vector2<float>;
    using Vector2d = Vector2<double>;
}
}



#undef VECTOR_VECTOR_ASSIGNMENT_OPERATOR_DEFINITION
#undef VECTOR_SCALAR_ASSIGNMENT_OPERATOR_DEFINITION
#undef VECTOR_BINARY_OPERATOR_DEFINITION
#undef VECTOR_VECTOR_BINARY_OPERATOR_DEFINITION
#undef VECTOR_SCALAR_BINARY_OPERATOR_DEFINITION
