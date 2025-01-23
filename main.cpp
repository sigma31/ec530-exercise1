#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

const double EARTH_RADIUS = 6371.0; // Earth's radius in kilometers

// Convert degrees to radians
double degreesToRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

// Calculate the Haversine distance between two points
double haversineDistance(double lat1, double lon1, double lat2, double lon2) {
    long double dLat = degreesToRadians(lat2 - lat1);
    long double dLon = degreesToRadians(lon2 - lon1);
    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(degreesToRadians(lat1)) * cos(degreesToRadians(lat2)) *
               sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return EARTH_RADIUS * c;
}

// Function to iterate through two vectors of GPS coordinates
vector<int> findClosestPoints(const vector<pair<double, double>>& array1,
                              const vector<pair<double, double>>& array2) {
    vector<int> closestIndices(array1.size());
    for (size_t i = 0; i < array1.size(); ++i) {
        double minDistance = numeric_limits<double>::max();
        int closestIndex = -1;
        for (size_t j = 0; j < array2.size(); ++j) {
            double distance = haversineDistance(array1[i].first, array1[i].second,
                                                array2[j].first, array2[j].second);
            if (distance < minDistance) {
                minDistance = distance;
                closestIndex = static_cast<int>(j);
            }
        }
        closestIndices[i] = closestIndex;
    }
    return closestIndices;
}

int main(){
    
    double lat1, lon1, lat2, lon2;

    cout << "Enter the latitude and longitude of the first point: ";
    cin >> lat1 >> lon1;

    cout << "Enter the latitude and longitude of the second point: ";
    cin >> lat2 >> lon2;

    double distance = haversineDistance(lat1, lon1, lat2, lon2);

    cout << "The Haversine distance between the two points is: " << distance << " kilometers." << endl;

    

    return 0;
}

