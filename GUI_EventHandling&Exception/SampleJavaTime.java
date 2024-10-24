import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.Period;
import java.time.format.DateTimeFormatter;
import java.time.temporal.ChronoUnit;

public class SampleJavaTime {

	// instance fields
	private int countOfDays;
	private int countOfMonths;
	private int countOfYears;
	private long numberOfDays;
	// WILL NEED THIS FOR GUI, VERY FIRST INTERFACE FOR BY-DEFAULT END DATE
	private String currentDate;

	// Constructor to calculate duration between start and end dates
	public SampleJavaTime(String start, String end) throws BadDateException {
		// Verify the dates using DataVerifier class
		// verifyDate method is of static type, hence should be able to call it directly
		DataVerifier.verifyDate("Start Date", start);
		DataVerifier.verifyDate("End Date", end);

		DateTimeFormatter formatter = DateTimeFormatter.ofPattern("d/M/yyyy");
		LocalDate startDate = LocalDate.parse(start, formatter);
		LocalDate endDate = LocalDate.parse(end, formatter);

		Period duration = Period.between(startDate, endDate);

		countOfDays = duration.getDays();
		countOfMonths = duration.getMonths();
		countOfYears = duration.getYears();
		numberOfDays = ChronoUnit.DAYS.between(startDate, endDate);
	}

	// another constructor who will take start and end date, and calculates duration
	// result
	// Constructor to initialize current date
	public SampleJavaTime() {
		LocalDate today = LocalDate.now();
		currentDate = today.format(DateTimeFormatter.ofPattern("dd/MM/yyyy"));
	}

	// Getters so that we can access these values,
	// hence gather result, use it to print result on pop-up menu
	public int getCountOfDays() {
		return countOfDays;
	}

	public int getCountOfMonths() {
		return countOfMonths;
	}

	public int getCountOfYears() {
		return countOfYears;
	}

	public long getNumberOfDays() {
		return numberOfDays;
	}

	public String getCurrentDate() {
        return currentDate;
    }
}