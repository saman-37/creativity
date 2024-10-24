import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.Random;

public class Client implements Protocol {
    public static void main(String[] args) throws IOException, InterruptedException {

        Socket client = new Socket("localhost", PORT);
        DataInputStream in = new DataInputStream(client.getInputStream());
        DataOutputStream out = new DataOutputStream(client.getOutputStream());

        Random random = new Random();

        // 10 requests to server
        for (int i = 0; i < 9; i++) {
            int delay = random.nextInt(401) + 100; // Random delay between 100 and 500 ms
            Thread.sleep(delay);
            System.out.println("--------------------------------");
            switch (i) {
                case 0:
                    System.out.println("Add item Balloon with 3 units");
                    out.writeInt(ADD_ITEM);
                    out.writeUTF("Balloon");
                    out.writeInt(3);
                    out.flush();
                    System.out.println("--------------------------------\n");
                    break;
                case 1:
                    System.out.println("Add item Cake with 10 units");
                    out.writeInt(ADD_ITEM);
                    out.writeUTF("Cake");
                    out.writeInt(10);
                    out.flush();
                    System.out.println("--------------------------------\n");
                    break;
                case 2:
                    System.out
                            .println("Check, and return no. of Cake in the inventory");
                    out.writeInt(CHECK_INVENTORY);
                    out.writeUTF("Cake");
                    out.flush();
                    int response = in.readInt();
                    if (response == SUCCEED)
                        System.out.println("Number of available units:" + in.readInt() + "\n");
                    // ??????????????????????????FAILED
                    System.out.println("--------------------------------\n");
                    break;
                case 3:
                    System.out.println(
                            "Remove 2 units of Dress(doesnt exist), & return how much left, else -1");
                    out.writeInt(TAKE_ITEM);
                    out.writeUTF("Dress");
                    out.writeInt(2);
                    out.flush();
                    response = in.readInt();
                    if (response == SUCCEED)
                        System.out.println("Number of available units:" + in.readInt() + "\n"); // expected -1
                    else
                        System.out.println("No such item exist, hence cannot be removed");

                    System.out.println("--------------------------------\n");
                    break;
                case 4:
                    System.out.println("Remove 2 Balloons & return how much left");
                    out.writeInt(TAKE_ITEM);
                    out.writeUTF("Balloon");
                    out.writeInt(2);
                    out.flush();
                    response = in.readInt();
                    if (response == SUCCEED)
                        System.out.println("Number of available units:" + in.readInt() + "\n"); // expected 1
                    System.out.println("--------------------------------\n");
                    break;
                case 5:
                    System.out.println("Returns all items and their available units below a threshold");
                    out.writeInt(GET_THRESHOLD);
                    out.writeInt(2);
                    out.flush();
                    response = in.readInt();
                    if (response == SUCCEED)
                        System.out.println("Threshold items: " + in.readUTF() + "\n");
                    System.out.println("--------------------------------\n");
                    break;

                case 6:
                    System.out.println("Add item Charm with 8 units");
                    out.writeInt(ADD_ITEM);
                    out.writeUTF("Charm");
                    out.writeInt(8);
                    out.flush();
                    System.out.println("--------------------------------\n");
                    break;
                case 7:
                    System.out.println("Remove 3 units of Charm & return how much left");
                    out.writeInt(TAKE_ITEM);
                    out.writeUTF("Charm");
                    out.writeInt(3);
                    out.flush();
                    response = in.readInt();
                    if (response == SUCCEED)
                        System.out.println("Number of available units:" + in.readInt() + "\n");
                    System.out.println("--------------------------------\n");
                    break;
                case 8:
                    System.out.println("Check, and return no. of Charm in the inventory");
                    out.writeInt(CHECK_INVENTORY);
                    out.writeUTF("Charm");
                    out.flush();
                    response = in.readInt();
                    if (response == SUCCEED)
                        System.out.println("Number of available units:" + in.readInt() + "\n");
                    System.out.println("--------------------------------\n");
                    break;

                case 9:
                    System.out.print("quit: ");
                    out.writeInt(QUIT);
                    out.flush();
                    response = in.readInt();
                    System.out.println("Received: " + response);
                    System.out.println("--------------------------------\n");
                    break;
            }
        }

        client.close();
    }
}
