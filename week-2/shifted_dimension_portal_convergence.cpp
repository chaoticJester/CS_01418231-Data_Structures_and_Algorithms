#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

//Struct of 2D dimension
typedef struct {
    double x1, y1, x2, y2;
} Dimension;

double findMax(double a, double b) {
    return (a - b > 1e-9) ? a : b;
}

double findMin(double a, double b) {
    return (b - a > 1e-9) ? a : b;
}

//Check if there is any Overlap. If there is, find the biggest Overlap.
//Or else, return 0.0
double findOverlap(std::vector<Dimension> dms, int num) {
    double max_area = 0.0;
    for(int i = 0; i < num; i++) {
        for(int j = i + 1; j < num; j++) {

            // Check if there is any overlap
            double overlap_x_min = findMax(dms[i].x1, dms[j].x1);
            double overlap_x_max = findMin(dms[i].x2, dms[j].x2);
            double overlap_y_min = findMax(dms[i].y1, dms[j].y1);
            double overlap_y_max = findMin(dms[i].y2, dms[j].y2);

            // Check if the rectangles actually overlap
            if((overlap_x_max - overlap_x_min) > 1e-9 && (overlap_y_max - overlap_y_min) > 1e-9) {
                // Calculate overlap area
                double horizontal_side = overlap_x_max - overlap_x_min;
                double vertical_side = overlap_y_max - overlap_y_min;
                double area = horizontal_side * vertical_side;
                // std::cout << "Overlap area: " << area << std::endl;
                if(area - max_area > 1e-9) {
                    max_area = area;
                }
            }
        }
    }

    return max_area;
}

int main() {
    //Input -------------------------------
    int num_dimension;
    std::cin >> num_dimension;

    std::vector<Dimension> dimensions;
    for(int i = 0; i < num_dimension; i++) {
        Dimension tmp_dimen;
        std::cin >> tmp_dimen.x1 >> tmp_dimen.y1 >> tmp_dimen.x2 >> tmp_dimen.y2;
        if(tmp_dimen.x1 - tmp_dimen.x2 > 1e-9 || tmp_dimen.x1 - tmp_dimen.x2 > 0.0) {
            double tmp = tmp_dimen.x1;
            tmp_dimen.x1 = tmp_dimen.x2;
            tmp_dimen.x2 = tmp;
        }
        if(tmp_dimen.y1 - tmp_dimen.y2 > 1e-9 || tmp_dimen.y1 - tmp_dimen.y2 > 0.0) {
            double tmp = tmp_dimen.y1;
            tmp_dimen.y1 = tmp_dimen.y2;
            tmp_dimen.y2 = tmp;
        }
        dimensions.push_back(tmp_dimen);
    }
    //--------------------------------------

    //Input test
    // for(int i = 0; i < num_dimension; i++) {
    //     std::cout << dimensions[i].x1 << " " << dimensions[i].y1 << " ";
    //     std::cout << dimensions[i].x2 << " " << dimensions[i].y2 << std::endl;
    // }

    //Output
    std::cout << std::fixed << std::setprecision(6) << findOverlap(dimensions, num_dimension) << std::endl;
}