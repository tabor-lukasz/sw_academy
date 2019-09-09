import java.util.Arrays;

interface Compare {
	boolean less(int a, int b);
}

class Heap {
	Compare cmp;
	int[] data;
	int[] index;
	int size = 0;

	Heap(int size, int maxId, Compare cmp) {
		data = new int[size + 1];
		index = new int[maxId + 1];
		this.cmp = cmp;
	}

	void add(int x) {
		if (index[x] > 0)
			return;

		if (x == 5 && size == 2) {
			int q = 0;
			q = -q;
		}

		grow();
		data[++size] = x;
		index[x] = size;
		heapUp(size);
	}

	boolean remove(int x) {
		int i = index[x];
		if (i < 1)
			return false;

		if (size == 0) {
			return false; // return 0 / 0 > 0;
		}

		index[x] = 0;
		size--;
		if (i <= size) {
			data[i] = data[size + 1];
			index[data[i]] = i;
			heapUp(i);
			heapDown(i);
		}

		if (index[x] != 0) {
			return false; // 0 / 0 > 0;
		}
		return true;
	}

	int top() {
		return data[1];
	}

	private void heapUp(int i) {
		if (i < 2)
			return;
		int parent = i / 2;
		if (isLess(i, parent)) {
			swap(i, parent);
			heapUp(parent);
		}
	}

	private void heapDown(int i) {
		if (i * 2 > size)
			return;
		int smallest = i;
		int left = 2 * i;
		int right = 2 * i + 1;
		if (isLess(left, smallest)) {
			smallest = left;
		}
		if (right <= size && isLess(right, smallest)) {
			smallest = right;
		}
		if (smallest != i) {
			swap(i, smallest);
			heapDown(smallest);
		}
	}

	private boolean isLess(int i, int j) {
		return cmp.less(data[i], data[j]);
	}

	private void swap(int i, int j) {
		int x = data[i];
		data[i] = data[j];
		data[j] = x;

		index[data[i]] = i;
		index[data[j]] = j;
	}

	void grow() {
		if (size + 1 == data.length) {
			int[] data = new int[2 * this.data.length];
			for (int i = 0; i < this.data.length; i++) {
				data[i] = this.data[i];
			}
			this.data = data;
		}
	}
}

class Solver {
	public Compare betterFirst = new Compare() {
		@Override
		public boolean less(int a, int b) {
			return lvl[a] * MULT + bid[a] < lvl[b] * MULT + bid[b];
		}
	};

	public Compare worseFirst = new Compare() {
		@Override
		public boolean less(int a, int b) {
			return lvl[a] * MULT + bid[a] > lvl[b] * MULT + bid[b];
		}
	};

	class Workshop {
		final static int REGISTERED = -1;
		final static int FAILED = -2;

		Heap registered = new Heap(M + 1, MAX_CALLS, worseFirst);
		Heap queue = new Heap(M + 1, MAX_CALLS, betterFirst);

		int register(int id) {
			if (registered.size < M) {
				registered.add(id);
				return REGISTERED;
			}
			int worse = registered.top();
			if (worseFirst.less(id, worse)) {
				queue.add(id);
				return FAILED;
			}
			registered.remove(worse);
			registered.add(id);
			return worse;
		}

		boolean unregister(int id) {
			queue.remove(id);
			if (registered.remove(id)) {
				return true;
			}
			return false;
		}

		public void report(int index) {
			//System.err.print(index + ": ");
			for (int i = 0; i < registered.size; i++) {
				//System.err.print(bid[registered.data[i + 1]] + " ");
			}
			//System.err.print("(");
			for (int i = 0; i < queue.size; i++) {
				int a = queue.data[i + 1];
				//System.err.print(bid[a] + ":" + lvl[a] * MULT + bid[a] + " ");
			}
			//System.err.print(")");
			//System.err.println();
		}
	}

	final static int MAX_CALLS = 500002;
	final static int MULT = 30_000_000;
	int N;
	int M;
	Workshop[] W;

