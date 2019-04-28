#include <iostream>
#include <string>

void scan(){
    int nl = 24, ne = 10;
    float el[10];

    for(int i=0; i<nl; i++){
        std::cin >> el[0] >> el[1] >> el[2] >> el[3] >> el[4] >> el[5] >> el[6] >> el[7] >> el[8] >> el[9];
        // printf("%s:\n", n);
        printf("glm::vec3(%.3ff,%.3ff,%.3ff)\n", el[0],el[1],el[2]);
        printf("glm::vec3(%.3ff,%.3ff,%.3ff)\n", el[3],el[4],el[5]);
        printf("glm::vec3(%.3ff,%.3ff,%.3ff)\n%.3ff\n\n", el[6],el[7],el[8], el[9]);
        /*for(int j=0; j<ne; j++){
            std::cin >> d;
            printf("%.8lf ", d);        
        }
        std::cout << "\n";*/
    }
}

int main(int argc, char const *argv[]){
    scan();
    return 0;
}