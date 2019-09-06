#include "judge.h"
#include <iostream>
#include <ctime>
using namespace std;

const int MAX = 100;

int data[MAX][MAX];
INON *rows[MAX];
INON *columns[MAX];
int tmp[MAX];

int type;
int height, width;

void show() {
	for (int row=0; row<height; ++row) {
		for (int col=0; col<width; ++col) {
			if (INON::COLOR_UNKNOWN == data[row][col]) cout << "?";
			if (INON::COLOR_WHITE == data[row][col]) cout << ".";
			if (INON::COLOR_BLACK == data[row][col]) cout << "#";
		}
		cout << "\n";
	}
	cout << "\n";
}

void Judge::run(INON *factory) {
	clock_t start = clock();

	cin >> type;
	cin >> height >> width;

	for (int row=0; row<height; ++row) for (int col=0; col<width; ++col) data[row][col] = INON::COLOR_UNKNOWN;
	for (int row=0; row<height; ++row) {
		int k; cin >> k;
		for (int i=0; i<k; ++i) cin >> tmp[i];
		rows[row] = factory->createLine(width, k, tmp);
	}
	for (int col=0; col<width; ++col) {
		int k; cin >> k;
		for (int i=0; i<k; ++i) cin >> tmp[i];
		columns[col] = factory->createLine(height, k, tmp);
	}

	bool anyChange = true;
	while (anyChange) {
		anyChange = false;
		for (int row=0; row<height; ++row) {
			for (int col=0; col<width; ++col) {
				if (INON::COLOR_UNKNOWN == data[row][col]) {
					int color = rows[row]->getColor(col);
					if (INON::COLOR_UNKNOWN != color) {
						data[row][col] = color;
						columns[col]->setColor(row, color);
						anyChange = true;
					}
				}
			}
		}
		for (int col=0; col<width; ++col) {
			for (int row=0; row<height; ++row) {
				if (INON::COLOR_UNKNOWN == data[row][col]) {
					int color = columns[col]->getColor(row);
					if (INON::COLOR_UNKNOWN != color) {
						data[row][col] = color;
						rows[row]->setColor(col, color);
						anyChange = true;
					}
				}
			}
		}
	}

	clock_t runningTime = clock() - start;

	cerr << (((double)runningTime) / CLOCKS_PER_SEC) << "\n";

	show();
}