	int bid[] = new int[MAX_CALLS + 1];
	byte[] choice = new byte[MAX_CALLS + 1];
	byte[] lvl = new byte[MAX_CALLS + 1];
	int[][] prefs = new int[MAX_CALLS + 1][];

	Solver(int n, int m) {
		N = n;
		M = m;
		W = new Workshop[n];
		for (int i = 0; i < n; i++) {
			W[i] = new Workshop();
		}
	}

	int register(int id, int byteid, byte level, int[] preferences) { // lvl 0 is best
		bid[id] = byteid;
		lvl[id] = level;
		prefs[id] = preferences;

		for (int i = 0; i < N; i++) {
			int w = preferences[i];
			int code = W[w].register(id);
			//System.err.printf("Trying register %d in %d\n", id, w);
			//System.err.println(code == -2 ? "FAILED" : ("OK: " + code));
			if (code == Workshop.FAILED)
				continue;
			choice[id] = (byte) (w + 0);
			if (code == Workshop.REGISTERED)
				return w;
			findPlaceFor(code);
			return w;
		}

		return -1;// 0 / 0;
	}

	void findPlaceFor(int id) {
		while (true) {
			for (int i = 0; i < N; i++) {
				int w = prefs[id][i];
				int code = W[w].register(id);
				if (code == Workshop.FAILED)
					continue;
				choice[id] = (byte) (w + 0);
				if (code == Workshop.REGISTERED)
					return;

				// code == kicked guy
				id = code;
				break;
			}
		}
	}

	private void fillSlot(int w) {
		while (true) {
			if (W[w].queue.size == 0)
				return;

			int id = W[w].queue.top();
			W[w].queue.remove(id);

			if (prefs[id] == null)
				continue;

			boolean next = false;
			for (int i = 0; i < N; i++) {
				if (prefs[id][i] == choice[id]) {
					next = true;
					break;
				}
				if (prefs[id][i] == w) {
					next = false;
					break;
				}
			}
			if (next)
				continue;

			int prev = choice[id];
			W[prev].unregister(id);

			W[w].register(id);
			choice[id] = (byte) w;

			w = prev;
		}
	}

	int unregister(int id) {
		prefs[id] = null;
		int workshop = -1;

		for (int i = 0; i < N; i++) {
			if (W[i].unregister(id)) {
				workshop = i;
			}
		}

		fillSlot(workshop);
		return workshop;
	}

	void report() {
		for (int i = 0; i < N; i++) {
			W[i].report(i);
		}
	}
}

public class WAR {
	Solver solver;

	final static int MAX_ID = 20_000_000;
	int NEXT_ID = 1;
	int[] getId = new int[MAX_ID + 1];

	public void init(int workshopsNum, int maxParticipants) {
		//System.err.println("INIT: " + workshopsNum + " " + maxParticipants);
//		if(1==1) return;
		solver = new Solver(workshopsNum, maxParticipants);
	}

	public int registration(int byteid, char[] level, int[] preferences) {
//		if(1==1) return 0;
		int id = getId[byteid] = NEXT_ID++;
		//System.err.println( "\n\nreg " + byteid + " " + id + " " + String.copyValueOf(level) + Arrays.toString(preferences));

		byte lvl = 0;
		if (level[0] == 'p') {
			lvl = 1;
		} else if (level[0] == 'a') {
			lvl = 2;
		} else if (level[0] == 'i') {
			lvl = 3;
		} else if (level[0] == 'n') {
			lvl = 4;
		}

		int[] prefs = new int[preferences.length];
		for (int i = 0; i < preferences.length; i++) {
			prefs[i] = preferences[i];
		}
		solver.report();
		return solver.register(id, byteid, lvl, prefs);
	}

	public int unregistration(int byteid) {
//		if(1==1) return 0;
		//System.err.println("\n\nunreg " + byteid);

		solver.report();
		return solver.unregister(getId[byteid]);
	}

	public static void main(String[] args) {
		Judge.run(new WAR());
	}
}

