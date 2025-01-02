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

    // Function to draw a dotted line
    void drawDottedCircles(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end, float dotSpacing, float dotRadius) {
        sf::Vector2f direction = end - start;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        // Normalize direction vector
        direction /= length;

        // Place dots along the line
        for (float i = 0; i < length; i += dotSpacing) {
            sf::Vector2f position = start + direction * i;
            sf::CircleShape dot(dotRadius);
            dot.setFillColor(sf::Color::White);
            dot.setPosition(position - sf::Vector2f(dotRadius, dotRadius)); // Center the dot

            window.draw(dot);
        }
    }

    void drawDottedLine(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end, float dotSpacing, sf::Color color) {
        sf::Vector2f direction = end - start;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        direction /= length;

        sf::VertexArray dots(sf::Points);

        for (float i = 0; i < length; i += dotSpacing) {
            sf::Vector2f position = start + direction * i;
            dots.append(sf::Vertex(position, color));
        }

        window.draw(dots);
    }

    void drawGradientDottedLine(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end, float dotSpacing) {
        sf::Vector2f direction = end - start;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length;

        for (float i = 0; i < length; i += dotSpacing) {
            sf::Vector2f position = start + direction * i;
            sf::Color color = sf::Color(255, 255, 255,  255 * (i/ length)); // Gradient effect

            sf::CircleShape dot(3.f);
            dot.setFillColor(color);
            dot.setPosition(position - sf::Vector2f(3.f, 3.f));

            window.draw(dot);
        }
    }



}

#endif // CIRCLE_HPP