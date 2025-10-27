#include "CollisionSystem.hpp"
#include <iostream> 

namespace CollisionSystem {

    void update(entt::registry& reg, entt::dispatcher& dispatcher) {
        auto view = reg.view<Position, Collider>();
        for (auto itA = view.begin(); itA != view.end(); itA++) {
            auto entityA = *itA;
            auto& posA = view.get<Position>(entityA);
            auto& colA = view.get<Collider>(entityA);

            for (auto itB = std::next(itA); itB != view.end(); itB++) {
                auto entityB = *itB;
                auto& posB = view.get<Position>(entityB);
                auto& colB = view.get<Collider>(entityB);

                if (checkAABB(posA.x, posA.y, colA.width, colA.height, 
                              posB.x, posB.y, colB.width, colB.height)) {
                    
                    // getting vector normalized
                    float diffX = posA.x - posB.x;
                    float diffY = posA.y - posB.y;
                    float distance = std::hypot(diffX, diffY);

                    float normX = 0.f;
                    float normY = 0.f;
                    
                    if (distance > 0.0001f) {
                         normX = diffX / distance;
                         normY = diffY / distance;
                    }
                    CollisionSystem::Vector2f normal = {normX, normY};
                                
                    dispatcher.trigger(CollisionEvent{ &reg, entityA, entityB, normal });
                    

                }
            }
        }
    }
}