import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;
import java.util.*;

public class Judge {
  static final int MAX_N = 2000;
  static int[] ver1 = new int[MAX_N + 1];
  static int[] ver2 = new int[MAX_N + 1];
  static int[] dist = new int[MAX_N + 1];

  static Scanner s = new Scanner(System.in);

  static public void run(WYB solution) {

    int T, N;

    T = s.nextInt();

    for (int i = 0; i < T; i++) {
      N = s.nextInt();
      for (int j = 0; j < N - 1; j++) {
        ver1[j] = s.nextInt();
        ver2[j] = s.nextInt();
        dist[j] = s.nextInt();
      }
      int ret = solution.improveNetwork(N, ver1, ver2, dist);
      System.out.println(ret);
    }
  }
}
