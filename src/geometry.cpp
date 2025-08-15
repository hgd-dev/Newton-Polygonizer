#include "include/config.h"
#include "include/utility.h"
#include "include/geometry.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>

std::deque <std::pair <int, int>> build_coordinate_deque(std::deque <int> given) //Given x-coordinates, generate a deque of coordinate pairs
{
    std::deque <std::pair <int, int>> answer;
    for (int i : given) {
        answer.push_back({i, polynomial_coordinates[i]});
    }
    return answer;
}
std::deque <std::pair <int, int>> build_deque_from_map(std::map <int, int> given) //Given a map with x to y key value pairs, generate a deque of coordinate pairs
{
    std::deque <std::pair <int, int>> answer;
    for (std::pair <int, int> pair : given) {
        answer.push_back(pair);
    }
    return answer;
}
void output_coordinate_deque(std::deque <std::pair <int, int>> given, std::string title) //Given a deque of coordinates and a title, display as a list in the terminal
{
    std::cout << '\n' << title << ":\n";
    for (std::pair <int, int> i : given) {
        std::cout << '(' << i.first << ", " << i.second << ")\n";
    }
}
std::deque <int> find_global_minima() //Find the minima in the list of points
{
    std::deque <int> answer;
    int curMin = INT_MAX;
    for (int i = 0; i <= n; ++i) {
        if (polynomial_coordinates[i] < curMin) {
            curMin = polynomial_coordinates[i];
            answer.clear();
            answer.push_back(i);
        }
        else if (polynomial_coordinates[i] == curMin) {
            answer.push_back(i);
        }
    }
    return answer;
}
void convexHullDescent() //Perform double-sided descent across the list of points to global minima
{
    std::deque <int> global_minima = find_global_minima();
    output_coordinate_deque(build_coordinate_deque(global_minima), "Global Minimums");
    int left = global_minima.front(), right = global_minima.back();
    global_minima.push_back(0);
    int previous_height = polynomial_coordinates[0];
    for (int i = 1; i < left; ++i) {
        if (polynomial_coordinates[i] < previous_height) {
            global_minima.push_back(i);
            previous_height = polynomial_coordinates[i];
        }
    }
    global_minima.push_back(n);
    previous_height = polynomial_coordinates[n];
    for (int i = n - 1; i > right; --i) {
        if (polynomial_coordinates[i] < previous_height) {
            global_minima.push_back(i);
            previous_height = polynomial_coordinates[i];
        }
    }
    polygon_lower = global_minima;
    sort(polygon_lower.begin(), polygon_lower.end());
}
std::deque <std::pair <int, int>> get_lattice_points(std::pair <int, int> left, std::pair <int, int> right) //Find list of lattice points between any two given lattice points, endpoint exclusive
{
    std::deque <std::pair <int, int>> lattice_points;
    if (abs(left.first - right.first) == 1 || abs(left.second - right.second) == 1) {
        return lattice_points;
    }
    int dx = right.first - left.first, dy = right.second - left.second;
    int steps = gcd_function(abs(dx), abs(dy));
    if (steps <= 1) {
        return lattice_points;
    }
    int stepX = dx / steps, stepY = dy / steps;
    for (int i = 1; i < steps; ++i) {
        lattice_points.emplace_back(left.first + i * stepX, left.second + i * stepY);
    }
    return lattice_points;
}
void fillLattice() //Add all lattice points between list of coordinates in the graph
{
    std::deque <int> add_lattice;
    for (int i = 0; i < polygon_lower.size() - 1; ++i) {
        std::pair <int, int> l = {polygon_lower[i], polynomial_coordinates[polygon_lower[i]]};
        std::pair <int, int> r = {polygon_lower[i + 1], polynomial_coordinates[polygon_lower[i + 1]]};
        std::deque <std::pair <int, int>> toadd = get_lattice_points(l, r);
        for (std::pair <int, int> x : toadd) {
            add_lattice.push_back(x.first);
            polynomial_coordinates[x.first] = x.second;
        }
    }
    for (int x : add_lattice) {
        polygon_lower.push_back(x);
    }
    sort(polygon_lower.begin(), polygon_lower.end());
}

