#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;

int n = 0, p = 0;
deque <int> polynomial_coefficients, polygon_lower;
map <int, int> polynomial_coordinates;

//Large Object Manipulation Functions
deque <pair <int, int>> build_coordinate_deque(deque <int> given) //Given x-coordinates, generate a deque of coordinate pairs
{
    deque <pair <int, int>> answer;
    for (int i : given) {
        answer.push_back({i, polynomial_coordinates[i]});
    }
    return answer;
}
deque <pair <int, int>> build_deque_from_map(map <int, int> given) //Given a map with x to y key value pairs, generate a deque of coordinate pairs
{
    deque <pair <int, int>> answer;
    for (pair <int, int> pair : given) {
        answer.push_back(pair);
    }
    return answer;
}
void output_given_polynomial() //Given all user inputs, display them into polynomial form
{
    cout << "\nf(x) = ";
    for (int i = n; i >= 0; --i) {
        cout << polynomial_coefficients[i];
        if (i != 0) {
            cout << "x^" << i << " + ";
        }
    }
    cout << '\n';
}
void output_coordinate_deque(deque <pair <int, int>> given, string title) //Given a deque of coordinates and a title, display as a list in the terminal
{
    cout << '\n' << title << ":\n";
    for (pair <int, int> i : given) {
        cout << '(' << i.first << ", " << i.second << ")\n";
    }
}

//Number Manipulation Functions
int nu_function(int prime, int coefficient) //Perform the nu function on a given prime and number
{
    if (coefficient == 0) {
        return INT_MAX;
    }
    else {
        coefficient = abs(coefficient);
    }
    int answer = 0;
    while (coefficient % prime == 0) {
        coefficient /= prime;
        answer++;
    }
    return answer;
}
int gcd_function(int a, int b) //Find the greatest common divisor between two given numbers
{
    return (b == 0) ? (abs(a)) : (gcd(b, a % b));
}
bool is_integer(string str) //Test if a given string is an integer
{
    if (str.empty()) return false;
    while (str.front() == ' ') {
        str = str.substr(1);
    }
    size_t start = 0;
    if (str[0] == '-' || str[0] == '+') {
        if (str.size() == 1) return false;
        start = 1;
    }
    for (size_t i = start; i < str.size(); ++i) {
        if (!std::isdigit(str[i])) {
            return false;
        }
    }
    return true;
}
bool is_prime(int number) //Test if a given integer is prime
{
    if (number < 2) {
        return false;
    }
    if (number == 2) {
        return true;
    }
    if (number % 2 == 0) { 
        return false;
    }
    for (int i = 3; (i*i) <= number; i += 2) {
        if (number % i == 0 ) {
            return false;
        }
    }
    return true;
}

