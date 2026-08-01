/*
 ============================================================================
 Name        : LuckyMaJong.c
 Author      : dad
 Version     : 0.2
 Copyright   : dwtfywwi
 Description : find all the lucky scores in offline Ma Jong
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <limits.h>
#include <ctype.h>
#include <stdbool.h>

#define _(String) String
#define MAXSETSIZE	INT_MAX - 2
#define MAXROWS		2000
#define MAXCOLS		20
#define VERSION "0.2"
const char *gittag = "";
int mingame = 1;
int maxgame = 100;

bool has_non_numeric(const char *str) {
	// If the string is empty count as non-numeric
	if (str[0] == '\0') {
		return true;
	}

	for (int i = 0; str[i] != '\0'; i++) {
		// Cast to unsigned char to prevent undefined behavior with non-ASCII
		if (!isdigit((unsigned char )str[i])) {
			return true; // Found a non-numeric character
		}
	}
	return false; // All characters were numbers
}

long long sumluck2(long long *score) {
	long long iret;
	if (*score == 0)
		return (0);
	if ((iret = *score / 10) == 0)
		return (*score % 10);
	return (sumluck2(&iret) + *score % 10);
}

int sumluck(long long *score) {
	int iret;
	long long lliret;
	if (*score == 0)
		return (0);
	if ((iret = (int) sumluck2(score)) < 10)
		return (iret);
	lliret = iret;
	return (sumluck(&lliret));
}

int findluck(long long *score, int *luck) {
	int i;
	for (i = (mingame - 1); i < (maxgame + 1); i++) {
		luck[i] = sumluck(score + i);
	}
	return (0);
}

int main(int argc, char **argv) {
	long long *score;
	int *luck;
	int i;
	int c;
	long long number = -1;
	int lucknumber;
	int numcols = 4;
	int numrows = 25;
	int numgames;
	int temprows;

	while (1) {
		int option_index = 0;
		static struct option long_options[] = { { "min-game", required_argument,
				0, 'm' }, { "max-game", required_argument, 0, 'x' }, {
				"num-cols", required_argument, 0, 'c' }, { "num-rows",
				required_argument, 0, 'r' }, { "help", no_argument, 0, '?' }, {
				"version", no_argument, 0, 'v' }, { 0, 0, 0, 0 } };

		c = getopt_long(argc, argv, "?v", long_options, &option_index);
		if (c == -1)
			break;

		switch (c) {
		case 0:
			fprintf(stderr, _(" option %s"), long_options[option_index].name);
			if (optarg)
				fprintf(stderr, " with arg %s", optarg);
			fprintf(stderr, "\n");
			break;

		case 'm':
			if (has_non_numeric(optarg)) {
				fprintf(stderr,
						"The argument string (\"%s\") for minimum game value contains a non-numeric character.\n",
						optarg);
				return EXIT_FAILURE;
			}
			mingame = atoi((const char *) optarg);
			if (mingame > MAXSETSIZE) {
				fprintf(stderr,
						_(
								"the minimum game value cannot be greater than \"%u\"\n"),
						MAXSETSIZE);
				return EXIT_FAILURE;
			} else if (mingame < 0) {
				fprintf(stderr,
						_("the minimum game value cannot be negative\n"));
				return EXIT_FAILURE;
			}
			break;

		case 'x':
			if (has_non_numeric(optarg)) {
				fprintf(stderr,
						"The argument string (\"%s\") for maximum game value contains a non-numeric character.\n",
						optarg);
				return EXIT_FAILURE;
			}
			maxgame = atoi((const char *) optarg);
			if (maxgame > MAXSETSIZE) {
				fprintf(stderr,
						_(
								"the maximum game value cannot be greater than \"%u\"\n"),
						MAXSETSIZE);
				return EXIT_FAILURE;
			} else if (maxgame < 0) {
				fprintf(stderr,
						_("the maximum game value cannot be negative\n"));
				return EXIT_FAILURE;
			}
			break;

		case 'c':
			if (has_non_numeric(optarg)) {
				fprintf(stderr,
						"The argument string (\"%s\") for number of columns contains a non-numeric character.\n",
						optarg);
				return EXIT_FAILURE;
			}
			numcols = atoi((const char *) optarg);
			if (numcols > MAXCOLS) {
				fprintf(stderr,
						_(
								"the number of columns cannot be greater than \"%u\"\n"),
						MAXCOLS);
				return EXIT_FAILURE;
			} else if (numcols < 0) {
				fprintf(stderr,
						_("the number of columns cannot be negative\n"));
				return EXIT_FAILURE;
			}
			break;

		case 'r':
			if (has_non_numeric(optarg)) {
				fprintf(stderr,
						"The argument string (\"%s\") for number of rows contains a non-numeric character.\n",
						optarg);
				return EXIT_FAILURE;
			}
			numrows = atoi((const char *) optarg);
			if (numrows > MAXROWS) {
				fprintf(stderr,
						_("the number or rows cannot be greater than \"%u\"\n"),
						MAXROWS);
				return EXIT_FAILURE;
			} else if (numrows < 0) {
				fprintf(stderr, _("the number of rows cannot be negative\n"));
				return EXIT_FAILURE;
			}
			break;

		case '?':
			fprintf(stderr, "Usage: %s [OPTIONS]... [NUMBER]\n", argv[0]);
			fprintf(stderr, _("Find the luck of a number.\n"));
			fprintf(stderr, _("  OPTIONS\n"));
			fprintf(stderr,
					_("  -m, --min-game=N        the starting game number\n"));
			fprintf(stderr,
					_("  -x, --max-game=M        the ending game number\n"));
			fprintf(stderr,
					_(
							"  -c, --num-cols=X        the number of columns printed per row\n"));
			fprintf(stderr,
					_(
							"  -r, --num-rows=Y        the number of rows printed per page\n"));
			fprintf(stderr,
					_(
							"  -?, --help              display this help and exit\n"));
			fprintf(stderr,
					_(
							"  -v, --version           output version information and exit\n"));
			fprintf(stderr,
					_("  NUMBER                  the number to be checked\n"));
			fprintf(stderr,
					_(
							"                          if NUMBER is missing, assume that we\n"));
			fprintf(stderr,
					_(
							"                          are to generate a lucky score table\n"));
			fprintf(stderr,
					_(
							"                          for the Mahjung game that we play.\n"));
			fprintf(stderr,
					_(
							"                          If NUMBER is specified, only a single\n"));
			fprintf(stderr,
					_(
							"                          value is output and OPTIONS are ignored\n"));
			fprintf(stderr,
					_(
							"                          Note that NUMBER **must** be positive\n"));
			fprintf(stderr, _("       default for N = 1\n"));
			fprintf(stderr, _("       default for M = 100\n"));
			fprintf(stderr, _("       default for X = 4\n"));
			fprintf(stderr, _("       default for Y = 25\n"));
			exit(EXIT_SUCCESS);
			break;

		case 'v':
			fprintf(stderr, _("%s version %s, gittag %s\n\n"), argv[0], VERSION,
					gittag);
			exit(EXIT_SUCCESS);
			break;

		default:
			fprintf(stderr, _(" ?? getopt returned character code 0%o ??\n"),
					c);
		}
	}
	if (optind < argc) {
		if (!(number = atoll((const char *) argv[optind++]))) {
			fprintf(stderr, "the argument (\"%s\") is not a valid number\n",
					argv[optind - 1]);
			return EXIT_FAILURE;
		}
		if (number < 0) {
			fprintf(stderr, "number must be positive\n");
			return EXIT_FAILURE;
		}
		if (number == LLONG_MAX) {
			fprintf(stderr, "sorry, that number is too big for me...\n");
			return EXIT_FAILURE;
		}
		if (has_non_numeric(argv[optind - 1])) {
			fprintf(stderr,
					"The argument string (\"%s\") contains a non-numeric character.\n",
					argv[optind - 1]);
			return EXIT_FAILURE;
		}
		if (optind < argc) {
			fprintf(stderr,
					"too many arguments... I don\'t know what to do. Try again specifying --help.\n");
			return EXIT_FAILURE;
		}
		mingame = 1;
		maxgame = 0;
		if (findluck(&number, &lucknumber))
			return EXIT_FAILURE;
		printf("%i\n", lucknumber);
		return EXIT_SUCCESS;
	}

	if (mingame > maxgame) {
		fprintf(stderr, "min-game cannot be greater than max-game\n");
		return EXIT_FAILURE;
	}
	score = (long long *) malloc((maxgame + 2) * sizeof(long long));
	luck = (int *) malloc((maxgame + 2) * sizeof(int));
	score[0] = 0;
	score[1] = 4;
	score[2] = 10;
	for (i = 3; i < maxgame + 1; i++) {
		score[i] = score[i - 1] + 8;
	}
	if (findluck(score, luck))
		return EXIT_FAILURE;
	temprows = numrows;
	numgames = mingame - 1;
	do {
		printf("\n\n");
		for (int j = 0; j < numcols; j++) {
			printf("game score luck    ");
		}
		printf("\n");
		if ((numrows * numcols + numgames) > maxgame) {
			temprows = (maxgame - numgames) / numcols;
			if ((maxgame - numgames) % numcols)
				temprows++;
		}
		for (i = 1 + numgames; i < (temprows + numgames + 1); i++) {
			for (int j = 0; j < numcols; j++) {
				if ((i + j * temprows) > maxgame)
					break;
				printf("%3i %5lli  %3i     ", i + j * temprows,
						score[i + j * temprows], luck[i + j * temprows]);
			}
			printf("\n");
		}
		numgames += (numrows * numcols);
	} while (numgames < maxgame);

	free(score);
	free(luck);

	return EXIT_SUCCESS;
}
