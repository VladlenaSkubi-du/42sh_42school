#include "shell42.h"
#include "readline.h"

int		delete_last_history_element(void)
{
	free(g_hist.hist[g_hist.last]);
	g_hist.hist[g_hist.last] = NULL;
	g_hist.counter--;
	g_hist.last--;
	if (g_hist.last_fc < 1)
	   g_hist.last_fc =  g_hist.len - 1;
	return (0);
}