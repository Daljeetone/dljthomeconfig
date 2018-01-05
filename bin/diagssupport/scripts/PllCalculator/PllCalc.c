#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#define SOURCE_PLL		24000000
// 8:4, 5 bits
#define PREDIV_BITS		5
// 20:12, 9 bits
#define FEEDBACK_BITS	9
// 3:0, 4 bits
#define POSTDIV_BITS	4
// 8:0, 9 bits
#define FCW_BITS		9

void PrintClockParams(double frequency,
					  int pre,
					  int mult,
					  int post,
					  int frac,
					  double error)
{
	printf("Viable result: %f\n", frequency);
	printf("\tMath: (%d / %d) * (%d.%3d) / %d\n", SOURCE_PLL, pre, mult, frac * 1000 / 512, post);
	printf("\tError: %f\n", error);
	printf("\tP = %3d, M = %3d, S = %3d, FRAC = %3d\n", pre, mult, post, frac); 
}

int main (int argc, char** argv)
{
	double error = 0.0;
	double mult = 0.0;
	double result = 0.0;
	int p, m, s, frac;
	int target = 0;
	int threshold = 0;
	
	double error_best = 1000000000.0;		// Arbitrarily big
	double result_best = 0.0;
	int p_best, m_best, s_best, frac_best;
	
	printf("\n");
	if (argc < 2) { 
		printf("Must specify a target frequency.\n");
		return -1;
	}
	
	if (argc >= 3) {
		threshold = atoi(argv[2]);
	} else {
		printf("Searching for exact frequency.\n");
		threshold = 0;
	}

	target = atoi(argv[1]);
	printf("Calculating target of %d.\n", target);
	
	for (p = 1; p < (1 << PREDIV_BITS); p++) {
		for (s = 0; s < (1 << POSTDIV_BITS); s++) {
			for (m = 0; m < (1 << FEEDBACK_BITS); m++) {
				for (frac = 0; frac < (1 << FCW_BITS); frac++) {
					mult = (double)m + ((double)(frac) / (double)(1 << FCW_BITS));
					result = (((SOURCE_PLL / p) * mult) / (s + 1));
					error = result - target;
					if (error < 0) { error *= -1; }
					if (error < error_best) {
						p_best = p;
						m_best = m;
						s_best = s;
						frac_best = frac;
						error_best = error;
						result_best = result;
					}
					if (error == 0) {
						goto PrintAndExit;
					} else if (((error > 0) && (error < threshold)) ||
								((error < 0) && (error > (threshold * -1)))) {
						PrintClockParams(result, p, m, s, frac, error);
					} 
				}
			}
		}
	}
	
PrintAndExit:
	printf("\n*** *** ***\nBest result:\n");
	PrintClockParams(result_best, p_best, m_best, s_best, frac_best, error_best);
}