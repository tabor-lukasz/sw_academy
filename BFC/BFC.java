public class BFC {

	double mySqrt(double fg) {
		double n = fg / 2.0;
		double lstX = 0.0;
		while(n != lstX) {
			lstX = n;
			n = (n + fg/n) / 2.0;
		}
		return n;
	}

	public double minFiberCableLength(int n, int[] x, int[] y, int minDist, int rangeDist) {
		return -1.0;
	}

	public static void main(String[] args) {
		Judge.run(new BFC());
	}

}

