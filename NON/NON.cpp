#include "judge.h"

//#include <iostream>

class NON;

class Obj {
public:
    NON *parent = nullptr;
    int size;
    int min_start;
    int max_end;
    Obj* prev = nullptr;
    Obj* next = nullptr;
    bool solved = false;

    //    void setNewBegin(int beg) {
    //        if (beg > min_start) {
    //            min_start = beg;
    //            check();
    //        }
    //    }

    //    void setNewEnd(int end) {
    //        if (max_start + size > end) {
    //            max_start = end - size;
    //            check();
    //        }
    //    }

    bool checkMiddle();
    bool checkSolved();
    bool checkMaxEnd();
    bool checkMinStart();
    bool anchorAround();
    bool checkOrphants();
    bool checkMaxRemaining();

    void notifyMaxEndChanged(int new_end);
    void notifyMinStartChanged(int new_start);
};

class NON : public INON {
public:
    INON *createLine(int n, int k, int *data) {
        auto obj = new NON();
        obj->init(n,k,data);
        return obj;
    }
    int getColor(int idx);
    void setColor(int idx, int color);

    ~NON() {delete [] objects; delete [] fields; delete fields_counters;}

    void init(int n, int k, int *data);

    int fields_count;
    int obj_count;
    Obj* objects = nullptr;
    int *fields = nullptr;
    int *fields_counters = nullptr;

//    void print();
    bool recalcCounters();
    bool checkMaxRemaining();
    bool checkOrdered();
};

//void NON::print() {
//    for (int i = 0; i < fields_count; i++) {
//        switch (fields[i]) {
//        case INON::COLOR_BLACK:
//            std::cout << "#";
//            break;
//        case INON::COLOR_WHITE:
//            std::cout<< ".";
//            break;
//        case INON::COLOR_UNKNOWN:
//            std::cout<<"?";
//        }
//    }
//    std::cout << "  ";
//    for(int i = 0; i < obj_count; i++) {
//        std::cout << objects[i].size;
//        std::cout << " ";
//        std::cout << objects[i].min_start;
//        std::cout << " ";
//        std::cout << objects[i].max_end;
//        std::cout << "  ";
//    }
//    std::cout << std::endl;
//}

bool Obj::checkMiddle() {
    bool changed = false;
    if (max_end - min_start < 2*size) {
        for(int i = max_end - size + 1; i < min_start + size; ++i) {
            if (parent->fields[i] != INON::COLOR_BLACK) {
                changed = true;
            }
            parent->fields[i] = INON::COLOR_BLACK;
        }
    }
//    if (changed)
//        parent->print();
    return changed;
}

bool Obj::checkSolved() {
    bool changed = false;
    if (max_end-min_start == size -1) {
        solved = true;
        if (max_end < parent->fields_count -1) {
            if (parent->fields[max_end +1] != INON::COLOR_WHITE) {
                changed = true;
            }
            parent->fields[max_end +1] = INON::COLOR_WHITE;
        }
        if (min_start > 0) {
            if (parent->fields[min_start - 1] != INON::COLOR_WHITE) {
                changed = true;
            }
            parent->fields[min_start - 1] = INON::COLOR_WHITE;
        }
        for (int i = min_start; i <= max_end;++i) {
            if (parent->fields[i] != INON::COLOR_BLACK) {
                changed = true;
            }
            parent->fields[i] = INON::COLOR_BLACK;
        }
        if (next)
            next->prev = nullptr;

        if (prev)
            prev->next = nullptr;
    }
//    if (changed)
//        parent->print();
    return changed;
}

bool Obj::checkMaxEnd() {
    bool changed = false;
    int cnt = 0;
    int black_cnt = 0;
    auto max_end_cpy = max_end;
    for (int i = max_end; i >= min_start; --i) {
        if (parent->fields[i] == INON::COLOR_WHITE || (i == max_end_cpy && (i < parent->fields_count -1) && parent->fields[i + 1] == INON::COLOR_BLACK)) {
            max_end_cpy = i - 1;
            cnt = 0;
            black_cnt = 0;
            continue;
        }
        ++cnt;
        if (parent->fields[i] == INON::COLOR_BLACK && parent->fields_counters[i] == 1) {
            black_cnt++;
        }
        if (cnt == size) {
            if (max_end_cpy != max_end) {
                changed = true;
                max_end = max_end_cpy;
                if (prev)
                    prev->notifyMaxEndChanged(max_end - size -1);
            }
            if (black_cnt == size) {
                changed = true;
                min_start = max_end - size + 1;
                if (next)
                    next->notifyMinStartChanged(min_start + size +1);
            }
            break;
        }
    }
//    if (changed)
//        parent->print();
    return changed;
}

