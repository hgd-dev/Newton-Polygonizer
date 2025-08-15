#pragma once
#include <deque>
#include <map>
#include <string>

std::deque<std::pair<int, int>> build_coordinate_deque(std::deque<int> given);
std::deque<std::pair<int, int>> build_deque_from_map(std::map<int, int> given);
void output_coordinate_deque(std::deque<std::pair<int, int>> given, std::string title);

std::deque<int> find_global_minima();
void convexHullDescent();
std::deque<std::pair<int, int>> get_lattice_points(std::pair<int, int> left, std::pair<int, int> right);
void fillLattice();
