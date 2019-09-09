package GAL;

public class GAL {
	enum types {
		Produkcja, Handel, Przetwarzanie, Ataki, Podatki
	};

	class point {
		int x;
		int y;

		point() {
			x = 0;
			y = 0;
		}

		point(int _x, int _y) {
			x = _x;
			y = _y;
		}

		boolean equals(point p) {
			return x == p.x && y == p.y;
		}

		boolean equals(int x, int y) {
			return x == this.x && y == this.y;
		}

		public boolean inRange(point a, point b) {
			if (x < a.x)
				return false;
			if (x > b.x)
				return false;
			if (y < a.y)
				return false;
			if (y > b.y)
				return false;
			return true;
		}
	};

	char[] text;

	int parseNum(int i, int[] num) {
		int x = 0;
		while (text[i] >= '0' && text[i] <= '9') {
			x *= 10;
			x += (text[i] - '0');
			i++;
		}
		num[0] = x;
		return i;
	}

	int parseCoords(int i, point out) {
		i++; // skip (
		int[] a = { 0 };
		int[] b = { 0 };
		i = parseNum(i, a);
		i++; // skip ,
		i = parseNum(i, b);
		i++; // skip ')'
		out.x = a[0];
		out.y = b[0];
		return i;
	}

	class Vector {
		node[] get = new node[1];
		int size = 0;

		void add(node n) {
			if (get.length == size) {
				grow();
			}
			get[size] = n;
			size++;
		}

		void grow() {
			node[] next = new node[2 * size];
			for (int i = 0; i < size; i++) {
				next[i] = get[i];
			}
			get = next;
		}

		public node pop() {
			return get[--size];
		}
	}

	class ArraySet {
		node[] get = new node[10000];
		int size = 0;

		void remove(node planet) {
			int i = planet.index;
			if (i > -1) {
				size--;
				planet.index = -1;
				if (i < size) {
					get[i] = get[size];
					get[i].index = i;
				}
			}
		}

		void add(node planet) {
			// brak tej linii - subtelny bug
			if(planet.index != -1) return;
			
			get[size] = planet;
			planet.index = size;
			size++;
		}
	}

	class node {
		int index = -1;
		long value = 0;
		point coords;
		point a = new point();
		point b = new point();
		types type = types.Produkcja;
		Vector next = null;

		int dependencies = 0;

		int analyzeDeps() {
			dependencies = 0;
			switch (type) {
			case Produkcja:
				break;
			case Handel:
			case Przetwarzanie:
				dependencies += GALAXY[a.x][a.y].add(this);
				dependencies += GALAXY[b.x][b.y].add(this);
				break;
			case Ataki:
			case Podatki:
				for (int x = a.x; x <= b.x; x++)
					for (int y = a.y; y <= b.y; y++) {
						dependencies += GALAXY[x][y].add(this);
					}
				break;
			}
			return dependencies;
		}

		int add(node node) {
			if (type == types.Produkcja)
				return 0;
			next.add(node);
			return 1;
		}

		void updateValue() {
			switch (type) {
			case Produkcja:
				return;
			case Handel:
			case Przetwarzanie:
				value = 0;
				value += GALAXY[a.x][a.y].value;
				value += GALAXY[b.x][b.y].value;
				if (type == types.Przetwarzanie) {
					value *= 2;
				}
				return;
			case Ataki:
				value = Long.MAX_VALUE;
				for (int x = a.x; x <= b.x; x++)
					for (int y = a.y; y <= b.y; y++) {
						long v = GALAXY[x][y].value;
						if (v < value)
							value = v;
					}
				return;
			case Podatki:
				value = 0;
				for (int x = a.x; x <= b.x; x++)
					for (int y = a.y; y <= b.y; y++) {
						long v = GALAXY[x][y].value;
						if (v > value)
							value = v;
					}
				return;
			}
		}

		void update() {
			updateValue();
			for (int i = 0; i < next.size; i++) {
				node n = next.get[i];
				n.dependencies--;
				if (n.dependencies == 0) {
					updateQueue.add(n);
				}
			}
		}
	};

	ArraySet nonTrivial = new ArraySet();
	Vector updateQueue = null;
	
	void update() {
		updateQueue = new Vector();
		for (int i = 0; i < nonTrivial.size; i++) {
			nonTrivial.get[i].next = new Vector();
		}
		for (int i = 0; i < nonTrivial.size; i++) {
			if (nonTrivial.get[i].analyzeDeps() == 0) {
				updateQueue.add(nonTrivial.get[i]);
			}
		}
		while (updateQueue.size > 0) {
			node n = updateQueue.pop();
			n.update();
		}
		for (int i = 0; i < nonTrivial.size; i++) {
			nonTrivial.get[i].next = null;
		}
		updateQueue = null;
	}

	node[][] GALAXY = new node[100][100];

	galaxy() {
		for (int i = 0; i < 100; i++)
			for (int j = 0; j < 100; j++) {
				GALAXY[i][j] = new node();
				GALAXY[i][j].coords = new point(i, j);
			}
	}

	public void report(char[] command) {
		point pt = new point();
		types type;
		text = command;
		int i = 0;
		i = parseCoords(i, pt);
		if (text[i + 1] == 'H') { // =Handel
			type = types.Handel;
			i += 7;
		} else if (text[i + 1] == 'A') { // =Ataki
			type = types.Ataki;
			i += 6;
		} else if (text[i + 2] == 'o') { // =Podatki
			type = types.Podatki;
			i += 8;
		} else if (text[i + 3] == 'o') { // =Produkcja
			type = types.Produkcja;
			i += 10;
		} else { // =Przetwarzanie
			type = types.Przetwarzanie;
			i += 14;
		}
		i++; // skip (
		node planet = GALAXY[pt.x][pt.y];

		if (type == types.Produkcja) {
			int[] value = { 0 };
			parseNum(i, value);
			planet.value = value[0];
			planet.type = type;
			nonTrivial.remove(planet);
		} else {
			planet.type = type;
			i = parseCoords(i, planet.a);
			i++; // skip , or :
			i = parseCoords(i, planet.b);
			nonTrivial.add(planet);
		}
	}

	public void summary(long[][] outputArray) {
		update();
		for (int i = 0; i < 100; i++)
			for (int j = 0; j < 100; j++) {
				outputArray[i][j] = GALAXY[i][j].value;
			}
	}
	
	public static void main(String[] args) {
		new judge().run(new GAL());
	}
}
