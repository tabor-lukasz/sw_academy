#include "judge.h"

//#include <iostream>
//using namespace std;


struct block {
    int w,h,d;

//    void print(int n = 0, string ss ="") {
//        for (int i = 0; i <n ; ++i) {
//            cout << " ";
//        }
//        cout << ss;
//        cout << w << " "  << d << " "  << h << endl;
//    }
};

class KLO : public IKLO {
public:
    int maxTowerHeight(int n, int *a, int *b, int *c) {
        max = 0;
        blocksCnt = n;
        for (int i = 0; i < blocksCnt; ++i) {
            blocks[i] = {a[i],b[i],c[i]};
        }

        permutation(0,n-1);

//        cout << counter << endl;

        return max;
    }

    int permutation(int start, int end)
    {
        if(start==end) {

//            counter++;

//            for (int i = 0; i < blocksCnt; i++) {
//                blocks[i].print();
//            }
//            cout << endl;

            int current;
            int maxCount = 0;
            for (int i = 0; i < 3; i++ ){
                block b1 = rotate(blocks[0],i);
//                b1.print();
                int count = 1;
                current = addBlock(b1.h,b1,1,count);
                if (current > this->max) {
                    this->max = current;
                }

                if (maxCount < count) {
                    maxCount = count;
                }

//                cout << "\t" << count << " " << current << " " << maxCount  << " " << this->max << endl << endl;
            }
            return maxCount;
        }

        auto maxCount = 1;
        for(int i=start;i<=end;i++)
        {
            swap(blocks[i], blocks[start]);
            maxCount = permutation(start+1, end);
            swap(blocks[i], blocks[start]);
            if (maxCount < start ) {
                return maxCount;
            }
        }
        return maxCount;
    }

    int addBlock(int currHeigh, block currentBlock, int newBlockIdx,  int& currCnt) {
        int max = currHeigh;
        int maxCurrCnt = currCnt;
        if (newBlockIdx < blocksCnt) {
            for (int i = 0; i < 3; ++i) {
                block newBlock = rotate(blocks[newBlockIdx],i);
                int currCntCpy = currCnt;
                if (check(currentBlock,newBlock)) {
                    currCntCpy++;
                    int possibleHeigh = addBlock(currHeigh+newBlock.h,newBlock,newBlockIdx+1,currCntCpy);
                    if(max < possibleHeigh) {
                        max = possibleHeigh;
                    }
                    if (currCntCpy > maxCurrCnt) {
                        maxCurrCnt = currCntCpy;
                    }
//                    newBlock.print(newBlockIdx);
                } else {
//                    newBlock.print(newBlockIdx,"x");
                }
            }
        }

        currCnt = maxCurrCnt;

        return max;
    }

    inline static void swap(block& a, block& b)
    {
        auto temp = a;
        a = b;
        b = temp;
    }

    inline static int check(const block& b1, const block& b2) {
        if ((b1.d > b2.d && b1.w > b2.w) || (b1.d > b2.w && b1.w > b2.d)) {
            return true;
        }
        return false;
    }

    inline static block rotate(block b, int orientation) {
        switch (orientation) {
        case 1: {
            int tmp = b.d;
            b.d = b.h;
            b.h = b.w;
            b.w = tmp;
            break;
        }
        case 2: {
            int tmp = b.d;
            b.d = b.w;
            b.w = b.h;
            b.h = tmp;
            break;
        }
        }
        return b;
    }

//    int counter;

    int blocksCnt;
    block blocks[7];
    int max = 0;
};


KLO sol;
int main() {
    Judge::run(&sol);
    return 0;
}
