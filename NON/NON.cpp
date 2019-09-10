#include "judge.h"

class Obj {
public:
    int*fields_prt;
    int size;
    int min_start;
    int max_start;
    Obj* prev;
    Obj* next;

    void setNewBegin(int beg) {
        if (beg > min_start) {
            min_start = beg;
            check();
        }
    }

    void setNewEnd(int end) {
        if (max_start + size > end) {
            max_start = end - size;
            check();
        }
    }

    void check() {
        int cnt = 0;
        //int idx = min_start;
        for (int i = min_start; i <= max_start + size; ++i) {
            if (fields_prt[i] == INON::COLOR_WHITE) {
                cnt = 0;
                continue;
            }
            cnt++;
            if (cnt == size) {
                if (i != min_start + size) {
                    min_start = i - size;
                }
                break;
            }
        }
        cnt = 0;
        for (int i = max_start + size; i >= min_start; --i) {
            if (fields_prt[i] == INON::COLOR_WHITE) {
                cnt = 0;
                continue;
            }
            cnt++;
            if (cnt == size) {
                if (i != max_start - size) {
                    min_start = i - size;
                }
                break;
            }
        }
    }
};

void Obj::check() {
    int counter = 0;
    for (int i = begin; i<=end; ++i) {
        if (fields_prt[i] == INON::COLOR_WHITE) {
            counter = 0;
            continue;
        }
        counter++;
        if (counter == size) {
            if (i - size != begin) {
                prev->setNewEnd(i-size -1);
                begin = i - size;
            }
        }
    }
}


class NON : public INON {
public:
    INON *createLine(int n, int k, int *data) {
        auto obj = new NON();
        obj->init(n,k,data);
        return obj;
    }
	int getColor(int) { return INON::COLOR_UNKNOWN; }
	void setColor(int, int) {  }

    NON();

    ~NON() {delete [] objects; delete [] fields;}

    void init(int n, int k, int *data);

    int fields_count;
    int obj_count;
    Obj* objects = nullptr;
    int *fields = nullptr;

};

void NON::init(int n, int k, int *data) {
    fields_count = n;
    fields = new int[n];
    for (int i = 0; i < n; ++i) {
        fields[i] = INON::COLOR_UNKNOWN;
    }

    obj_count = k;
    objects = new Obj[k];

    int beginnings = 0;

    for (int i = 0; i < k; i++) {
        objects[i].size = data[i];
        objects[i].begin = beginnings;
        beginnings += data[i] + 1;

        objects[i].fields_prt = fields;

        if (i < k-1 ) {
            objects[i].next = &objects[i+1];
        }

        if (i > 0) {
            objects[i].prev = &objects[i-1];
        }
    }

    int endings = n-1;

    for (int i = k-1; i >=0; i--) {
        objects[i].end = endings;
        endings -= objects[i].size - 1;
    }
}

NON factory;
int main() {
	Judge::run(&factory);
	return 0;
}

