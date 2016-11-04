/*
    Fibonacci. Displays the the first n numbers of the Fibonacci sequence.
    Copyright (C) 2016 Jordi Trubat.

    Fibonacci is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Fibonacci is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    
    The author can be contacted at <jtrubat@uoc.edu>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include <getopt.h>

#define NAME "fibonacci"
#define VERSION "1.0.0"
#define AUTHOR "Jordi Trubat"
#define MAIL "jtrubat@uoc.edu"
#define TRUE 1
#define FALSE 0

/* headers */
static void version (FILE *, int);
static void usage (FILE *, int);
static void help (FILE *, int);
void print_fibonacci (unsigned long, mpz_t);

/* global options */
int padding = 0;
int columnar = FALSE;
int number = FALSE;

 /* main */
int
main (int argc, char *argv[])
{
  /* three integer variables are needed */
  mpz_t f0, f1, f2;

  /* initialize variables */
  mpz_init (f0);
  mpz_init (f1);
  mpz_init (f2);

  /* set f0 = f1 = 1 by default */
  mpz_set_ui (f0, 1);
  mpz_set_ui (f1, 1);

  /* sequence length */
  unsigned long n;

  /* counter */
  unsigned long i;

  /* options */
  int next_option;
  const char *const short_options = "hv0Cn";
  const struct option long_options[] = {
    {"help", 0, NULL, 'h'},
    {"version", 0, NULL, 'v'},
    {NULL, 0, NULL, '0'},
    {NULL, 0, NULL, 'C'},
    {"number", 0, NULL, 'n'},
    {NULL, 0, NULL, 0}
  };

  /* process options */
  do
    {
      next_option =
	getopt_long (argc, argv, short_options, long_options, NULL);
      switch (next_option)
	{
	case 'h':		/* print help */
	  help (stdout, 0);
	  break;
	case 'v':		/* print version */
	  version (stdout, 0);
	  break;
	case '0':		/* begin sequence by 0 */
	  mpz_set_ui (f0, 0);
	  break;
	case 'C':		/* print columnar */
	  columnar = TRUE;
	  break;
	case 'n':		/* print columnar and numbering */
	  columnar = TRUE;
	  number = TRUE;
	  break;
	case '?':		/* print usage */
	  usage (stderr, 1);
	case -1:
	  break;
	default:		/* something wrong happened */
	  abort ();
	}
    }
  while (next_option != -1);

  /* if no arguments set n = 2 */
  if (optind == argc)
    {
      n = 2;
    }
  else
    {

      /* sequence length */
      n = atol (argv[optind]);

      /* set n = 2 */
      if (n <= 1)
	n = 2;

      /* if numbering on, set padding */
      padding = strlen (argv[optind]);
    }

  /* print first two fibonacci numbers */
  print_fibonacci ((unsigned long) 1, f0);
  print_fibonacci ((unsigned long) 2, f1);

  /* print the rest of the sequence */
  for (i = 3; i <= n; i++)
    {

      /* f2 = f0 + f1 */
      mpz_add (f2, f0, f1);

      /* print i-th number */
      print_fibonacci (i, f2);

      /* f0 = f1 */
      mpz_set (f0, f1);

      /* f1 = f2 */
      mpz_set (f1, f2);
    }
  if(!columnar) printf ("\n");

  /* clear */
  mpz_clear (f0);
  mpz_clear (f1);
  mpz_clear (f2);

  /* quit */
  return EXIT_SUCCESS;
}

/* version */
static void
version (FILE * stream, int exit_code)
{
  fprintf (stream, "%s %s\n", NAME, VERSION);
  fprintf (stream,
	   "Copyright (C) 2016 Free Software Foundation, Inc. <http://fsf.org/>\n"
	   "This is free software with ABSOLUTELY NO WARRANTY.\n");
  fprintf (stream, "Written by %s.\n", AUTHOR);
  exit (exit_code);
}

/* usage */
static void
usage (FILE * stream, int exit_code)
{
  fprintf (stream,
	   "Usage: finobacci [general options] [-0Cnvh] [ n ]\n"
	   "General options: \n");
  exit (exit_code);
}

/* help */
static void
help (FILE * stream, int exit_code)
{
  fprintf (stream, "Usage: %s options\n", NAME);
  fprintf (stream,
	   "  -0                 Extend the sequence by the initial term 0.\n\n"
	   "  -C                 Display sequence in columnar form.\n\n"
	   "  -n  --number       Display and number the sequence in columnar form.\n\n"
	   "  -h  --help         Print this usage and exit.\n\n"
	   "  -v  --version      Print version information and exit.\n\n"
	   "Report bugs to: <%s>\n", MAIL);

  exit (exit_code);
}

/* print fibonacci number */
void
print_fibonacci (unsigned long i, mpz_t a)
{
  /* numbering on ? */
  if (number)
    printf ("%*lu ", padding, i);

  /* print number */
  gmp_printf ("%Zd", a);

  /* columnar output ? */
  columnar ? printf ("\n") : printf (" ");
}
