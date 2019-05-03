#include "sphere.h"

bool Sphere::Hit(const Ray & ray, float tMin, float tMax, GeometryHitInfo & hit) const
{
    Vector3f oc = ray.m_Origin - m_Center;
    float a = Dot(ray.m_Direction, ray.m_Direction);
    float b = Dot(oc, ray.m_Direction);
    float c = Dot(oc, oc) - m_Radius * m_Radius;
    float discriminant = b * b - a * c;

    // solve quadratic equation to find t
    if (discriminant > 0)
    {
        float hitPoint1 = (-b - sqrt(b * b - a * c)) / a;
        float hitPoint2 = (-b + sqrt(b * b - a * c)) / a;

        if (hitPoint1 <= tMax && hitPoint1 >= tMin)
        {
            hit.t = hitPoint1;
            hit.point = ray(hit.t);
            hit.normal = (hit.point - m_Center) / m_Radius;
            hit.material = m_Material;
            return true;
        }

        if (hitPoint2 <= tMax && hitPoint2 >= tMin)
        {
            hit.t = hitPoint2;
            hit.point = ray(hit.t);
            hit.normal = (hit.point - m_Center) / m_Radius;
            hit.material = m_Material;
            return true;
        }
    }

    // no real value, did not intersect sphere
    return false;
}
