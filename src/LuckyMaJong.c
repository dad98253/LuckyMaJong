/*
 ============================================================================
 Name        : LuckyMaJong.c
 Author      : dad
 Version     :
 Copyright   : dwtfywwi
 Description : find all the lucky scores in offline Ma Jong
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>


#define _(String) String
#define VERSION "0.1"
const char *gittag = "";

int sumluck2 ( int *score ) {
	int iret;
	if ( *score == 0 ) return ( 0 );
	if ( ( iret = *score / 10 ) == 0 ) return ( *score%10 );
	return ( sumluck2( &iret ) + *score%10 );
}

int sumluck ( int *score ) {
	int iret;
	if ( *score == 0 ) return ( 0 );
	if ( ( iret = sumluck2( score ) ) < 10 ) return (iret );
	return ( sumluck( &iret ) );
}

int findluck( int *score, int *luck ) {
	int i;
	for (i = 0 ; i < 101 ; i++) {
		luck[i] = sumluck( score+i );
	}
	return (0);
}

int main( int argc, char **argv ) {
int score[101];
int luck[101];
int i;
int c;
int number = -1;
int lucknumber;


while (1) {
    int option_index = 0;
    static struct option long_options[] = {
//        {"min-word-size",  required_argument, 0, 'm'},
//        {"max-word-size",  required_argument, 0, 'x'},
		{"help",  no_argument, 0, '?'},
		{"version",  no_argument, 0, 'v'},
        {0,         0,                 0,  0 }
    };

    c = getopt_long(argc, argv, "?v",
                    long_options, &option_index);
    if (c == -1)
        break;

    switch (c) {
    case 0:
        fprintf(stderr,_(" option %s"), long_options[option_index].name);
        if (optarg)
            fprintf(stderr," with arg %s", optarg);
        fprintf(stderr,"\n");
        break;

    case '?':
//        fprintf(stderr, "Usage: %s [OPTION]... [NUMBER]\n", argv[0]);
        fprintf(stderr, "Usage: %s [NUMBER]\n", argv[0]);
        fprintf(stderr, _("Find the luck of a number.\n"));
//		 fprintf(stderr, _("  -m, --min-word-size=N    the minimum size of a derived word\n"));
//		 fprintf(stderr, _("  -x, --max-word-size=X    the maximum size of a derived word\n"));
//		 fprintf(stderr, _("  -?, --help               display this help and exit\n"));
//		 fprintf(stderr, _("  -v, --version            output version information and exit\n"));
		fprintf(stderr, _("  NUMBER                   the number to be checked\n"));
		fprintf(stderr, _("                           if NUMBER is missing, assume that we\n"));
		fprintf(stderr, _("                           are to generate a lucky score table\n"));
		fprintf(stderr, _("                           for the Ma Jung game that we play\n"));
		fprintf(stderr, _("                           online\n"));
//        fprintf(stderr, _("       default for N = 3\n"));
//        fprintf(stderr, _("       default for X = length of STRING\n"));
//        fprintf(stderr, _("       to find the permutations of STRING taken M at a time (i.e., P(STRING,M))\n"));
//        fprintf(stderr, _("       enter: %s -m M -x M STRING\n"), argv[0]);
        exit(EXIT_SUCCESS);
        break;

    case 'v':
        fprintf(stderr, _("%s version %s, gittag %s\n\n"), argv[0],VERSION,gittag);
        exit(EXIT_SUCCESS);
        break;

    default:
        fprintf(stderr,_(" ?? getopt returned character code 0%o ??\n"), c);
    }
}
if (optind < argc) {
	number = atoi((const char *)argv[optind++]);
}

if ( number > -1 ) {
	if ( findluck( &number, &lucknumber ) ) return EXIT_FAILURE;
	printf ( "%i\n", lucknumber);
	return EXIT_SUCCESS;
}

score[0] = 0;
score[1] = 4;
score[2] = 10;
for (i = 3 ; i < 101 ; i++) {
	score[i] = score[i-1] + 8;
}
if ( findluck( score, luck ) ) return EXIT_FAILURE;
printf ("\n\ngame score luck    game score luck    game score luck    game score luck\n");
for (i = 1 ; i < 26 ; i++) {
	printf ("%3i   %3i  %3i     %3i   %3i  %3i     %3i   %3i  %3i     %3i   %3i  %3i\n", i, score[i], luck[i], i+25, score[i+25], luck[i+25], i+50, score[i+50], luck[i+50], i+75, score[i+75], luck[i+75] );
}



	return EXIT_SUCCESS;
}
