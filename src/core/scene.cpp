#include "scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
   for (std::vector<Geometry*>::iterator it = m_Primitives.begin() ; it != m_Primitives.end(); ++it)
   {
       delete (*it);
   } 

   m_Primitives.clear();
}

void Scene::AddPrimitive(Geometry* geometry)
{
    m_Primitives.push_back(geometry);
}

bool Scene::RaytraceScene(const Ray& viewRay, GeometryHitInfo& hitInfo) const
{
    GeometryHitInfo tempHitInfo;

    bool hitAnything = false;

    float nearestDist = viewRay.m_tMax;

    for (int i = 0; i < m_Primitives.size(); i++)
    {
        if (m_Primitives[i]->Hit(viewRay, tempHitInfo) && tempHitInfo.t < nearestDist)
        {
            hitAnything = true;
            nearestDist = tempHitInfo.t;
            hitInfo = tempHitInfo;
        }
    }

    return hitAnything;
}