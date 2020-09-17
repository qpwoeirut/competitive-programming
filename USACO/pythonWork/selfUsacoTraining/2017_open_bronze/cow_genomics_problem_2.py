# Start 1:15pm
# End 2:04 pm
# 3/18/18
# http://www.usaco.org/index.php?page=viewproblem2&cpid=736


def calculate_answer(spotty_genome_count, genome_variable_count, genomes: list):
    answer = 0
    spotty_genomes = [spotted_g for spotted_g in genomes if genomes.index(spotted_g) < spotty_genome_count]
    plain_genomes = [plain_g for plain_g in genomes if plain_g not in spotty_genomes]
    # print(spotty_genomes)
    # print(plain_genomes)
    spotty_index_and_char = {}
    plain_index_and_char = {}

    for spotty_char_idx in range(genome_variable_count): # genome variable count starts from 1. Range starts from 0
        spotty_index_and_char[spotty_char_idx] = set(spotty_genome[spotty_char_idx] for spotty_genome in spotty_genomes)
    # print(spotty_index_and_char)

    for plain_char_idx in range(genome_variable_count):
        plain_index_and_char[plain_char_idx] = set(plain_genome[plain_char_idx] for plain_genome in plain_genomes)
    # print(plain_index_and_char)

    for index, chars in spotty_index_and_char.items():
        potential_answer = 0
        for char in chars:
            if char in plain_index_and_char[index]:
                potential_answer = 0
                break
            potential_answer = 1

        # print(index)
        # print(chars)
        # print()
        answer += potential_answer  # The chars are not in the other dict, so the spotty genome is different from the plain one

    return answer


print(calculate_answer(3, 8, ['AATCCCAT', 'GATTGCAA', 'GGTCGCAA', 'ACTCCCAG', 'ACTCGCAT', 'ACTTCCAT']))