bool Obj::checkMinStart() {
    bool changed = false;
    int cnt = 0;
    int black_cnt = 0;
    int min_start_cpy = min_start;
    for (int i = min_start; i <= max_end; ++i) {
        if (parent->fields[i] == INON::COLOR_WHITE || ((i == min_start_cpy && i>0 && parent->fields[i-1] == INON::COLOR_BLACK))) {
            min_start_cpy = i+1;
            cnt = 0;
            black_cnt = 0;
            continue;
        }
        ++cnt;
        if (parent->fields[i] == INON::COLOR_BLACK && parent->fields_counters[i] == 1) {
            black_cnt++;
        }
        if (cnt == size) {
            if (min_start_cpy != min_start) {
                changed = true;
                min_start = min_start_cpy;
                //                checkMiddle();
                if (next)
                    next->notifyMinStartChanged(min_start + size +1);
            }

            if (black_cnt == size) {
                changed = true;
                max_end = min_start + size -1;
                //                checkSolved();
                if (prev)
                    prev->notifyMaxEndChanged(max_end - size -1);
            }
            break;
        }
    }
//    if (changed)
//        parent->print();
    return changed;
}

void Obj::notifyMaxEndChanged(int new_end) {
    if (new_end < max_end) {
        max_end = new_end;
        //checkMaxEnd();
        if (prev) {
            prev->notifyMaxEndChanged(max_end - size -1);
        }
    }
}

void Obj::notifyMinStartChanged(int new_start) {
    if (new_start > min_start) {
        min_start = new_start;
        //checkMinStart();
        if (next) {
            next->notifyMinStartChanged(min_start + size +1);
        }
    }
}

bool Obj::anchorAround() {
    bool changed = false;
    for (int i = min_start; i <= max_end; ++i) {
        if (parent->fields[i] == INON::COLOR_BLACK && (!next || next->min_start > i) && (!prev || prev->max_end < i)) {
            if (max_end > i + size - 1) {
                changed = true;
                max_end = i + size - 1;
                if (prev)
                    prev->notifyMaxEndChanged(max_end - size -1);
            }
            break;
        }
    }

    for (int i = max_end; i >= min_start; --i) {
        if (parent->fields[i] == INON::COLOR_BLACK && (!next || next->min_start > i) && (!prev || prev->max_end < i)) {
            if (min_start < i - size + 1) {
                changed = true;
                min_start = i - size + 1;
                if (next)
                    next->notifyMinStartChanged(min_start + size +1);
            }
            break;
        }
    }
//    if (changed)
//        parent->print();
    return changed;
}

