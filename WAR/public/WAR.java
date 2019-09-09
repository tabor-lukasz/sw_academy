public class WAR {
	public void init(int workshopsNum, int maxParticipants) {}
	public int registration(int byteid, char[] level, int[] preferences) { return 0; }
	public int unregistration(int byteid) { return 0; }

	public static void main(String[] args) {
		Judge.run(new WAR());
	}
}

