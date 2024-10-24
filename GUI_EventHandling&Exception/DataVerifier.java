/**
 * DataVerifier is a utility class that checks the format of input dates for
 * validation & throws exceptions if the date does not have required format.
 *
 **/
public class DataVerifier {

    public static void verifyDate(String date, String type) throws BadDateException {

        int l = date.length(); // store length
        if (!(l == 8 || l == 9 || l == 10)) { // Check for correct number of symbols
            throw new BadDateException(type + "not the right number of symbols. Use the following format DD/MM/YYYY");
        }

        // split into parts, to verify individual components
        String[] parts = date.split("/");
        if (parts.length != 3)
            throw new BadDateException(type + ": missing or too many fields. The correct format is DD/MM/YYYY");

        String day = parts[0];
        String month = parts[1];
        String year = parts[2];

        // Check if only digits
        if (!day.matches("\\d+") || !month.matches("\\d+") || !year.matches("\\d+"))
            throw new BadDateException(type + ": only digits are allowed. D, M, and Y are digits in DD/MM/YYYY");

        // Further checking for correct number of digits in each part,and in correct
        // range
        // For that, conversion to int needed
        int dayInt = Integer.parseInt(day);
        int monthInt = Integer.parseInt(month);
        int yearInt = Integer.parseInt(year);

        // Verify month
        if (monthInt < 1 || monthInt > 12) {
            throw new BadDateException(type + ": incorrect \"month digits\" - " + month);
        }

        // Verify day
        if (dayInt < 1 || dayInt > 31) {
            throw new BadDateException(type + ": incorrect \"day digits\" - " + day);
        }

        // Verify year
        if (yearInt < 1000 || yearInt > 3000) {
            throw new BadDateException(type + ": maximum year is 3000");
        }

        // Check for short year format
        if (year.length() != 4) {
            throw new BadDateException(type + ": incorrect \"year digits\" of " + year);
        }

    }

}