bool Obj::checkOrphants() {
    if (!prev) {
        for(int i = max_end; i > min_start; --i) {
            if( parent->fields[i] == INON::COLOR_BLACK) {
                for (int j = i - size; j >= min_start; --j) {
                    if (parent->fields[j] == INON::COLOR_BLACK) {
                        max_end = j + size - 1;
//                        parent->print();
                        return true;
                    }
                }
            }
        }
    }
    if (!next) {
        for(int i = min_start; i < max_end; ++i) {
            if( parent->fields[i] == INON::COLOR_BLACK) {
                for (int j = i + size; j <= max_end; ++j) {
                    if (parent->fields[j] == INON::COLOR_BLACK) {
                        min_start = j - size + 1;
//                        parent->print();
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void NON::init(int n, int k, int *data) {
    fields_count = n;
    fields = new int[n];
    fields_counters = new int[n];
    for (int i = 0; i < n; ++i) {
        fields[i] = INON::COLOR_UNKNOWN;
        fields_counters[i] = 0;
    }

    obj_count = k;
    objects = new Obj[k];

    int beginnings = 0;

    for (int i = 0; i < k; i++) {
        objects[i].parent = this;
        objects[i].size = data[i];
        objects[i].min_start = beginnings;
        beginnings += data[i] + 1;

        if (i < k-1 ) {
            objects[i].next = &objects[i+1];
        }

        if (i > 0) {
            objects[i].prev = &objects[i-1];
        }
    }

    int endings = n-1;

    for (int i = k-1; i >=0; i--) {
        objects[i].max_end = endings;
        endings -= objects[i].size + 1;
    }

    for (int i = 0; i < k; i++) {
        for (int j = objects[i].min_start; j <= objects[i].max_end;j++) {
            fields_counters[j]++;
        }
    }

    for (int i = 0; i < k; i++) {
        objects[i].checkMiddle();
    }
    recalcCounters();
//    print();
}

bool NON::recalcCounters() {
    bool changed = false;
    for (int i = 0; i < fields_count; ++i) {
        fields_counters[i] = 0;
    }
    for (int i = 0; i < obj_count; i++) {
        for (int j = objects[i].min_start; j <= objects[i].max_end;j++) {
            if (fields[j] != INON::COLOR_WHITE)
                fields_counters[j]++;
        }
    }
    for (int i = 0; i < fields_count; ++i) {
        if (fields_counters[i] == 0) {
            if (fields[i] != INON::COLOR_WHITE) {
                fields[i] = INON::COLOR_WHITE;
                changed = true;
            }
        }
    }
//    if (changed)
//        print();
    return changed;
}

bool NON::checkMaxRemaining()
{
    int max = 0;
    for (int i = 0; i < obj_count; ++i) {
        if (!objects[i].solved) {
            if (max < objects[i].size) {
                max = objects[i].size;
            }
        }
    }

    if (max > 0) {
        for (int i = 0; i < obj_count; ++i) {
            if (!objects[i].solved && objects[i].size == max) {
                int cnt = 0;
                bool changed = false;
                for (int j = objects[i].min_start; j <= objects[i].max_end; ++j) {
                    if (INON::COLOR_BLACK == fields[j]) {
                        cnt++;
                        if (cnt == max) {
                            if (j + 1 < fields_count && fields[j+1] == INON::COLOR_UNKNOWN) {
                                fields[j+1] = INON::COLOR_WHITE;
                                changed = true;
                            }

                            if (j - max >= 0 && fields[j - max] == INON::COLOR_UNKNOWN) {
                                fields[j - max] = INON::COLOR_WHITE;
                                changed = true;
                            }

                            if (changed) {
//                                auto center = j - max/2.0;

//                                int min_dist = fields_count;
//                                int idx = -1;

//                                for (int k = 0; k < obj_count; ++k) {
//                                    if (!objects[k].solved && objects[k].size == max) {
//                                        auto center2 = (objects[k].min_start + objects[k].max_end)/2.0;
//                                        auto diff = (center - center2) > 0 ? (center - center2) : (center2 - center);
//                                        if (diff < min_dist) {
//                                            min_dist = diff;
//                                            idx = k;
//                                        }
//                                    }
//                                }

//                                objects[idx].min_start = j - max + 1;
//                                objects[idx].max_end = j;
                                return true;
                            }

                        }
                    } else {
                        cnt = 0;
                    }
                }
            }
        }
    }
    return false;
}

void NON::setColor(int idx, int color) {
    if (fields[idx] != color) {
//        print();
        fields[idx] = color;
//        print();
        bool changed = true;
        while (changed) {
            changed = false;
            for (int i = 0;i < obj_count; ++i) {
                if (!objects[i].solved) {
                    //                    if (idx > objects[i].max_end+1 || idx < objects[i].min_start -1) {
                    //                        continue;
                    //                    }
                    changed |= objects[i].checkMinStart();
                    changed |= objects[i].checkMaxEnd();
                    changed |= objects[i].checkMiddle();
                    changed |= objects[i].anchorAround();
                    changed |= objects[i].checkSolved();
                    changed |= objects[i].checkOrphants();
                }
            }
            changed |= recalcCounters();
            changed |= checkMaxRemaining();
        }
    }
//    print();
}

int NON::getColor(int idx) {
//    print();
    return fields[idx];
}

NON factory;
int main() {
    Judge::run(&factory);
    return 0;
}

