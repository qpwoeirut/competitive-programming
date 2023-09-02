def filter_valid_words(input_filename, output_filename):
    with open(input_filename, 'r') as infile:
        words = infile.readlines()

    valid_words = [word.strip() for word in words if 3 <= len(word.strip()) <= 100]

    with open(output_filename, 'w') as outfile:
        for word in valid_words:
            outfile.write(word + '\n')

    print(f"Filtered words saved to {output_filename}.")


# Use the function to process words from 'word.txt' and save to 'valid_words.txt'
filter_valid_words('word.txt', 'valid_words.txt')
