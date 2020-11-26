#include <stdio.h>
#include <stdlib.h>

#define PRIMES_PER_FILE 1000000
#define NUMBER_OF_FILES 412

int main() {
    FILE* prime_file;
    // The sum of all the squares of so far
    unsigned long long running_sum = 0;

    printf("Searching for solutions...\n");
    for (unsigned long long n = 1; n <= PRIMES_PER_FILE * NUMBER_OF_FILES;
         n++) {
        int idx = n - 1;
        if (idx % PRIMES_PER_FILE == 0) {
            // we must load a new file
            if (prime_file != NULL) fclose(prime_file);

            char filename[64];
            sprintf(filename, "primes/Ate_100G_part%u.txt",
                    idx / PRIMES_PER_FILE + 1);
            fprintf(stderr, "Opening new file %s\n", filename);

            prime_file = fopen(filename, "r");
            if (prime_file == NULL) {
                fprintf(stderr, "Could not open file\n");
                exit(1);
            }
        }

        // Load the nth prime
        int prime;
        fscanf(prime_file, "%d", &prime);
        // Add its square to the running total
        running_sum += prime * prime;

        // Is this a multiple of N?
        if (running_sum % n == 0) {
            // eyy
            printf("%u\n", n);
        }
    }

    fclose(prime_file);

    printf("Finished!\n");
    return 0;
}