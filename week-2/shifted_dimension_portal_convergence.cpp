#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

//Struct of 2D dimension
typedef struct {
    float x1, y1, x2, y2;
} Dimension;

float findMax(float a, float b) {
    return (a > b) ? a : b;
}

float findMin(float a, float b) {
    return (a < b) ? a : b;
}

//Check if there is any Overlap. If there is, find the biggest Overlap.
//Or else, return 0.0
float findOverlap(std::vector<Dimension> dms) {
    float max_area = 0.0;

    for(int i = 0; i < dms.size(); i++) {
        for(int j = 0; j < dms.size(); j++) {
            if(j == i) {
                continue;
            }

            // Check if there is any overlap
            float overlap_x_min = findMax(dms[i].x1, dms[j].x1);
            float overlap_x_max = findMin(dms[i].x2, dms[j].x2);
            float overlap_y_min = findMax(dms[i].y1, dms[j].y1);
            float overlap_y_max = findMin(dms[i].y2, dms[j].y2);

            // Check if the rectangles actually overlap
            if((overlap_x_max - overlap_x_min) > 1e-9 && (overlap_y_max - overlap_y_min) > 1e-9) {
                // Calculate overlap area
                float horizontal_side = overlap_x_max - overlap_x_min;
                float vertical_side = overlap_y_max - overlap_y_min;
                float area = horizontal_side * vertical_side;
                if(area > max_area) {
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
        if(tmp_dimen.x1 - tmp_dimen.x2 > 1e-9) {
            float tmp = tmp_dimen.x1;
            tmp_dimen.x1 = tmp_dimen.x2;
            tmp_dimen.x2 = tmp;
        }
        if(tmp_dimen.y1 - tmp_dimen.y2 > 1e-9) {
            float tmp = tmp_dimen.y1;
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
    std::cout << std::fixed << std::setprecision(6) << findOverlap(dimensions) << std::endl;
}