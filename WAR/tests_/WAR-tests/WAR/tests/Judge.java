import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.BitSet;


public class Judge {
	static long seed = 0;
	static final int MOD = 1000000007;

	static int pseudo_rand() {
		seed = seed * 134775813 + 1;
		return (((int)seed) & 0x7FFFFFFF) % MOD;
	}

	static final int MAX_WORKSHOPS = 5;
	static final int MAX_LEVELS = 5;
	static final int MAX_KNOX_ID = 20 * 1000 * 1000;
	static final int MAX_CALLS = 500 * 1000;

	static char[][] levels = {
		{'n','o','n','e','l','i','g','i','b','l','e'},
		{'i','n','t','e','r','m','e','d','i','a','t','e'},
		{'a','d','v','a','n','c','e','d'},
		{'p','r','o','f','e','s','s','i','o','n','a','l'},
		{'e','x','p','e','r','t'}
	};

	static class vector {
		int[] mData;
		int mDataSize;
		int mSize;
		public vector() {
			mData = new int[4];
			mDataSize = 4;
			mSize = 0;
		}
		public int getAt(int pos) { return mData[pos]; }
		public void setAt(int pos, int v) { mData[pos] = v; }
		int size() { return mSize; }
		boolean empty() { return 0 == size(); }
		void pop_back() { --mSize; }
		void push_back(int v) {
			if (mSize == mDataSize) {
				int newSize = mDataSize * 2;
				int[] newData = new int[newSize];
				for (int i=0; i<mSize; ++i)
					newData[i] = mData[i];
				mData = newData;
				mDataSize = newSize;
			}
			mData[mSize++] = v;
		}
		int removeAt(int pos) {
			int res = mData[pos];
			mData[pos] = mData[--mSize];
			return res;
		}
	}

	static public void run(WAR w) {
		Scanner s = new Scanner(System.in);
		int typ = s.nextInt();
		char[] level = new char[15];
		int[] preferences = new int[MAX_WORKSHOPS];
		if (typ == 1) {
			int workshopsNum = s.nextInt();
			int maxParticipants = s.nextInt();
			int callsNum = s.nextInt();
			w.init(workshopsNum, maxParticipants);
			for (int i = 0; i < callsNum; ++i) {
				int op = s.nextInt();
				if (op == 0) {
					int byteid = s.nextInt();
					String lvl = s.next();
					for (int j=0; j<lvl.length(); ++j) level[j] = lvl.charAt(j);
					for (int j = 0; j < workshopsNum; ++j)
						preferences[j] = s.nextInt();
					//cout << "  wynik: " << w->registration(byteid, level, preferences) << "\n";
					System.out.println(w.registration(byteid, level, preferences));
				} else {
					int byteid = s.nextInt();
					//cout << "  wynik: " << w->unregistration(byteid) << "\n";
					System.out.println(w.unregistration(byteid));
				}
			}
		} else if (typ == 2)
		{
			int java = s.nextInt();
			seed = s.nextLong();
			int workshopsNum = s.nextInt();
			int maxParticipants = s.nextInt();
			int regNum = s.nextInt();
			int unregNum = s.nextInt();
			int callsNum = 0;
			int eqPref = s.nextInt();
			int HASH = s.nextInt();
			if (java == 0) {
				// test dla Javy
				System.out.println(HASH);
				return;
			}
			callsNum = regNum + unregNum;
			w.init(workshopsNum, maxParticipants);
			
			int[] oper = new int[MAX_CALLS];
			for (int i = 0; i < regNum; ++i) oper[i] = 0;
			for (int i = regNum; i < callsNum; ++i) oper[i] = 1;
			for (int i = 1; i < callsNum; ++i) { int pos = pseudo_rand() % i; int t = oper[i]; oper[i] = oper[pos]; oper[pos] = t; }
			for (int i = 1; i < callsNum; ++i) { int pos = pseudo_rand() % i; int t = oper[i]; oper[i] = oper[pos]; oper[pos] = t; }

			BitSet byteS = new BitSet(MAX_KNOX_ID + 1);
			vector byteV = new vector();
			int hash = 0;
			int realOps = 0;
			for (int i = 0; i < workshopsNum; ++i) preferences[i] = i;
			for (int i = 1; i < workshopsNum; ++i) { int pos = pseudo_rand() % i; int t = preferences[i]; preferences[i] = preferences[pos]; preferences[pos] = t; }

			for (int op = 0; op < callsNum; ++op)
			{
				if (oper[op] == 0)
				{
					if (byteV.size() >= workshopsNum * maxParticipants)
					{
						continue;
					}
					int byteid = -1;
					while (true)
					{
						byteid = pseudo_rand() % MAX_KNOX_ID + 1;
						if (byteS.get(byteid) == false) {
							byteS.set(byteid);
							break;
						}
					}
					byteV.push_back(byteid);
					int levelXXX = pseudo_rand() % MAX_LEVELS;
					if (eqPref == 0)
					{
						for (int i = 1; i < workshopsNum; ++i) { int pos = pseudo_rand() % i; int t = preferences[i]; preferences[i] = preferences[pos]; preferences[pos] = t; }
					}
					int res = w.registration(byteid, levels[levelXXX], preferences);
					hash = (hash * 11 + res) % 1000000007;
					++realOps;
				} else
				{
					if (byteV.empty())
					{
						continue;
					}
					int pos = pseudo_rand() % (byteV.size());
					int byteid = byteV.removeAt(pos);
					int res = w.unregistration(byteid);
					hash = (hash * 11 + res) % 1000000007;
					++realOps;
				}
			}
			System.out.println(hash);
			System.err.println("num ops: " + realOps);
		}
	}
}

