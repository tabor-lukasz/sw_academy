//void printState() {
//    for (int i = 5;  i >= 0; --i) {
//        for (int j = 5; j >= 0; --j) {
//            std::cout << board[i][j];
//        }

//        std::cout <<" ";
//        for (int j = 5; j >= 0; --j) {
//            std::cout << forbidden[i][j];
//        }

//        if (i < 4) {
//            std::cout <<" ";
//            for (int j = 3; j >= 0; --j) {
//                std::cout << pattern[i][j];
//            }
//        }

//        std::cout << std::endl;
//    }
//    std::cout << std::endl;
//}

//#include "skl_answer3.cpp"
//#include <iostream>
//#include <ctime>

//Skleroza solution;
//int main() {
//    // You can initialize Your data structures here

//    // But the last instructions should not been modified

//    auto cases = {54,58,63,68,73,79,85,91,98,105,113,121,130,140,150,161,173,186,200,215,231,248,266,285,305,327,350,375,402,431,462,495,530,568,608,651,697,746,799,855,915,980,1049,1123,1202,1287,1378,1475,1579,1690,1809,1936,2072,2218,2374,2541,2719,2910,3114,3332,3566,3816,4084,4370,4676,5004,5355,5730,6132,6562,7022,7514,8040,8603,9206,9851,10541,11279,12069,12914,13819,14787,15823,16931,18117,19386,20744,22197,23751,25414,27193,29097,31134,33314,35647,38143,40814,43671,46728,49999};
//    double sum = 0.0;
//    double max = 0.0;
//    for (auto cc : cases) {
//        if (cc == 85) {
//            int a = 9;
//            a++;
//        }
//        Judge::tcc = cc;
//        Judge::seeed = rand();
//        auto now = clock();
//        Judge::run(&solution);
//        auto end = clock();
//        auto diff = 1.0* (end - now) / CLOCKS_PER_SEC;
//        if (max < diff)
//            max = diff;
//        sum += diff;
////        cout << 1.0* (end - now) / CLOCKS_PER_SEC << "\t" << Judge::tcc << "\t" << Judge::seeed << endl;
//    }
////    cout << "Total: " << sum  << "\tMax: " << max << "\tAvg: " << sum / cases.size() << endl;

//    return 0;
//}
