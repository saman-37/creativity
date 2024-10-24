import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Server implements Protocol {

    public static void main(String[] args) throws IOException {

        Inventory inventory = new Inventory();
        ServerSocket server = new ServerSocket(PORT);

        while (true) {
            try {
                System.out.println("Waiting for clients to connect");
                Socket client = server.accept();
                System.out.println("Client connected.");
                Service service = new Service(client, inventory);
                Thread t1 = new Thread(service);
                t1.start();
            } catch (IOException e) {
                e.printStackTrace();
            }

        }

    }
}

class Service implements Protocol, Runnable {
    private Socket client = null;
    private DataInputStream in;
    private DataOutputStream out;
    private Inventory inventory;

    // constructor
    public Service(Socket client, Inventory inventory) {
        this.client = client;
        this.inventory = inventory;
    }

    @Override
    public void run() {
        try {
            try {
                in = new DataInputStream(client.getInputStream());
                out = new DataOutputStream(client.getOutputStream());
                doAction();
            } catch (IOException e) {
                out.writeInt(FAILED);
            } finally {
                client.close();
            }
        } catch (IOException exception) {
            // Handling any exceptions that might occur during socket close
        }

    }

    private void doAction() throws IOException {
        int command = 0;
        int count;
        String item;

        while (command != QUIT) {
            command = in.readInt();
            int leftCount;

            switch (command) {

                case ADD_ITEM:
                    item = in.readUTF(); // gather inputs
                    count = in.readInt();
                    inventory.addItem(item, count); // conduct process
                    out.writeInt(SUCCEED);
                    out.flush();
                    break;

                case TAKE_ITEM:
                    item = in.readUTF();
                    count = in.readInt();
                    // TAKEITEM & CHECKINVENTORY BOTH WILL RETURN AN INTEGER, WE NEED TO PRINT THAT
                    leftCount = inventory.takeItem(item, count);
                    // -----------------FAILED SITUATION CHECK---------------||
                    if (leftCount == -1) {
                        out.writeInt(FAILED);
                    } else {
                        out.writeInt(SUCCEED);
                        out.writeInt(leftCount);
                    }

                    out.flush();
                    break;

                case CHECK_INVENTORY:
                    item = in.readUTF();
                    leftCount = inventory.checkInventory(item);
                    if (leftCount == -1) {
                        out.writeInt(FAILED);
                    } else {
                        out.writeInt(SUCCEED);
                        out.writeInt(leftCount);
                    }

                    out.flush();
                    break;

                case GET_THRESHOLD:
                    count = in.readInt();
                    String thresholdItems = inventory.getThreshold(count);
                    out.writeInt(SUCCEED);
                    out.writeUTF(thresholdItems);

                    out.flush();
                    break;

                case QUIT:
                    out.writeInt(CLOSED);
                    out.flush();
                    break;

                default:
                    out.writeInt(FAILED);
                    out.flush();
                    break;
            }
        }

    }

}