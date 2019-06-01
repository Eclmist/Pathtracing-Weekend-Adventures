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

#include "sphere.h"

exrBEGIN_NAMESPACE

bool Sphere::Intersect(const Ray& ray, exrFloat tMin, exrFloat tMax, Interaction& hit) const
{
    Ray localRay = m_Transform.GetInverseMatrix() * ray;
    exrVector3 r0 = localRay.m_Origin - exrPoint::Zero();
    exrFloat a = Dot(localRay.m_Direction, localRay.m_Direction);
    exrFloat b = 2 * Dot(r0, localRay.m_Direction);
    exrFloat c = Dot(r0, r0) - (m_Radius * m_Radius);

    // solve quadratic equation to find t
    exrFloat t0, t1;
    if (!exrQuadratic(a, b, c, &t0, &t1))
        return false;

    if (t0 > tMax || t1 <= tMin)
        return false;

    if (t0 <= tMin)
        t0 = t1;

    hit.m_Time = t0;
    hit.m_Point = m_Transform.GetMatrix() * localRay(t0);
    hit.m_Normal = static_cast<exrVector3>(localRay(t0)) / m_Radius;
    hit.m_Material = m_Material.get();

    return true;
}
bool Sphere::ComputeBoundingVolume()
{
    exrPoint min = m_Transform.GetMatrix() * exrPoint(-m_Radius);
    exrPoint max = m_Transform.GetMatrix() * exrPoint(m_Radius);
    m_BoundingVolume = AABB(min, max);
    return true;
}

exrEND_NAMESPACE