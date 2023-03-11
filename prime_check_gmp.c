/*
 prime_check_gmp - Check if given integer is a prime using the GNU MP library.
 Copyright (C) 2023 Robert <modrobert@gmail.com>

 Permission to use, copy, modify, and/or distribute this software for any
 purpose with or without fee is hereby granted.

 THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 PERFORMANCE OF THIS SOFTWARE.

 Compile with: gcc -O3 -Wpedantic prime_check_gmp.c -o prime_check_gmp -lgmp
*/

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REPS 50

const char *PROGTITLE = "prime_check_gmp v0.12 by modrobert in 2023\n";

int ptest(char *str, int base)
{
 mpz_t n;
 int conv, result;
 
 mpz_init(n);
 conv = mpz_set_str(n, str, base);
 if (conv != 0)
 {
  fprintf(stderr, "Error: string conversion to big integer failed\n");
  exit(3);
 }

 /* Determine whether n is prime. Return 2 if n is definitely prime, return 1
    if p is probably prime (without being certain), or return 0 if n is 
    definitely non-prime.

    This function performs some trial divisions, a Baillie-PSW probable prime
    test, then reps-24 Miller-Rabin probabilistic primality tests. A higher
    reps value will reduce the chances of a non-prime being identified as
    "probably prime". A composite number will be identified as a prime with an
    asymptotic probability of less than 4−reps . Reasonable values of reps are
    between 15 and 50. */
 result = mpz_probab_prime_p(n, REPS);

 mpz_clear(n);

 return result;
}

int main(int argc, char * argv[])
{
 char *hex = "0x";
 int base, result;

 if (argc < 2)
 {
  fprintf(stderr, "%s", PROGTITLE);
  fprintf(stderr, "Syntax: %s <integer or '0x' prefixed hex string>\n", argv[0]);
  exit(3);
 }

 /* check for hex prefix. */
 if (strstr(argv[1], hex) != NULL)
 {
  /* remove hex prefix */
  memmove(argv[1], argv[1] + strlen(hex), strlen(argv[1]));
  base = 16;
 }
 else
  base = 10;

 /* check if prime */
 result = ptest(argv[1], base);

 switch (result)
 {
  case 0:
   printf("not a prime\n");
   break;
  case 1:
   printf("probably a prime\n");
   break;
  case 2:
   printf("definitely a prime\n");
   break;
 }

 return result;
}

/* vim:ts=1:sw=1:ft=c:et:ai:
*/
