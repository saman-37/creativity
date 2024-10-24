import java.util.Timer;
import java.util.TimerTask;

public class BucketThreadTester {

    public static void main(String[] args) {

        // creating instance of main "shared" class
        Bucket bucket = new Bucket();

        // creating instance of "parallel" running classes
        Consumer c = new Consumer(bucket);
        Producer d = new Producer(bucket);

        Thread t1 = new Thread(c);
        Thread t2 = new Thread(d);

        t1.start();
        t2.start();

        // Timing
        // Creating and scheduling the TimerTask to interrupt threads after 10 seconds
        TimerTask stopTask = new TimerTask() {
            @Override
            public void run() {
                t1.interrupt();
                t2.interrupt();
                System.out.println("Threads have been interrupted after 30 seconds.");
            }
        };

        Timer timer = new Timer();
        timer.schedule(stopTask, 10000); // Schedule task to run after 10 seconds

    }

}
