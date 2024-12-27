#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

namespace Utils {
    sf::VertexArray CreateArc(sf::Vector2f center, float radius, float thickness, float percentage, int pointCount, sf::Color color = sf::Color::Cyan) {
        sf::VertexArray arc(sf::TrianglesStrip);
        float startAngle = -90.0f; // Start from top
        float sweepAngle = 360.0f * percentage; // Calculate angle range

        for (int i = 0; i <= pointCount; ++i) {
            float angle = startAngle + (sweepAngle * i / pointCount);
            float rad = angle * (3.14159265359f / 180.0f); // Convert to radians

            // Outer point
            sf::Vector2f outerPoint = center + sf::Vector2f(
                std::cos(rad) * radius,
                std::sin(rad) * radius
            );

            // Inner point (thickness applied)
            sf::Vector2f innerPoint = center + sf::Vector2f(
                std::cos(rad) * (radius - thickness),
                std::sin(rad) * (radius - thickness)
            );

            arc.append(sf::Vertex(outerPoint, color));
            arc.append(sf::Vertex(innerPoint, color));
        }

        return arc;
    }
}

#endif // CIRCLE_HPP