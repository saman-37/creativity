
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.stage.Modality;
import javafx.scene.text.Text;

public class GUI extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    // We will need instance of Time class 2 times, once during beginning to get
    // current date
    // once during event handling, when need to produce result
    private SampleJavaTime counter = new SampleJavaTime(); // calling no-arg constructor

    @Override
    public void start(Stage primaryStage) {
        Pane root = new Pane();

        root.setPrefWidth(300);
        root.setPrefHeight(300);

        Scene scene = new Scene(root);
        primaryStage.setTitle("Date Counter");
        primaryStage.setScene(scene);

        // Get the content from content() method
        HBox finalContent = content();
        root.getChildren().add(finalContent);

        primaryStage.show();
    }

    private HBox content() {

        // Set To Default Value
        TextField date1 = new TextField("1/1/2000");
        // GET FROM SampleJavaTime class, this date????
        TextField date2 = new TextField(counter.getCurrentDate());

        Button count = new Button("Count");
        CountListener countListener = new CountListener(date1, date2); // Pass text fields to listener
        count.setOnAction(countListener);

        Label startDate = new Label("Start Date");
        Label endDate = new Label("End Date");

        VBox labels = new VBox(20, startDate, endDate);
        VBox textboxesAndButton = new VBox(10, date1, date2, count);

        HBox contents = new HBox(10, labels, textboxesAndButton);
        return contents;
    }

    /*
     * We want to save the inputs when user hits count
     * So that later can use them in Time class to calculate duration
     */
    // Let this class rethrow the exception, and handle it in Lab9's main
    private class CountListener implements EventHandler<ActionEvent> {

        // Fields
        private TextField date1Field;
        private TextField date2Field;

        // constructor
        public CountListener(TextField date1, TextField date2) {
            this.date1Field = date1;
            this.date2Field = date2;
        }

        // method
        /*
         * just 1 button, so we dont need to detect source, since singular action
         * SampleJavaTime counter = new SampleJavaTime(startDate, endDate);
         * Verification happens before calculation
         */
        @Override
        public void handle(ActionEvent e) {
            String startDate = date1Field.getText();
            String endDate = date2Field.getText();

            try {
                DataVerifier.verifyDate(startDate, "Start Date");
                DataVerifier.verifyDate(endDate, "End Date");

                SampleJavaTime counter = new SampleJavaTime(startDate, endDate); // calling second constructor
                showPopUpWindow(counter);
            }

            // rethrows BadDateException wrapped in RuntimeException so that the Lab9 class
            // can catch it
            catch (BadDateException ex) {
                // throw new RuntimeException(ex);
                System.out.println(ex.getMessage());
                // do not throw exception here, catch it and print mesage in popup
            }

        }

        private void showPopUpWindow(SampleJavaTime counter) {
            Stage popUpStage = new Stage();
            popUpStage.initModality(Modality.APPLICATION_MODAL);
            VBox dialogVbox = new VBox(20);

            // The data that we are getting here from Time class is in numeric as we have
            // gotten this data from duration object , %d represents int
            String output = String.format("%d days\n%d months \n%d years\n%d total days", counter.getCountOfDays(),
                    counter.getCountOfMonths(), counter.getCountOfYears(), counter.getNumberOfDays());

            dialogVbox.getChildren().add(new Text(output));
            Scene dialogScene = new Scene(dialogVbox, 300, 200);
            popUpStage.setScene(dialogScene);
            popUpStage.show();
        }

    }
}