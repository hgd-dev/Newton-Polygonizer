#include "include/config.h"
#include "include/utility.h"
#include "include/polynomial.h"
#include "include/geometry.h"
#include "include/graphics.h"
#include <thread>
#include <iostream>

int main() {
    take_inputs();
    output_given_polynomial();

    for (int i = n; i >= 0; --i) {
        polynomial_coordinates[n - i] = nu_function(p, polynomial_coefficients[i]);
    }

    auto all_points = build_deque_from_map(polynomial_coordinates);
    output_coordinate_deque(all_points, "All Points");

    convexHullDescent();
    auto convex_hull = build_coordinate_deque(polygon_lower);
    output_coordinate_deque(convex_hull, "Convex Hull");

    fillLattice();
    auto latticed_hull = build_coordinate_deque(polygon_lower);
    output_coordinate_deque(latticed_hull, "Latticed Hull");

    std::cout << "\nNewton Polygon result numbers:\n";
    for (size_t i = 0; i < latticed_hull.size() - 1; ++i) {
        std::cout << latticed_hull[i + 1].first - latticed_hull[i].first << ' ';
    }

    std::thread t1(create_SFML_plots, all_points, "All Points", sf::Color::Red);
    std::thread t2(create_SFML_plots, convex_hull, "Convex Hull", sf::Color::Blue);
    std::thread t3(create_SFML_plots, latticed_hull, "Latticed Hull", sf::Color::Green);

    t1.join();
    t2.join();
    t3.join();
    while (true) {}
}