//Overall Step Operation Functions
deque <int> find_global_minima() //Find the minima in the list of points
{
    deque <int> answer;
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
    deque <int> global_minima = find_global_minima();
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
deque <pair <int, int>> get_lattice_points(pair <int, int> left, pair <int, int> right) //Find list of lattice points between any two given lattice points, endpoint exclusive
{
    deque <pair <int, int>> lattice_points;
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
    deque <int> add_lattice;
    for (int i = 0; i < polygon_lower.size() - 1; ++i) {
        pair <int, int> l = {polygon_lower[i], polynomial_coordinates[polygon_lower[i]]};
        pair <int, int> r = {polygon_lower[i + 1], polynomial_coordinates[polygon_lower[i + 1]]};
        deque <pair <int, int>> toadd = get_lattice_points(l, r);
        for (pair <int, int> x : toadd) {
            add_lattice.push_back(x.first);
            polynomial_coordinates[x.first] = x.second;
        }
    }
    for (int x : add_lattice) {
        polygon_lower.push_back(x);
    }
    sort(polygon_lower.begin(), polygon_lower.end());
}
void create_SFML_plots(deque <pair <int, int>> points, string title, sf::Color pointColor) //Given a deque of coordinate pairs, a title, and a pen color, create a labeled coordinate plane plot using SFML in a new window
{
    const int width = 600, height = 600;
    const int padding = 50;
    const int scale = 50;
    sf::RenderWindow window(sf::VideoMode(width, height), title);
    int maxX = 0, maxY = 0;
    for (auto &pt : points) {
        maxX = max(maxX, pt.first);
        maxY = max(maxY, pt.second == INT_MAX ? 0 : pt.second);
    }
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::White);
        for (int x = 0; x <= maxX + 2; ++x) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(padding + x * scale, height - padding), sf::Color(200,200,200)),
                sf::Vertex(sf::Vector2f(padding + x * scale, padding), sf::Color(200,200,200))
            };
            window.draw(line, 2, sf::Lines);
        }
        for (int y = 0; y <= maxY + 2; ++y) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(padding, height - padding - y * scale), sf::Color(200,200,200)),
                sf::Vertex(sf::Vector2f(width - padding, height - padding - y * scale), sf::Color(200,200,200))
            };
            window.draw(line, 2, sf::Lines);
        }

        // Draw axes
        sf::Vertex xAxis[] = {
            sf::Vertex(sf::Vector2f(padding, height - padding), sf::Color::Black),
            sf::Vertex(sf::Vector2f(width - padding, height - padding), sf::Color::Black)
        };
        sf::Vertex yAxis[] = {
            sf::Vertex(sf::Vector2f(padding, height - padding), sf::Color::Black),
            sf::Vertex(sf::Vector2f(padding, padding), sf::Color::Black)
        };
        window.draw(xAxis, 2, sf::Lines);
        window.draw(yAxis, 2, sf::Lines);

        // Draw points and connect them
        if (!points.empty()) {
            sf::VertexArray lines(sf::LineStrip, points.size());
            int idx = 0;
            for (auto &pt : points) {
                float px = padding + pt.first * scale;
                float py = height - padding - (pt.second == INT_MAX ? 0 : pt.second) * scale;
                lines[idx].position = sf::Vector2f(px, py);
                lines[idx].color = pointColor;

                sf::CircleShape circle(5);
                circle.setFillColor(pointColor);
                circle.setOrigin(5, 5);
                circle.setPosition(px, py);
                window.draw(circle);
                idx++;
            }
            window.draw(lines);
        }

        window.display();
    }
}
void take_inputs() //Take user inputs, with failsafes against invalid inputes
{
    string temp;
    while (true) {
        cout << "Enter polygon target prime:\n";
        getline(cin, temp);
        if (is_integer(temp) && is_prime(stoi(temp))) {
            p = stoi(temp);
            break;
        }
        else { cout << "Invalid input! Attempt aborted.\n\n"; }
    }

    while (true) {
        cout << "Enter polynomial degree:\n";
        getline(cin, temp);
        if (is_integer(temp) && stoi(temp) >= 0) {
            n = stoi(temp);
            break;
        }
        else { cout << "Invalid input! Attempt aborted.\n\n"; }
    }
    polynomial_coefficients.resize(n + 1);

    for (int i = n; i >= 0; --i) {
        while (true) {
            cout << "Enter the coefficient for term x^" << i << " or 0 if term is not present:\n";
            getline(cin, temp);
            if (is_integer(temp)) {
                polynomial_coefficients[i] = stoi(temp);
                break;
            }
            else { cout << "Invalid input! Attempt aborted.\n\n"; }
        }
    }
}
// void quick_test_preinputs() //Useful for quick preinputting and testing
// {
//     p = , n = ;
//     polynomial_coefficients = {}; //Caveat: coefficient list is reversed, starting with constant term and ending with the highest power
// }

int main() {
    //Input:
    take_inputs();
    //quick_test_preinputs();

    //Construct polynomial:
    cout << "Complete Polynomial Expression Given:\n";
    output_given_polynomial();

    //Build polygon by coordinates:
    for (int i = n; i >= 0; --i) {
        polynomial_coordinates[n - i] = nu_function(p, polynomial_coefficients[i]);
    }
    deque <pair <int, int>> all_points = build_deque_from_map(polynomial_coordinates);
    output_coordinate_deque(all_points, "All Points");

    //Take the lower half convex hull:
    convexHullDescent();
    deque <pair <int, int>> convex_hull = build_coordinate_deque(polygon_lower);
    output_coordinate_deque(convex_hull, "Convex Hull");

    //Fill lattice points between convex hull points:
    fillLattice();
    deque <pair <int, int>> latticed_hull = build_coordinate_deque(polygon_lower);
    output_coordinate_deque(latticed_hull, "Latticed Hull");

    //Output polygon results:
    cout << "\nNewton Polygon result numbers:\n";
    for (int i = 0; i < latticed_hull.size() - 1; ++i) {
        cout << latticed_hull[i + 1].first - latticed_hull[i].first << ' ';
    }

    //Create graphs and detach for window persistency
    thread t1(create_SFML_plots, all_points, "All Points", sf::Color::Red);
    thread t2(create_SFML_plots, convex_hull, "Convex Hull", sf::Color::Blue);
    thread t3(create_SFML_plots, latticed_hull, "Latticed Hull", sf::Color::Green);
    t1.join();
    t2.join();
    t3.join();
    while (true) {}
    return 0;
}