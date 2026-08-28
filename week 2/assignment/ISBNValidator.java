import java.util.Scanner;

public class ISBNValidator {

    // Normalize the code
    public static String normalizeCode(String raw) {

        // Remove leading and trailing spaces
        raw = raw.trim();

        // Convert only first 3 characters to uppercase
        if (raw.length() >= 3) {
            String publisherCode =
                raw.substring(0, 3).toUpperCase();

            String remaining =
                raw.substring(3);

            return publisherCode + remaining;
        }

        return raw;
    }


    // Validate and format the code
    public static String validateAndFormat(String code) {

        // Check length
        if (code.length() != 13) {
            return "Invalid: wrong length";
        }


        // Check first 3 characters
        for (int i = 0; i < 3; i++) {

            if (!Character.isLetter(code.charAt(i))) {
                return
                    "Invalid: publisher code must be 3 letters";
            }
        }


        // Check remaining 10 characters
        for (int i = 3; i < 13; i++) {

            if (!Character.isDigit(code.charAt(i))) {
                return "Invalid: body must contain digits only";
            }
        }


        // Extract parts
        String publisherCode = code.substring(0, 3);

        String year = code.substring(3, 7);

        String catalog = code.substring(7, 13);


        // Build formatted output
        StringBuilder result = new StringBuilder();

        result.append("[");
        result.append(publisherCode);
        result.append("] YEAR: ");
        result.append(year);
        result.append(" | CATALOG: ");
        result.append(catalog);

        return result.toString();
    }


    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.print("Enter ISBN-style code: ");
        String raw = sc.nextLine();

        String normalizedCode = normalizeCode(raw);

        String result =
            validateAndFormat(normalizedCode);

        System.out.println(result);

        sc.close();
    }
}