import java.util.Timer;
import java.util.TimerTask;

public class TimerDemo {
   private Timer timer;
   public static void main(String[] args) {
      
      new TimerDemo().schedule();
     
   }
   
   private void schedule(){
      TimerTask  task = new MySchedule();
      timer = new Timer();
      /*
      schedule(TimerTask task, long delay, long period)
      Schedules the specified task for repeated fixed-delay
      execution, beginning after the specified delay.
      */
      timer.schedule(task,10,1000);      

   }

   private class MySchedule extends TimerTask{
      // this method performs the task
      private int count =0;
      
      public void run() {
         System.out.println("timer working: "+count);  
         count+=1;
         // You can invoke cancel() method of the timer to stop it.
         if(count==5)
            timer.cancel(); 
      }   
   } 

}