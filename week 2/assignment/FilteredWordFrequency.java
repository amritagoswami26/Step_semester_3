import java.util.*;

public class FilteredWordFrequency {

    public static void printFilteredWordFrequency(
        String feedback
    ) {

        // Stop words
        String[] stopWords = {
            "the", "was", "and", "a", "is", "of", "in"
        };

        // Normalize to lowercase
        feedback = feedback.toLowerCase();

        // Remove punctuation
        feedback = feedback.replace(".", "");
        feedback = feedback.replace(",", "");

        // Split into words
        String[] words = feedback.split("\\s+");

        // Store word frequencies
        HashMap<String, Integer> frequency =
            new HashMap<>();


        for (String word : words) {

            boolean isStopWord = false;

            // Check stop-word list
            for (String stopWord : stopWords) {

                if (word.equals(stopWord)) {
                    isStopWord = true;
                    break;
                }
            }

            // Count non-stop words
            if (!isStopWord && !word.isEmpty()) {

                frequency.put(
                    word,
                    frequency.getOrDefault(word, 0) + 1
                );
            }
        }


        // Convert HashMap entries to a list
        List<Map.Entry<String, Integer>> list =
            new ArrayList<>(frequency.entrySet());


        // Sort in descending order of frequency
        Collections.sort(
            list,
            (a, b) -> b.getValue().compareTo(a.getValue())
        );


        // Print result
        for (Map.Entry<String, Integer> entry : list) {

            System.out.println(
                entry.getKey() + ": " +
                entry.getValue()
            );
        }
    }


    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.println(
            "Enter feedback paragraph:"
        );

        String feedback = sc.nextLine();

        printFilteredWordFrequency(feedback);

        sc.close();
    }
}