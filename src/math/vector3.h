/*
    This file is part of Elixir, an open-source cross platform physically
    based renderer.

    Copyright (c) 2019 Samuel Van Allen - All rights reserved.

    Elixir is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "math/mathutils.h"

exrBEGIN_NAMESPACE

template <class T>
class Vector3
{
public:
    Vector3<T>() : x(0), y(0), z(0) {}
    Vector3<T>(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
    Vector3<T>(T t) : x(t), y(t), z(t) {}
    Vector3<T>(const Vector3<T>& copy) : x(copy.x), y(copy.y), z(copy.z) {}
    Vector3<T>(const T* const d) : x(d[0]), y(d[1]), z(d[2]) {}

    inline const Vector3<T>& operator+() const { return *this; }
    inline Vector3<T> operator-() const { return Vector3<T>(-x, -y, -z); }
    inline void operator=(const Vector3<T>& v) { x = v.x; y = v.y; z = v.z; }
    inline T operator[](int i) const { return m_Data[i]; }
    inline T& operator[](int i) { return m_Data[i]; }

    inline Vector3<T>& operator+=(const Vector3<T>& v) { x += v.x; y += v.y; z += v.z; return *this; }
    inline Vector3<T>& operator-=(const Vector3<T>& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
    inline Vector3<T>& operator*=(const Vector3<T>& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
    inline Vector3<T>& operator/=(const Vector3<T>& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }
    inline Vector3<T>& operator*=(const float t) { x *= t; y *= t; z *= t; return *this; }
    inline Vector3<T>& operator/=(const float t) { x /= t; y /= t; z /= t; return *this; }
    inline bool operator==(const Vector3<T>& v) { return (x == v.x) && (y == v.y) && (z == v.z); }

public:
    inline explicit operator Point3<T>() const { return Point3<T>(x, y, z); }

public:
    inline const float MagnitudeSquared() const { return x * x + y * y + z * z; }
    inline const float Magnitude() const { return sqrt(MagnitudeSquared()); }
    inline Vector3<T> Normalized() const { return MagnitudeSquared() == 0 ? *this : *this / Magnitude(); };

public:
    static Vector3<T> Zero() { return Vector3<T>(0.0f); }
    static Vector3<T> Up() { return Vector3<T>(0.0f, 1.0f, 0.0f); }
    static Vector3<T> Right() { return Vector3<T>(1.0f, 0.0f, 0.0f); }
    static Vector3<T> Forward() { return Vector3<T>(0.0f, 0.0f, 1.0f); }

public:
    union
    {
        struct { T x, y, z; };
        struct { T r, g, b; };
        struct { T m_Data[3]; };
    };
};

template<class T>
inline Vector3<T> operator+(const Vector3<T>& v1, const Vector3<T>& v2)
{
    return Vector3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

template<class T>
inline Vector3<T> operator-(const Vector3<T>& v1, const Vector3<T>& v2)
{
    return Vector3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

template<class T>
inline Vector3<T> operator*(const Vector3<T>& v1, const Vector3<T>& v2)
{
    return Vector3<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

template<class T>
inline Vector3<T> operator/(const Vector3<T>& v1, const Vector3<T>& v2)
{
    return Vector3<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

template<class T>
inline Vector3<T> operator*(const Vector3<T>& v, float t)
{
    return Vector3<T>(v.x * t, v.y * t, v.z * t);
}

template<class T>
inline Vector3<T> operator*(float t, const Vector3<T>& v)
{
    return Vector3<T>(v.x * t, v.y * t, v.z * t);
}

template<class T>
inline Vector3<T> operator/(const Vector3<T>& v, float t)
{
    return Vector3<T>(v.x / t, v.y / t, v.z / t);
}

template<class T>
inline float Dot(const Vector3<T>& v1, const Vector3<T>& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template<class T>
inline float AbsDot(const Vector3<T>& v1, const Vector3<T>& v2)
{
    return abs(Dot(v1, v2));
}

template<class T>
inline Vector3<T> Cross(const Vector3<T>& v1, const Vector3<T>& v2)
{
    return Vector3<T>((v1.y * v2.z - v1.z * v2.y),
                     -(v1.x * v2.z - v1.z * v2.x),
                      (v1.x * v2.y - v1.y * v2.x));
}

template<class T>
inline float CosAngle(const Vector3<T>& v1, const Vector3<T>& v2)
{
    return (Dot(v1, v2) / (v1.Magnitude() * v2.Magnitude()));
}

template<class T>
inline float Angle(const Vector3<T>& v1, const Vector3<T>& v2)
{
    return acos(CosAngle(v1, v2));
}

template<class T>
inline Vector3<T> Reflect(const Vector3<T>& v, const Vector3<T>& n)
{
    return v - 2 * Dot(v, n) * n;
}

template<class T>
inline bool Refract(const Vector3<T>& v, const Vector3<T>& n, float ni_over_nt, Vector3<T>& refracted)
{
    Vector3<T> vNorm = v.Normalized();
    float dt = Dot(vNorm, n);
    float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);

    if (discriminant > 0)
    {
        refracted = ni_over_nt * (vNorm - n * dt) - n * sqrt(discriminant);
        return true;
    }

    return false;
}

template<class T>
inline void CoordinateSystem(const Vector3<T>& v1, Vector3<T>* v2, Vector3<T>* v3)
{
    if (abs(v1.x) > abs(v1.y))
        *v2 = Vector3<T>(-v1.z, 0, v1.x) / sqrt(v1.x * v1.x + v1.z * v1.z);
    else
        *v2 = Vector3<T>(0, v1.z, -v1.y) / sqrt(v1.y * v1.y + v1.z * v1.z);

    *v3 = Cross(v1, *v2);
}

exrEND_NAMESPACE
