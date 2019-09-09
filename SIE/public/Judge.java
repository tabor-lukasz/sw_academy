import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Judge {

static Scanner s = new Scanner(System.in);

  static public void run(SIE w) {
    int typ = s.nextInt();

    int callsNum = s.nextInt();
    for (int i = 0; i < callsNum; ++i)
    {
      int op = s.nextInt();
      if (op == 0)
      {
        int idNew = s.nextInt();
        int idExisting = s.nextInt();
        int linkThroughput = s.nextInt();
        w.addServer(idNew, idExisting, linkThroughput);
      } else if (op == 1)
      {
        int id = s.nextInt();
        System.out.println(w.directLinks(id));
      } else if (op == 2)
      {
        int id1 = s.nextInt();
        int id2 = s.nextInt();
        System.out.println(w.connectionThroughput(id1, id2));
      } else if (op == 3)
      {
        int id1 = s.nextInt();
        int id2 = s.nextInt();
        int linkThroughput = s.nextInt();
        w.improveThroughput(id1, id2, linkThroughput);
      }
    }

  }

}

